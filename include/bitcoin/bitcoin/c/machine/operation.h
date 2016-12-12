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
#ifndef LIBBITCOIN_C_MACHINE_OPERATION_H
#define LIBBITCOIN_C_MACHINE_OPERATION_H

#include <bitcoin/bitcoin/c/machine/opcode.h>
#include <bitcoin/bitcoin/c/math/elliptic_curve.h>
#include <bitcoin/bitcoin/c/math/hash.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>
#include <bitcoin/bitcoin/c/utility/vector.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_operation_t bc_operation_t;

BC_DECLARE_VECTOR(operation_list, bc_operation_t);

// Constructors.
//-------------------------------------------------------------------------
bc_operation_t* bc_create_operation();
bc_operation_t* bc_create_operation_copy(const bc_operation_t* other);
bc_operation_t* bc_create_operation_Data(const bc_data_chunk_t* uncoded);
bc_operation_t* bc_create_operation_Data_nominimal(
    const bc_data_chunk_t* uncoded);
bc_operation_t* bc_create_operation_Opcode(bc_opcode_t code);

// Destructor.
//-------------------------------------------------------------------------
void bc_destroy_operation(bc_operation_t* self);

// Operators.
//-------------------------------------------------------------------------
void bc_operation__copy(bc_operation_t* self, const bc_operation_t* other);

bool bc_operation__equals(
    const bc_operation_t* self, const bc_operation_t* other);
bool bc_operation__not_equals(
    const bc_operation_t* self, const bc_operation_t* other);

// Deserialization.
//-------------------------------------------------------------------------
bc_operation_t* bc_operation__factory_from_data(const bc_data_chunk_t* encoded);

bool bc_operation__from_data(bc_operation_t* self,
    const bc_data_chunk_t* encoded);

bool bc_operation__from_string(bc_operation_t* self, const char* mnemonic);

bool bc_operation__is_valid(const bc_operation_t* self);

// Serialization.
//-------------------------------------------------------------------------
bc_data_chunk_t* bc_operation__to_data(const bc_operation_t* self);

bc_string_t* bc_operation__to_string(
    const bc_operation_t* self, uint32_t active_forks);

// Properties (size, accessors, cache).
//-------------------------------------------------------------------------

size_t bc_operation__serialized_size(const bc_operation_t* self);

/// Get the op code [0..255], if is_valid is consistent with data.
bc_opcode_t bc_operation__code(const bc_operation_t* self);

/// Get the data, empty if not a push code or if invalid.
bc_data_chunk_t* bc_operation__data(const bc_operation_t* self);

// Utilities.
//-------------------------------------------------------------------------

/// Compute the minimal data opcode based on size alone.
bc_opcode_t bc_operation__opcode_from_size(size_t size);

/// Compute the minimal data opcode for a given chunk of data.
/// If a numeric code is used then corresponding data must be set to empty.
bc_opcode_t bc_operation__opcode_from_data(const bc_data_chunk_t* data);

/// Convert the [1..16] value to the corresponding opcode (or undefined).
bc_opcode_t bc_operation__opcode_from_positive(uint8_t value);

/// Convert the opcode to the corresponding [1..16] value (or undefined).
uint8_t bc_operation__opcode_to_positive(bc_opcode_t code);

/// Categories of opcodes.
bool bc_operation__is_push_Static(bc_opcode_t code);
bool bc_operation__is_counted_Static(bc_opcode_t code);
bool bc_operation__is_numeric_Static(bc_opcode_t code);
bool bc_operation__is_positive_Static(bc_opcode_t code);
bool bc_operation__is_disabled_Static(bc_opcode_t code);
bool bc_operation__is_conditional_Static(bc_opcode_t code);
bool bc_operation__is_relaxed_push_Static(bc_opcode_t code);

// Validation.
//-------------------------------------------------------------------------

/// Categories of opcodes.
bool bc_operation__is_push(const bc_operation_t* self);
bool bc_operation__is_counted(const bc_operation_t* self);
bool bc_operation__is_positive(const bc_operation_t* self);
bool bc_operation__is_disabled(const bc_operation_t* self);
bool bc_operation__is_conditional(const bc_operation_t* self);
bool bc_operation__is_relaxed_push(const bc_operation_t* self);

/// Validate the data against the code.
bool bc_operation__is_oversized(const bc_operation_t* self);

#ifdef __cplusplus
}
#endif

#endif

