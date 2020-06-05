

#include "LowParse.h"

uint8_t LowParse_BitFields_get_bitfield_gen8(uint8_t x, uint32_t lo, uint32_t hi)
{
  uint8_t op1 = x << ((uint32_t)8U - hi);
  return op1 >> ((uint32_t)8U - hi + lo);
}

uint8_t LowParse_BitFields_set_bitfield_gen8(uint8_t x, uint32_t lo, uint32_t hi, uint8_t v)
{
  uint8_t op0 = (uint8_t)255U;
  uint8_t op1 = op0 >> ((uint32_t)8U - (hi - lo));
  uint8_t op2 = op1 << lo;
  uint8_t op3 = ~op2;
  uint8_t op4 = x & op3;
  uint8_t op5 = v << lo;
  return op4 | op5;
}

