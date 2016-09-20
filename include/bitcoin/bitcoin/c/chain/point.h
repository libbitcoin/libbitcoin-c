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
#ifndef LIBBITCOIN_C_CHAIN_POINT_H
#define LIBBITCOIN_C_CHAIN_POINT_H

#include <bitcoin/bitcoin/c/math/hash.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>
#include <bitcoin/bitcoin/c/utility/vector.h>

#ifdef __cplusplus
extern "C" {
#endif

// Immutable vector of uint32_t
typedef struct bc_point_indexes_t bc_point_indexes_t;
// Constructor
bc_point_indexes_t* bc_create_point_indexes(
    const uint32_t* indexes, size_t size);
// Destructor
void bc_destroy_point_indexes(bc_point_indexes_t* self);
// Member functions
size_t bc_point_indexes_size(const bc_point_indexes_t* self);
uint32_t bc_point_indexes_at(const bc_point_indexes_t* self, size_t pos);

typedef struct bc_point_t bc_point_t;
BC_DECLARE_VECTOR(chain_point_list, bc_point_t);
// Static functions
bc_point_t* bc_point_factory_from_data(const bc_data_chunk_t* data);
uint64_t bc_point_satoshi_fixed_size();
// Constructor
bc_point_t* bc_create_point();
// Destructor
void bc_destroy_point(bc_point_t* self);
// Member functions
uint64_t bc_point_checksum(const bc_point_t* self);
bool bc_point_is_null(const bc_point_t* self);
bool bc_point_from_data(bc_point_t* self, const bc_data_chunk_t* data);
bc_data_chunk_t* bc_point_to_data(const bc_point_t* self);
bc_string_t* bc_point_to_string(const bc_point_t* self);
bool bc_point_is_valid(const bc_point_t* self);
void bc_point_reset(bc_point_t* self);
uint64_t bc_point_serialized_size(const bc_point_t* self);
// Member variables
bc_hash_digest_t* bc_point_hash(const bc_point_t* self);
void bc_point_set_hash(bc_point_t* self, const bc_hash_digest_t* hash);
uint32_t bc_point_index(const bc_point_t* self);
void bc_point_set_index(bc_point_t* self, uint32_t index);
// Operators
bool bc_point_equals(const bc_point_t* left, const bc_point_t* right);
bool bc_point_not_equals(const bc_point_t* left, const bc_point_t* right);

typedef bc_point_t bc_input_point_t;
typedef bc_point_t bc_output_point_t;

typedef struct bc_points_info_t bc_points_info_t;
bc_points_info_t* bc_create_points_info();
void bc_destroy_points_info(bc_points_info_t* self);
bc_chain_point_list_t* bc_points_info_points(const bc_points_info_t* self);
void bc_points_info_set_points(bc_points_info_t* self,
    const bc_chain_point_list_t* points);
uint64_t bc_points_info_change(const bc_points_info_t* self);
void bc_points_info_set_change(bc_points_info_t* self, uint64_t change);

#ifdef __cplusplus
}
#endif

#endif

