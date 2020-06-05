
#include "kremlin/internal/target.h"
#include "kremlin/internal/types.h"
#include "kremlin/lowstar_endianness.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#ifndef __QUIC_H
#define __QUIC_H

#include "EverQuic.h"
#include "EverQuic_EverCrypt.h"


typedef Prims_int QUIC_nat62;

Prims_int QUIC_cipher_keysize(Spec_Agile_AEAD_alg a);

typedef uint8_t QUIC_u2;

typedef uint8_t QUIC_u4;

typedef uint64_t QUIC_u62;

typedef EverQuic_index QUIC_index;

EverCrypt_Error_error_code
QUIC_encrypt(
  EverQuic_index i,
  EverQuic_state_s *s,
  uint8_t *dst,
  uint64_t *dst_pn,
  EverQuic_header h,
  uint8_t *plain,
  uint32_t plain_len
);

EverCrypt_Error_error_code
QUIC_decrypt(
  EverQuic_state_s *uu____2057,
  EverQuic_result *uu____2058,
  uint8_t *uu____2059,
  uint32_t uu____2060,
  uint8_t uu____2061
);

#define __QUIC_H_DEFINED
#endif
