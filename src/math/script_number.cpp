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
#include <bitcoin/bitcoin/c/math/script_number.h>
#include <bitcoin/bitcoin/c/internal/math/script_number.hpp>

#include <bitcoin/bitcoin/math/script_number.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>

extern "C" {

bc_script_number_t* bc_create_script_number_default()
{
    return new bc_script_number_t{ new libbitcoin::script_number };
}
bc_script_number_t* bc_create_script_number(int64_t value)
{
    return new bc_script_number_t{ new libbitcoin::script_number(value) };
}

void bc_destroy_script_number(bc_script_number_t* self)
{
    delete self->obj;
    delete self;
}

bool bc_script_number__set_data(const bc_script_number_t* self,
    const bc_data_chunk_t* data, uint8_t max_size)
{
    return self->obj->set_data(*data->obj, max_size);
}

bc_data_chunk_t* bc_script_number__data(const bc_script_number_t* self)
{
    return bc_create_data_chunk_Internal(self->obj->data());
}
int32_t bc_script_number__int32(const bc_script_number_t* self)
{
    return self->obj->int32();
}
int64_t bc_script_number__int64(const bc_script_number_t* self)
{
    return self->obj->int64();
}

// Arithmetic with a number.
bc_script_number_t* bc_script_number__add(
    const bc_script_number_t* self, int64_t value)
{
    return new bc_script_number_t{ new libbitcoin::script_number(
        *self->obj + value) };
}
bc_script_number_t* bc_script_number__subtract(
    const bc_script_number_t* self, int64_t value)
{
    return new bc_script_number_t{ new libbitcoin::script_number(
        *self->obj - value) };
}

// Arithmetic with another script_number.
bc_script_number_t* bc_script_number__add_ScriptNumber(
    const bc_script_number_t* self, const bc_script_number_t* other)
{
    return new bc_script_number_t{ new libbitcoin::script_number(
        *self->obj + *other->obj) };
}
bc_script_number_t* bc_script_number__subtract_ScriptNumber(
    const bc_script_number_t* self, const bc_script_number_t* other)
{
    return new bc_script_number_t{ new libbitcoin::script_number(
        *self->obj - *other->obj) };
}

// -script_number
bc_script_number_t* bc_script_number__negate(const bc_script_number_t* self)
{
    return new bc_script_number_t{ new libbitcoin::script_number(
        -*self->obj) };
}

// Comparison operators with a number.
bool bc_script_number__equals(
    const bc_script_number_t* self, int64_t value)
{
    return *self->obj == value;
}
bool bc_script_number__not_equals(
    const bc_script_number_t* self, int64_t value)
{
    return *self->obj != value;
}
bool bc_script_number__less_than_or_equals(
    const bc_script_number_t* self, int64_t value)
{
    return *self->obj <= value;
}
bool bc_script_number__less_than(
    const bc_script_number_t* self, int64_t value)
{
    return *self->obj < value;
}
bool bc_script_number__greater_than_or_equals(
    const bc_script_number_t* self, int64_t value)
{
    return *self->obj >= value;
}
bool bc_script_number__greater_than(
    const bc_script_number_t* self, int64_t value)
{
    return *self->obj > value;
}

// Comparison operators with another script_number.
bool bc_script_number__equals_ScriptNumber(
    const bc_script_number_t* self, const bc_script_number_t* other)
{
    return *self->obj == *other->obj;
}
bool bc_script_number__not_equals_ScriptNumber(
    const bc_script_number_t* self, const bc_script_number_t* other)
{
    return *self->obj != *other->obj;
}
bool bc_script_number__less_than_or_equals_ScriptNumber(
    const bc_script_number_t* self, const bc_script_number_t* other)
{
    return *self->obj <= *other->obj;
}
bool bc_script_number__less_than_ScriptNumber(
    const bc_script_number_t* self, const bc_script_number_t* other)
{
    return *self->obj < *other->obj;
}
bool bc_script_number__greater_than_or_equals_ScriptNumber(
    const bc_script_number_t* self, const bc_script_number_t* other)
{
    return *self->obj >= *other->obj;
}
bool bc_script_number__greater_than_ScriptNumber(
    const bc_script_number_t* self, const bc_script_number_t* other)
{
    return *self->obj > *other->obj;
}

} // extern C

