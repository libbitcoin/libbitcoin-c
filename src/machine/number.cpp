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
#include <bitcoin/bitcoin/c/machine/number.h>
#include <bitcoin/bitcoin/c/internal/machine/number.hpp>

#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/vector.hpp>

extern "C" {

uint8_t bc_machine_number__negative_1()
{
    return libbitcoin::machine::number::negative_1;
}
uint8_t bc_machine_number__negative_0()
{
    return libbitcoin::machine::number::negative_0;
}
uint8_t bc_machine_number__positive_0()
{
    return libbitcoin::machine::number::positive_0;
}
uint8_t bc_machine_number__positive_1()
{
    return libbitcoin::machine::number::positive_1;
}
uint8_t bc_machine_number__positive_2()
{
    return libbitcoin::machine::number::positive_2;
}
uint8_t bc_machine_number__positive_3()
{
    return libbitcoin::machine::number::positive_3;
}
uint8_t bc_machine_number__positive_4()
{
    return libbitcoin::machine::number::positive_4;
}
uint8_t bc_machine_number__positive_5()
{
    return libbitcoin::machine::number::positive_5;
}
uint8_t bc_machine_number__positive_6()
{
    return libbitcoin::machine::number::positive_6;
}
uint8_t bc_machine_number__positive_7()
{
    return libbitcoin::machine::number::positive_7;
}
uint8_t bc_machine_number__positive_8()
{
    return libbitcoin::machine::number::positive_8;
}
uint8_t bc_machine_number__positive_9()
{
    return libbitcoin::machine::number::positive_9;
}
uint8_t bc_machine_number__positive_10()
{
    return libbitcoin::machine::number::positive_10;
}
uint8_t bc_machine_number__positive_11()
{
    return libbitcoin::machine::number::positive_11;
}
uint8_t bc_machine_number__positive_12()
{
    return libbitcoin::machine::number::positive_12;
}
uint8_t bc_machine_number__positive_13()
{
    return libbitcoin::machine::number::positive_13;
}
uint8_t bc_machine_number__positive_14()
{
    return libbitcoin::machine::number::positive_14;
}
uint8_t bc_machine_number__positive_15()
{
    return libbitcoin::machine::number::positive_15;
}
uint8_t bc_machine_number__positive_16()
{
    return libbitcoin::machine::number::positive_16;
}
uint8_t bc_machine_number__negative_mask()
{
    return libbitcoin::machine::number::negative_mask;
}

/// Construct with zero value.
bc_machine_number_t* bc_create_machine_number()
{
    return new bc_machine_number_t{ new libbitcoin::machine::number };
}

/// Construct with specified value.
bc_machine_number_t* bc_create_machine_number_Value(int64_t value)
{
    return new bc_machine_number_t{ new libbitcoin::machine::number(value) };
}

/// Replace the value derived from a byte vector with LSB first ordering.
bool bc_machine_number__set_data(bc_machine_number_t* self,
    const bc_data_chunk_t* data, size_t max_size)
{
    return self->obj->set_data(*data->obj, max_size);
}

// Properties
//-----------------------------------------------------------------------------

/// Return the value as a byte vector with LSB first ordering.
bc_data_chunk_t* bc_machine_number__data(const bc_machine_number_t* self)
{
    return bc_create_data_chunk_Internal(self->obj->data());
}

/// Return the value bounded by the limits of int32.
int32_t bc_machine_number__int32(const bc_machine_number_t* self)
{
    return self->obj->int32();
}

/// Return the unbounded value.
int64_t bc_machine_number__int64(const bc_machine_number_t* self)
{
    return self->obj->int64();
}

// Stack Helpers
//-----------------------------------------------------------------------------

/// Return value as stack boolean (nonzero is true).
bool bc_machine_number__is_true(const bc_machine_number_t* self)
{
    return self->obj->is_true();
}

/// Return value as stack boolean (zero is false).
bool bc_machine_number__is_false(const bc_machine_number_t* self)
{
    return self->obj->is_false();
}

// Operators
//-----------------------------------------------------------------------------

//************************************************************************
// CONSENSUS: script::number implements consensus critical overflow
// behavior for all operators, specifically [-, +, +=, -=].
//*************************************************************************

bool bc_machine_number__greater_than(
    const bc_machine_number_t* self, int64_t value)
{
    return *self->obj > value;
}
bool bc_machine_number__less_than(
    const bc_machine_number_t* self, int64_t value)
{
    return *self->obj < value;
}
bool bc_machine_number__greater_than_or_equals(
    const bc_machine_number_t* self, int64_t value)
{
    return *self->obj >= value;
}
bool bc_machine_number__less_than_or_equals(
    const bc_machine_number_t* self, int64_t value)
{
    return *self->obj <= value;
}
bool bc_machine_number__equals(
    const bc_machine_number_t* self, int64_t value)
{
    return *self->obj == value;
}
bool bc_machine_number__not_equals(
    const bc_machine_number_t* self, int64_t value)
{
    return *self->obj != value;
}

bool bc_machine_number__greater_than_Number(
    const bc_machine_number_t* self, const bc_machine_number_t* other)
{
    return *self->obj > *other->obj;
}
bool bc_machine_number__less_than_Number(
    const bc_machine_number_t* self, const bc_machine_number_t* other)
{
    return *self->obj < *other->obj;
}
bool bc_machine_number__greater_than_or_equals_Number(
    const bc_machine_number_t* self, const bc_machine_number_t* other)
{
    return *self->obj >= *other->obj;
}
bool bc_machine_number__less_than_or_equals_Number(
    const bc_machine_number_t* self, const bc_machine_number_t* other)
{
    return *self->obj <= *other->obj;
}
bool bc_machine_number__equals_Number(
    const bc_machine_number_t* self, const bc_machine_number_t* other)
{
    return *self->obj == *other->obj;
}
bool bc_machine_number__not_equals_Number(
    const bc_machine_number_t* self, const bc_machine_number_t* other)
{
    return *self->obj != *other->obj;
}

bc_machine_number_t* bc_machine_number__positive(
    const bc_machine_number_t* self)
{
    return new bc_machine_number_t{ new libbitcoin::machine::number(
        +(*self->obj)) };
}
bc_machine_number_t* bc_machine_number__negative(
    const bc_machine_number_t* self)
{
    return new bc_machine_number_t{ new libbitcoin::machine::number(
        -(*self->obj)) };
}
bc_machine_number_t* bc_machine_number__add(
    const bc_machine_number_t* self, int64_t value)
{
    return new bc_machine_number_t{ new libbitcoin::machine::number(
        (*self->obj) + value) };
}
bc_machine_number_t* bc_machine_number__sub(
    const bc_machine_number_t* self, int64_t value)
{
    return new bc_machine_number_t{ new libbitcoin::machine::number(
        (*self->obj) - value) };
}
bc_machine_number_t* bc_machine_number__add_Number(
    const bc_machine_number_t* self, const bc_machine_number_t* other)
{
    return new bc_machine_number_t{ new libbitcoin::machine::number(
        (*self->obj) + (*other->obj)) };
}
bc_machine_number_t* bc_machine_number__sub_Number(
    const bc_machine_number_t* self, const bc_machine_number_t* other)
{
    return new bc_machine_number_t{ new libbitcoin::machine::number(
        (*self->obj) - (*other->obj)) };
}

void bc_machine_number__plus_equals(
    bc_machine_number_t* self, int64_t value)
{
    *self->obj += value;
}
void bc_machine_number__minus_equals(
    bc_machine_number_t* self, int64_t value)
{
    *self->obj -= value;
}
void bc_machine_number__plus_equals_Number(
    bc_machine_number_t* self, const bc_machine_number_t* other)
{
    *self->obj += *other->obj;
}
void bc_machine_number__minus_equals_Number(
    bc_machine_number_t* self, const bc_machine_number_t* other)
{
    *self->obj -= *other->obj;
}

} // extern C

