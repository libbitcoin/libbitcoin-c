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
#include <bitcoin/bitcoin/c/utility/ostream_writer.h>
#include <bitcoin/bitcoin/c/internal/utility/ostream_writer.hpp>

#include <bitcoin/bitcoin/utility/ostream_writer.hpp>
#include <bitcoin/bitcoin/c/internal/error.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>

extern "C" {

// Destructor
void bc_destroy_ostream_writer(bc_ostream_writer_t* self)
{
    delete self->obj;
    delete self;
}

/// Context.
bool bc_ostream_writer__is_valid(const bc_ostream_writer_t* self)
{
    return static_cast<bool>(self->obj);
}
bool bc_ostream_writer__is_not_valid(const bc_ostream_writer_t* self)
{
    return !(*self->obj);
}

/// Write hashes.
void bc_ostream_writer__write_hash(
    bc_ostream_writer_t* self, const bc_hash_digest_t* value)
{
    self->obj->write_hash(*value->obj);
}
void bc_ostream_writer__write_short_hash(
    bc_ostream_writer_t* self, const bc_short_hash_t* value)
{
    self->obj->write_short_hash(*value->obj);
}
void bc_ostream_writer__write_mini_hash(
    bc_ostream_writer_t* self, const bc_mini_hash_t* value)
{
    self->obj->write_mini_hash(*value->obj);
}

/// Write big endian integers.
void bc_ostream_writer__write_2_bytes_big_endian(
    bc_ostream_writer_t* self, uint16_t value)
{
    self->obj->write_2_bytes_big_endian(value);
}
void bc_ostream_writer__write_4_bytes_big_endian(
    bc_ostream_writer_t* self, uint32_t value)
{
    self->obj->write_4_bytes_big_endian(value);
}
void bc_ostream_writer__write_8_bytes_big_endian(
    bc_ostream_writer_t* self, uint64_t value)
{
    self->obj->write_8_bytes_big_endian(value);
}
void bc_ostream_writer__write_variable_big_endian(
    bc_ostream_writer_t* self, uint64_t value)
{
    self->obj->write_variable_big_endian(value);
}
void bc_ostream_writer__write_size_big_endian(
    bc_ostream_writer_t* self, uint64_t value)
{
    self->obj->write_size_big_endian(value);
}

/// Write little endian integers.
void bc_ostream_writer__write_error_code(
    bc_ostream_writer_t* self, bc_error_t ec)
{
    self->obj->write_error_code(bc_error_code_from_ctype(ec));
}
void bc_ostream_writer__write_2_bytes_little_endian(
    bc_ostream_writer_t* self, uint16_t value)
{
    self->obj->write_2_bytes_little_endian(value);
}
void bc_ostream_writer__write_4_bytes_little_endian(
    bc_ostream_writer_t* self, uint32_t value)
{
    self->obj->write_4_bytes_little_endian(value);
}
void bc_ostream_writer__write_8_bytes_little_endian(
    bc_ostream_writer_t* self, uint64_t value)
{
    self->obj->write_8_bytes_little_endian(value);
}
void bc_ostream_writer__write_variable_little_endian(
    bc_ostream_writer_t* self, uint64_t value)
{
    self->obj->write_variable_little_endian(value);
}
void bc_ostream_writer__write_size_little_endian(
    bc_ostream_writer_t* self, uint64_t value)
{
    self->obj->write_size_little_endian(value);
}

/// Write one byte.
void bc_ostream_writer__write_byte(bc_ostream_writer_t* self, uint8_t value)
{
    self->obj->write_byte(value);
}

/// Write all bytes.
void bc_ostream_writer__write_bytes(
    bc_ostream_writer_t* self, const bc_data_chunk_t* data)
{
    self->obj->write_bytes(*data->obj);
}

/// Write required size buffer.
void bc_ostream_writer__write_bytes_Buffer(
    bc_ostream_writer_t* self, const uint8_t* data, size_t size)
{
    self->obj->write_bytes(data, size);
}

/// Write variable length string.
void bc_ostream_writer__write_string_Size(
    bc_ostream_writer_t* self, const char* value, size_t size)
{
    self->obj->write_string(value, size);
}

/// Write required length string, padded with nulls.
void bc_ostream_writer__write_string(
    bc_ostream_writer_t* self, const char* value)
{
    self->obj->write_string(value);
}

/// Advance iterator without writing.
void bc_ostream_writer__skip(bc_ostream_writer_t* self, size_t size)
{
    self->obj->skip(size);
}

} // extern C

