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
#ifndef LIBBITCOIN_C_CHAIN_TRANSACTION_H
#define LIBBITCOIN_C_CHAIN_TRANSACTION_H

#include <bitcoin/bitcoin/c/chain/input.h>
#include <bitcoin/bitcoin/c/chain/output.h>
#include <bitcoin/bitcoin/c/math/hash.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>
#include <bitcoin/bitcoin/c/utility/vector.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_transaction_t bc_transaction_t;
BC_DECLARE_VECTOR(transaction_list, bc_transaction_t);
// Static functions
bc_transaction_t* bc_transaction_factory_from_data(
    const bc_data_chunk_t* data);
uint64_t bc_transaction_satoshi_fixed_size();
// Constructor
bc_transaction_t* bc_create_transaction();
bc_transaction_t* bc_create_transaction_copy(const bc_transaction_t* other);
bc_transaction_t* bc_create_transaction_Parts(
    uint32_t version, uint32_t locktime,
    const bc_input_list_t* inputs, const bc_output_list_t* outputs);
// Destructor
void bc_destroy_transaction(bc_transaction_t* self);
// Member functions
bool bc_transaction_from_data(bc_transaction_t* self,
    const bc_data_chunk_t* data);
bc_data_chunk_t* bc_transaction_to_data(const bc_transaction_t* self);
bc_string_t* bc_transaction_to_string(const bc_transaction_t* self,
    uint32_t flags);
bool bc_transaction_is_valid(const bc_transaction_t* self);
void bc_transaction_reset(bc_transaction_t* self);
bc_hash_digest_t* bc_transaction_hash(const bc_transaction_t* self);
// sighash_type is used by OP_CHECKSIG
bc_hash_digest_t* bc_transaction_hash_Sighash(const bc_transaction_t* self,
    uint32_t sighash_type);
bool bc_transaction_is_coinbase(const bc_transaction_t* self);
bool bc_transaction_is_final(const bc_transaction_t* self,
    uint64_t block_height, uint32_t block_time);
bool bc_transaction_is_locktime_conflict(const bc_transaction_t* self);
uint64_t bc_transaction_total_output_value(const bc_transaction_t* self);
uint64_t bc_transaction_serialized_size(const bc_transaction_t* self);
// Member variables
uint32_t bc_transaction_version(const bc_transaction_t* self);
void bc_transaction_set_version(bc_transaction_t* self, uint32_t version);
uint32_t bc_transaction_locktime(const bc_transaction_t* self);
void bc_transaction_set_locktime(bc_transaction_t* self, uint32_t locktime);
bc_input_list_t* bc_transaction_inputs(const bc_transaction_t* self);
void bc_transaction_set_inputs(const bc_transaction_t* self,
    bc_input_list_t* inputs);
bc_output_list_t* bc_transaction_outputs(const bc_transaction_t* self);
void bc_transaction_set_outputs(const bc_transaction_t* self,
    bc_output_list_t* outputs);

#ifdef __cplusplus
}
#endif

#endif

