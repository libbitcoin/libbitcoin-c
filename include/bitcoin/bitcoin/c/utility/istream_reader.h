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
#ifndef LIBBITCOIN_C_UTILITY_ISTREAM_READER_H
#define LIBBITCOIN_C_UTILITY_ISTREAM_READER_H

#include <stddef.h>
#include <stdint.h>
#include <bitcoin/bitcoin/c/error.h>
#include <bitcoin/bitcoin/c/math/hash.h>
#include <bitcoin/bitcoin/c/utility/binary.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_istream_reader_t bc_istream_reader_t;

// Constructor

// Destructor
void bc_destroy_istream_reader(bc_istream_reader_t* self);

/// Context
bool bc_istream_reader__is_valid(const bc_istream_reader_t* self);
bool bc_istream_reader__is_not_valid(const bc_istream_reader_t* self);

bool bc_isteam_reader__is_exhausted(const bc_istream_reader_t* self);
void bc_isteam_reader__invalidate(bc_istream_reader_t* self);

/// Read hashes.
bc_hash_digest_t* bc_istream_reader__read_hash(
    bc_istream_reader_t* self);
bc_short_hash_t* bc_istream_reader__read_short_hash(
    bc_istream_reader_t* self);
bc_mini_hash_t* bc_istream_reader__read_mini_hash(
    bc_istream_reader_t* self);

/// Read big endian integers.
uint16_t bc_istream_reader__read_2_bytes_big_endian(
    bc_istream_reader_t* self);
uint32_t bc_istream_reader__read_4_bytes_big_endian(
    bc_istream_reader_t* self);
uint64_t bc_istream_reader__read_8_bytes_big_endian(
    bc_istream_reader_t* self);
uint64_t bc_istream_reader__read_variable_big_endian(
    bc_istream_reader_t* self);
size_t bc_read_size_big_endian(bc_istream_reader_t* self);

/// Read little endian integers.
bc_error_code_t* bc_read_error_code(bc_istream_reader_t* self);
uint16_t bc_istream_reader__read_2_bytes_little_endian(
    bc_istream_reader_t* self);
uint32_t bc_istream_reader__read_4_bytes_little_endian(
    bc_istream_reader_t* self);
uint64_t bc_istream_reader__read_8_bytes_little_endian(
    bc_istream_reader_t* self);
uint64_t bc_istream_reader__read_variable_little_endian(
    bc_istream_reader_t* self);
size_t bc_read_size_little_endian(bc_istream_reader_t* self);

/// Read one byte.
uint8_t bc_istream_reader__read_byte(bc_istream_reader_t* self);

/// Read all remaining bytes.
bc_data_chunk_t* bc_istream_reader__read_bytes_Eof(
    bc_istream_reader_t* self);

/// Read required size buffer.
bc_data_chunk_t* bc_istream_reader__read_bytes(
    bc_istream_reader_t* self, size_t size);

/// Read variable length string.
bc_string_t* bc_istream_reader__read_string(
    bc_istream_reader_t* self);

/// Read required size string and trim nulls.
bc_string_t* bc_istream_reader__read_string_Size(
    bc_istream_reader_t* self, size_t size);

/// Advance iterator without reading.
void bc_istream_reader__skip(bc_istream_reader_t* self, size_t size);

#ifdef __cplusplus
}
#endif

#endif

