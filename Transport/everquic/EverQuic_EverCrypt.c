/* 
  This file was generated by KreMLin <https://github.com/FStarLang/kremlin>
  KreMLin invocation: /home/work/everest/master/kremlin/krml -library EverCrypt,EverCrypt.* /home/work/everquic-crypto/test/obj/FStar_Pervasives_Native.krml /home/work/everquic-crypto/test/obj/FStar_Pervasives.krml /home/work/everquic-crypto/test/obj/FStar_Squash.krml /home/work/everquic-crypto/test/obj/FStar_Classical.krml /home/work/everquic-crypto/test/obj/FStar_FunctionalExtensionality.krml /home/work/everquic-crypto/test/obj/FStar_Set.krml /home/work/everquic-crypto/test/obj/FStar_Map.krml /home/work/everquic-crypto/test/obj/FStar_StrongExcludedMiddle.krml /home/work/everquic-crypto/test/obj/FStar_List_Tot_Base.krml /home/work/everquic-crypto/test/obj/FStar_List_Tot_Properties.krml /home/work/everquic-crypto/test/obj/FStar_List_Tot.krml /home/work/everquic-crypto/test/obj/FStar_Seq_Base.krml /home/work/everquic-crypto/test/obj/FStar_Seq_Properties.krml /home/work/everquic-crypto/test/obj/FStar_Seq.krml /home/work/everquic-crypto/test/obj/FStar_Mul.krml /home/work/everquic-crypto/test/obj/Vale_Lib_Seqs_s.krml /home/work/everquic-crypto/test/obj/FStar_Preorder.krml /home/work/everquic-crypto/test/obj/FStar_Calc.krml /home/work/everquic-crypto/test/obj/FStar_Math_Lib.krml /home/work/everquic-crypto/test/obj/FStar_Math_Lemmas.krml /home/work/everquic-crypto/test/obj/FStar_BitVector.krml /home/work/everquic-crypto/test/obj/FStar_UInt.krml /home/work/everquic-crypto/test/obj/FStar_UInt32.krml /home/work/everquic-crypto/test/obj/FStar_UInt8.krml /home/work/everquic-crypto/test/obj/Vale_Def_Words_s.krml /home/work/everquic-crypto/test/obj/Vale_Def_Words_Four_s.krml /home/work/everquic-crypto/test/obj/Vale_Def_Words_Two_s.krml /home/work/everquic-crypto/test/obj/Vale_Def_Words_Seq_s.krml /home/work/everquic-crypto/test/obj/Vale_Def_Opaque_s.krml /home/work/everquic-crypto/test/obj/Vale_Def_Types_s.krml /home/work/everquic-crypto/test/obj/Vale_Arch_HeapTypes_s.krml /home/work/everquic-crypto/test/obj/Vale_X64_Machine_s.krml /home/work/everquic-crypto/test/obj/Vale_Lib_Map16.krml /home/work/everquic-crypto/test/obj/Vale_Def_Prop_s.krml /home/work/everquic-crypto/test/obj/Vale_X64_Flags.krml /home/work/everquic-crypto/test/obj/Vale_AES_AES_s.krml /home/work/everquic-crypto/test/obj/FStar_Float.krml /home/work/everquic-crypto/test/obj/FStar_UInt64.krml /home/work/everquic-crypto/test/obj/FStar_UInt16.krml /home/work/everquic-crypto/test/obj/FStar_Exn.krml /home/work/everquic-crypto/test/obj/FStar_Monotonic_Witnessed.krml /home/work/everquic-crypto/test/obj/FStar_Ghost.krml /home/work/everquic-crypto/test/obj/FStar_ErasedLogic.krml /home/work/everquic-crypto/test/obj/FStar_PropositionalExtensionality.krml /home/work/everquic-crypto/test/obj/FStar_PredicateExtensionality.krml /home/work/everquic-crypto/test/obj/FStar_TSet.krml /home/work/everquic-crypto/test/obj/FStar_Monotonic_Heap.krml /home/work/everquic-crypto/test/obj/FStar_Heap.krml /home/work/everquic-crypto/test/obj/FStar_ST.krml /home/work/everquic-crypto/test/obj/FStar_All.krml /home/work/everquic-crypto/test/obj/FStar_IO.krml /home/work/everquic-crypto/test/obj/Vale_Lib_Meta.krml /home/work/everquic-crypto/test/obj/Vale_Def_Words_Two.krml /home/work/everquic-crypto/test/obj/FStar_List.krml /home/work/everquic-crypto/test/obj/Vale_Lib_Seqs.krml /home/work/everquic-crypto/test/obj/Vale_Def_TypesNative_s.krml /home/work/everquic-crypto/test/obj/Vale_Arch_TypesNative.krml /home/work/everquic-crypto/test/obj/Vale_Def_Words_Seq.krml /home/work/everquic-crypto/test/obj/Vale_Arch_Types.krml /home/work/everquic-crypto/test/obj/Vale_Arch_MachineHeap_s.krml /home/work/everquic-crypto/test/obj/Vale_Arch_MachineHeap.krml /home/work/everquic-crypto/test/obj/FStar_Monotonic_HyperHeap.krml /home/work/everquic-crypto/test/obj/FStar_Monotonic_HyperStack.krml /home/work/everquic-crypto/test/obj/FStar_HyperStack.krml /home/work/everquic-crypto/test/obj/FStar_HyperStack_ST.krml /home/work/everquic-crypto/test/obj/FStar_Universe.krml /home/work/everquic-crypto/test/obj/FStar_GSet.krml /home/work/everquic-crypto/test/obj/FStar_ModifiesGen.krml /home/work/everquic-crypto/test/obj/FStar_Range.krml /home/work/everquic-crypto/test/obj/FStar_Reflection_Types.krml /home/work/everquic-crypto/test/obj/FStar_Tactics_Types.krml /home/work/everquic-crypto/test/obj/FStar_Tactics_Result.krml /home/work/everquic-crypto/test/obj/FStar_Tactics_Effect.krml /home/work/everquic-crypto/test/obj/FStar_Reflection_Data.krml /home/work/everquic-crypto/test/obj/FStar_Tactics_Builtins.krml /home/work/everquic-crypto/test/obj/FStar_Reflection_Const.krml /home/work/everquic-crypto/test/obj/FStar_Order.krml /home/work/everquic-crypto/test/obj/FStar_Reflection_Builtins.krml /home/work/everquic-crypto/test/obj/FStar_Reflection_Derived.krml /home/work/everquic-crypto/test/obj/FStar_Reflection_Derived_Lemmas.krml /home/work/everquic-crypto/test/obj/FStar_Reflection.krml /home/work/everquic-crypto/test/obj/FStar_Tactics_SyntaxHelpers.krml /home/work/everquic-crypto/test/obj/FStar_Tactics_Util.krml /home/work/everquic-crypto/test/obj/FStar_Reflection_Formula.krml /home/work/everquic-crypto/test/obj/FStar_Tactics_Derived.krml /home/work/everquic-crypto/test/obj/FStar_Tactics_Logic.krml /home/work/everquic-crypto/test/obj/FStar_Tactics.krml /home/work/everquic-crypto/test/obj/FStar_BigOps.krml /home/work/everquic-crypto/test/obj/LowStar_Monotonic_Buffer.krml /home/work/everquic-crypto/test/obj/LowStar_BufferView_Down.krml /home/work/everquic-crypto/test/obj/LowStar_BufferView_Up.krml /home/work/everquic-crypto/test/obj/Vale_Interop_Views.krml /home/work/everquic-crypto/test/obj/LowStar_Buffer.krml /home/work/everquic-crypto/test/obj/LowStar_Modifies.krml /home/work/everquic-crypto/test/obj/LowStar_ModifiesPat.krml /home/work/everquic-crypto/test/obj/LowStar_BufferView.krml /home/work/everquic-crypto/test/obj/Vale_Lib_BufferViewHelpers.krml /home/work/everquic-crypto/test/obj/LowStar_ImmutableBuffer.krml /home/work/everquic-crypto/test/obj/Vale_Interop_Types.krml /home/work/everquic-crypto/test/obj/Vale_Interop_Heap_s.krml /home/work/everquic-crypto/test/obj/Vale_Interop.krml /home/work/everquic-crypto/test/obj/FStar_Option.krml /home/work/everquic-crypto/test/obj/Vale_Lib_Set.krml /home/work/everquic-crypto/test/obj/Vale_Arch_HeapImpl.krml /home/work/everquic-crypto/test/obj/Vale_Arch_Heap.krml /home/work/everquic-crypto/test/obj/Vale_X64_Instruction_s.krml /home/work/everquic-crypto/test/obj/Vale_X64_Bytes_Code_s.krml /home/work/everquic-crypto/test/obj/Vale_Math_Poly2_Defs_s.krml /home/work/everquic-crypto/test/obj/Vale_Math_Poly2_s.krml /home/work/everquic-crypto/test/obj/Vale_Math_Poly2_Bits_s.krml /home/work/everquic-crypto/test/obj/Lib_LoopCombinators.krml /home/work/everquic-crypto/test/obj/FStar_Int.krml /home/work/everquic-crypto/test/obj/FStar_Int64.krml /home/work/everquic-crypto/test/obj/FStar_Int32.krml /home/work/everquic-crypto/test/obj/FStar_Int16.krml /home/work/everquic-crypto/test/obj/FStar_Int8.krml /home/work/everquic-crypto/test/obj/FStar_Int_Cast.krml /home/work/everquic-crypto/test/obj/FStar_UInt128.krml /home/work/everquic-crypto/test/obj/FStar_Int_Cast_Full.krml /home/work/everquic-crypto/test/obj/FStar_Int128.krml /home/work/everquic-crypto/test/obj/Lib_IntTypes.krml /home/work/everquic-crypto/test/obj/Lib_RawIntTypes.krml /home/work/everquic-crypto/test/obj/Lib_Sequence.krml /home/work/everquic-crypto/test/obj/Lib_ByteSequence.krml /home/work/everquic-crypto/test/obj/Spec_Hash_Definitions.krml /home/work/everquic-crypto/test/obj/Spec_Hash_Lemmas0.krml /home/work/everquic-crypto/test/obj/Spec_Hash_PadFinish.krml /home/work/everquic-crypto/test/obj/Spec_Loops.krml /home/work/everquic-crypto/test/obj/Spec_SHA2_Constants.krml /home/work/everquic-crypto/test/obj/Spec_SHA2.krml /home/work/everquic-crypto/test/obj/Vale_X64_CryptoInstructions_s.krml /home/work/everquic-crypto/test/obj/Vale_X64_CPU_Features_s.krml /home/work/everquic-crypto/test/obj/Vale_X64_Instructions_s.krml /home/work/everquic-crypto/test/obj/Vale_X64_Machine_Semantics_s.krml /home/work/everquic-crypto/test/obj/Vale_Interop_Base.krml /home/work/everquic-crypto/test/obj/Vale_X64_Memory.krml /home/work/everquic-crypto/test/obj/Vale_X64_BufferViewStore.krml /home/work/everquic-crypto/test/obj/Vale_X64_Memory_Sems.krml /home/work/everquic-crypto/test/obj/Vale_Def_PossiblyMonad.krml /home/work/everquic-crypto/test/obj/Vale_X64_Stack_i.krml /home/work/everquic-crypto/test/obj/Vale_X64_Stack_Sems.krml /home/work/everquic-crypto/test/obj/Vale_X64_Regs.krml /home/work/everquic-crypto/test/obj/Vale_X64_State.krml /home/work/everquic-crypto/test/obj/Vale_X64_StateLemmas.krml /home/work/everquic-crypto/test/obj/Vale_Arch_HeapLemmas.krml /home/work/everquic-crypto/test/obj/Vale_X64_Lemmas.krml /home/work/everquic-crypto/test/obj/Vale_X64_Print_s.krml /home/work/everquic-crypto/test/obj/Vale_X64_Decls.krml /home/work/everquic-crypto/test/obj/Vale_X64_Taint_Semantics.krml /home/work/everquic-crypto/test/obj/Vale_X64_InsLemmas.krml /home/work/everquic-crypto/test/obj/Vale_X64_QuickCode.krml /home/work/everquic-crypto/test/obj/Vale_X64_InsAes.krml /home/work/everquic-crypto/test/obj/Spec_Chacha20.krml /home/work/everquic-crypto/test/obj/Meta_Attribute.krml /home/work/everquic-crypto/test/obj/LowStar_BufferOps.krml /home/work/everquic-crypto/test/obj/C_Loops.krml /home/work/everquic-crypto/test/obj/Lib_Loops.krml /home/work/everquic-crypto/test/obj/FStar_Endianness.krml /home/work/everquic-crypto/test/obj/LowStar_Endianness.krml /home/work/everquic-crypto/test/obj/LowStar_ConstBuffer.krml /home/work/everquic-crypto/test/obj/Lib_Buffer.krml /home/work/everquic-crypto/test/obj/Lib_ByteBuffer.krml /home/work/everquic-crypto/test/obj/FStar_HyperStack_All.krml /home/work/everquic-crypto/test/obj/Lib_IntVector_Intrinsics.krml /home/work/everquic-crypto/test/obj/Spec_GaloisField.krml /home/work/everquic-crypto/test/obj/Spec_AES.krml /home/work/everquic-crypto/test/obj/Lib_IntVector.krml /home/work/everquic-crypto/test/obj/Hacl_Spec_Chacha20_Vec.krml /home/work/everquic-crypto/test/obj/Lib_Sequence_Lemmas.krml /home/work/everquic-crypto/test/obj/Lib_Vec_Lemmas.krml /home/work/everquic-crypto/test/obj/Hacl_Spec_Chacha20_Lemmas.krml /home/work/everquic-crypto/test/obj/Hacl_Spec_Chacha20_Equiv.krml /home/work/everquic-crypto/test/obj/Hacl_Impl_Chacha20_Core32xN.krml /home/work/everquic-crypto/test/obj/Hacl_Impl_Chacha20_Vec.krml /home/work/everquic-crypto/test/obj/LowParse_Bytes.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_Base.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_Combinators.krml /home/work/everquic-crypto/test/obj/LowParse_Math.krml /home/work/everquic-crypto/test/obj/LowParse_Slice.krml /home/work/everquic-crypto/test/obj/LowParse_Low_Base_Spec.krml /home/work/everquic-crypto/test/obj/LowParse_Low_Base.krml /home/work/everquic-crypto/test/obj/LowParse_Low_Combinators.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_Seq.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_Int.krml /home/work/everquic-crypto/test/obj/LowParse_Low_Endianness.krml /home/work/everquic-crypto/test/obj/LowParse_Low_Int.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_BoundedInt.krml /home/work/everquic-crypto/test/obj/LowParse_BitFields.krml /home/work/everquic-crypto/test/obj/LowParse_Endianness.krml /home/work/everquic-crypto/test/obj/LowParse_Endianness_BitFields.krml /home/work/everquic-crypto/test/obj/LowParse_Low_BoundedInt.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_BitFields.krml /home/work/everquic-crypto/test/obj/QUIC_Secret_Int_Base.krml /home/work/everquic-crypto/test/obj/QUIC_Secret_Int_Aux.krml /home/work/everquic-crypto/test/obj/QUIC_Secret_Int.krml /home/work/everquic-crypto/test/obj/QUIC_UInt62.krml /home/work/everquic-crypto/test/obj/QUIC_Spec_VarInt.krml /home/work/everquic-crypto/test/obj/QUIC_Impl_Base.krml /home/work/everquic-crypto/test/obj/QUIC_Impl_VarInt.krml /home/work/everquic-crypto/test/obj/Vale_Transformers_Locations.krml /home/work/everquic-crypto/test/obj/Vale_Math_Poly2_Defs.krml /home/work/everquic-crypto/test/obj/Vale_Math_Poly2.krml /home/work/everquic-crypto/test/obj/Vale_Math_Poly2_Lemmas.krml /home/work/everquic-crypto/test/obj/Vale_Math_Poly2_Bits.krml /home/work/everquic-crypto/test/obj/Vale_Math_Poly2_Words.krml /home/work/everquic-crypto/test/obj/Vale_AES_GF128_s.krml /home/work/everquic-crypto/test/obj/Vale_AES_GF128.krml /home/work/everquic-crypto/test/obj/Vale_AES_OptPublic.krml /home/work/everquic-crypto/test/obj/Vale_X64_QuickCodes.krml /home/work/everquic-crypto/test/obj/Vale_X64_InsBasic.krml /home/work/everquic-crypto/test/obj/Vale_X64_InsMem.krml /home/work/everquic-crypto/test/obj/Vale_X64_InsVector.krml /home/work/everquic-crypto/test/obj/Vale_AES_X64_GF128_Mul.krml /home/work/everquic-crypto/test/obj/Vale_AES_X64_PolyOps.krml /home/work/everquic-crypto/test/obj/Vale_X64_InsStack.krml /home/work/everquic-crypto/test/obj/Vale_X64_Stack.krml /home/work/everquic-crypto/test/obj/FStar_BV.krml /home/work/everquic-crypto/test/obj/Vale_Lib_Bv_s.krml /home/work/everquic-crypto/test/obj/Vale_Math_Bits.krml /home/work/everquic-crypto/test/obj/Vale_Lib_Tactics.krml /home/work/everquic-crypto/test/obj/FStar_Reflection_Arith.krml /home/work/everquic-crypto/test/obj/FStar_Tactics_BV.krml /home/work/everquic-crypto/test/obj/Vale_Poly1305_Bitvectors.krml /home/work/everquic-crypto/test/obj/Vale_AES_GCTR_s.krml /home/work/everquic-crypto/test/obj/Vale_AES_GCM_helpers.krml /home/work/everquic-crypto/test/obj/Vale_AES_GCTR.krml /home/work/everquic-crypto/test/obj/Vale_AES_AES256_helpers.krml /home/work/everquic-crypto/test/obj/Vale_AES_X64_AES256.krml /home/work/everquic-crypto/test/obj/Vale_AES_AES_helpers.krml /home/work/everquic-crypto/test/obj/Vale_AES_X64_AES128.krml /home/work/everquic-crypto/test/obj/Vale_AES_X64_AES.krml /home/work/everquic-crypto/test/obj/Vale_AES_GHash_s.krml /home/work/everquic-crypto/test/obj/Vale_AES_GHash.krml /home/work/everquic-crypto/test/obj/Vale_AES_X64_GF128_Init.krml /home/work/everquic-crypto/test/obj/Lib_UpdateMulti.krml /home/work/everquic-crypto/test/obj/Spec_SHA1.krml /home/work/everquic-crypto/test/obj/Spec_MD5.krml /home/work/everquic-crypto/test/obj/Spec_Agile_Hash.krml /home/work/everquic-crypto/test/obj/Spec_Hash_Incremental.krml /home/work/everquic-crypto/test/obj/Spec_Hash_Lemmas.krml /home/work/everquic-crypto/test/obj/FStar_Kremlin_Endianness.krml /home/work/everquic-crypto/test/obj/Hacl_Hash_Lemmas.krml /home/work/everquic-crypto/test/obj/Hacl_Hash_Definitions.krml /home/work/everquic-crypto/test/obj/Hacl_Hash_PadFinish.krml /home/work/everquic-crypto/test/obj/Hacl_Hash_MD.krml /home/work/everquic-crypto/test/obj/Spec_SHA2_Lemmas.krml /home/work/everquic-crypto/test/obj/Vale_X64_MemoryAdapters.krml /home/work/everquic-crypto/test/obj/Vale_Interop_Assumptions.krml /home/work/everquic-crypto/test/obj/Vale_Interop_X64.krml /home/work/everquic-crypto/test/obj/Vale_AsLowStar_ValeSig.krml /home/work/everquic-crypto/test/obj/Vale_AsLowStar_LowStarSig.krml /home/work/everquic-crypto/test/obj/Vale_AsLowStar_MemoryHelpers.krml /home/work/everquic-crypto/test/obj/Vale_SHA_SHA_helpers.krml /home/work/everquic-crypto/test/obj/Vale_X64_InsSha.krml /home/work/everquic-crypto/test/obj/Vale_SHA_X64.krml /home/work/everquic-crypto/test/obj/Vale_AsLowStar_Wrapper.krml /home/work/everquic-crypto/test/obj/Vale_Stdcalls_X64_Sha.krml /home/work/everquic-crypto/test/obj/FStar_Algebra_CommMonoid.krml /home/work/everquic-crypto/test/obj/FStar_Tactics_CanonCommSemiring.krml /home/work/everquic-crypto/test/obj/Vale_Math_Lemmas_Int.krml /home/work/everquic-crypto/test/obj/FStar_Tactics_Canon.krml /home/work/everquic-crypto/test/obj/Vale_Poly1305_Spec_s.krml /home/work/everquic-crypto/test/obj/Vale_Poly1305_Math.krml /home/work/everquic-crypto/test/obj/Vale_Poly1305_Util.krml /home/work/everquic-crypto/test/obj/Vale_Poly1305_X64.krml /home/work/everquic-crypto/test/obj/Vale_Stdcalls_X64_Poly.krml /home/work/everquic-crypto/test/obj/Vale_Wrapper_X64_Poly.krml /home/work/everquic-crypto/test/obj/Vale_Arch_BufferFriend.krml /home/work/everquic-crypto/test/obj/Vale_SHA_Simplify_Sha.krml /home/work/everquic-crypto/test/obj/Vale_Wrapper_X64_Sha.krml /home/work/everquic-crypto/test/obj/EverCrypt_TargetConfig.krml /home/work/everquic-crypto/test/obj/Hacl_Hash_Core_SHA2.krml /home/work/everquic-crypto/test/obj/Hacl_Hash_SHA2.krml /home/work/everquic-crypto/test/obj/Hacl_Hash_Core_SHA1.krml /home/work/everquic-crypto/test/obj/Hacl_Hash_SHA1.krml /home/work/everquic-crypto/test/obj/Hacl_Hash_Core_MD5.krml /home/work/everquic-crypto/test/obj/Hacl_Hash_MD5.krml /home/work/everquic-crypto/test/obj/C.krml /home/work/everquic-crypto/test/obj/FStar_Char.krml /home/work/everquic-crypto/test/obj/FStar_String.krml /home/work/everquic-crypto/test/obj/C_String.krml /home/work/everquic-crypto/test/obj/C_Failure.krml /home/work/everquic-crypto/test/obj/FStar_Integers.krml /home/work/everquic-crypto/test/obj/EverCrypt_StaticConfig.krml /home/work/everquic-crypto/test/obj/Vale_Lib_Basic.krml /home/work/everquic-crypto/test/obj/Vale_Lib_X64_Cpuid.krml /home/work/everquic-crypto/test/obj/Vale_Lib_X64_Cpuidstdcall.krml /home/work/everquic-crypto/test/obj/Vale_Stdcalls_X64_Cpuid.krml /home/work/everquic-crypto/test/obj/Vale_Wrapper_X64_Cpuid.krml /home/work/everquic-crypto/test/obj/EverCrypt_AutoConfig2.krml /home/work/everquic-crypto/test/obj/EverCrypt_Helpers.krml /home/work/everquic-crypto/test/obj/EverCrypt_Hash.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_IfThenElse.krml /home/work/everquic-crypto/test/obj/Vale_AES_GCM_s.krml /home/work/everquic-crypto/test/obj/Vale_AES_GCM.krml /home/work/everquic-crypto/test/obj/Vale_AES_X64_AESopt2.krml /home/work/everquic-crypto/test/obj/Vale_AES_X64_AESGCM_expected_code.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_FLData.krml /home/work/everquic-crypto/test/obj/Hacl_Impl_Poly1305_Lemmas.krml /home/work/everquic-crypto/test/obj/Spec_Poly1305.krml /home/work/everquic-crypto/test/obj/Hacl_Spec_Poly1305_Vec.krml /home/work/everquic-crypto/test/obj/Hacl_Spec_Poly1305_Field32xN.krml /home/work/everquic-crypto/test/obj/Hacl_Poly1305_Field32xN_Lemmas2.krml /home/work/everquic-crypto/test/obj/Hacl_Poly1305_Field32xN_Lemmas1.krml /home/work/everquic-crypto/test/obj/Hacl_Poly1305_Field32xN_Lemmas0.krml /home/work/everquic-crypto/test/obj/Hacl_Spec_Poly1305_Field32xN_Lemmas.krml /home/work/everquic-crypto/test/obj/Hacl_Impl_Poly1305_Field32xN.krml /home/work/everquic-crypto/test/obj/Hacl_Spec_Poly1305_Lemmas.krml /home/work/everquic-crypto/test/obj/Hacl_Spec_Poly1305_Equiv.krml /home/work/everquic-crypto/test/obj/Hacl_Impl_Poly1305_Field32xN_256.krml /home/work/everquic-crypto/test/obj/Hacl_Impl_Poly1305_Field32xN_128.krml /home/work/everquic-crypto/test/obj/Hacl_Impl_Poly1305_Field32xN_32.krml /home/work/everquic-crypto/test/obj/Hacl_Impl_Poly1305_Fields.krml /home/work/everquic-crypto/test/obj/Hacl_Impl_Poly1305.krml /home/work/everquic-crypto/test/obj/Spec_Chacha20Poly1305.krml /home/work/everquic-crypto/test/obj/Hacl_Impl_Chacha20Poly1305_PolyCore.krml /home/work/everquic-crypto/test/obj/Hacl_Impl_Chacha20Poly1305.krml /home/work/everquic-crypto/test/obj/FStar_List_Pure_Base.krml /home/work/everquic-crypto/test/obj/FStar_List_Pure_Properties.krml /home/work/everquic-crypto/test/obj/FStar_List_Pure.krml /home/work/everquic-crypto/test/obj/Meta_Interface.krml /home/work/everquic-crypto/test/obj/Hacl_Meta_Chacha20Poly1305.krml /home/work/everquic-crypto/test/obj/Hacl_Meta_Chacha20_Vec.krml /home/work/everquic-crypto/test/obj/Hacl_Chacha20_Vec256.krml /home/work/everquic-crypto/test/obj/Hacl_Meta_Poly1305.krml /home/work/everquic-crypto/test/obj/Hacl_Poly1305_256.krml /home/work/everquic-crypto/test/obj/Hacl_Chacha20Poly1305_256.krml /home/work/everquic-crypto/test/obj/Spec_Agile_HMAC.krml /home/work/everquic-crypto/test/obj/Hacl_HMAC.krml /home/work/everquic-crypto/test/obj/FStar_Bytes.krml /home/work/everquic-crypto/test/obj/QUIC_Spec_Base.krml /home/work/everquic-crypto/test/obj/Vale_AES_X64_GHash.krml /home/work/everquic-crypto/test/obj/Vale_AES_X64_AESCTR.krml /home/work/everquic-crypto/test/obj/Vale_AES_X64_AESCTRplain.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_List.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_SeqBytes_Base.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_DER.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_BCVLI.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_AllIntegers.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_VLData.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_Array.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_VCList.krml /home/work/everquic-crypto/test/obj/Vale_Transformers_BoundedInstructionEffects.krml /home/work/everquic-crypto/test/obj/Vale_Transformers_InstructionReorder.krml /home/work/everquic-crypto/test/obj/Vale_Transformers_Common.krml /home/work/everquic-crypto/test/obj/Vale_Transformers_PeepHole.krml /home/work/everquic-crypto/test/obj/Vale_Transformers_MovMovElim.krml /home/work/everquic-crypto/test/obj/Vale_Transformers_MovbeElim.krml /home/work/everquic-crypto/test/obj/Vale_Transformers_Transform.krml /home/work/everquic-crypto/test/obj/Vale_AES_X64_AESopt.krml /home/work/everquic-crypto/test/obj/Vale_AES_X64_AESGCM.krml /home/work/everquic-crypto/test/obj/Vale_AES_X64_GCTR.krml /home/work/everquic-crypto/test/obj/Vale_AES_X64_GCMencryptOpt.krml /home/work/everquic-crypto/test/obj/Vale_AES_X64_GCMdecryptOpt.krml /home/work/everquic-crypto/test/obj/QUIC_Spec_Lemmas.krml /home/work/everquic-crypto/test/obj/Spec_Agile_Cipher.krml /home/work/everquic-crypto/test/obj/Spec_Agile_AEAD.krml /home/work/everquic-crypto/test/obj/QUIC_Secret_Seq.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_Enum.krml /home/work/everquic-crypto/test/obj/FStar_WellFounded.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_BitSum.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_VLGen.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_Option.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_Bytes.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_SeqBytes.krml /home/work/everquic-crypto/test/obj/LowParse_TacLib.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_Sum.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_Tac_Enum.krml /home/work/everquic-crypto/test/obj/LowParse_Spec_Tac_Sum.krml /home/work/everquic-crypto/test/obj/LowParse_Spec.krml /home/work/everquic-crypto/test/obj/QUIC_Spec_Header_Public.krml /home/work/everquic-crypto/test/obj/QUIC_Spec_PacketNumber_Lemmas.krml /home/work/everquic-crypto/test/obj/QUIC_Spec_PacketNumber_Base.krml /home/work/everquic-crypto/test/obj/QUIC_Spec_PacketNumber.krml /home/work/everquic-crypto/test/obj/QUIC_Spec_Header_Base.krml /home/work/everquic-crypto/test/obj/QUIC_Spec_Header_Parse.krml /home/work/everquic-crypto/test/obj/Spec_Agile_HKDF.krml /home/work/everquic-crypto/test/obj/QUIC_Spec_Crypto.krml /home/work/everquic-crypto/test/obj/QUIC_Spec_Header.krml /home/work/everquic-crypto/test/obj/Vale_AES_Gcm_simplify.krml /home/work/everquic-crypto/test/obj/Vale_Stdcalls_X64_GCMdecryptOpt.krml /home/work/everquic-crypto/test/obj/Vale_Stdcalls_X64_Aes.krml /home/work/everquic-crypto/test/obj/Vale_Wrapper_X64_AES.krml /home/work/everquic-crypto/test/obj/Vale_Wrapper_X64_GCMdecryptOpt.krml /home/work/everquic-crypto/test/obj/Vale_Wrapper_X64_GCMdecryptOpt256.krml /home/work/everquic-crypto/test/obj/Hacl_Impl_Chacha20_Core32.krml /home/work/everquic-crypto/test/obj/Hacl_Impl_Chacha20.krml /home/work/everquic-crypto/test/obj/Hacl_Chacha20.krml /home/work/everquic-crypto/test/obj/Hacl_Poly1305_32.krml /home/work/everquic-crypto/test/obj/Hacl_Chacha20Poly1305_32.krml /home/work/everquic-crypto/test/obj/Hacl_Chacha20_Vec128.krml /home/work/everquic-crypto/test/obj/Hacl_Poly1305_128.krml /home/work/everquic-crypto/test/obj/Hacl_Chacha20Poly1305_128.krml /home/work/everquic-crypto/test/obj/EverCrypt_Chacha20Poly1305.krml /home/work/everquic-crypto/test/obj/LowStar_Failure.krml /home/work/everquic-crypto/test/obj/Vale_Stdcalls_X64_GCM_IV.krml /home/work/everquic-crypto/test/obj/Vale_Wrapper_X64_GCM_IV.krml /home/work/everquic-crypto/test/obj/Vale_Stdcalls_X64_GCMencryptOpt.krml /home/work/everquic-crypto/test/obj/Vale_Wrapper_X64_GCMencryptOpt.krml /home/work/everquic-crypto/test/obj/Vale_Wrapper_X64_GCMencryptOpt256.krml /home/work/everquic-crypto/test/obj/Vale_Stdcalls_X64_AesHash.krml /home/work/everquic-crypto/test/obj/Vale_Wrapper_X64_AEShash.krml /home/work/everquic-crypto/test/obj/Spec_Cipher_Expansion.krml /home/work/everquic-crypto/test/obj/EverCrypt_CTR_Keys.krml /home/work/everquic-crypto/test/obj/EverCrypt_Error.krml /home/work/everquic-crypto/test/obj/EverCrypt_AEAD.krml /home/work/everquic-crypto/test/obj/LowParse_Low_Option.krml /home/work/everquic-crypto/test/obj/LowStar_Printf.krml /home/work/everquic-crypto/test/obj/QUIC_Spec.krml /home/work/everquic-crypto/test/obj/Vale_Stdcalls_X64_GCTR.krml /home/work/everquic-crypto/test/obj/Vale_Wrapper_X64_GCTR.krml /home/work/everquic-crypto/test/obj/Spec_Agile_CTR.krml /home/work/everquic-crypto/test/obj/EverCrypt_CTR.krml /home/work/everquic-crypto/test/obj/QUIC_Impl_Lemmas.krml /home/work/everquic-crypto/test/obj/QUIC_Secret_Buffer.krml /home/work/everquic-crypto/test/obj/EverCrypt_HMAC.krml /home/work/everquic-crypto/test/obj/Hacl_HKDF.krml /home/work/everquic-crypto/test/obj/EverCrypt_HKDF.krml /home/work/everquic-crypto/test/obj/EverCrypt_Cipher.krml /home/work/everquic-crypto/test/obj/QUIC_Impl_Crypto.krml /home/work/everquic-crypto/test/obj/QUIC_Impl_PacketNumber.krml /home/work/everquic-crypto/test/obj/LowParse_Low_BitSum.krml /home/work/everquic-crypto/test/obj/LowParse_Bytes32.krml /home/work/everquic-crypto/test/obj/LowParse_Low_FLData.krml /home/work/everquic-crypto/test/obj/LowParse_Low_VLData.krml /home/work/everquic-crypto/test/obj/LowParse_Low_VLGen.krml /home/work/everquic-crypto/test/obj/LowParse_Low_Bytes.krml /home/work/everquic-crypto/test/obj/LowParse_Low_Writers.krml /home/work/everquic-crypto/test/obj/LowParse_Low_Writers_Instances.krml /home/work/everquic-crypto/test/obj/LowParse_Low_DER.krml /home/work/everquic-crypto/test/obj/LowParse_Low_BCVLI.krml /home/work/everquic-crypto/test/obj/LowParse_Low_List.krml /home/work/everquic-crypto/test/obj/LowParse_Low_VCList.krml /home/work/everquic-crypto/test/obj/LowParse_Low_IfThenElse.krml /home/work/everquic-crypto/test/obj/LowParse_Low_Enum.krml /home/work/everquic-crypto/test/obj/LowParse_Low_Sum.krml /home/work/everquic-crypto/test/obj/LowParse_Low_Tac_Sum.krml /home/work/everquic-crypto/test/obj/LowParse_Low_Array.krml /home/work/everquic-crypto/test/obj/LowParse_Low.krml /home/work/everquic-crypto/test/obj/QUIC_Impl_Header_Public.krml /home/work/everquic-crypto/test/obj/QUIC_Impl_Header_Base.krml /home/work/everquic-crypto/test/obj/QUIC_Impl_Header_Parse.krml /home/work/everquic-crypto/test/obj/QUIC_Impl_Header.krml /home/work/everquic-crypto/test/obj/QUIC_Impl.krml /home/work/everquic-crypto/test/obj/QUICTest.krml -tmpdir dist -skip-compilation -minimal -add-include "kremlin/internal/target.h" -add-include "kremlin/internal/types.h" -add-include "kremlin/lowstar_endianness.h" -add-include <stdint.h> -add-include <stdbool.h> -add-include <string.h> -fparentheses -o libeverquic.a -bundle LowParse.* -bundle LowStar.* -bundle Prims,C.Failure,C,C.String,C.Loops,Spec.Loops,C.Endianness,FStar.*[rename=EverQuic_Kremlib] -bundle Meta.*,Hacl.*,Vale.*,Spec.*,Lib.*,EverCrypt,EverCrypt.*[rename=EverQuic_EverCrypt] -bundle QUIC.Impl+QUIC.Impl.Crypto+QUIC.Impl.Header.Base=QUIC.\*[rename=EverQuic,rename-prefix]
  F* version: f209605d
  KreMLin version: 6f95f261
 */

