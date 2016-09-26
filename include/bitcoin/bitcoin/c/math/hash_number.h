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
#ifndef LIBBITCOIN_C_MATH_HASH_NUMBER_H
#define LIBBITCOIN_C_MATH_HASH_NUMBER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <bitcoin/bitcoin/c/math/hash.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Represents a target hash or proof of work sum.
 * Used for block proof of works to calculate whether they reach
 * a certain target or which chain is longest.
 */
typedef struct bc_hash_number_t bc_hash_number_t;
/// Constructors.
bc_hash_number_t* bc_create_hash_number();
bc_hash_number_t* bc_create_hash_number_Value(uint64_t value);
bc_hash_number_t* bc_create_hash_number_Hash(const bc_hash_digest_t* value);
/// Destructors
void bc_destroy_hash_number(bc_hash_number_t* self);

/// Properties.
bc_hash_digest_t* bc_hash_number__hash(const bc_hash_number_t* self);
bool bc_hash_number__set_compact(bc_hash_number_t* self, uint32_t compact);
uint32_t bc_hash_number__compact(const bc_hash_number_t* self);

/// Copy Operators.
bc_hash_number_t* bc_hash_number__negate(const bc_hash_number_t* self);

/// Change Operators.
void bc_hash_number__shift_left(bc_hash_number_t* self, uint32_t shift);
void bc_hash_number__multiply(bc_hash_number_t* self, uint32_t value);
void bc_hash_number__divide(bc_hash_number_t* self, uint32_t value);
void bc_hash_number__divide_HashNumber(bc_hash_number_t* self,
    const bc_hash_number_t* value);
void bc_hash_number__add(bc_hash_number_t* self,
    const bc_hash_number_t* value);

/// Comparison Operators.
bool bc_hash_number__equals(const bc_hash_number_t* self, uint64_t value);
bool bc_hash_number__not_equals(const bc_hash_number_t* self, uint64_t value);
bool bc_hash_number__greater_than(const bc_hash_number_t* self,
    const bc_hash_number_t* value);
bool bc_hash_number__less_than(const bc_hash_number_t* self,
    const bc_hash_number_t* value);
bool bc_hash_number__greater_than_or_equals(const bc_hash_number_t* self,
    const bc_hash_number_t* value);
bool bc_hash_number__less_than_or_equals(const bc_hash_number_t* self,
    const bc_hash_number_t* value);

#ifdef __cplusplus
}
#endif

#endif

