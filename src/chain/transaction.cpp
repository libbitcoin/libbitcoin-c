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
#include <bitcoin/bitcoin/c/chain/transaction.h>
#include <bitcoin/bitcoin/c/internal/chain/transaction.hpp>

#include <bitcoin/bitcoin/c/internal/chain/input.hpp>
#include <bitcoin/bitcoin/c/internal/chain/output.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>
#include <bitcoin/bitcoin/c/internal/utility/vector.hpp>

BC_IMPLEMENT_VECTOR(transaction_list, bc_transaction_t, bc_destroy_transaction,
    libbitcoin::chain::transaction::list);

extern "C" {

// Static functions
bc_transaction_t* bc_transaction_factory_from_data(
    const bc_data_chunk_t* data)
{
    return new bc_transaction_t{ new libbitcoin::chain::transaction(
        libbitcoin::chain::transaction::factory_from_data(*data->obj)) };
}
// Constructor
bc_transaction_t* bc_create_transaction()
{
    return new bc_transaction_t{ new libbitcoin::chain::transaction };
}
bc_transaction_t* bc_create_transaction_copy(const bc_transaction_t* other)
{
    return new bc_transaction_t{ new libbitcoin::chain::transaction(
        *other->obj) };
}
bc_transaction_t* bc_create_transaction_Parts(
    uint32_t version, uint32_t locktime,
    const bc_input_list_t* inputs, const bc_output_list_t* outputs)
{
    const auto inputs_vector = bc_input_list_from_ctype(inputs);
    const auto outputs_vector = bc_output_list_from_ctype(outputs);
    return new bc_transaction_t{ new libbitcoin::chain::transaction(
        version, locktime, inputs_vector, outputs_vector) };
}
// Destructor
void bc_destroy_transaction(bc_transaction_t* self)
{
    delete self->obj;
    delete self;
}
// Member functions
bool bc_transaction_from_data(bc_transaction_t* self,
    const bc_data_chunk_t* data)
{
    return self->obj->from_data(*data->obj);
}
bc_data_chunk_t* bc_transaction_to_data(const bc_transaction_t* self)
{
    return bc_create_data_chunk_Internal(self->obj->to_data());
}
bc_string_t* bc_transaction_to_string(const bc_transaction_t* self,
    uint32_t flags)
{
    return bc_create_string_StdString(self->obj->to_string(flags));
}
bool bc_transaction_is_valid(const bc_transaction_t* self)
{
    return self->obj->is_valid();
}
void bc_transaction_reset(bc_transaction_t* self)
{
    self->obj->reset();
}
bc_hash_digest_t* bc_transaction_hash(const bc_transaction_t* self)
{
    return bc_create_hash_digest_Internal(self->obj->hash());
}
// sighash_type is used by OP_CHECKSIG
bc_hash_digest_t* bc_transaction_hash_Sighash(const bc_transaction_t* self,
    uint32_t sighash_type)
{
    return bc_create_hash_digest_Internal(self->obj->hash(sighash_type));
}
bool bc_transaction_is_coinbase(const bc_transaction_t* self)
{
    return self->obj->is_coinbase();
}
bool bc_transaction_is_final(const bc_transaction_t* self,
    uint64_t block_height, uint32_t block_time)
{
    return self->obj->is_final(block_height, block_time);
}
bool bc_transaction_is_locktime_conflict(const bc_transaction_t* self)
{
    return self->obj->is_locktime_conflict();
}
uint64_t bc_transaction_total_output_value(const bc_transaction_t* self)
{
    return self->obj->total_output_value();
}
uint64_t bc_transaction_serialized_size(const bc_transaction_t* self)
{
    return self->obj->serialized_size();
}
// Member variables
uint32_t bc_transaction_version(const bc_transaction_t* self)
{
    return self->obj->version;
}
void bc_transaction_set_version(bc_transaction_t* self, uint32_t version)
{
    self->obj->version = version;
}
uint32_t bc_transaction_locktime(const bc_transaction_t* self)
{
    return self->obj->locktime;
}
void bc_transaction_set_locktime(bc_transaction_t* self, uint32_t locktime)
{
    self->obj->locktime = locktime;
}
bc_input_list_t* bc_transaction_inputs(const bc_transaction_t* self)
{
    return bc_input_list_to_ctype(self->obj->inputs);
}
void bc_transaction_set_inputs(const bc_transaction_t* self,
    bc_input_list_t* inputs)
{
    self->obj->inputs = bc_input_list_from_ctype(inputs);
}
bc_output_list_t* bc_transaction_outputs(const bc_transaction_t* self)
{
    return bc_output_list_to_ctype(self->obj->outputs);
}
void bc_transaction_set_outputs(const bc_transaction_t* self,
    bc_output_list_t* outputs)
{
    self->obj->outputs = bc_output_list_from_ctype(outputs);
}

} // extern C

