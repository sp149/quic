module Model.Helpers

let lbytes (l:nat) = b:Seq.seq Lib.IntTypes.uint8 { Seq.length b = l }

let hide (b:Seq.seq UInt8.t) : lbytes (Seq.length b) =
  Seq.init (Seq.length b) (fun i -> Lib.RawIntTypes.u8_from_UInt8 (Seq.index b i))

let reveal #l (b:lbytes l) : (QUIC.Spec.lbytes l) =
  Seq.init l (fun i -> Lib.RawIntTypes.u8_to_UInt8 (Seq.index b i)) 

let reveal_eq (b:Seq.seq Lib.IntTypes.uint8): Lemma
  (ensures reveal #(Seq.length b) b == QUIC.Secret.Seq.seq_reveal b)
  [ SMTPat (QUIC.Secret.Seq.seq_reveal b) ]
= 
  assert (reveal #(Seq.length b) b `Seq.equal` QUIC.Secret.Seq.seq_reveal b)


val correct (#l: nat) (b:Seq.seq UInt8.t{Seq.length b = l})
  : Lemma (reveal #l (hide b) == b)
  [SMTPat (reveal #l (hide b))]

val correct2 (#l: nat) (b:lbytes l)
  : Lemma (hide (reveal #l b) == b)
  [SMTPat (hide (reveal #l b))]

let random (l: nat { l < pow2 32 })
  : HyperStack.ST.ST (lbytes l)
  (requires fun h0 -> True)
  (ensures fun h0 _ h1 -> h0 == h1)
  =
  let open Lib.RandomSequence in
  snd (crypto_random entropy0 l)

let rec lbytes_eq (x y: Seq.seq Lib.IntTypes.uint8): Tot (b:bool { b <==> x `Seq.equal` y }) (decreases (Seq.length x)) =
  if Seq.length x = 0 && Seq.length y = 0 then
    true
  else if Seq.length x = 0 && Seq.length y <> 0 then
    false
  else if Seq.length x <> 0 && Seq.length y = 0 then
    false
  else
    let hx = Seq.head x in
    let hy = Seq.head y in
    let tx = Seq.tail x in
    let ty = Seq.tail y in
    if Lib.RawIntTypes.u8_to_UInt8 hx = Lib.RawIntTypes.u8_to_UInt8 hy && lbytes_eq tx ty then begin
      assert (x `Seq.equal` Seq.append (Seq.create 1 hx) tx);
      assert (y `Seq.equal` Seq.append (Seq.create 1 hy) ty);
      assert (Seq.index (Seq.create 1 hx) 0 == Seq.index (Seq.create 1 hy) 0);
      assert (Seq.create 1 hx `Seq.equal` Seq.create 1 hy);
      true
    end else
      false
