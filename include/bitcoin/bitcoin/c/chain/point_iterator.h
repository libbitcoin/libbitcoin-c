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

#include <bitcoin/bitcoin/c/chain/point.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_point_iterator_t bc_point_iterator_t;

// Constructors
bc_point_iterator_t* bc_create_point_iterator(const bc_point_t* value);
bc_point_iterator_t* bc_create_point_iterator_End(
    const bc_point_t* value, bool end);
bc_point_iterator_t* bc_create_point_iterator_Offset(
    const bc_point_t* value, uint8_t offset);
// Destructor
void bc_destroy_point_iterator(bc_point_iterator_t* self);

// Operators
bool bc_point_iterator_is_valid(const bc_point_iterator_t* self);
uint8_t bc_point_iterator_access(const bc_point_iterator_t* self);
bool bc_point_iterator_equals(
    const bc_point_iterator_t* self, const bc_point_iterator_t* other);
bool bc_point_iterator_not_equals(
    const bc_point_iterator_t* self, const bc_point_iterator_t* other);
void bc_point_iterator_increment(bc_point_iterator_t* self);
void bc_point_iterator_decrement(bc_point_iterator_t* self);

#ifdef __cplusplus
}
#endif

#endif

