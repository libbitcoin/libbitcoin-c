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
#include <bitcoin/bitcoin/c/chain/script.h>
#include <bitcoin/bitcoin/c/internal/chain/script.hpp>

#include <bitcoin/bitcoin/c/internal/chain/transaction.hpp>
#include <bitcoin/bitcoin/c/internal/error.hpp>
#include <bitcoin/bitcoin/c/internal/machine/opcode.hpp>
#include <bitcoin/bitcoin/c/internal/machine/operation.hpp>
#include <bitcoin/bitcoin/c/internal/machine/rule_fork.hpp>
#include <bitcoin/bitcoin/c/internal/machine/script_pattern.hpp>
#include <bitcoin/bitcoin/c/internal/math/elliptic_curve.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>

extern "C" {

// Constructor
bc_script_t* bc_create_script()
{
    return new bc_script_t{ new libbitcoin::chain::script, true };
}
bc_script_t* bc_create_script_copy(const bc_script_t* other)
{
    return new bc_script_t{ new libbitcoin::chain::script(
        *other->obj), true };
}
bc_script_t* bc_create_script_Ops(const bc_operation_list_t* ops)
{
    return new bc_script_t{ new libbitcoin::chain::script(
        *ops->obj), true };
}
bc_script_t* bc_create_script_Data(
    const bc_data_chunk_t* encoded, bool prefix)
{
    return new bc_script_t{ new libbitcoin::chain::script(
        *encoded->obj, prefix), true };
}
// Destructor
void bc_destroy_script(bc_script_t* self)
{
    if (self->delete_obj)
        delete self->obj;
    delete self;
}

// Operators
void bc_script__copy(bc_script_t* self, const bc_script_t* other)
{
    *self->obj = *other->obj;
}

bool bc_script__equals(const bc_script_t* self, const bc_script_t* other)
{
    return *self->obj == *other->obj;
}
bool bc_script__not_equals(const bc_script_t* self, const bc_script_t* other)
{
    return *self->obj != *other->obj;
}

/*
// Member functions
bc_script_pattern_t bc_script__pattern(const bc_script_t* self)
{
    return bc_script_pattern_to_ctype(self->obj->pattern());
}
bool bc_script__is_raw_data(const bc_script_t* self)
{
    return self->obj->is_raw_data();
}
*/

// Deserialization.
bc_script_t* bc_script__factory_from_data(
    const bc_data_chunk_t* encoded, bool prefix)
{
    return new bc_script_t{ new libbitcoin::chain::script(
        libbitcoin::chain::script::factory_from_data(
            *encoded->obj, prefix)) };
}

/// Deserialization invalidates the iterator.
bool bc_script__from_data(bc_script_t* self,
    const bc_data_chunk_t* encoded, bool prefix)
{
    return self->obj->from_data(*encoded->obj, prefix);
}

/// Deserialization invalidates the iterator.
void bc_script__from_operations(bc_script_t* self,
    const bc_operation_list_t* ops)
{
    self->obj->from_operations(*ops->obj);
}
bool bc_script__from_string(bc_script_t* self, const char* mnemonic)
{
    return self->obj->from_string(mnemonic);
}

/// A script object is valid if the byte count matches the prefix.
bool bc_script__is_valid(const bc_script_t* self)
{
    return self->obj->is_valid();
}

/// Script operations is valid if all push ops have the predicated size.
bool bc_script__is_valid_operations(const bc_script_t* self)
{
    return self->obj->is_valid_operations();
}

// Serialization.
bc_data_chunk_t* bc_script__to_data(const bc_script_t* self, bool prefix)
{
    return bc_create_data_chunk_Internal(self->obj->to_data(prefix));
}

bc_string_t* bc_script__to_string(
    const bc_script_t* self, uint32_t active_forks)
{
    return bc_create_string_StdString(self->obj->to_string(active_forks));
}

// Iteration.
bool bc_script__empty(const bc_script_t* self)
{
    return self->obj->empty();
}
size_t bc_script__size(const bc_script_t* self)
{
    return self->obj->size();
}
bc_operation_t* bc_script__front(const bc_script_t* self)
{
    return new bc_operation_t{ new libbitcoin::machine::operation(
        self->obj->front()), true };
}
bc_operation_t* bc_script__back(const bc_script_t* self)
{
    return new bc_operation_t{ new libbitcoin::machine::operation(
        self->obj->back()), true };
}
bc_operation_t* bc_script__at(const bc_script_t* self, size_t index)
{
    return new bc_operation_t{ new libbitcoin::machine::operation(
        (*self->obj)[index]), true };
}

// Properties (size, accessors, cache).
uint64_t bc_script__satoshi_content_size(const bc_script_t* self)
{
    return self->obj->satoshi_content_size();
}
uint64_t bc_script__serialized_size(const bc_script_t* self, bool prefix)
{
    return self->obj->serialized_size(prefix);
}
bc_operation_list_t* bc_script__operations(const bc_script_t* self)
{
    return new bc_operation_list_t{ new libbitcoin::machine::operation::list(
        self->obj->operations()) };
}

// Signing.

bc_hash_digest_t* bc_script__generate_signature_hash(
    const bc_transaction_t* tx, uint32_t input_index,
    const bc_script_t* script_code, uint8_t sighash_type)
{
    return new bc_hash_digest_t{ new libbitcoin::hash_digest(
        libbitcoin::chain::script::generate_signature_hash(
            *tx->obj, input_index, *script_code->obj, sighash_type)) };
}

bool bc_script__check_signature(const bc_ec_signature_t* signature,
    uint8_t sighash_type, const bc_data_chunk_t* public_key,
    const bc_script_t* script_code, const bc_transaction_t* tx,
    uint32_t input_index)
{
    return libbitcoin::chain::script::check_signature(
        *signature->obj, sighash_type, *public_key->obj,
        *script_code->obj, *tx->obj, input_index);
}

bool bc_script__create_endorsement(
    bc_endorsement_t* out, const bc_ec_secret_t* secret,
    const bc_script_t* prevout_script, const bc_transaction_t* tx,
    uint32_t input_index, uint8_t sighash_type)
{
    return libbitcoin::chain::script::create_endorsement(
        *out->obj, *secret->obj, *prevout_script->obj, *tx->obj,
        input_index, sighash_type);
}

// Utilities (static).

/// Determine if the fork is enabled in the active forks set.
bool bc_script__is_enabled(uint32_t active_forks,
    bc_rule_fork_t fork)
{
    return libbitcoin::chain::script::is_enabled(active_forks,
        bc_rule_fork_from_ctype(fork));
}

/// No-code patterns (consensus).
bool bc_script__is_push_only(const bc_operation_list_t* ops)
{
    return libbitcoin::chain::script::is_push_only(*ops->obj);
}
bool bc_script__is_relaxed_push(const bc_operation_list_t* ops)
{
    return libbitcoin::chain::script::is_relaxed_push(*ops->obj);
}
bool bc_script__is_coinbase_pattern(
    const bc_operation_list_t* ops, size_t height)
{
    return libbitcoin::chain::script::is_coinbase_pattern(*ops->obj, height);
}

/// Unspendable pattern (standard).
bool bc_script__is_null_data_pattern(const bc_operation_list_t* ops)
{
    return libbitcoin::chain::script::is_null_data_pattern(*ops->obj);
}

/// Payment script patterns (standard, psh is also consensus).
bool bc_script__is_pay_multisig_pattern(const bc_operation_list_t* ops)
{
    return libbitcoin::chain::script::is_pay_multisig_pattern(*ops->obj);
}
bool bc_script__is_pay_public_key_pattern(const bc_operation_list_t* ops)
{
    return libbitcoin::chain::script::is_pay_public_key_pattern(*ops->obj);
}
bool bc_script__is_pay_key_hash_pattern(const bc_operation_list_t* ops)
{
    return libbitcoin::chain::script::is_pay_key_hash_pattern(*ops->obj);
}
bool bc_script__is_pay_script_hash_pattern(const bc_operation_list_t* ops)
{
    return libbitcoin::chain::script::is_pay_script_hash_pattern(*ops->obj);
}

/// Signature script patterns (standard).
bool bc_script__is_sign_multisig_pattern(const bc_operation_list_t* ops)
{
    return libbitcoin::chain::script::is_sign_multisig_pattern(*ops->obj);
}
bool bc_script__is_sign_public_key_pattern(const bc_operation_list_t* ops)
{
    return libbitcoin::chain::script::is_sign_public_key_pattern(*ops->obj);
}
bool bc_script__is_sign_key_hash_pattern(const bc_operation_list_t* ops)
{
    return libbitcoin::chain::script::is_sign_key_hash_pattern(*ops->obj);
}
bool bc_script__is_sign_script_hash_pattern(const bc_operation_list_t* ops)
{
    return libbitcoin::chain::script::is_sign_script_hash_pattern(*ops->obj);
}

/// Stack factories (standard).
bc_operation_list_t* bc_script__to_null_data_pattern(
    const bc_data_chunk_t* data)
{
    return new bc_operation_list_t{ new libbitcoin::machine::operation::list(
        libbitcoin::chain::script::to_null_data_pattern(*data->obj)) };
}
bc_operation_list_t* bc_script__to_pay_public_key_pattern(
    const bc_data_chunk_t* data)
{
    return new bc_operation_list_t{ new libbitcoin::machine::operation::list(
        libbitcoin::chain::script::to_pay_public_key_pattern(*data->obj)) };
}
bc_operation_list_t* bc_script__to_pay_key_hash_pattern(
    const bc_short_hash_t* hash)
{
    return new bc_operation_list_t{ new libbitcoin::machine::operation::list(
        libbitcoin::chain::script::to_pay_key_hash_pattern(*hash->obj)) };
}
bc_operation_list_t* bc_script__to_pay_script_hash_pattern(
    const bc_short_hash_t* hash)
{
    return new bc_operation_list_t{ new libbitcoin::machine::operation::list(
        libbitcoin::chain::script::to_pay_script_hash_pattern(*hash->obj)) };
}
bc_operation_list_t* bc_script__to_pay_multisig_pattern(
    uint8_t signatures, const bc_point_list_t* points)
{
    return new bc_operation_list_t{ new libbitcoin::machine::operation::list(
        libbitcoin::chain::script::to_pay_multisig_pattern(
            signatures, *points->obj)) };
}
bc_operation_list_t* bc_script__to_pay_multisig_pattern_DataStack(
    uint8_t signatures, const bc_data_stack_t* points)
{
    return new bc_operation_list_t{ new libbitcoin::machine::operation::list(
        libbitcoin::chain::script::to_pay_multisig_pattern(
            signatures, *points->obj)) };
}

// Utilities (non-static).

bc_script_pattern_t bc_script__pattern(const bc_script_t* self)
{
    return bc_script_pattern_to_ctype(self->obj->pattern());
}
size_t bc_script__sigops(const bc_script_t* self, bool embedded)
{
    return self->obj->sigops(embedded);
}
size_t bc_script__embedded_sigops(
    const bc_script_t* self, const bc_script_t* prevout_script)
{
    return self->obj->embedded_sigops(*prevout_script->obj);
}
void bc_script__find_and_delete(
    const bc_script_t* self, const bc_data_stack_t* endorsements)
{
    return self->obj->find_and_delete(*endorsements->obj);
}

// Validation.

bc_error_code_t* bc_script__verify(
    const bc_transaction_t* tx, uint32_t input, uint32_t forks)
{
    return new bc_error_code_t{ new std::error_code(
        libbitcoin::chain::script::verify(*tx->obj, input, forks)) };
}

} // extern C

