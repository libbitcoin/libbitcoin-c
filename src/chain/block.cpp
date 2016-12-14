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
#include <bitcoin/bitcoin/c/chain/block.h>
#include <bitcoin/bitcoin/c/internal/chain/block.hpp>

#include <bitcoin/bitcoin/c/internal/error.hpp>
#include <bitcoin/bitcoin/c/internal/chain/chain_state.hpp>
#include <bitcoin/bitcoin/c/internal/chain/header.hpp>
#include <bitcoin/bitcoin/c/internal/chain/transaction.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/math/uint256.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/vector.hpp>

extern "C" {

BC_IMPLEMENT_VECTOR(block_list, bc_block_t,
    bc_destroy_block, libbitcoin::chain::block::list);
BC_IMPLEMENT_INT_VECTOR(block_indexes, size_t,
    libbitcoin::chain::block::indexes);

// Constructor
//-------------------------------------------------------------------------
bc_block_t* bc_create_block()
{
    return new bc_block_t{ new libbitcoin::chain::block };
}
bc_block_t* bc_create_block_copy(const bc_block_t* other)
{
    return new bc_block_t{ new libbitcoin::chain::block(*other->obj) };
}
bc_block_t* bc_create_block_Options(
    const bc_header_t* header,
    const bc_transaction_list_t* transactions)
{
    return new bc_block_t{ new libbitcoin::chain::block(
        *header->obj, *transactions->obj) };
}

// Destructor
void bc_destroy_block(const bc_block_t* self)
{
    delete self->obj;
    delete self;
}

// Operators.
//-------------------------------------------------------------------------

bool bc_block__equals(const bc_block_t* self, const bc_block_t* other)
{
    return *self->obj == *other->obj;
}
bool bc_block__not_equals(const bc_block_t* self, const bc_block_t* other)
{
    return *self->obj != *other->obj;
}

// Deserialization.
//-------------------------------------------------------------------------

bc_block_t* bc_block__factory_from_data(
    const bc_data_chunk_t* data)
{
    return new bc_block_t{ new libbitcoin::chain::block(
        libbitcoin::chain::block::factory_from_data(*data->obj)) };
}

bool bc_block__from_data(
    bc_block_t* self, const bc_data_chunk_t* data)
{
    return self->obj->from_data(*data->obj);
}

bool bc_block__is_valid(const bc_block_t* self)
{
    return self->obj->is_valid();
}

// Serialization.
//-------------------------------------------------------------------------

bc_data_chunk_t* bc_block__to_data(const bc_block_t* self)
{
    return bc_create_data_chunk_Internal(self->obj->to_data());
}

// Properties (size, accessors, cache).
//-------------------------------------------------------------------------

uint64_t bc_block__serialized_size(const bc_block_t* self)
{
    return self->obj->serialized_size();
}

bc_header_t* bc_block__header(const bc_block_t* self)
{
    return new bc_header_t{ new libbitcoin::chain::header(
        self->obj->header()), true };
}
void bc_block__set_header(bc_block_t* self, const bc_header_t* header)
{
    self->obj->set_header(*header->obj);
}

bc_transaction_list_t* bc_block__transactions(const bc_block_t* self)
{
    return new bc_transaction_list_t{ new libbitcoin::chain::transaction::list(
        self->obj->transactions()), true };
}
void bc_block__set_transactions(bc_block_t* self,
    const bc_transaction_list_t* transactions)
{
    self->obj->set_transactions(*transactions->obj);
}

bc_hash_digest_t* bc_block__hash(const bc_block_t* self)
{
    return bc_create_hash_digest_Internal(self->obj->hash());
}

// Utilities.
//-------------------------------------------------------------------------

bc_block_t* bc_block__genesis_mainnet()
{
    return new bc_block_t{ new libbitcoin::chain::block(
        libbitcoin::chain::block::genesis_mainnet()) };
}
bc_block_t* bc_block__genesis_testnet()
{
    return new bc_block_t{ new libbitcoin::chain::block(
        libbitcoin::chain::block::genesis_testnet()) };
}
size_t bc_block__locator_size(size_t top)
{
    return libbitcoin::chain::block::locator_size(top);
}
bc_block_indexes_t* bc_block__locator_heights(size_t top)
{
    return new bc_block_indexes_t{ new libbitcoin::chain::block::indexes(
        libbitcoin::chain::block::locator_heights(top)) };
}

// Validation.
//-------------------------------------------------------------------------

uint64_t bc_block__subsidy(size_t height)
{
    return libbitcoin::chain::block::subsidy(height);
}
bc_uint256_t* bc_block__difficulty_Static(uint32_t bits)
{
    return new bc_uint256_t{ new libbitcoin::uint256_t(
        libbitcoin::chain::block::difficulty(bits)) };
}

uint64_t bc_block__fees(const bc_block_t* self)
{
    return self->obj->fees();
}
uint64_t bc_block__claim(const bc_block_t* self)
{
    return self->obj->claim();
}
uint64_t bc_block__reward(const bc_block_t* self, size_t height)
{
    return self->obj->reward(height);
}
bc_uint256_t* bc_block__difficulty(const bc_block_t* self)
{
    return new bc_uint256_t{ new libbitcoin::uint256_t(
        self->obj->difficulty()) };
}
bc_hash_digest_t* bc_block__generate_merkle_root(const bc_block_t* self)
{
    return bc_create_hash_digest_Internal(self->obj->generate_merkle_root());
}
size_t bc_block__signature_operations(const bc_block_t* self)
{
    return self->obj->signature_operations();
}
size_t bc_block__signature_operations_Bip16(
    const bc_block_t* self, bool bip16_active)
{
    return self->obj->signature_operations(bip16_active);
}
size_t bc_block__total_inputs(const bc_block_t* self)
{
    return self->obj->total_inputs();
}
size_t bc_block__total_inputs_nocoinbase(const bc_block_t* self)
{
    return self->obj->total_inputs(false);
}

bool bc_block__is_extra_coinbases(const bc_block_t* self)
{
    return self->obj->is_extra_coinbases();
}
bool bc_block__is_final(const bc_block_t* self, size_t height)
{
    return self->obj->is_final(height);
}
bool bc_block__is_distinct_transaction_set(const bc_block_t* self)
{
    return self->obj->is_distinct_transaction_set();
}
bool bc_block__is_valid_coinbase_claim(const bc_block_t* self, size_t height)
{
    return self->obj->is_valid_coinbase_claim(height);
}
bool bc_block__is_valid_coinbase_script(const bc_block_t* self, size_t height)
{
    return self->obj->is_valid_coinbase_script(height);
}
bool bc_block__is_internal_double_spend(const bc_block_t* self)
{
    return self->obj->is_internal_double_spend();
}
bool bc_block__is_valid_merkle_root(const bc_block_t* self)
{
    return self->obj->is_valid_merkle_root();
}

bc_error_code_t* bc_block__check(const bc_block_t* self)
{
    return new bc_error_code_t{ new std::error_code(
        self->obj->check()) };
}
bc_error_code_t* bc_block__check_transactions(const bc_block_t* self)
{
    return new bc_error_code_t{ new std::error_code(
        self->obj->check_transactions()) };
}
bc_error_code_t* bc_block__accept(
    const bc_block_t* self)
{
    return new bc_error_code_t{ new std::error_code(self->obj->accept()) };
}
bc_error_code_t* bc_block__accept_notransactions(
    const bc_block_t* self)
{
    return new bc_error_code_t{ new std::error_code(
        self->obj->accept(false)) };
}
bc_error_code_t* bc_block__accept_ChainState(
    const bc_block_t* self, const bc_chain_state_t* state)
{
    return new bc_error_code_t{ new std::error_code(
        self->obj->accept(*state->obj)) };
}
bc_error_code_t* bc_block__accept_ChainState_notransactions(
    const bc_block_t* self, const bc_chain_state_t* state)
{
    return new bc_error_code_t{ new std::error_code(
        self->obj->accept(*state->obj, false)) };
}
bc_error_code_t* bc_block__accept_transactions(
    const bc_block_t* self, const bc_chain_state_t* state)
{
    return new bc_error_code_t{ new std::error_code(
        self->obj->accept_transactions(*state->obj)) };
}
bc_error_code_t* bc_block__connect(const bc_block_t* self)
{
    return new bc_error_code_t{ new std::error_code(self->obj->connect()) };
}
bc_error_code_t* bc_block__connect_ChainState(
    const bc_block_t* self, const bc_chain_state_t* state)
{
    return new bc_error_code_t{ new std::error_code(
        self->obj->connect(*state->obj)) };
}
bc_error_code_t* bc_block__connect_transactions(
    const bc_block_t* self, const bc_chain_state_t* state)
{
    return new bc_error_code_t{ new std::error_code(
        self->obj->connect_transactions(*state->obj)) };
}

} // extern C

