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
#ifndef LIBBITCOIN_C_CHAIN_POINT_ITERATOR_H
#define LIBBITCOIN_C_CHAIN_POINT_ITERATOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_point_t bc_point_t;

typedef struct bc_point_iterator_t bc_point_iterator_t;

// Constructors
bc_point_iterator_t* bc_create_point_iterator_copy(
    const bc_point_iterator_t* other);
bc_point_iterator_t* bc_create_point_iterator_Value(
    const bc_point_t* value);
bc_point_iterator_t* bc_create_point_iterator_Value_Index(
    const bc_point_t* value, unsigned index);

// Destructor
void bc_destroy_point_iterator(bc_point_iterator_t* self);

// Operators
bool bc_point_iterator__is_valid(const bc_point_iterator_t* self);
uint8_t bc_point_iterator__access(const bc_point_iterator_t* self);
void bc_point_iterator__increment(bc_point_iterator_t* self);
void bc_point_iterator__decrement(bc_point_iterator_t* self);
bool bc_point_iterator__equals(
    const bc_point_iterator_t* self, const bc_point_iterator_t* other);
bool bc_point_iterator__not_equals(
    const bc_point_iterator_t* self, const bc_point_iterator_t* other);

#ifdef __cplusplus
}
#endif

#endif

