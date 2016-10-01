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
#ifndef LIBBITCOIN_C_CHAIN_OUTPUT_POINT_H
#define LIBBITCOIN_C_CHAIN_OUTPUT_POINT_H

#include <bitcoin/bitcoin/c/chain/output.h>
#include <bitcoin/bitcoin/c/chain/point.h>
#include <bitcoin/bitcoin/c/math/hash.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_output_point_t bc_output_point_t;
/// Static values
/// This is a sentinel used in .height to indicate not coinbase.
uint64_t bc_output_point__not_coinbase();

/// Constructors
bc_output_point_t* bc_create_output_point();
bc_output_point_t* bc_create_output_point_copy(const bc_output_point_t* other);
bc_output_point_t* bc_create_output_point_Point(const bc_point_t* value);
bc_output_point_t* bc_create_output_point_Tuple(
    const bc_hash_digest_t* hash, uint32_t index);

/// Destructor
void bc_destroy_output_point(bc_output_point_t* self);

/// Operators
bool bc_output_point__equals(const bc_output_point_t* self,
    const bc_output_point_t* other);
bool bc_output_point__not_equals(const bc_output_point_t* self,
    const bc_output_point_t* other);

bc_point_t* bc_output_point__to_point(bc_output_point_t* self);

/// Methods
void bc_output_point__reset(bc_output_point_t* self);

/// Determine if the previous output cache is populated.
bool bc_output_point__is_cached(const bc_output_point_t* self);

/// Using .height and the given target height, determine spend maturity.
bool bc_output_point__is_mature(const bc_output_point_t* self,
    size_t target_height);

/// Class members
// These fields do not participate in serialization or comparison.

/// An output is spent if a valid transaction has a valid claim on it.
/// When validating blocks only long chain blocks can have a claim.
/// When validating a memory pool tx another mempool tx can have a claim.
bool bc_output_point__spent(const bc_output_point_t* self);
void bc_output_point__set_spent(bc_output_point_t* self, bool spent);

/// A spend is confirmed if the spender is long chain (not memory pool).
bool bc_output_point__confirmed(const bc_output_point_t* self);
void bc_output_point__set_confirmed(bc_output_point_t* self, bool confirmed);

/// The height of a coinbase output is necessary in determining maturity.
/// This should be set to not_coinbase if the output is not coinbase.
size_t bc_output_point__height(const bc_output_point_t* self);
void bc_output_point__set_height(bc_output_point_t* self, size_t height);

/// The output cache contains the output referenced by the input point.
/// If the cache.value is not_found then the output has not been found.
bc_output_t* bc_output_point__cache(const bc_output_point_t* self);
void bc_output_point__set_cache(bc_output_point_t* self,
    const bc_output_t* cache);

typedef struct bc_points_info_t bc_points_info_t;
bc_points_info_t* bc_create_points_info();
void bc_destroy_points_info(bc_points_info_t* self);
bc_chain_point_list_t* bc_points_info__points(const bc_points_info_t* self);
void bc_points_info__set_points(bc_points_info_t* self,
    const bc_chain_point_list_t* points);
uint64_t bc_points_info__change(const bc_points_info_t* self);
void bc_points_info__set_change(bc_points_info_t* self, uint64_t change);

typedef struct bc_output_info_t bc_output_info_t;
BC_DECLARE_VECTOR(output_info_list, bc_output_info_t);
bc_output_info_t* bc_create_output_info();
void bc_destroy_output_info(bc_output_info_t* self);
bc_output_point_t* bc_output_info__point(const bc_output_info_t* self);
void bc_output_info__set_point(bc_output_info_t* self,
    const bc_output_point_t* point);
uint64_t bc_output_info__value(const bc_output_info_t* self);
void bc_output_info__set_value(bc_output_info_t* self, uint64_t value);

#ifdef __cplusplus
}
#endif

#endif

