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
#ifndef LIBBITCOIN_C_BASE_58_H
#define LIBBITCOIN_C_BASE_58_H

#include <stdbool.h>
#include <stdint.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>

#ifdef __cplusplus
extern "C" {
#endif

bool bc_is_base58_Char(const char ch);
bool bc_is_base58(const char* text);

/**
 * Encode data as base58.
 * @return the base58 encoded string.
 */
bc_string_t* bc_encode_base58(const bc_data_chunk_t* unencoded);

/**
 * Attempt to decode base58 data.
 * @return false if the input contains non-base58 characters.
 */
bool bc_decode_base58(bc_data_chunk_t* out, const char* in);

#ifdef __cplusplus
}
#endif

#endif

