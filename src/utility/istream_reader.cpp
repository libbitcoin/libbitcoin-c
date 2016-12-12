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

#include <bitcoin/bitcoin/c/internal/error.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>

extern "C" {

// Destructor
void bc_destroy_istream_reader(bc_istream_reader_t* self)
{
    delete self->obj;
    delete self;
}

/// Context
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
void bc_isteam_reader__invalidate(bc_istream_reader_t* self)
{
    self->obj->invalidate();
}

/// Read hashes.
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

/// Read big endian integers.
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
uint64_t bc_istream_reader__read_variable_big_endian(
    bc_istream_reader_t* self)
{
    return self->obj->read_variable_big_endian();
}
size_t bc_read_size_big_endian(bc_istream_reader_t* self)
{
    return self->obj->read_size_big_endian();
}

/// Read little endian integers.
bc_error_code_t* bc_read_error_code(bc_istream_reader_t* self)
{
    return new bc_error_code_t{ new std::error_code(
        self->obj->read_error_code()) };
}
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
uint64_t bc_istream_reader__read_variable_little_endian(
    bc_istream_reader_t* self)
{
    return self->obj->read_variable_little_endian();
}
size_t bc_read_size_little_endian(bc_istream_reader_t* self)
{
    return self->obj->read_size_little_endian();
}

/// Read one byte.
uint8_t bc_istream_reader__read_byte(bc_istream_reader_t* self)
{
    return self->obj->read_byte();
}

/// Read all remaining bytes.
bc_data_chunk_t* bc_istream_reader__read_bytes_Eof(
    bc_istream_reader_t* self)
{
    return bc_create_data_chunk_Internal(self->obj->read_bytes());
}

/// Read required size buffer.
bc_data_chunk_t* bc_istream_reader__read_bytes(
    bc_istream_reader_t* self, size_t size)
{
    return bc_create_data_chunk_Internal(self->obj->read_bytes(size));
}

/// Read variable length string.
bc_string_t* bc_istream_reader__read_string(
    bc_istream_reader_t* self)
{
    return bc_create_string_StdString(self->obj->read_string());
}

/// Read required size string and trim nulls.
bc_string_t* bc_istream_reader__read_string_Size(
    bc_istream_reader_t* self, size_t size)
{
    return bc_create_string_StdString(self->obj->read_string(size));
}

/// Advance iterator without reading.
void bc_istream_reader__skip(bc_istream_reader_t* self, size_t size)
{
    self->obj->skip(size);
}

} // extern C

