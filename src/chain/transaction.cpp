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

#include <bitcoin/bitcoin/c/internal/error.hpp>
#include <bitcoin/bitcoin/c/internal/chain/chain_state.hpp>
#include <bitcoin/bitcoin/c/internal/chain/input.hpp>
#include <bitcoin/bitcoin/c/internal/chain/output.hpp>
#include <bitcoin/bitcoin/c/internal/chain/point.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>
#include <bitcoin/bitcoin/c/internal/utility/vector.hpp>

extern "C" {

BC_IMPLEMENT_VECTOR(transaction_list, bc_transaction_t, bc_destroy_transaction,
    libbitcoin::chain::transaction::list);

// Constructor
bc_transaction_t* bc_create_transaction()
{
    return new bc_transaction_t{ new libbitcoin::chain::transaction, true };
}
bc_transaction_t* bc_create_transaction_copy(const bc_transaction_t* other)
{
    return new bc_transaction_t{ new libbitcoin::chain::transaction(
        *other->obj), true };
}
bc_transaction_t* bc_create_transaction_copy_Hash(
    const bc_transaction_t* other, const bc_hash_digest_t* hash)
{
    return new bc_transaction_t{ new libbitcoin::chain::transaction(
        *other->obj, *hash->obj), true };
}
bc_transaction_t* bc_create_transaction_Parts(
    uint32_t version, uint32_t locktime,
    const bc_input_list_t* inputs, const bc_output_list_t* outputs)
{
    return new bc_transaction_t{ new libbitcoin::chain::transaction(
        version, locktime, *inputs->obj, *outputs->obj), true };
}
// Destructor
void bc_destroy_transaction(bc_transaction_t* self)
{
    if (self->delete_obj)
        delete self->obj;
    delete self;
}

// Operators.
void bc_transaction__copy(
    bc_transaction_t* self, const bc_transaction_t* other)
{
    *self->obj = *other->obj;
}

bool bc_transaction__equals(
    const bc_transaction_t* self, const bc_transaction_t* other)
{
    return *self->obj == *other->obj;
}
bool bc_transaction__not_equals(
    const bc_transaction_t* self, const bc_transaction_t* other)
{
    return *self->obj != *other->obj;
}

// Deserialization.
bc_transaction_t* bc_transaction__factory_from_data(
    const bc_data_chunk_t* data)
{
    return new bc_transaction_t{ new libbitcoin::chain::transaction(
        libbitcoin::chain::transaction::factory_from_data(*data->obj)), true };
}
bc_transaction_t* bc_transaction__factory_from_data_nowire(
    const bc_data_chunk_t* data)
{
    return new bc_transaction_t{ new libbitcoin::chain::transaction(
        libbitcoin::chain::transaction::factory_from_data(
            *data->obj, false)), true };
}

bool bc_transaction__from_data(bc_transaction_t* self,
    const bc_data_chunk_t* data)
{
    return self->obj->from_data(*data->obj);
}
bool bc_transaction__from_data_nowire(bc_transaction_t* self,
    const bc_data_chunk_t* data)
{
    return self->obj->from_data(*data->obj, false);
}

bool bc_transaction__is_valid(const bc_transaction_t* self)
{
    return self->obj->is_valid();
}

// Serialization.
bc_data_chunk_t* bc_transaction__to_data(const bc_transaction_t* self)
{
    return bc_create_data_chunk_Internal(self->obj->to_data());
}
bc_data_chunk_t* bc_transaction__to_data_nowire(
    const bc_transaction_t* self)
{
    return bc_create_data_chunk_Internal(self->obj->to_data(false));
}

// Properties (size, accessors, cache).
uint64_t bc_transaction__serialized_size(const bc_transaction_t* self)
{
    return self->obj->serialized_size();
}
uint64_t bc_transaction__serialized_size_nowire(const bc_transaction_t* self)
{
    return self->obj->serialized_size(false);
}

uint32_t bc_transaction__version(const bc_transaction_t* self)
{
    return self->obj->version();
}
void bc_transaction__set_version(bc_transaction_t* self, uint32_t version)
{
    self->obj->set_version(version);
}

uint32_t bc_transaction__locktime(const bc_transaction_t* self)
{
    return self->obj->locktime();
}
void bc_transaction__set_locktime(bc_transaction_t* self, uint32_t locktime)
{
    self->obj->set_locktime(locktime);
}

bc_input_list_t* bc_transaction__inputs(const bc_transaction_t* self)
{
    return new bc_input_list_t{ new libbitcoin::chain::input::list(
        self->obj->inputs()), true };
}
void bc_transaction__set_inputs(bc_transaction_t* self,
    const bc_input_list_t* inputs)
{
    self->obj->set_inputs(*inputs->obj);
}

bc_output_list_t* bc_transaction__outputs(const bc_transaction_t* self)
{
    return new bc_output_list_t{ new libbitcoin::chain::output::list(
        self->obj->outputs()), true };
}
void bc_transaction__set_outputs(bc_transaction_t* self,
    const bc_output_list_t* outputs)
{
    self->obj->set_outputs(*outputs->obj);
}

bc_hash_digest_t* bc_transaction__hash(const bc_transaction_t* self)
{
    return bc_create_hash_digest_Internal(self->obj->hash());
}
bc_hash_digest_t* bc_transaction__hash_Sighash(const bc_transaction_t* self,
    uint32_t sighash_type)
{
    return bc_create_hash_digest_Internal(self->obj->hash(sighash_type));
}

// Validation.
uint64_t bc_transaction__fees(const bc_transaction_t* self)
{
    return self->obj->fees();
}
/*bc_point_indexes_t* bc_transaction__double_spends(
    const bc_transaction_t* self, bool include_unconfirmed)
{
    const auto indexes = self->obj->double_spends(include_unconfirmed);
    return new bc_point_indexes_t{ new libbitcoin::chain::point::indexes(
        indexes), true };
}
bc_point_indexes_t* bc_transaction__immature_inputs(
    const bc_transaction_t* self, size_t target_height)
{
    const auto indexes = self->obj->immature_inputs(target_height);
    return new bc_point_indexes_t{ new libbitcoin::chain::point::indexes(
        indexes), true };
}
bc_point_indexes_t* bc_transaction__missing_previous_outputs(
    const bc_transaction_t* self)
{
    const auto indexes = self->obj->missing_previous_outputs();
    return new bc_point_indexes_t{ new libbitcoin::chain::point::indexes(
        indexes), true };
}*/
uint64_t bc_transaction__total_input_value(const bc_transaction_t* self)
{
    return self->obj->total_input_value();
}
uint64_t bc_transaction__total_output_value(const bc_transaction_t* self)
{
    return self->obj->total_output_value();
}
size_t bc_transaction__signature_operations(
    const bc_transaction_t* self, bool bip16_active)
{
    return self->obj->signature_operations(bip16_active);
}

bool bc_transaction__is_coinbase(const bc_transaction_t* self)
{
    return self->obj->is_coinbase();
}
bool bc_transaction__is_null_non_coinbase(const bc_transaction_t* self)
{
    return self->obj->is_null_non_coinbase();
}
bool bc_transaction__is_oversized_coinbase(const bc_transaction_t* self)
{
    return self->obj->is_oversized_coinbase();
}
bool bc_transaction__is_immature(const bc_transaction_t* self,
    size_t target_height)
{
    return self->obj->is_immature(target_height);
}
bool bc_transaction__is_overspent(const bc_transaction_t* self)
{
    return self->obj->is_overspent();
}
bool bc_transaction__is_double_spend(const bc_transaction_t* self,
    bool include_unconfirmed)
{
    return self->obj->is_double_spend(include_unconfirmed);
}
bool bc_transaction__is_missing_previous_outputs(const bc_transaction_t* self)
{
    return self->obj->is_missing_previous_outputs();
}
bool bc_transaction__is_final(const bc_transaction_t* self,
    uint64_t block_height, uint32_t block_time)
{
    return self->obj->is_final(block_height, block_time);
}
bool bc_transaction__is_locktime_conflict(const bc_transaction_t* self)
{
    return self->obj->is_locktime_conflict();
}

bc_error_code_t* bc_transaction__check(const bc_transaction_t* self)
{
    return new bc_error_code_t{ new std::error_code(
        self->obj->check()) };
}
bc_error_code_t* bc_transaction__check_notransaction_pool(
    const bc_transaction_t* self)
{
    return new bc_error_code_t{ new std::error_code(
        self->obj->check(false)) };
}
bc_error_code_t* bc_transaction__accept(
    const bc_transaction_t* self, const bc_chain_state_t* state)
{
    return new bc_error_code_t{ new std::error_code(
        self->obj->accept(*state->obj)) };
}
bc_error_code_t* bc_transaction__accept_notransaction_pool(
    const bc_transaction_t* self, const bc_chain_state_t* state)
{
    return new bc_error_code_t{ new std::error_code(
        self->obj->accept(*state->obj, false)) };
}
bc_error_code_t* bc_transaction__connect(
    const bc_transaction_t* self, const bc_chain_state_t* state)
{
    return new bc_error_code_t{ new std::error_code(
        self->obj->connect(*state->obj)) };
}
bc_error_code_t* bc_transaction__connect_input(
    const bc_transaction_t* self, const bc_chain_state_t* state,
    uint32_t input_index)
{
    return new bc_error_code_t{ new std::error_code(
        self->obj->connect_input(*state->obj, input_index)) };
}

} // extern C