#include "EverQuic_EverCrypt.h"

Spec_Agile_Cipher_cipher_alg Spec_Agile_AEAD_cipher_alg_of_supported_alg(Spec_Agile_AEAD_alg a)
{
  switch (a)
  {
    case Spec_Agile_AEAD_AES128_GCM:
      {
        return Spec_Agile_Cipher_AES128;
      }
    case Spec_Agile_AEAD_AES256_GCM:
      {
        return Spec_Agile_Cipher_AES256;
      }
    case Spec_Agile_AEAD_CHACHA20_POLY1305:
      {
        return Spec_Agile_Cipher_CHACHA20;
      }
    default:
      {
        KRML_HOST_EPRINTF("KreMLin incomplete match at %s:%d\n", __FILE__, __LINE__);
        KRML_HOST_EXIT(253U);
      }
  }
}

typedef struct EverCrypt_AEAD_state_s_s
{
  Spec_Cipher_Expansion_impl impl;
  uint8_t *ek;
}
EverCrypt_AEAD_state_s;

typedef struct EverCrypt_CTR_state_s_s
{
  Spec_Cipher_Expansion_impl i;
  uint8_t *iv;
  uint32_t iv_len;
  uint8_t *xkey;
  uint32_t ctr;
}
EverCrypt_CTR_state_s;
