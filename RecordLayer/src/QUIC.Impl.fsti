/// An implementation of QUIC.Spec.fst that is concerned only with functional
/// correctness and side-channel resistance (no notion of model for now).
module QUIC.Impl
include QUIC.Impl.Crypto
include QUIC.Impl.Header.Base

module Spec = QUIC.Spec
module PN = QUIC.Spec.PacketNumber.Base
module Secret = QUIC.Secret.Int
module Seq = QUIC.Secret.Seq
module Parse = QUIC.Spec.Header.Parse

// This MUST be kept in sync with QUIC.Impl.fst...
module G = FStar.Ghost
module B = LowStar.Buffer
module S = FStar.Seq
module HS = FStar.HyperStack
module HST = FStar.HyperStack.ST


module Cipher = EverCrypt.Cipher
module AEAD = EverCrypt.AEAD
module HKDF = EverCrypt.HKDF
module CTR = EverCrypt.CTR

module SAEAD = Spec.Agile.AEAD
module SCipher = Spec.Agile.Cipher
module SHKDF = Spec.Agile.HKDF

module U64 = FStar.UInt64
module U32 = FStar.UInt32
module U8 = FStar.UInt8

open FStar.HyperStack
open FStar.HyperStack.ST

open EverCrypt.Helpers
open EverCrypt.Error

#set-options "--z3rlimit 16"

/// Low-level types used in this API
/// --------------------------------

type u2 = n:U8.t{U8.v n < 4}
type u4 = n:U8.t{U8.v n < 16}
type u62 = n:UInt64.t{UInt64.v n < pow2 62}

val dummy: unit

unfold
let encrypt_pre
  (a: ea)
  (aead: AEAD.state a)
  (siv: B.buffer Secret.uint8)
  (ctr: CTR.state (SAEAD.cipher_alg_of_supported_alg a))
  (hpk: B.buffer Secret.uint8)
  (dst: B.buffer U8.t)
  (h: header)
  (pn: PN.packet_number_t)
  (plain: B.buffer Secret.uint8)
  (plain_len: Secret.uint32) // should be secret, because otherwise one can compute the packet number length
  (m: HS.mem)
: GTot Type0
=
  let a' = SAEAD.cipher_alg_of_supported_alg a in
  B.all_disjoint [
    AEAD.footprint m aead;
    B.loc_buffer siv;
    CTR.footprint m ctr;
    B.loc_buffer hpk;
    B.loc_buffer dst;
    header_footprint h;
    B.loc_buffer plain;
  ] /\
  AEAD.invariant m aead /\
  B.live m siv /\ B.length siv == 12 /\
  CTR.invariant m ctr /\
  B.live m hpk /\ B.length hpk == SCipher.key_length a' /\
  B.live m dst /\
  header_live h m /\
  B.live m plain /\ B.length plain == Secret.v plain_len /\
  begin
    if is_retry h
    then
      B.length plain == 0 /\
      B.length dst == Secret.v (header_len h)
    else
      B.length dst == Secret.v (header_len h) + Secret.v plain_len + SAEAD.tag_length a /\
      3 <= Secret.v plain_len /\ Secret.v plain_len < max_plain_length
  end

