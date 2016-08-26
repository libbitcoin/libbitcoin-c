/**
 * Copyright (c) 2011-2016 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * libbitcoin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBBITCOIN_C_BASE_16_H
#define LIBBITCOIN_C_BASE_16_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <bitcoin/bitcoin/c/math/hash.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns true if a character is a hexadecimal digit.
 * The C standard library function `isxdigit` depends on the current locale,
 * and does not necessarily match the base16 encoding.
 */
bool bc_is_base16(const char c);

/**
 * Convert data into a user-readable hex string.
 */
bc_string_t* bc_encode_base16(const bc_data_chunk_t* data);

/**
 * Convert a hex string into bytes.
 * @return false if the input is malformed.
 */
bool bc_decode_base16(bc_data_chunk_t* out, const char* in);

/**
 * Converts a bitcoin_hash to a string.
 * The bitcoin_hash format is like base16, but with the bytes reversed.
 */
bc_string_t* bc_encode_hash(const bc_hash_digest_t* hash);

/**
 * Convert a string into a bitcoin_hash.
 * The bitcoin_hash format is like base16, but with the bytes reversed.
 * @return false if the input is malformed.
 */
bool bc_decode_hash(bc_hash_digest_t* out, const char* in);

/**
 * Convert a hex string literal into a bitcoin_hash.
 * The bitcoin_hash format is like base16, but with the bytes reversed.
 */
bc_hash_digest_t* bc_hash_literal(const char (*string)[65]);

#ifdef __cplusplus
}
#endif

#endif

