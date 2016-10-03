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
#include <bitcoin/bitcoin/c/utility/istream_reader.h>
#include <bitcoin/bitcoin/c/internal/utility/istream_reader.hpp>

#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>

extern "C" {

bool bc_istream_reader__is_valid(const bc_istream_reader_t* self)
{
    return static_cast<bool>(self->obj);
}
bool bc_istream_reader__is_not_valid(const bc_istream_reader_t* self)
{
    return !(*self->obj);
}

bool bc_isteam_reader__is_exhausted(const bc_istream_reader_t* self)
{
    return self->obj->is_exhausted();
}
uint8_t bc_istream_reader__read_byte(bc_istream_reader_t* self)
{
    return self->obj->read_byte();
}
bc_data_chunk_t* bc_istream_reader__read_data_DataChunk(
    bc_istream_reader_t* self, size_t size)
{
    return bc_create_data_chunk_Internal(self->obj->read_data(size));
}
size_t bc_istream_reader__read_data(
    bc_istream_reader_t* self, uint8_t* data, size_t size)
{
    return self->obj->read_data(data, size);
}
bc_data_chunk_t* bc_istream_reader__read_data_to_eof(
    bc_istream_reader_t* self)
{
    return bc_create_data_chunk_Internal(self->obj->read_data_to_eof());
}
bc_hash_digest_t* bc_istream_reader__read_hash(
    bc_istream_reader_t* self)
{
    return bc_create_hash_digest_Internal(self->obj->read_hash());
}
bc_short_hash_t* bc_istream_reader__read_short_hash(
    bc_istream_reader_t* self)
{
    return bc_create_short_hash_Internal(self->obj->read_short_hash());
}
bc_mini_hash_t* bc_istream_reader__read_mini_hash(
    bc_istream_reader_t* self)
{
    return bc_create_mini_hash_Internal(self->obj->read_mini_hash());
}

// These read data in little endian format: 
uint16_t bc_istream_reader__read_2_bytes_little_endian(
    bc_istream_reader_t* self)
{
    return self->obj->read_2_bytes_little_endian();
}
uint32_t bc_istream_reader__read_4_bytes_little_endian(
    bc_istream_reader_t* self)
{
    return self->obj->read_4_bytes_little_endian();
}
uint64_t bc_istream_reader__read_8_bytes_little_endian(
    bc_istream_reader_t* self)
{
    return self->obj->read_8_bytes_little_endian();
}
uint64_t bc_istream_reader__read_variable_uint_little_endian(
    bc_istream_reader_t* self)
{
    return self->obj->read_variable_uint_little_endian();
}

// These read data in big endian format:
uint16_t bc_istream_reader__read_2_bytes_big_endian(
    bc_istream_reader_t* self)
{
    return self->obj->read_2_bytes_big_endian();
}
uint32_t bc_istream_reader__read_4_bytes_big_endian(
    bc_istream_reader_t* self)
{
    return self->obj->read_4_bytes_big_endian();
}
uint64_t bc_istream_reader__read_8_bytes_big_endian(
    bc_istream_reader_t* self)
{
    return self->obj->read_8_bytes_big_endian();
}
uint64_t bc_istream_reader__read_variable_uint_big_endian(
    bc_istream_reader_t* self)
{
    return self->obj->read_variable_uint_big_endian();
}

/**
 * Read a fixed size string padded with zeroes.
 */
bc_string_t* bc_istream_reader__read_fixed_string(
    bc_istream_reader_t* self, size_t length)
{
    return bc_create_string_StdString(self->obj->read_fixed_string(length));
}

/**
 * Read a variable length string.
 */
bc_string_t* bc_istream_reader__read_string(
    bc_istream_reader_t* self)
{
    return bc_create_string_StdString(self->obj->read_string());
}

} // extern C

