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
#ifndef LIBBITCOIN_C_CHAIN_HEADER_H
#define LIBBITCOIN_C_CHAIN_HEADER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <bitcoin/bitcoin/c/error.h>
#include <bitcoin/bitcoin/c/chain/chain_state.h>
#include <bitcoin/bitcoin/c/math/hash.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>
#include <bitcoin/bitcoin/c/utility/vector.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_header_t bc_header_t;
BC_DECLARE_VECTOR(header_list, bc_header_t);

// Constructor
bc_header_t* bc_create_header();
bc_header_t* bc_create_header_copy(const bc_header_t* other);
bc_header_t* bc_create_header_copy_with_Hash(const bc_header_t* other,
    const bc_hash_digest_t* hash);
bc_header_t* bc_create_header_Options(
    uint32_t version, const bc_hash_digest_t* previous_block_hash,
    const bc_hash_digest_t* merkle, uint32_t timestamp, uint32_t bits,
    uint32_t nonce);

// Destructor
void bc_destroy_header(const bc_header_t* self);

// Operators
void bc_header__copy(bc_header_t* self, const bc_header_t* other);

bool bc_header__equals(const bc_header_t* self, const bc_header_t* other);
bool bc_header__not_equals(const bc_header_t* self, const bc_header_t* other);

// Deserialization.
//-----------------------------------------------------------------------------
bc_header_t* bc_header__factory_from_data(
    const bc_data_chunk_t* data);

bool bc_header__from_data(
    bc_header_t* self, const bc_data_chunk_t* data);

bool bc_header__is_valid(const bc_header_t* self);

// Serialization.
//-----------------------------------------------------------------------------

bc_data_chunk_t* bc_header__to_data(const bc_header_t* self);

// Properties (size, accessors, cache).
//-----------------------------------------------------------------------------

uint64_t bc_header__satoshi_fixed_size();
uint64_t bc_header__serialized_size(const bc_header_t* self);

// Member variables
uint32_t bc_header__version(const bc_header_t* self);
void bc_header__set_version(bc_header_t* self, uint32_t version);

bc_hash_digest_t* bc_header__previous_block_hash(const bc_header_t* self);
void bc_header__set_previous_block_hash(bc_header_t* self,
    const bc_hash_digest_t* previous_block_hash);

bc_hash_digest_t* bc_header__merkle(const bc_header_t* self);
void bc_header__set_merkle(bc_header_t* self,
    const bc_hash_digest_t* merkle);

uint32_t bc_header__timestamp(const bc_header_t* self);
void bc_header__set_timestamp(bc_header_t* self, uint32_t timestamp);

uint32_t bc_header__bits(const bc_header_t* self);
void bc_header__set_bits(bc_header_t* self, uint32_t bits);

uint32_t bc_header__nonce(const bc_header_t* self);
void bc_header__set_nonce(bc_header_t* self, uint32_t nonce);

bc_hash_digest_t* bc_header__hash(const bc_header_t* self);

// Validation.
//-----------------------------------------------------------------------------

bool bc_header__is_valid_timestamp(const bc_header_t* self);
bool bc_header__is_valid_proof_of_work(const bc_header_t* self);

bc_error_code_t* bc_header__check(const bc_header_t* self);
bc_error_code_t* bc_header__accept(const bc_header_t* self,
    const bc_chain_state_t* state);

#ifdef __cplusplus
}
#endif

#endif

