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
#include <bitcoin/bitcoin/c/utility/binary.h>
#include <bitcoin/bitcoin/c/internal/utility/binary.hpp>

#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>

extern "C" {

/// Static values
size_t bc_binary_bits_per_block()
{
    return libbitcoin::binary::bits_per_block;
}

/// Static methods
size_t bc_binary_blocks_size(size_t bit_size)
{
    return libbitcoin::binary::blocks_size(bit_size);
}
bool bc_binary_is_base2(const char* text)
{
    return libbitcoin::binary::is_base2(text);
}

/// Constructors.
bc_binary_t* bc_create_binary()
{
    return new bc_binary_t{ new libbitcoin::binary };
}
bc_binary_t* bc_create_binary_copy(const bc_binary_t* other)
{
    return new bc_binary_t{ new libbitcoin::binary(*other->obj) };
}
bc_binary_t* bc_create_binary_String(const char* bit_string)
{
    return new bc_binary_t{ new libbitcoin::binary(bit_string) };
}
bc_binary_t* bc_create_binary_Blocks(size_t size, const uint8_t* blocks)
{
    const auto blocks_end = blocks + bc_binary_blocks_size(size);
    const libbitcoin::data_slice slice(blocks, blocks_end);
    return new bc_binary_t{ new libbitcoin::binary(size, slice) };
}

/// Destructor
void bc_destroy_binary(bc_binary_t* self)
{
    delete self->obj;
    delete self;
}

/// Methods
size_t bc_binary_resize(bc_binary_t* self, size_t size)
{
    self->obj->resize(size);
}
bool bc_binary_at(const bc_binary_t* self, size_t index)
{
    return (*self->obj)[index];
}
bc_data_chunk_t* bc_binary_blocks(const bc_binary_t* self)
{
    return bc_create_data_chunk_Internal(self->obj->blocks());
}
bc_string_t* bc_binary_encoded(const bc_binary_t* self)
{
    return bc_create_string_StdString(self->obj->encoded());
}

// size in bits
size_t bc_binary_size(const bc_binary_t* self)
{
    return self->obj->size();
}
void bc_binary_append(bc_binary_t* self, const bc_binary_t* post)
{
    self->obj->append(*post->obj);
}
void bc_binary_prepend(bc_binary_t* self, const bc_binary_t* prior)
{
    self->obj->prepend(*prior->obj);
}
void bc_binary_shift_left(bc_binary_t* self, size_t distance)
{
    self->obj->shift_left(distance);
}
void bc_binary_shift_right(bc_binary_t* self, size_t distance)
{
    self->obj->shift_right(distance);
}
bc_binary_t* bc_binary_substring(bc_binary_t* self, size_t first)
{
    return new bc_binary_t{ new libbitcoin::binary(
        self->obj->substring(first)) };
}
bc_binary_t* bc_binary_substring_Length(bc_binary_t* self,
    size_t first, size_t length)
{
    return new bc_binary_t{ new libbitcoin::binary(
        self->obj->substring(first, length)) };
}

bool bc_binary_is_prefix_of(const bc_binary_t* self,
    const uint8_t* field_begin, const uint8_t* field_end)
{
    const libbitcoin::data_slice slice(field_begin, field_end);
    return self->obj->is_prefix_of(slice);
}
bool bc_binary_is_prefix_of_Uint32(const bc_binary_t* self, uint32_t field)
{
    return self->obj->is_prefix_of(field);
}
bool bc_binary_is_prefix_of_Binary(const bc_binary_t* self,
    const bc_binary_t* field)
{
    return self->obj->is_prefix_of(*field->obj);
}

/// Operators.
bool bc_binary_less_than(const bc_binary_t* self, const bc_binary_t* other)
{
    return *self->obj < *other->obj;
}
bool bc_binary_equals(const bc_binary_t* self, const bc_binary_t* other)
{
    return *self->obj == *other->obj;
}
bool bc_binary_not_equals(const bc_binary_t* self, const bc_binary_t* other)
{
    return *self->obj != *other->obj;
}
bc_binary_t* bc_binary_copy(bc_binary_t* self, const bc_binary_t* other)
{
    *self->obj = *other->obj;
    return self;
}
// Stream operators ignored.

}

