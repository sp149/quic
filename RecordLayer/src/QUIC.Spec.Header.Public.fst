module QUIC.Spec.Header.Public

module LP = LowParse.Spec
module LPB = LowParse.Spec.BitSum

inline_for_extraction
type header_form_t =
  | Long
  | Short

[@LPB.filter_bitsum'_t_attr]
inline_for_extraction
noextract
let header_form : LP.enum header_form_t (LPB.bitfield LPB.uint8 1) = [
  Long, 1uy;
  Short, 0uy;
]

[@LPB.filter_bitsum'_t_attr]
inline_for_extraction
noextract
let fixed_bit : LP.enum unit (LPB.bitfield LPB.uint8 1) = [
  (), 1uy;
]

inline_for_extraction
type long_packet_type_t =
  | Initial
  | ZeroRTT
  | Handshake
  | Retry

[@LPB.filter_bitsum'_t_attr]
inline_for_extraction
noextract
let long_packet_type : LP.enum long_packet_type_t (LPB.bitfield LPB.uint8 2) = [
  Initial, 0uy;
  ZeroRTT, 1uy;
  Handshake, 2uy;
  Retry, 3uy;
]

[@LPB.filter_bitsum'_t_attr]
inline_for_extraction
noextract
let first_byte : LPB.bitsum' LPB.uint8 8 =
  LPB.BitSum' _ _ header_form (function
    | Short ->
      LPB.BitSum' _ _ fixed_bit (fun _ ->
        LPB.BitField (* spin bit *) 1 (
          LPB.BitField (* protected bits *) 5 (
            LPB.BitStop ()
          )
        )
      )
    | Long ->
      LPB.BitSum' _ _ fixed_bit (fun _ ->
        LPB.BitSum' _ _ long_packet_type (function
          | _ -> LPB.BitField (* protected bits *) 4 (LPB.BitStop ())
        )
      )
  )

#push-options "--z3rlimit 16"

