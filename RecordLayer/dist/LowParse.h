
#include "kremlin/internal/target.h"
#include "kremlin/internal/types.h"
#include "kremlin/lowstar_endianness.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#ifndef __LowParse_H
#define __LowParse_H




typedef struct LowParse_Slice_slice_s
{
  uint8_t *base;
  uint32_t len;
}
LowParse_Slice_slice;

#define LOWPARSE_LOW_BASE_VALIDATOR_MAX_LENGTH ((uint32_t)4294967279U)

#define LOWPARSE_LOW_BASE_VALIDATOR_ERROR_GENERIC ((uint32_t)4294967280U)

#define LOWPARSE_LOW_BASE_VALIDATOR_ERROR_NOT_ENOUGH_DATA ((uint32_t)4294967281U)

uint8_t LowParse_BitFields_get_bitfield_gen8(uint8_t x, uint32_t lo, uint32_t hi);

uint8_t LowParse_BitFields_set_bitfield_gen8(uint8_t x, uint32_t lo, uint32_t hi, uint8_t v);

#define __LowParse_H_DEFINED
#endif
