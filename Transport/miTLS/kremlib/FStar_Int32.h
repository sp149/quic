/*
  Copyright (c) INRIA and Microsoft Corporation. All rights reserved.
  Licensed under the Apache 2.0 License.

  This file was generated by KreMLin <https://github.com/FStarLang/kremlin>
  KreMLin invocation: ../krml -fparentheses -fcurly-braces -fno-shadow -header copyright-header.txt -minimal -tmpdir dist/generic -warn-error +9+11 -skip-compilation -extract-uints -add-include <inttypes.h> -add-include "kremlib.h" -add-include "kremlin/internal/compat.h" -add-include "kremlin/internal/target.h" -bundle FStar.UInt64+FStar.UInt32+FStar.UInt16+FStar.UInt8=[rename=FStar_UInt_8_16_32_64] -bundle C.Endianness= -bundle FStar.Reflection,FStar.Reflection.*,FStar.Tactics,FStar.Tactics.*,FStar.Range -library C,C.Endianness,C.Failure,C.Loops,FStar.BitVector,FStar.Bytes,FStar.Char,FStar.Int,FStar.Kremlin.Endianness,FStar.Math.Lib,FStar.ModifiesGen,FStar.Monotonic.Heap,FStar.Monotonic.HyperStack,FStar.Mul,FStar.Pervasives,FStar.Pervasives.Native,FStar.ST,FStar.UInt,FStar.UInt128,FStar.UInt63,LowStar.Printf fstar_int8.c fstar_hyperstack_io.c prims.c c_string.c fstar_char.c fstar_date.c fstar_int64.c fstar_uint8.c fstar_int32.c c.c testlib.c fstar_uint32.c fstar_uint64.c fstar_bytes.c fstar_int16.c lowstar_printf.c fstar_io.c fstar_string.c fstar_dyn.c fstar_uint128.c fstar_uint16.c -o libkremlib.a .extract/prims.krml .extract/FStar_Pervasives_Native.krml .extract/FStar_Pervasives.krml .extract/FStar_Reflection_Types.krml .extract/FStar_Reflection_Data.krml .extract/FStar_Order.krml .extract/FStar_Reflection_Basic.krml .extract/FStar_Preorder.krml .extract/FStar_Calc.krml .extract/FStar_Squash.krml .extract/FStar_Classical.krml .extract/FStar_StrongExcludedMiddle.krml .extract/FStar_FunctionalExtensionality.krml .extract/FStar_List_Tot_Base.krml .extract/FStar_List_Tot_Properties.krml .extract/FStar_List_Tot.krml .extract/FStar_Seq_Base.krml .extract/FStar_Seq_Properties.krml .extract/FStar_Seq.krml .extract/FStar_Mul.krml .extract/FStar_Math_Lib.krml .extract/FStar_Math_Lemmas.krml .extract/FStar_BitVector.krml .extract/FStar_UInt.krml .extract/FStar_UInt32.krml .extract/FStar_Int.krml .extract/FStar_Int16.krml .extract/FStar_Ghost.krml .extract/FStar_ErasedLogic.krml .extract/FStar_UInt64.krml .extract/FStar_Set.krml .extract/FStar_PropositionalExtensionality.krml .extract/FStar_PredicateExtensionality.krml .extract/FStar_TSet.krml .extract/FStar_Monotonic_Heap.krml .extract/FStar_Heap.krml .extract/FStar_Map.krml .extract/FStar_Monotonic_HyperHeap.krml .extract/FStar_Monotonic_HyperStack.krml .extract/FStar_HyperStack.krml .extract/FStar_Monotonic_Witnessed.krml .extract/FStar_HyperStack_ST.krml .extract/FStar_HyperStack_All.krml .extract/FStar_Date.krml .extract/FStar_Char.krml .extract/FStar_Exn.krml .extract/FStar_ST.krml .extract/FStar_All.krml .extract/FStar_List.krml .extract/FStar_String.krml .extract/FStar_Reflection_Const.krml .extract/FStar_Reflection_Derived.krml .extract/FStar_Reflection_Derived_Lemmas.krml .extract/FStar_Universe.krml .extract/FStar_GSet.krml .extract/FStar_ModifiesGen.krml .extract/FStar_Range.krml .extract/FStar_Tactics_Types.krml .extract/FStar_Tactics_Result.krml .extract/FStar_Tactics_Effect.krml .extract/FStar_Tactics_Util.krml .extract/FStar_Tactics_Builtins.krml .extract/FStar_Reflection_Formula.krml .extract/FStar_Reflection.krml .extract/FStar_Tactics_Derived.krml .extract/FStar_Tactics_Logic.krml .extract/FStar_Tactics.krml .extract/FStar_BigOps.krml .extract/LowStar_Monotonic_Buffer.krml .extract/LowStar_Buffer.krml .extract/Spec_Loops.krml .extract/LowStar_BufferOps.krml .extract/C_Loops.krml .extract/FStar_UInt8.krml .extract/FStar_Kremlin_Endianness.krml .extract/FStar_UInt63.krml .extract/FStar_Dyn.krml .extract/FStar_Int63.krml .extract/FStar_Int64.krml .extract/FStar_Int32.krml .extract/FStar_Int8.krml .extract/FStar_UInt16.krml .extract/FStar_Int_Cast.krml .extract/FStar_UInt128.krml .extract/C_Endianness.krml .extract/WasmSupport.krml .extract/FStar_Float.krml .extract/FStar_IO.krml .extract/C.krml .extract/LowStar_Modifies.krml .extract/C_String.krml .extract/FStar_Bytes.krml .extract/FStar_HyperStack_IO.krml .extract/LowStar_Printf.krml .extract/C_Failure.krml .extract/TestLib.krml .extract/FStar_Int_Cast_Full.krml
  F* version: 946ec3ee
  KreMLin version: 88253438
*/

#include <inttypes.h>
#include "kremlib.h"
#include "kremlin/internal/compat.h"
#include "kremlin/internal/target.h"

#ifndef __FStar_Int32_H
#define __FStar_Int32_H




extern Prims_int FStar_Int32_n;

extern Prims_int FStar_Int32_v(int32_t x);

extern int32_t FStar_Int32_int_to_t(Prims_int x);

extern int32_t FStar_Int32_add(int32_t a, int32_t b);

extern int32_t FStar_Int32_sub(int32_t a, int32_t b);

extern int32_t FStar_Int32_mul(int32_t a, int32_t b);

extern int32_t FStar_Int32_div(int32_t a, int32_t b);

extern int32_t FStar_Int32_rem(int32_t a, int32_t b);

extern int32_t FStar_Int32_logand(int32_t x, int32_t y);

extern int32_t FStar_Int32_logxor(int32_t x, int32_t y);

extern int32_t FStar_Int32_logor(int32_t x, int32_t y);

extern int32_t FStar_Int32_lognot(int32_t x);

extern int32_t FStar_Int32_shift_right(int32_t a, uint32_t s);

extern int32_t FStar_Int32_shift_left(int32_t a, uint32_t s);

extern bool FStar_Int32_eq(int32_t a, int32_t b);

extern bool FStar_Int32_gt(int32_t a, int32_t b);

extern bool FStar_Int32_gte(int32_t a, int32_t b);

extern bool FStar_Int32_lt(int32_t a, int32_t b);

extern bool FStar_Int32_lte(int32_t a, int32_t b);

extern int32_t FStar_Int32_ct_abs(int32_t a);

extern Prims_string FStar_Int32_to_string(int32_t uu____503);

extern int32_t FStar_Int32_of_string(Prims_string uu____515);

#define __FStar_Int32_H_DEFINED
#endif