/*
bc_signature_hash_algorithm_t bc_signature_hash_algorithm_to_ctype(
    libbitcoin::chain::signature_hash_algorithm alg)
{
    return static_cast<bc_signature_hash_algorithm_t>(alg);
}

libbitcoin::chain::signature_hash_algorithm
    bc_signature_hash_algorithm_from_ctype(bc_signature_hash_algorithm_t alg)
{
    return static_cast<libbitcoin::chain::signature_hash_algorithm>(alg);
}

bc_script_parse_mode_t bc_script_parse_mode_to_ctype(
    libbitcoin::chain::script::parse_mode mode)
{
    switch (mode)
    {
        case libbitcoin::chain::script::parse_mode::strict:
            return bc_script_parse_mode__strict;

        case libbitcoin::chain::script::parse_mode::raw_data:
            return bc_script_parse_mode__raw_data;

        case libbitcoin::chain::script::parse_mode::raw_data_fallback:
            return bc_script_parse_mode__raw_data_fallback;
    }
}

libbitcoin::chain::script::parse_mode bc_script_parse_mode_from_ctype(
    bc_script_parse_mode_t mode)
{
    switch (mode)
    {
        case bc_script_parse_mode__strict:
            return libbitcoin::chain::script::parse_mode::strict;

        case bc_script_parse_mode__raw_data:
            return libbitcoin::chain::script::parse_mode::raw_data;

        case bc_script_parse_mode__raw_data_fallback:
            return libbitcoin::chain::script::parse_mode::raw_data_fallback;
    }
}
*/

