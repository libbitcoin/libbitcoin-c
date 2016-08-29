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
#ifndef LIBBITCOIN_C_UTILITY_BINARY_H
#define LIBBITCOIN_C_UTILITY_BINARY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_binary_t bc_binary_t;

/// Static values
size_t bc_binary_bits_per_block();

/// Static methods
size_t bc_binary_blocks_size(size_t bit_size);
bool bc_binary_is_base2(const char* text);

/// Constructors.
bc_binary_t* bc_create_binary();
bc_binary_t* bc_create_binary_copy(const bc_binary_t* other);
bc_binary_t* bc_create_binary_String(const char* bit_string);
bc_binary_t* bc_create_binary_Blocks(size_t size, const uint8_t* blocks);

/// Destructor
void bc_destroy_binary(bc_binary_t* self);

/// Methods
size_t bc_binary_resize(bc_binary_t* self, size_t size);
bool bc_binary_at(const bc_binary_t* self, size_t index);
bc_data_chunk_t* bc_binary_blocks(const bc_binary_t* self);
bc_string_t* bc_binary_encoded(const bc_binary_t* self);

// size in bits
size_t bc_binary_size(const bc_binary_t* self);
void bc_binary_append(bc_binary_t* self, const bc_binary_t* post);
void bc_binary_prepend(bc_binary_t* self, const bc_binary_t* prior);
void bc_binary_shift_left(bc_binary_t* self, size_t distance);
void bc_binary_shift_right(bc_binary_t* self, size_t distance);
bc_binary_t* bc_binary_substring(bc_binary_t* self, size_t first);
bc_binary_t* bc_binary_substring_Length(bc_binary_t* self,
    size_t first, size_t length);

bool bc_binary_is_prefix_of(const bc_binary_t* self,
    const uint8_t* field_begin, const uint8_t* field_end);
bool bc_binary_is_prefix_of_Uint32(const bc_binary_t* self, uint32_t field);
bool bc_binary_is_prefix_of_Binary(const bc_binary_t* self,
    const bc_binary_t* field);

/// Operators.
bool bc_binary_less_than(const bc_binary_t* self, const bc_binary_t* other);
bool bc_binary_equals(const bc_binary_t* self, const bc_binary_t* other);
bool bc_binary_not_equals(const bc_binary_t* self, const bc_binary_t* other);
bc_binary_t* bc_binary_copy(bc_binary_t* self, const bc_binary_t* other);
// Stream operators ignored.

#ifdef __cplusplus
}
#endif

#endif

