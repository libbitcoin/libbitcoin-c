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

typedef struct bc_output_point_validation_t bc_output_point_validation_t;

void bc_destroy_output_point_validation(bc_output_point_validation_t* self);

size_t bc_output_point_validation__not_specified();

bool bc_output_point_validation__spent(
    const bc_output_point_validation_t* self);
void bc_output_point_validation__set_spent(
    bc_output_point_validation_t* self, bool spent);

bool bc_output_point_validation__confirmed(
    const bc_output_point_validation_t* self);
void bc_output_point_validation__set_confirmed(
    bc_output_point_validation_t* self, bool confirmed);

size_t bc_output_point_validation__height(
    const bc_output_point_validation_t* self);
void bc_output_point_validation__set_height(
    bc_output_point_validation_t* self, size_t height);

bc_output_t* bc_output_point_validation__cache(
    const bc_output_point_validation_t* self);

typedef struct bc_output_point_t bc_output_point_t;

/// Constructors
bc_output_point_t* bc_create_output_point();
bc_output_point_t* bc_create_output_point_Point(const bc_point_t* value);
bc_output_point_t* bc_create_output_point_copy(const bc_output_point_t* other);
bc_output_point_t* bc_create_output_point_Tuple(
    const bc_hash_digest_t* hash, uint32_t index);

/// Destructor
void bc_destroy_output_point(bc_output_point_t* self);

/// Operators
bool bc_output_point__copy_Point(const bc_output_point_t* self,
    const bc_point_t* other);
bool bc_output_point__copy(const bc_output_point_t* self,
    const bc_output_point_t* other);

bool bc_output_point__equals(const bc_output_point_t* self,
    const bc_output_point_t* other);
bool bc_output_point__not_equals(const bc_output_point_t* self,
    const bc_output_point_t* other);

// Deserialization.
bc_output_point_t* bc_output_point__factory_from_data(
    const bc_data_chunk_t* data);

bc_point_t* bc_output_point__point_Base(bc_output_point_t* self);

/// False if previous output is not cached.
/// True if the previous output is mature enough to spend from target.
bool bc_output_point__is_mature(const bc_output_point_t* self,
    size_t target_height);

bc_output_point_validation_t* bc_output_point__validation(
    const bc_output_point_t* self);

#ifdef __cplusplus
}
#endif

#endif

