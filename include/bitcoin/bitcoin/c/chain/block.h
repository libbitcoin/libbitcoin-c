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
#ifndef LIBBITCOIN_C_CHAIN_BLOCK_H
#define LIBBITCOIN_C_CHAIN_BLOCK_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <bitcoin/bitcoin/c/chain/header.h>
#include <bitcoin/bitcoin/c/chain/transaction.h>
#include <bitcoin/bitcoin/c/math/hash.h>
#include <bitcoin/bitcoin/c/math/uint256.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/vector.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_block_t bc_block_t;

BC_DECLARE_VECTOR(block_list, bc_block_t);
BC_DECLARE_INT_VECTOR(block_indexes, size_t);

// Constructor
//-------------------------------------------------------------------------
bc_block_t* bc_create_block();
bc_block_t* bc_create_block_copy(const bc_block_t* other);
bc_block_t* bc_create_block_Options(
    const bc_header_t* header,
    const bc_transaction_list_t* transactions);

// Destructor
void bc_destroy_block(const bc_block_t* self);

// Operators.
//-------------------------------------------------------------------------

bool bc_block__equals(const bc_block_t* self, const bc_block_t* other);
bool bc_block__not_equals(const bc_block_t* self, const bc_block_t* other);

// Deserialization.
//-------------------------------------------------------------------------

bc_block_t* bc_block__factory_from_data(
    const bc_data_chunk_t* data);

bool bc_block__from_data(
    bc_block_t* self, const bc_data_chunk_t* data);

bool bc_block__is_valid(const bc_block_t* self);

// Serialization.
//-------------------------------------------------------------------------

bc_data_chunk_t* bc_block__to_data(const bc_block_t* self);

// Properties (size, accessors, cache).
//-------------------------------------------------------------------------

uint64_t bc_block__serialized_size(const bc_block_t* self);

bc_header_t* bc_block__header(const bc_block_t* self);
void bc_block__set_header(bc_block_t* self, const bc_header_t* header);

bc_transaction_list_t* bc_block__transactions(const bc_block_t* self);
void bc_block__set_transactions(bc_block_t* self,
    const bc_transaction_list_t* transactions);

bc_hash_digest_t* bc_block__hash(const bc_block_t* self);

// Utilities.
//-------------------------------------------------------------------------

bc_block_t* bc_block__genesis_mainnet();
bc_block_t* bc_block__genesis_testnet();
size_t bc_block__locator_size(size_t top);
bc_block_indexes_t* bc_block__locator_heights(size_t top);

// Validation.
//-------------------------------------------------------------------------

uint64_t bc_block__subsidy(size_t height);
bc_uint256_t* bc_block__difficulty_Static(uint32_t bits);

uint64_t bc_block__fees(const bc_block_t* self);
uint64_t bc_block__claim(const bc_block_t* self);
uint64_t bc_block__reward(const bc_block_t* self, size_t height);
bc_uint256_t* bc_block__difficulty(const bc_block_t* self);
bc_hash_digest_t* bc_block__generate_merkle_root(const bc_block_t* self);
size_t bc_block__signature_operations(const bc_block_t* self);
size_t bc_block__signature_operations_Bip16(
    const bc_block_t* self, bool bip16_active);
size_t bc_block__total_inputs(const bc_block_t* self);
size_t bc_block__total_inputs_nocoinbase(const bc_block_t* self);

bool bc_block__is_extra_coinbases(const bc_block_t* self);
bool bc_block__is_final(const bc_block_t* self, size_t height);
bool bc_block__is_distinct_transaction_set(const bc_block_t* self);
bool bc_block__is_valid_coinbase_claim(const bc_block_t* self, size_t height);
bool bc_block__is_valid_coinbase_script(const bc_block_t* self, size_t height);
bool bc_block__is_internal_double_spend(const bc_block_t* self);
bool bc_block__is_valid_merkle_root(const bc_block_t* self);

bc_error_code_t* bc_block__check(const bc_block_t* self);
bc_error_code_t* bc_block__check_transactions(const bc_block_t* self);
bc_error_code_t* bc_block__accept(
    const bc_block_t* self);
bc_error_code_t* bc_block__accept_notransactions(
    const bc_block_t* self);
bc_error_code_t* bc_block__accept_ChainState(
    const bc_block_t* self, const bc_chain_state_t* state);
bc_error_code_t* bc_block__accept_ChainState_notransactions(
    const bc_block_t* self, const bc_chain_state_t* state);
bc_error_code_t* bc_block__accept_transactions(
    const bc_block_t* self, const bc_chain_state_t* state);
bc_error_code_t* bc_block__connect(
    const bc_block_t* self);
bc_error_code_t* bc_block__connect_ChainState(
    const bc_block_t* self, const bc_chain_state_t* state);
bc_error_code_t* bc_block__connect_transactions(
    const bc_block_t* self, const bc_chain_state_t* state);

#ifdef __cplusplus
}
#endif

#endif

