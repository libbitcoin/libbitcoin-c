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
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/vector.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_block_t bc_block_t;
BC_DECLARE_VECTOR(block_list, bc_block_t);

// Static functions
bc_block_t* bc_block_factory_from_data(
    const bc_data_chunk_t* data);
bc_block_t* bc_block_factory_from_data_without_transaction_count(
    const bc_data_chunk_t* data);
bc_hash_digest_t* bc_block_generate_merkle_root(
    const bc_transaction_list_t* transactions);
bc_block_t* bc_block_genesis_mainnet();
bc_block_t* bc_block_genesis_testnet();

// Constructor
bc_block_t* bc_create_block();
bc_block_t* bc_create_block_copy(const bc_block_t* other);
bc_block_t* bc_create_block_Options(
    const bc_header_t* header,
    const bc_transaction_list_t* transactions);

// Destructor
void bc_destroy_block(const bc_block_t* self);

// Member functions
bool bc_block_from_data(
    bc_block_t* self, const bc_data_chunk_t* data);
bool bc_block_from_data_without_transaction_count(
    bc_block_t* self, const bc_data_chunk_t* data);
bc_data_chunk_t* bc_block_to_data(const bc_block_t* self);
bc_data_chunk_t* bc_block_to_data_without_transaction_count(
    const bc_block_t* self);
bool bc_block_is_valid(const bc_block_t* self);
void bc_block_reset(bc_block_t* self);
uint64_t bc_block_serialized_size(const bc_block_t* self);
uint64_t bc_block_serialized_size_without_transaction_count(
    const bc_block_t* self);

// Member variables
bc_header_t* bc_block_header(const bc_block_t* self);
void bc_block_set_header(bc_block_t* self, const bc_header_t* header);
bc_transaction_list_t* bc_block_transactions(const bc_block_t* self);
void bc_block_set_transactions(bc_block_t* self,
    const bc_transaction_list_t* transactions);

#ifdef __cplusplus
}
#endif

#endif

