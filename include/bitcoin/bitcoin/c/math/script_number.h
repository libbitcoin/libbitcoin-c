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
#ifndef LIBBITCOIN_C_MATH_SCRIPT_NUMBER_H
#define LIBBITCOIN_C_MATH_SCRIPT_NUMBER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <bitcoin/bitcoin/c/utility/data.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t bc_max_script_number_size();
size_t bc_cltv_max_script_number_size();

/**
 * Numeric opcodes (OP_1ADD, etc) are restricted to operating on
 * 4-byte integers. The semantics are subtle, though: operands must be
 * in the range [-2^31 +1...2^31 -1], but results may overflow (and are
 * valid as long as they are not used in a subsequent numeric operation).
 *
 * script_number enforces those semantics by storing results as
 * an int64 and allowing out-of-range values to be returned as a vector of
 * bytes but throwing an exception if arithmetic is done or the result is
 * interpreted as an integer.
 */
typedef struct bc_script_number_t bc_script_number_t;

bc_script_number_t* bc_create_script_number(int64_t value);

/// Construct with zero value, may call set_data() after.
bc_script_number_t* bc_create_script_number_default();
/// Set the value from a byte vector with LSB first ordering.
bool bc_script_number_set_data(const bc_script_number_t* self,
    const bc_data_chunk_t* data, uint8_t max_size);

bc_data_chunk_t* bc_script_number_data(const bc_script_number_t* self);
int32_t bc_script_number_int32(const bc_script_number_t* self);
int64_t bc_script_number_int64(const bc_script_number_t* self);

void bc_destroy_script_number(bc_script_number_t* self);

// Arithmetic with a number.
bc_script_number_t* bc_script_number_add(
    const bc_script_number_t* self, int64_t value);
bc_script_number_t* bc_script_number_subtract(
    const bc_script_number_t* self, int64_t value);

// Arithmetic with another script_number.
bc_script_number_t* bc_script_number_add_ScriptNumber(
    const bc_script_number_t* self, const bc_script_number_t* other);
bc_script_number_t* bc_script_number_subtract_ScriptNumber(
    const bc_script_number_t* self, const bc_script_number_t* other);

// -script_number
bc_script_number_t* bc_script_number_negate(const bc_script_number_t* self);

// Comparison operators with a number.
bool bc_script_number_equals(
    const bc_script_number_t* self, int64_t value);
bool bc_script_number_not_equals(
    const bc_script_number_t* self, int64_t value);
bool bc_script_number_less_than_or_equals(
    const bc_script_number_t* self, int64_t value);
bool bc_script_number_less_than(
    const bc_script_number_t* self, int64_t value);
bool bc_script_number_greater_than_or_equals(
    const bc_script_number_t* self, int64_t value);
bool bc_script_number_greater_than(
    const bc_script_number_t* self, int64_t value);

// Comparison operators with another script_number.
bool bc_script_number_equals_ScriptNumber(
    const bc_script_number_t* self, const bc_script_number_t* other);
bool bc_script_number_not_equals_ScriptNumber(
    const bc_script_number_t* self, const bc_script_number_t* other);
bool bc_script_number_less_than_or_equals_ScriptNumber(
    const bc_script_number_t* self, const bc_script_number_t* other);
bool bc_script_number_less_than_ScriptNumber(
    const bc_script_number_t* self, const bc_script_number_t* other);
bool bc_script_number_greater_than_or_equals_ScriptNumber(
    const bc_script_number_t* self, const bc_script_number_t* other);
bool bc_script_number_greater_than_ScriptNumber(
    const bc_script_number_t* self, const bc_script_number_t* other);

#ifdef __cplusplus
}
#endif

#endif

