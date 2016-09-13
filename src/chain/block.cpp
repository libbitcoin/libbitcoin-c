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

#include <bitcoin/bitcoin/c/internal/chain/header.hpp>
#include <bitcoin/bitcoin/c/internal/chain/transaction.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/vector.hpp>

BC_IMPLEMENT_VECTOR(block_list, bc_block_t, bc_destroy_block,
    libbitcoin::chain::block::list);

extern "C" {

// Static functions
bc_block_t* bc_block_factory_from_data(
    const bc_data_chunk_t* data)
{
    return new bc_block_t{ new libbitcoin::chain::block(
        libbitcoin::chain::block::factory_from_data(*data->obj)) };
}
bc_block_t* bc_block_factory_from_data_without_transaction_count(
    const bc_data_chunk_t* data)
{
    return new bc_block_t{ new libbitcoin::chain::block(
        libbitcoin::chain::block::factory_from_data(
            *data->obj, false)) };
}
bc_hash_digest_t* bc_block_generate_merkle_root(
    const bc_transaction_list_t* transactions)
{
    const auto transactions_converted =
        bc_transaction_list_from_ctype(transactions);
    const auto merkle = libbitcoin::chain::block::generate_merkle_root(
        transactions_converted);
    return bc_create_hash_digest_Internal(merkle);
}
bc_block_t* bc_block_genesis_mainnet()
{
    return new bc_block_t{ new libbitcoin::chain::block(
        libbitcoin::chain::block::genesis_mainnet()) };
}
bc_block_t* bc_block_genesis_testnet()
{
    return new bc_block_t{ new libbitcoin::chain::block(
        libbitcoin::chain::block::genesis_testnet()) };
}

// Constructor
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
    const auto transactions_converted =
        bc_transaction_list_from_ctype(transactions);
    return new bc_block_t{ new libbitcoin::chain::block(
        *header->obj, transactions_converted) };
}

// Destructor
void bc_destroy_block(const bc_block_t* self)
{
    delete self->obj;
    delete self;
}

// Member functions
bool bc_block_from_data(
    bc_block_t* self, const bc_data_chunk_t* data)
{
    return self->obj->from_data(*data->obj);
}
bc_data_chunk_t* bc_block_to_data(const bc_block_t* self)
{
    return bc_create_data_chunk_Internal(self->obj->to_data());
}
bool bc_block_is_valid(const bc_block_t* self)
{
    return self->obj->is_valid();
}
void bc_block_reset(bc_block_t* self)
{
    self->obj->reset();
}
uint64_t bc_block_serialized_size(const bc_block_t* self)
{
    return self->obj->serialized_size();
}
uint64_t bc_block_serialized_size_without_transaction_count(
    const bc_block_t* self)
{
    return self->obj->serialized_size(false);
}

// Member variables
bc_header_t* bc_block_header(const bc_block_t* self)
{
    return new bc_header_t{ new libbitcoin::chain::header(
        self->obj->header) };
}
void bc_block_set_header(bc_block_t* self, const bc_header_t* header)
{
    self->obj->header = *header->obj;
}
bc_transaction_list_t* bc_block_transactions(const bc_block_t* self)
{
    return bc_transaction_list_to_ctype(self->obj->transactions);
}
void bc_block_set_transactions(bc_block_t* self,
    const bc_transaction_list_t* transactions)
{
    self->obj->transactions = bc_transaction_list_from_ctype(transactions);
}

} // extern C