inline_for_extraction
noextract
let first_byte_of_header'
  (short_dcid_len: short_dcid_len_t)
  (t: Type0)
  (f: (LPB.bitsum'_type first_byte -> Tot t))
  (m: header' short_dcid_len)
: Tot t
= match m with
  | PShort protected_bits spin dcid ->
    let spin : LPB.bitfield LPB.uint8 1 = if spin then 1uy else 0uy in
    f (| Short, (| (), (spin, (protected_bits, () ) ) |) |)
  | PLong protected_bits version dcid scid spec ->
    begin match spec with
    | PInitial _ payload_and_pn_length ->
      f (| Long, (| (), (| Initial, (protected_bits, () ) |) |) |)
    | PZeroRTT payload_and_pn_length ->
      f (| Long, (| (), (| ZeroRTT, (protected_bits, () ) |) |) |)
    | PHandshake payload_and_pn_length ->
      f (| Long, (| (), (| Handshake, (protected_bits, () ) |) |) |)
    | PRetry _ ->
      f (| Long, (| (), (| Retry, (protected_bits, () ) |) |) |)
    end

#pop-options

let first_byte_of_header
  (short_dcid_len: short_dcid_len_t)
  (m: header' short_dcid_len)
: Tot (LPB.bitsum'_type first_byte)
= first_byte_of_header' short_dcid_len (LPB.bitsum'_type first_byte) id m

[@LPB.filter_bitsum'_t_attr]
inline_for_extraction
noextract
let common_long_t
: Type0
= (U32.t & (LP.parse_bounded_vlbytes_t 0 20 & LP.parse_bounded_vlbytes_t 0 20))

inline_for_extraction
let payload_and_pn_length_prop
  (x: U62.t)
: Tot bool
= x `U64.gte` 20uL

let payload_and_pn_length_t' = LP.parse_filter_refine payload_and_pn_length_prop

#push-options "--z3rlimit 32 --max_fuel 8 --max_ifuel 8 --initial_fuel 8 --initial_ifuel 8"

let long_zero_rtt_body_t = (common_long_t & payload_and_pn_length_t')
let long_handshake_body_t = (common_long_t & payload_and_pn_length_t')
let long_retry_body_t = (common_long_t & LP.parse_bounded_vlbytes_t 0 20)
let long_initial_body_t = (common_long_t & (LP.parse_bounded_vlbytes_t 0 token_max_len & payload_and_pn_length_t'))

[@LPB.filter_bitsum'_t_attr]
inline_for_extraction
noextract
let header_body_type
  (short_dcid_len: short_dcid_len_t)
  (k' : LPB.bitsum'_key_type first_byte)
: Tot Type0
= match k' with
  | (| Long, (| (), (| Initial, () |) |) |) ->
    long_initial_body_t
  | (| Long, (| (), (| ZeroRTT, () |) |) |) ->
    long_zero_rtt_body_t
  | (| Long, (| (), (| Handshake, () |) |) |) ->
    long_handshake_body_t
  | (| Long, (| (), (| Retry, () |) |) |) ->
    long_retry_body_t
  | (| Short, (| (), () |) |) ->
    FB.lbytes (U32.v short_dcid_len)

[@LPB.filter_bitsum'_t_attr]
inline_for_extraction
noextract
let mk_header
  (short_dcid_len: short_dcid_len_t)
  (k' : LPB.bitsum'_type first_byte)
  (pl: header_body_type short_dcid_len (LPB.bitsum'_key_of_t first_byte k'))
: Tot (LP.refine_with_tag (first_byte_of_header short_dcid_len) k')
= match k' with
  | (| Short, (| (), (spin, (protected_bits, ()) ) |) |) ->
    let spin = (spin = 1uy) in
    let dcid = LP.coerce (FB.lbytes (U32.v short_dcid_len)) pl in
    PShort protected_bits spin dcid
  | (| Long, (| (), (| Initial, (protected_bits, ()) |) |) |) ->
    begin match LP.coerce (common_long_t & (LP.parse_bounded_vlbytes_t 0 token_max_len & payload_and_pn_length_t')) pl with
    | ((version, (dcid, scid)), (token, (payload_and_pn_length))) ->
      PLong protected_bits version dcid scid (PInitial token payload_and_pn_length)
    end
  | (| Long, (| (), (| ZeroRTT, (protected_bits, ()) |) |) |) ->
    begin match LP.coerce (common_long_t & payload_and_pn_length_t') pl with
    | ((version, (dcid, scid)), payload_and_pn_length) ->
      PLong protected_bits version dcid scid (PZeroRTT payload_and_pn_length)
    end
  | (| Long, (| (), (| Handshake, (protected_bits, ()) |) |) |) ->
    begin match LP.coerce (common_long_t & payload_and_pn_length_t') pl with
    | ((version, (dcid, scid)), (payload_and_pn_length)) ->
      PLong protected_bits version dcid scid (PHandshake (payload_and_pn_length))
    end
  | (| Long, (| (), (| Retry, (protected_bits, ()) |) |) |) ->
    begin match LP.coerce (common_long_t & LP.parse_bounded_vlbytes_t 0 20) pl with
    | ((version, (dcid, scid)), odcid) ->
      PLong protected_bits version dcid scid (PRetry odcid)
    end

[@LPB.filter_bitsum'_t_attr]
inline_for_extraction
noextract
let mk_header_body
  (short_dcid_len: short_dcid_len_t)
  (k' : LPB.bitsum'_type first_byte)
  (pl: LP.refine_with_tag (first_byte_of_header short_dcid_len) k')
: Tot (header_body_type short_dcid_len (LPB.bitsum'_key_of_t first_byte k'))
= match k' with
  | (| Short, (| (), (spin, (protected_bits, ())) |) |) ->
    begin match pl with
    | PShort _ _ dcid -> LP.coerce (header_body_type short_dcid_len (LPB.bitsum'_key_of_t first_byte k')) ((dcid) <: (FB.lbytes (U32.v short_dcid_len)))
    end
  | (| Long, (| (), (| Initial, (protected_bits, ()) |) |) |) ->
    begin match pl with
    | PLong _ version dcid scid (PInitial token payload_and_pn_length) ->
      LP.coerce (header_body_type short_dcid_len (LPB.bitsum'_key_of_t first_byte k')) (((version, (dcid, scid)), (token, (payload_and_pn_length))) <: (common_long_t & (LP.parse_bounded_vlbytes_t 0 token_max_len & payload_and_pn_length_t')))
    end
  | (| Long, (| (), (| ZeroRTT, (protected_bits, ()) |) |) |) ->
    begin match pl with
    | PLong _ version dcid scid (PZeroRTT payload_and_pn_length) ->
      LP.coerce (header_body_type short_dcid_len (LPB.bitsum'_key_of_t first_byte k')) (((version, (dcid, scid)), (payload_and_pn_length)) <: (common_long_t & payload_and_pn_length_t'))
    end
  | (| Long, (| (), (| Handshake, (protected_bits, ()) |) |) |) ->
    begin match pl with
    | PLong _ version dcid scid (PHandshake payload_and_pn_length) ->
      LP.coerce (header_body_type short_dcid_len (LPB.bitsum'_key_of_t first_byte k')) (((version, (dcid, scid)), (payload_and_pn_length)) <: (common_long_t & payload_and_pn_length_t'))
    end
  | (| Long, (| (), (| Retry, (protected_bits, ()) |) |) |) ->
    begin match pl with
    | PLong _ version dcid scid (PRetry odcid) ->
      LP.coerce (header_body_type short_dcid_len (LPB.bitsum'_key_of_t first_byte k')) (((version, (dcid, scid)), odcid) <: (common_long_t & LP.parse_bounded_vlbytes_t 0 20))
    end

[@LPB.filter_bitsum'_t_attr]
inline_for_extraction
noextract
let header_synth
  (short_dcid_len: short_dcid_len_t)
: Tot (LPB.synth_case_t first_byte (header' short_dcid_len) (first_byte_of_header short_dcid_len) (header_body_type short_dcid_len))
= 
  (LPB.SynthCase
    #_ #_ #_ #first_byte #_ #(first_byte_of_header short_dcid_len) #(header_body_type short_dcid_len)
    (mk_header short_dcid_len)
    (fun k x y -> ())
    (mk_header_body short_dcid_len)
    (fun k x -> ())
  )

let parse_common_long : LP.parser _ common_long_t =
  LP.parse_u32 `LP.nondep_then` (LP.parse_bounded_vlbytes 0 20 `LP.nondep_then` LP.parse_bounded_vlbytes 0 20)

module VI = QUIC.Spec.VarInt

let parse_payload_and_pn_length : LP.parser _ payload_and_pn_length_t' =
  LP.parse_filter VI.parse_varint payload_and_pn_length_prop

let parse_long_zero_rtt_body : LP.parser _ long_zero_rtt_body_t = parse_common_long `LP.nondep_then` parse_payload_and_pn_length
let parse_long_handshake_body : LP.parser _ long_handshake_body_t = parse_common_long `LP.nondep_then` parse_payload_and_pn_length
let parse_long_retry_body : LP.parser _ long_retry_body_t = parse_common_long `LP.nondep_then` LP.parse_bounded_vlbytes 0 20
let parse_long_initial_body : LP.parser _ long_initial_body_t = parse_common_long `LP.nondep_then` (
      LP.parse_bounded_vlgenbytes 0 token_max_len (VI.parse_bounded_varint 0 token_max_len) `LP.nondep_then` parse_payload_and_pn_length)

[@LPB.filter_bitsum'_t_attr]
inline_for_extraction
noextract
let parse_header_body
  (short_dcid_len: short_dcid_len_t)
  (k' : LPB.bitsum'_key_type first_byte)
: Tot (k: LP.parser_kind & LP.parser k (header_body_type short_dcid_len k'))
= match k' with
  | (| Short, (| (), () |) |) ->
    (| _ , LP.weaken (LP.strong_parser_kind 0 20 None) (LP.parse_flbytes (U32.v short_dcid_len)) |)
  | (| Long, (| (), (| Initial, () |) |) |) ->
    (| _, parse_long_initial_body  |)
  | (| Long, (| (), (| ZeroRTT, () |) |) |) ->
    (| _, parse_long_zero_rtt_body |)
  | (| Long, (| (), (| Handshake, () |) |) |) ->
    (| _, parse_long_handshake_body |)
  | (| Long, (| (), (| Retry, () |) |) |) ->
    (| _, parse_long_retry_body |)

let weaken_parse_bitsum_cases_kind_parse_header_body
  (short_dcid_len: short_dcid_len_t)
: Lemma
  (let k = LPB.weaken_parse_bitsum_cases_kind first_byte (header_body_type short_dcid_len) (parse_header_body short_dcid_len) in
   k.LP.parser_kind_subkind == Some LP.ParserStrong /\
   begin match k.LP.parser_kind_high with
   | None -> False
   | Some max -> max + 5 < header_len_bound
   end
   )
  [SMTPat (LPB.weaken_parse_bitsum_cases_kind first_byte (header_body_type short_dcid_len) (parse_header_body short_dcid_len))]
= let k = LPB.weaken_parse_bitsum_cases_kind first_byte (header_body_type short_dcid_len) (parse_header_body short_dcid_len) in
  assert_norm (
    k.LP.parser_kind_subkind == Some LP.ParserStrong /\
    begin match k.LP.parser_kind_high with
    | None -> False
    | Some max -> max + 5 < header_len_bound
    end
  )

[@LPB.filter_bitsum'_t_attr]
inline_for_extraction
noextract
let parse_header_kind
  short_dcid_len
= LPB.parse_bitsum_kind LP.parse_u8_kind first_byte (header_body_type short_dcid_len) (parse_header_body short_dcid_len)

let parse_header
  (short_dcid_len: short_dcid_len_t)
: Tot (LP.parser (parse_header_kind short_dcid_len) (header' short_dcid_len))
= LPB.parse_bitsum
    first_byte
    (first_byte_of_header short_dcid_len)
    (header_body_type short_dcid_len)
    (header_synth short_dcid_len)
    LP.parse_u8
    (parse_header_body short_dcid_len)

let serialize_common_long : LP.serializer parse_common_long =
  LP.serialize_u32 `LP.serialize_nondep_then` (LP.serialize_bounded_vlbytes 0 20 `LP.serialize_nondep_then` LP.serialize_bounded_vlbytes 0 20)

let serialize_payload_and_pn_length : LP.serializer parse_payload_and_pn_length =
  LP.serialize_filter VI.serialize_varint payload_and_pn_length_prop

let serialize_long_zero_rtt_body : LP.serializer parse_long_zero_rtt_body = serialize_common_long `LP.serialize_nondep_then` serialize_payload_and_pn_length
let serialize_long_handshake_body : LP.serializer parse_long_handshake_body = serialize_common_long `LP.serialize_nondep_then` serialize_payload_and_pn_length
let serialize_long_retry_body : LP.serializer parse_long_retry_body = serialize_common_long `LP.serialize_nondep_then` LP.serialize_bounded_vlbytes 0 20
let serialize_long_initial_body : LP.serializer parse_long_initial_body = serialize_common_long `LP.serialize_nondep_then` (
      LP.serialize_bounded_vlgenbytes 0 token_max_len (VI.serialize_bounded_varint 0 token_max_len) `LP.serialize_nondep_then` serialize_payload_and_pn_length)

let serialize_header_body
  (short_dcid_len: short_dcid_len_t)
  (k' : LPB.bitsum'_key_type first_byte)
: Tot (LP.serializer (dsnd (parse_header_body short_dcid_len k')))
= match LP.coerce (LPB.bitsum'_key_type first_byte) k' with
  | (| Short, (| (), () |) |) ->
    LP.serialize_weaken (LP.strong_parser_kind 0 20 None) (LP.serialize_flbytes (U32.v short_dcid_len))
  | (| Long, (| (), (| ZeroRTT, () |) |) |) ->
    serialize_long_zero_rtt_body
  | (| Long, (| (), (| Handshake, () |) |) |) ->
    serialize_long_handshake_body
  | (| Long, (| (), (| Initial, () |) |) |) ->
    serialize_long_initial_body
  | (| Long, (| (), (| Retry, () |) |) |) ->
    serialize_long_retry_body

let serialize_header
  (short_dcid_len: short_dcid_len_t)
: Tot (LP.serializer (parse_header short_dcid_len))
= LPB.serialize_bitsum
    #LP.parse_u8_kind
    #8
    #U8.t
    first_byte
    #(header' short_dcid_len)
    (first_byte_of_header short_dcid_len)
    (header_body_type short_dcid_len)
    (header_synth short_dcid_len)
    #LP.parse_u8
    LP.serialize_u8
    #(parse_header_body short_dcid_len)
    (serialize_header_body short_dcid_len)

let serialize_header_eq
  (short_dcid_len: short_dcid_len_t)
  (h: header' short_dcid_len)
: Lemma
  (LP.serialize (serialize_header short_dcid_len) h ==
    LP.serialize LP.serialize_u8 (LPB.synth_bitsum'_recip first_byte (first_byte_of_header short_dcid_len h)) `Seq.append`
    LP.serialize (serialize_header_body short_dcid_len (LPB.bitsum'_key_of_t first_byte (first_byte_of_header short_dcid_len h))) (mk_header_body short_dcid_len (first_byte_of_header short_dcid_len h) h))
= LPB.serialize_bitsum_eq'
    #LP.parse_u8_kind
    #8
    #U8.t
    first_byte
    #(header' short_dcid_len)
    (first_byte_of_header short_dcid_len)
    (header_body_type short_dcid_len)
    (header_synth short_dcid_len)
    #LP.parse_u8
    LP.serialize_u8
    #(parse_header_body short_dcid_len)
    (serialize_header_body short_dcid_len)
    h

let serialize_header_ext
  (short_dcid_len1 short_dcid_len2: short_dcid_len_t)
  (h: header)
: Lemma
  (requires (short_dcid_len_prop short_dcid_len1 h /\ short_dcid_len_prop short_dcid_len2 h))
  (ensures (
    short_dcid_len_prop short_dcid_len1 h /\ short_dcid_len_prop short_dcid_len2 h /\
    LP.serialize (serialize_header short_dcid_len1) h == LP.serialize (serialize_header short_dcid_len2) h
  ))
= serialize_header_eq short_dcid_len1 h;
  serialize_header_eq short_dcid_len2 h;
  ()

let serialize_header_is_short
  dl h
=
  serialize_header_eq dl h;
  let tg = first_byte_of_header dl h in
  let x = LPB.synth_bitsum'_recip first_byte tg in
  LP.serialize_u8_spec x;
  let s = LP.serialize (serialize_header dl) h in
  assert (Seq.index s 0 == x);
  assert (PShort? h <==> LPB.uint8.LPB.get_bitfield (Seq.index s 0) 7 8 == (LowParse.Spec.Enum.enum_repr_of_key header_form Short <: U8.t))

let first_byte_is_retry
  (k: LPB.bitsum'_type first_byte)
: GTot bool
= match k with
  | (| Long, (| (), (| Retry, (unused, ()) |) |) |) -> true
  | _ -> false

let first_byte_is_retry_correct
  (short_dcid_len: short_dcid_len_t)
  (h: header' short_dcid_len)
: Lemma
  (is_retry h <==> first_byte_is_retry (first_byte_of_header short_dcid_len h))
= ()

#push-options "--z3rlimit 256"

let serialize_header_is_retry
  dl h
=
  serialize_header_eq dl h;
  let tg = first_byte_of_header dl h in
  let x = LPB.synth_bitsum'_recip first_byte tg in
  LP.serialize_u8_spec x;
  let s = LP.serialize (serialize_header dl) h in  
  assert (Seq.index s 0 == x);
  assert (is_retry h <==> (
    LPB.uint8.LPB.get_bitfield (Seq.index s 0) 7 8 == (LowParse.Spec.Enum.enum_repr_of_key header_form Long <: U8.t) /\
    LPB.uint8.LPB.get_bitfield (Seq.index s 0) 4 6 == (LowParse.Spec.Enum.enum_repr_of_key long_packet_type Retry <: U8.t)
  ))

#pop-options

#restart-solver


let is_valid_bitfield_intro
  (short_dcid_len: short_dcid_len_t)
  (h: header' short_dcid_len)
: Lemma
  (LPB.is_valid_bitfield first_byte (LPB.bitsum'_key_of_t first_byte (first_byte_of_header short_dcid_len h)) 0 (if PShort? h then 5 else 4))
= ()

let set_valid_bitfield_intro'
  (short_dcid_len: short_dcid_len_t)
  (h: header' short_dcid_len)
  (new_pb: bitfield (if PShort? h then 5 else 4))
: Lemma
  (
    LPB.is_valid_bitfield first_byte (LPB.bitsum'_key_of_t first_byte (first_byte_of_header short_dcid_len h)) 0 (if PShort? h then 5 else 4) /\
    first_byte_of_header short_dcid_len (set_protected_bits h new_pb) == LPB.set_valid_bitfield first_byte (first_byte_of_header short_dcid_len h) 0 (if PShort? h then 5 else 4) new_pb
  )
= is_valid_bitfield_intro short_dcid_len h

let set_valid_bitfield_intro
  (short_dcid_len: short_dcid_len_t)
  (h: header' short_dcid_len)
  (new_pb: bitfield (if PShort? h then 5 else 4))
: Lemma
  (
    LPB.is_valid_bitfield first_byte (LPB.bitsum'_key_of_t first_byte (first_byte_of_header short_dcid_len h)) 0 (if PShort? h then 5 else 4) /\
    first_byte_of_header short_dcid_len (set_protected_bits h new_pb) == LPB.set_valid_bitfield first_byte (first_byte_of_header short_dcid_len h) 0 (if PShort? h then 5 else 4) new_pb /\
    LPB.bitsum'_key_of_t first_byte (first_byte_of_header short_dcid_len (set_protected_bits h new_pb)) == LPB.bitsum'_key_of_t first_byte (first_byte_of_header short_dcid_len h)
  )
= set_valid_bitfield_intro' short_dcid_len h new_pb;
  LPB.bitsum'_key_of_t_set_valid_bitfield first_byte (first_byte_of_header short_dcid_len h) 0 (if PShort? h then 5 else 4) new_pb

let mk_header_body_set_valid_bitfield
  (short_dcid_len: short_dcid_len_t)
  (h: header' short_dcid_len)
  (new_pb: bitfield (if PShort? h then 5 else 4))
: Lemma
  (mk_header_body short_dcid_len (first_byte_of_header short_dcid_len (set_protected_bits h new_pb)) (set_protected_bits h new_pb) ==
    mk_header_body short_dcid_len (first_byte_of_header short_dcid_len h) h)
= ()

#push-options "--z3rlimit 512"

#restart-solver

let serialize_get_protected_bits
  (short_dcid_len: short_dcid_len_t)
  (h: header' short_dcid_len)
: Lemma
  (let sq = LP.serialize (serialize_header short_dcid_len) h in
   Seq.length sq > 0 /\
   get_protected_bits h == LPB.uint8.LPB.get_bitfield (Seq.head sq) 0 (if PShort? h then 5 else 4))
= let sq = LP.serialize (serialize_header short_dcid_len) h in
  serialize_header_eq
    short_dcid_len
    h;
  LP.serialize_u8_spec (LPB.synth_bitsum'_recip first_byte (first_byte_of_header short_dcid_len h))

#restart-solver

let serialize_set_protected_bits
  short_dcid_len h new_pb
= let h' = set_protected_bits h new_pb in
  let sq = LP.serialize (serialize_header short_dcid_len) h in
  let sq' = LP.serialize (serialize_header short_dcid_len) h' in
  set_valid_bitfield_intro short_dcid_len h new_pb;
  serialize_header_eq
    short_dcid_len
    h;
  serialize_header_eq
    short_dcid_len
    h';
  LP.serialize_u8_spec (LPB.synth_bitsum'_recip first_byte (first_byte_of_header short_dcid_len h));
  LP.serialize_u8_spec (LPB.synth_bitsum'_recip first_byte (first_byte_of_header short_dcid_len h'));
  LPB.set_valid_bitfield_correct first_byte (first_byte_of_header short_dcid_len h) 0 (if PShort? h then 5 else 4) new_pb;
  mk_header_body_set_valid_bitfield short_dcid_len h new_pb;
  assert (LP.serialize (serialize_header_body short_dcid_len (LPB.bitsum'_key_of_t first_byte (first_byte_of_header short_dcid_len h'))) (mk_header_body short_dcid_len (first_byte_of_header short_dcid_len h') h') == LP.serialize (serialize_header_body short_dcid_len (LPB.bitsum'_key_of_t first_byte (first_byte_of_header short_dcid_len h))) (mk_header_body short_dcid_len (first_byte_of_header short_dcid_len h) h));
  assert (Seq.tail sq' `Seq.equal` LP.serialize (serialize_header_body short_dcid_len (LPB.bitsum'_key_of_t first_byte (first_byte_of_header short_dcid_len h'))) (mk_header_body short_dcid_len (first_byte_of_header short_dcid_len h') h'));
  assert (Seq.tail sq `Seq.equal` LP.serialize (serialize_header_body short_dcid_len (LPB.bitsum'_key_of_t first_byte (first_byte_of_header short_dcid_len h))) (mk_header_body short_dcid_len (first_byte_of_header short_dcid_len h) h))

#pop-options


let header_len'_correct_short
  (short_dcid_len: short_dcid_len_t)
  (protected_bits: bitfield 5)
  (spin: bool)
  (dcid: vlbytes 0 20)
: Lemma
  (requires (let h = PShort protected_bits spin dcid in
    parse_header_prop short_dcid_len h
  ))
  (ensures (
    let h = PShort protected_bits spin dcid in
    header_len' h == Seq.length (LP.serialize (serialize_header short_dcid_len) h)
  ))
= 
  let h = PShort protected_bits spin dcid in
  serialize_header_eq short_dcid_len h;
  let tg = first_byte_of_header short_dcid_len h in
  let x = LPB.synth_bitsum'_recip first_byte tg in
  LP.serialize_length LP.serialize_u8 x;
  assert_norm (first_byte_of_header short_dcid_len (PShort protected_bits spin dcid) == (| Short, (| (), ((if spin then 1uy else 0uy), (protected_bits, ()) ) |) |) );
  assert_norm (LPB.bitsum'_key_of_t first_byte (first_byte_of_header short_dcid_len (PShort protected_bits spin dcid)) == (| Short, (| (), () |) |) );
  LP.serialize_length (LP.serialize_flbytes (U32.v short_dcid_len)) dcid

let length_serialize_common_long
  (version: U32.t)
  (dcid: vlbytes 0 20)
  (scid: vlbytes 0 20)
: Lemma
  (Seq.length (LP.serialize serialize_common_long (version, (dcid, scid))) == 6 + FB.length dcid + FB.length scid)
= LP.serialize_nondep_then_eq LP.serialize_u32 (LP.serialize_bounded_vlbytes 0 20 `LP.serialize_nondep_then` LP.serialize_bounded_vlbytes 0 20) (version, (dcid, scid));
  LP.serialize_length LP.serialize_u32 version;
  LP.serialize_nondep_then_eq (LP.serialize_bounded_vlbytes 0 20) (LP.serialize_bounded_vlbytes 0 20) (dcid, scid);
  LP.length_serialize_bounded_vlbytes 0 20 dcid;
  LP.length_serialize_bounded_vlbytes 0 20 scid

let length_serialize_payload_and_pn_length
  (payload_and_pn_length: payload_and_pn_length_t)
: Lemma
  (Seq.length (LP.serialize serialize_payload_and_pn_length payload_and_pn_length) == varint_len payload_and_pn_length)
= VI.varint_len_correct payload_and_pn_length

#pop-options

#push-options "--z3rlimit 128 --query_stats"

#restart-solver

let header_len'_correct_long_initial
  (short_dcid_len: short_dcid_len_t)
  (protected_bits: bitfield 4)
  (version: U32.t)
  (dcid: vlbytes 0 20)
  (scid: vlbytes 0 20)
  (token: vlbytes 0 token_max_len)
  (payload_and_pn_length: payload_and_pn_length_t)
: Lemma
  (requires (
    let h = PLong protected_bits version dcid scid (PInitial token payload_and_pn_length) in
    parse_header_prop short_dcid_len h
  ))
  (ensures (
    let h = PLong protected_bits version dcid scid (PInitial token payload_and_pn_length) in
    header_len' h == Seq.length (LP.serialize (serialize_header short_dcid_len) h)
  ))
=
  let h = PLong protected_bits version dcid scid (PInitial token payload_and_pn_length) in
  serialize_header_eq short_dcid_len h;
  let tg : LPB.bitsum'_type first_byte = (| Long, (| (), (| Initial, (protected_bits, ()) |) |) |) in
  assert_norm (first_byte_of_header short_dcid_len h == tg);
  let x = LPB.synth_bitsum'_recip first_byte tg in
  LP.serialize_length LP.serialize_u8 x;
  let kt : LPB.bitsum'_key_type first_byte = (| Long, (| (), (| Initial, () |) |) |) in
  assert_norm (LPB.bitsum'_key_of_t first_byte (first_byte_of_header short_dcid_len h) == kt );
  LP.length_serialize_nondep_then serialize_common_long (LP.serialize_bounded_vlgenbytes 0 token_max_len (VI.serialize_bounded_varint 0 token_max_len) `LP.serialize_nondep_then` serialize_payload_and_pn_length) (version, (dcid, scid)) (token, payload_and_pn_length);
  length_serialize_common_long version dcid scid;
  LP.length_serialize_nondep_then (LP.serialize_bounded_vlgenbytes 0 token_max_len (VI.serialize_bounded_varint 0 token_max_len)) (serialize_payload_and_pn_length) token payload_and_pn_length;
  LP.length_serialize_bounded_vlgenbytes 0 token_max_len (VI.serialize_bounded_varint 0 token_max_len) token;
  VI.bounded_varint_len_correct 0 token_max_len (FB.len token);
  length_serialize_payload_and_pn_length payload_and_pn_length

#pop-options

#push-options "--z3rlimit 128 --query_stats"

#restart-solver

let header_len'_correct_long_handshake
  (short_dcid_len: short_dcid_len_t)
  (protected_bits: bitfield 4)
  (version: U32.t)
  (dcid: vlbytes 0 20)
  (scid: vlbytes 0 20)
  (payload_and_pn_length: payload_and_pn_length_t)
: Lemma
  (requires (
    let h = PLong protected_bits version dcid scid (PHandshake payload_and_pn_length) in
    parse_header_prop short_dcid_len h
  ))
  (ensures (
    let h = PLong protected_bits version dcid scid (PHandshake payload_and_pn_length) in
    header_len' h == Seq.length (LP.serialize (serialize_header short_dcid_len) h)
  ))
=
  let h = PLong protected_bits version dcid scid (PHandshake payload_and_pn_length) in
  serialize_header_eq short_dcid_len h;
  let tg : LPB.bitsum'_type first_byte = (| Long, (| (), (| Handshake, (protected_bits, ()) |) |) |) in
  assert_norm (first_byte_of_header short_dcid_len h == tg);
  let x = LPB.synth_bitsum'_recip first_byte tg in
  LP.serialize_length LP.serialize_u8 x;
  let kt : LPB.bitsum'_key_type first_byte = (| Long, (| (), (| Handshake, () |) |) |) in
  assert_norm (LPB.bitsum'_key_of_t first_byte (first_byte_of_header short_dcid_len h) == kt );
  LP.length_serialize_nondep_then serialize_common_long serialize_payload_and_pn_length (version, (dcid, scid)) payload_and_pn_length;
  length_serialize_common_long version dcid scid;
  length_serialize_payload_and_pn_length payload_and_pn_length

#restart-solver

let header_len'_correct_long_zero_rtt
  (short_dcid_len: short_dcid_len_t)
  (protected_bits: bitfield 4)
  (version: U32.t)
  (dcid: vlbytes 0 20)
  (scid: vlbytes 0 20)
  (payload_and_pn_length: payload_and_pn_length_t)
: Lemma
  (requires (
    let h = PLong protected_bits version dcid scid (PZeroRTT payload_and_pn_length) in
    parse_header_prop short_dcid_len h
  ))
  (ensures (
    let h = PLong protected_bits version dcid scid (PZeroRTT payload_and_pn_length) in
    header_len' h == Seq.length (LP.serialize (serialize_header short_dcid_len) h)
  ))
=
  let h = PLong protected_bits version dcid scid (PZeroRTT payload_and_pn_length) in
  serialize_header_eq short_dcid_len h;
  let tg : LPB.bitsum'_type first_byte = (| Long, (| (), (| ZeroRTT, (protected_bits, ()) |) |) |) in
  assert_norm (first_byte_of_header short_dcid_len h == tg);
  let x = LPB.synth_bitsum'_recip first_byte tg in
  LP.serialize_length LP.serialize_u8 x;
  let kt : LPB.bitsum'_key_type first_byte = (| Long, (| (), (| ZeroRTT, () |) |) |) in
  assert_norm (LPB.bitsum'_key_of_t first_byte (first_byte_of_header short_dcid_len h) == kt );
  LP.length_serialize_nondep_then serialize_common_long serialize_payload_and_pn_length (version, (dcid, scid)) payload_and_pn_length;
  length_serialize_common_long version dcid scid;
  length_serialize_payload_and_pn_length payload_and_pn_length

#restart-solver

let header_len'_correct_long_retry
  (short_dcid_len: short_dcid_len_t)
  (version: U32.t)
  (dcid: vlbytes 0 20)
  (scid: vlbytes 0 20)
  (unused: bitfield 4)
  (odcid: vlbytes 0 20)
: Lemma
  (requires (
    let h = PLong unused version dcid scid (PRetry odcid) in
    parse_header_prop short_dcid_len h
  ))
  (ensures (
    let h = PLong unused version dcid scid (PRetry odcid) in
    header_len' h == Seq.length (LP.serialize (serialize_header short_dcid_len) h)
  ))
=
  let h = PLong unused version dcid scid (PRetry odcid) in
  serialize_header_eq short_dcid_len h;
  let tg = (| Long, (| (), (| Retry, (unused, ()) |) |) |) in
  let x = LPB.synth_bitsum'_recip first_byte tg in
  LP.serialize_length LP.serialize_u8 x;
  let kt : LPB.bitsum'_key_type first_byte = (| Long, (| (), (| Retry, () |) |) |) in
  assert_norm (first_byte_of_header short_dcid_len h == tg );
  assert_norm (LPB.bitsum'_key_of_t first_byte (first_byte_of_header short_dcid_len h) == kt );
  LP.length_serialize_nondep_then serialize_common_long (LP.serialize_bounded_vlbytes 0 20) (version, (dcid, scid)) odcid;
  length_serialize_common_long version dcid scid;
  LP.length_serialize_bounded_vlbytes 0 20 odcid

#restart-solver

let header_len'_correct
  short_dcid_len h
= match h with
  | PShort pb spin dcid ->
    header_len'_correct_short short_dcid_len pb spin dcid
  | PLong pb version dcid scid spec ->
    begin match spec with
    | PInitial token payload_and_pn_length ->
      header_len'_correct_long_initial short_dcid_len pb version dcid scid token payload_and_pn_length
    | PHandshake payload_and_pn_length ->
      header_len'_correct_long_handshake short_dcid_len pb version dcid scid payload_and_pn_length
    | PZeroRTT payload_and_pn_length ->
      header_len'_correct_long_zero_rtt short_dcid_len pb version dcid scid payload_and_pn_length
    | PRetry odcid ->
      header_len'_correct_long_retry short_dcid_len version dcid scid pb odcid
    end

