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
#ifndef LIBBITCOIN_C_CHAIN_POINT_VALUE_H
#define LIBBITCOIN_C_CHAIN_POINT_VALUE_H

#include <bitcoin/bitcoin/c/chain/point.h>
#include <bitcoin/bitcoin/c/utility/vector.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_point_value_t bc_point_value_t;
BC_DECLARE_VECTOR(point_value_list, bc_point_value_t);
// Constructor
bc_point_value_t* bc_create_point_value();
bc_point_value_t* bc_create_point_value_copy(const bc_point_value_t* other);
bc_point_value_t* bc_create_point_value_Point(
    const bc_point_t* instance, uint64_t value);
// Destructor
void bc_destroy_point_value(bc_point_value_t* self);

void bc_point_value__copy(
    bc_point_value_t* self, const bc_point_value_t* other);

bool bc_point_value__equals(
    bc_point_value_t* self, const bc_point_value_t* other);
bool bc_point_value__not_equals(
    bc_point_value_t* self, const bc_point_value_t* other);

uint64_t bc_point_value__value(const bc_point_value_t* other);
void bc_point_value__set_value(bc_point_value_t* other, uint64_t value);

bc_point_t* bc_point_value__Base(bc_point_value_t* self);

#ifdef __cplusplus
}
#endif

#endif


