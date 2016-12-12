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
#include <bitcoin/bitcoin/c/machine/operation.h>
#include <bitcoin/bitcoin/c/internal/machine/operation.hpp>

#include <bitcoin/bitcoin/c/internal/machine/opcode.hpp>
#include <bitcoin/bitcoin/c/internal/math/elliptic_curve.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>
#include <bitcoin/bitcoin/c/internal/utility/vector.hpp>

BC_IMPLEMENT_VECTOR(operation_list, bc_operation_t, bc_destroy_operation,
    libbitcoin::machine::operation::list);

extern "C" {

// Constructors.
//-------------------------------------------------------------------------
bc_operation_t* bc_create_operation()
{
    return new bc_operation_t{ new libbitcoin::machine::operation };
}
bc_operation_t* bc_create_operation_copy(const bc_operation_t* other)
{
    return new bc_operation_t{ new libbitcoin::machine::operation(
        *other->obj) };
}
bc_operation_t* bc_create_operation_Data(const bc_data_chunk_t* uncoded)
{
    return new bc_operation_t{ new libbitcoin::machine::operation(
        *uncoded->obj) };
}
bc_operation_t* bc_create_operation_Data_nominimal(
    const bc_data_chunk_t* uncoded)
{
    return new bc_operation_t{ new libbitcoin::machine::operation(
        *uncoded->obj, false) };
}
bc_operation_t* bc_create_operation_Opcode(bc_opcode_t code)
{
    return new bc_operation_t{ new libbitcoin::machine::operation(
        bc_opcode_from_ctype(code)) };
}

// Destructor.
//-------------------------------------------------------------------------
void bc_destroy_operation(bc_operation_t* self)
{
    delete self->obj;
    delete self;
}

// Operators.
//-------------------------------------------------------------------------
void bc_operation__copy(bc_operation_t* self, const bc_operation_t* other)
{
    *self->obj = *other->obj;
}

bool bc_operation__equals(
    const bc_operation_t* self, const bc_operation_t* other)
{
    return *self->obj == *other->obj;
}
bool bc_operation__not_equals(
    const bc_operation_t* self, const bc_operation_t* other)
{
    return *self->obj != *other->obj;
}

// Deserialization.
//-------------------------------------------------------------------------
bc_operation_t* bc_operation__factory_from_data(const bc_data_chunk_t* encoded)
{
    return new bc_operation_t{ new libbitcoin::machine::operation(
        libbitcoin::machine::operation::factory_from_data(
            *encoded->obj)) };
}

bool bc_operation__from_data(bc_operation_t* self,
    const bc_data_chunk_t* encoded)
{
    return self->obj->from_data(*encoded->obj);
}

bool bc_operation__from_string(bc_operation_t* self, const char* mnemonic)
{
    return self->obj->from_string(mnemonic);
}

bool bc_operation__is_valid(const bc_operation_t* self)
{
    return self->obj->is_valid();
}

// Serialization.
//-------------------------------------------------------------------------
bc_data_chunk_t* bc_operation__to_data(const bc_operation_t* self)
{
    return bc_create_data_chunk_Internal(self->obj->to_data());
}

bc_string_t* bc_operation__to_string(
    const bc_operation_t* self, uint32_t active_forks)
{
    return bc_create_string_StdString(self->obj->to_string(active_forks));
}

// Properties (size, accessors, cache).
//-------------------------------------------------------------------------

size_t bc_operation__serialized_size(const bc_operation_t* self)
{
    return self->obj->serialized_size();
}

/// Get the op code [0..255], if is_valid is consistent with data.
bc_opcode_t bc_operation__code(const bc_operation_t* self)
{
    return bc_opcode_to_ctype(self->obj->code());
}

/// Get the data, empty if not a push code or if invalid.
bc_data_chunk_t* bc_operation__data(const bc_operation_t* self)
{
    return bc_create_data_chunk_Internal(self->obj->data());
}

// Utilities.
//-------------------------------------------------------------------------

/// Compute the minimal data opcode based on size alone.
bc_opcode_t bc_operation__opcode_from_size(size_t size)
{
    return bc_opcode_to_ctype(
        libbitcoin::machine::operation::opcode_from_size(size));
}

/// Compute the minimal data opcode for a given chunk of data.
/// If a numeric code is used then corresponding data must be set to empty.
bc_opcode_t bc_operation__opcode_from_data(const bc_data_chunk_t* data)
{
    return bc_opcode_to_ctype(
        libbitcoin::machine::operation::opcode_from_data(*data->obj));
}

/// Convert the [1..16] value to the corresponding opcode (or undefined).
bc_opcode_t bc_operation__opcode_from_positive(uint8_t value)
{
    return bc_opcode_to_ctype(
        libbitcoin::machine::operation::opcode_from_positive(value));
}

/// Convert the opcode to the corresponding [1..16] value (or undefined).
uint8_t bc_operation__opcode_to_positive(bc_opcode_t code)
{
    return libbitcoin::machine::operation::opcode_to_positive(
        bc_opcode_from_ctype(code));
}

/// Categories of opcodes.
bool bc_operation__is_push_Static(bc_opcode_t code)
{
    return libbitcoin::machine::operation::is_push(
        bc_opcode_from_ctype(code));
}
bool bc_operation__is_counted_Static(bc_opcode_t code)
{
    return libbitcoin::machine::operation::is_counted(
        bc_opcode_from_ctype(code));
}
bool bc_operation__is_numeric_Static(bc_opcode_t code)
{
    return libbitcoin::machine::operation::is_numeric(
        bc_opcode_from_ctype(code));
}
bool bc_operation__is_positive_Static(bc_opcode_t code)
{
    return libbitcoin::machine::operation::is_positive(
        bc_opcode_from_ctype(code));
}
bool bc_operation__is_disabled_Static(bc_opcode_t code)
{
    return libbitcoin::machine::operation::is_disabled(
        bc_opcode_from_ctype(code));
}
bool bc_operation__is_conditional_Static(bc_opcode_t code)
{
    return libbitcoin::machine::operation::is_conditional(
        bc_opcode_from_ctype(code));
}
bool bc_operation__is_relaxed_push_Static(bc_opcode_t code)
{
    return libbitcoin::machine::operation::is_relaxed_push(
        bc_opcode_from_ctype(code));
}

// Validation.
//-------------------------------------------------------------------------

/// Categories of opcodes.
bool bc_operation__is_push(const bc_operation_t* self)
{
    return self->obj->is_push();
}
bool bc_operation__is_counted(const bc_operation_t* self)
{
    return self->obj->is_counted();
}
bool bc_operation__is_positive(const bc_operation_t* self)
{
    return self->obj->is_positive();
}
bool bc_operation__is_disabled(const bc_operation_t* self)
{
    return self->obj->is_disabled();
}
bool bc_operation__is_conditional(const bc_operation_t* self)
{
    return self->obj->is_conditional();
}
bool bc_operation__is_relaxed_push(const bc_operation_t* self)
{
    return self->obj->is_relaxed_push();
}

/// Validate the data against the code.
bool bc_operation__is_oversized(const bc_operation_t* self)
{
    return self->obj->is_oversized();
}

} // extern C

