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

#include <bitcoin/bitcoin/c/chain/point_iterator.h>
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
// Static values
/// This is a sentinel used in .index to indicate no output, e.g. coinbase.
/// This value is serialized and defined by consensus, not implementation.
uint32_t bc_point__null_index();
// Constructors.
//-------------------------------------------------------------------------
bc_point_t* bc_create_point();
bc_point_t* bc_create_point_copy(const bc_point_t* other);
bc_point_t* bc_create_point_Tuple(
    const bc_hash_digest_t* hash, uint32_t index);
// Destructor
void bc_destroy_point(bc_point_t* self);

// Operators
void bc_point__copy(bc_point_t* self, const bc_point_t* other);

bool bc_point__equals(const bc_point_t* left, const bc_point_t* right);
bool bc_point__not_equals(const bc_point_t* left, const bc_point_t* right);

// Deserialization.
//-------------------------------------------------------------------------
bc_point_t* bc_point__factory_from_data(const bc_data_chunk_t* data);
bool bc_point__from_data(bc_point_t* self, const bc_data_chunk_t* data);
bool bc_point__is_valid(const bc_point_t* self);

// Serialization.
//-------------------------------------------------------------------------
bc_data_chunk_t* bc_point__to_data(const bc_point_t* self);

// Iteration.
//-------------------------------------------------------------------------
bc_point_iterator_t* bc_point__begin(const bc_point_t* self);
bc_point_iterator_t* bc_point__end(const bc_point_t* self);

// Properties (size, accessors, cache).
//-------------------------------------------------------------------------
uint64_t bc_point__satoshi_fixed_size();
uint64_t bc_point__serialized_size(const bc_point_t* self);

bc_hash_digest_t* bc_point__hash(const bc_point_t* self);
void bc_point__set_hash(bc_point_t* self, const bc_hash_digest_t* hash);

uint32_t bc_point__index(const bc_point_t* self);
void bc_point__set_index(bc_point_t* self, uint32_t index);

// Utilities.
//-------------------------------------------------------------------------
uint64_t bc_point__checksum(const bc_point_t* self);

// Validation.
//-------------------------------------------------------------------------
bool bc_point__is_null(const bc_point_t* self);

#ifdef __cplusplus
}
#endif

#endif

