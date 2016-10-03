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
#ifndef LIBBITCOIN_C_UTILITY_OSTREAM_WRITER_H
#define LIBBITCOIN_C_UTILITY_OSTREAM_WRITER_H

#include <stddef.h>
#include <stdint.h>
#include <bitcoin/bitcoin/c/math/hash.h>
#include <bitcoin/bitcoin/c/utility/binary.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_ostream_writer_t bc_ostream_writer_t;

// Constructor

// Destructor
void bc_destroy_ostream_writer(bc_ostream_writer_t* self);

bool bc_ostream_writer__is_valid(const bc_ostream_writer_t* self);
bool bc_ostream_writer__is_not_valid(const bc_ostream_writer_t* self);

void bc_ostream_writer__write_byte(bc_ostream_writer_t* self, uint8_t value);
void bc_ostream_writer__write_data_DataChunk(
    bc_ostream_writer_t* self, const bc_data_chunk_t* data);
void bc_ostream_writer__write_data(
    bc_ostream_writer_t* self, const uint8_t* data, size_t size);
void bc_ostream_writer__write_hash(
    bc_ostream_writer_t* self, const bc_hash_digest_t* value);
void bc_ostream_writer__write_short_hash(
    bc_ostream_writer_t* self, const bc_short_hash_t* value);
void bc_ostream_writer__write_mini_hash(
    bc_ostream_writer_t* self, const bc_mini_hash_t* value);

// These write data in little endian format: 
void bc_ostream_writer__write_2_bytes_little_endian(
    bc_ostream_writer_t* self, uint16_t value);
void bc_ostream_writer__write_4_bytes_little_endian(
    bc_ostream_writer_t* self, uint32_t value);
void bc_ostream_writer__write_8_bytes_little_endian(
    bc_ostream_writer_t* self, uint64_t value);
void bc_ostream_writer__write_variable_uint_little_endian(
    bc_ostream_writer_t* self, uint64_t value);

// These write data in big endian format:
void bc_ostream_writer__write_2_bytes_big_endian(
    bc_ostream_writer_t* self, uint16_t value);
void bc_ostream_writer__write_4_bytes_big_endian(
    bc_ostream_writer_t* self, uint32_t value);
void bc_ostream_writer__write_8_bytes_big_endian(
    bc_ostream_writer_t* self, uint64_t value);
void bc_ostream_writer__write_variable_uint_big_endian(
    bc_ostream_writer_t* self, uint64_t value);

/**
 * Write a fixed size string padded with zeroes.
 */
void bc_ostream_writer__write_fixed_string(
    bc_ostream_writer_t* self, const char* value, size_t size);

/**
 * Write a variable length string.
 */
void bc_ostream_writer__write_string(
    bc_ostream_writer_t* self, const char* value);

#ifdef __cplusplus
}
#endif

#endif

