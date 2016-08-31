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
#ifndef LIBBITCOIN_C_DATA_H
#define LIBBITCOIN_C_DATA_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <bitcoin/bitcoin/c/utility/string.h>
#include <bitcoin/bitcoin/c/utility/vector.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BC_DECLARE_BYTE_ARRAY(typename) \
    size_t bc_##typename##_size(); \
    typedef struct bc_##typename##_t bc_##typename##_t; \
    bc_##typename##_t* bc_create_##typename(); \
    bc_##typename##_t* bc_create_##typename##_Data(const uint8_t* data); \
    bc_##typename##_t* bc_create_##typename##_Base16( \
        const char* encoded_bytes); \
    void bc_destroy_##typename(bc_##typename##_t* self); \
    uint8_t* bc_##typename##_data(bc_##typename##_t* self); \
    const uint8_t* bc_##typename##_cdata(const bc_##typename##_t* self); \
    bc_string_t* bc_##typename##_encode_base16( \
        const bc_##typename##_t* self);

typedef struct bc_data_chunk_t bc_data_chunk_t;
// Empty chunk
bc_data_chunk_t* bc_create_data_chunk();
// Copy constructor
bc_data_chunk_t* bc_create_data_chunk_copy(const bc_data_chunk_t* other);
// Initialize data chunk from uint8_t array
bc_data_chunk_t* bc_create_data_chunk_Array(const uint8_t* data, size_t size);
// Destructor
void bc_destroy_data_chunk(bc_data_chunk_t* self);
// .size()
size_t bc_data_chunk_size(const bc_data_chunk_t* self);
// .empty()
bool bc_data_chunk_empty(const bc_data_chunk_t* self);
// .data()
uint8_t* bc_data_chunk_data(bc_data_chunk_t* self);
// const .data()
const uint8_t* bc_data_chunk_cdata(const bc_data_chunk_t* self);
// extend_data()
void bc_data_chunk_extend_data(
    bc_data_chunk_t* self, const bc_data_chunk_t* other);
// a == b
bool bc_data_chunk_equals(
    const bc_data_chunk_t* self, const bc_data_chunk_t* other);

BC_DECLARE_VECTOR(data_stack, bc_data_chunk_t);

/**
 * Constrain a numeric value within a given range.
 */
size_t bc_range_constrain(size_t value, size_t minimum, size_t maximum);

#ifdef __cplusplus
}
#endif

#endif