unfold
let encrypt_post
  (a: ea)
  (aead: AEAD.state a)
  (siv: B.buffer Secret.uint8)
  (ctr: CTR.state (SAEAD.cipher_alg_of_supported_alg a))
  (hpk: B.buffer Secret.uint8)
  (dst: B.buffer U8.t)
  (h: header)
  (pn: PN.packet_number_t)
  (plain: B.buffer Secret.uint8)
  (plain_len: Secret.uint32)
  (m: HS.mem)
  (res: error_code)
  (m' : HS.mem)
: GTot Type0
=
  encrypt_pre a aead siv ctr hpk dst h pn plain plain_len m /\
  B.modifies (B.loc_buffer dst `B.loc_union` AEAD.footprint m aead `B.loc_union` CTR.footprint m ctr) m m' /\
  AEAD.invariant m' aead /\ AEAD.footprint m' aead == AEAD.footprint m aead /\
  AEAD.preserves_freeable aead m m' /\
  AEAD.as_kv (B.deref m' aead) == AEAD.as_kv (B.deref m aead) /\
  CTR.invariant m' ctr /\ CTR.footprint m' ctr == CTR.footprint m ctr /\
  B.as_seq m' dst `Seq.equal` Spec.encrypt a (AEAD.as_kv (B.deref m aead)) (B.as_seq m siv) (B.as_seq m hpk) (g_header h m pn) (Seq.seq_reveal (B.as_seq m plain)) /\
  res == Success

val encrypt
  (a: ea)
  (aead: AEAD.state a)
  (siv: B.buffer Secret.uint8)
  (ctr: CTR.state (SAEAD.cipher_alg_of_supported_alg a))
  (hpk: B.buffer Secret.uint8)
  (dst: B.buffer U8.t)
  (h: header)
  (pn: PN.packet_number_t)
  (plain: B.buffer Secret.uint8)
  (plain_len: Secret.uint32)
: HST.Stack error_code
  (requires (fun m ->
    encrypt_pre a aead siv ctr hpk dst h pn plain plain_len m
  ))
  (ensures (fun m res m' ->
    encrypt_post a aead siv ctr hpk dst h pn plain plain_len m res m'
  ))

unfold
let decrypt_pre
  (a: ea)
  (aead: AEAD.state a)
  (siv: B.buffer Secret.uint8)
  (ctr: CTR.state (SAEAD.cipher_alg_of_supported_alg a))
  (hpk: B.buffer Secret.uint8)
  (dst: B.buffer U8.t)
  (dst_len: U32.t)
  (dst_hdr: B.pointer result)
  (last_pn: PN.last_packet_number_t)
  (cid_len: short_dcid_len_t)
  (m: HS.mem)
: GTot Type0
=
  let a' = SAEAD.cipher_alg_of_supported_alg a in
  B.all_disjoint [
    AEAD.footprint m aead;
    B.loc_buffer siv;
    CTR.footprint m ctr;
    B.loc_buffer hpk;
    B.loc_buffer dst;
    B.loc_buffer dst_hdr;
  ] /\
  AEAD.invariant m aead /\
  B.live m siv /\ B.length siv == 12 /\
  CTR.invariant m ctr /\
  B.live m hpk /\ B.length hpk == SCipher.key_length a' /\
  B.live m dst /\ B.length dst == U32.v dst_len /\
  B.live m dst_hdr

unfold
let decrypt_post
  (a: ea)
  (aead: AEAD.state a)
  (siv: B.buffer Secret.uint8)
  (ctr: CTR.state (SAEAD.cipher_alg_of_supported_alg a))
  (hpk: B.buffer Secret.uint8)
  (dst: B.buffer U8.t)
  (dst_len: U32.t)
  (dst_hdr: B.pointer result)
  (last_pn: PN.last_packet_number_t)
  (cid_len: short_dcid_len_t)
  (m: HS.mem)
  (res: error_code)
  (m' : HS.mem)
: GTot Type0
=
  decrypt_pre a aead siv ctr hpk dst dst_len dst_hdr last_pn cid_len m /\
  AEAD.invariant m' aead /\ AEAD.footprint m' aead == AEAD.footprint m aead /\
  AEAD.preserves_freeable aead m m' /\
  AEAD.as_kv (B.deref m' aead) == AEAD.as_kv (B.deref m aead) /\
  CTR.invariant m' ctr /\ CTR.footprint m' ctr == CTR.footprint m ctr /\
  begin match res, Spec.decrypt a (AEAD.as_kv (B.deref m aead)) (B.as_seq m siv) (B.as_seq m hpk) (Secret.v last_pn) (U32.v cid_len) (B.as_seq m dst) with
  | AuthenticationFailure, Spec.Failure ->
    let r = B.deref m' dst_hdr in
    Secret.v r.total_len <= B.length dst /\
    B.modifies (AEAD.footprint m aead `B.loc_union` CTR.footprint m ctr `B.loc_union` B.loc_buffer dst_hdr `B.loc_union` B.loc_buffer (B.gsub dst 0ul (Secret.reveal r.total_len))) m m'
  | DecodeError, Spec.Failure ->
    B.modifies B.loc_none m m'
  | Success, Spec.Success gh plain rem ->
    let r = B.deref m' dst_hdr in
    let h = r.header in
    header_live h m' /\
    gh == g_header h m' r.pn /\
    r.header_len == header_len h /\
    Secret.v r.plain_len == Seq.length plain /\
    Secret.v r.header_len + Secret.v r.plain_len <= Secret.v r.total_len /\
    Secret.v r.total_len <= B.length dst /\
    B.loc_buffer (B.gsub dst 0ul (public_header_len h)) `B.loc_includes` header_footprint h /\
    (
      B.modifies (AEAD.footprint m aead `B.loc_union` CTR.footprint m ctr `B.loc_union` B.loc_buffer dst_hdr `B.loc_union` B.loc_buffer (B.gsub dst 0ul (Secret.reveal r.total_len))) m m' /\
      B.as_seq m' (B.gsub dst 0ul (Secret.reveal r.header_len)) `Seq.equal` Parse.format_header (g_header h m' r.pn) /\
      B.as_seq m' (B.gsub dst (Secret.reveal r.header_len) (Secret.reveal r.plain_len)) `Seq.equal` plain /\
      B.as_seq m' (B.gsub dst (Secret.reveal r.total_len) (B.len dst `U32.sub` Secret.reveal r.total_len)) `Seq.equal` rem
    )
  | _ -> False
  end

val decrypt
  (a: ea)
  (aead: AEAD.state a)
  (siv: B.buffer Secret.uint8)
  (ctr: CTR.state (SAEAD.cipher_alg_of_supported_alg a))
  (hpk: B.buffer Secret.uint8)
  (dst: B.buffer U8.t)
  (dst_len: U32.t)
  (dst_hdr: B.pointer result)
  (last_pn: PN.last_packet_number_t)
  (cid_len: short_dcid_len_t)
: HST.Stack error_code
  (requires (fun m ->
    decrypt_pre a aead siv ctr hpk dst dst_len dst_hdr last_pn cid_len m
  ))
  (ensures (fun m res m' ->
    decrypt_post a aead siv ctr hpk dst dst_len dst_hdr last_pn cid_len m res m'
  ))
