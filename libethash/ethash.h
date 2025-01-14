/*
  This file is part of ethash.

  ethash is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  ethash is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with ethash.  If not, see <http://www.gnu.org/licenses/>.
*/

/** @file ethash.h
* @date 2015
*/
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include "compiler.h"

#define ETHASH_REVISION 23
#define ETHASH_DATASET_BYTES_INIT 1073741824U // 2**30
#define ETHASH_DATASET_BYTES_GROWTH 8388608U  // 2**23
#define ETHASH_CACHE_BYTES_INIT 1073741824U // 2**24
#define ETHASH_CACHE_BYTES_GROWTH 131072U  // 2**17
#define ETHASH_EPOCH_LENGTH 30000U
#define ETHASH_MIX_BYTES 128
#define ETHASH_HASH_BYTES 64
#define ETHASH_DATASET_PARENTS 512
#define ETHASH_CACHE_ROUNDS 3
#define ETHASH_ACCESSES 64

#ifdef __cplusplus
extern "C" {
#endif

/// Type of a seedhash/blockhash e.t.c.
typedef struct ethash_h256 { uint8_t b[32]; } ethash_h256_t;

struct ethash_light;
typedef struct ethash_light* ethash_light_t;

typedef struct ethash_return_value {
	ethash_h256_t result;
	ethash_h256_t mix_hash;
	bool success;
} ethash_return_value_t;

/**
 * Allocate and initialize a new ethash_light handler
 *
 * @param block_number   The block number for which to create the handler
 * @return               Newly allocated ethash_light handler or NULL in case of
 *                       ERRNOMEM or invalid parameters used for @ref ethash_compute_cache_nodes()
 */
ethash_light_t ethash_light_new(uint64_t block_number);
/**
 * Frees a previously allocated ethash_light handler
 * @param light        The light handler to free
 */
void ethash_light_delete(ethash_light_t light);
/**
 * Calculate the light client data
 *
 * @param light          The light client handler
 * @param header_hash    The header hash to pack into the mix
 * @param nonce          The nonce to pack into the mix
 * @return               an object of ethash_return_value_t holding the return values
 */
ethash_return_value_t ethash_light_compute(
	ethash_light_t light,
	ethash_h256_t const header_hash,
	uint64_t nonce
);

/**
 * Calculate the seedhash for a given block number
 */
ethash_h256_t ethash_get_seedhash(uint64_t block_number);

#ifdef __cplusplus
}
#endif
