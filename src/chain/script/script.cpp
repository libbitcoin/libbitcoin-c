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
#include <bitcoin/bitcoin/c/chain/script/script.h>
#include <bitcoin/bitcoin/c/internal/chain/script/script.hpp>

#include <bitcoin/bitcoin/c/internal/chain/script/opcode.hpp>
#include <bitcoin/bitcoin/c/internal/chain/script/operation.hpp>
#include <bitcoin/bitcoin/c/internal/chain/transaction.hpp>
#include <bitcoin/bitcoin/c/internal/error.hpp>
#include <bitcoin/bitcoin/c/internal/math/elliptic_curve.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>

extern "C" {

// Static functions
bc_script_t* bc_script__factory_from_data(const bc_data_chunk_t* data,
    bool prefix, bc_script_parse_mode_t mode)
{
    const auto script = libbitcoin::chain::script::factory_from_data(
        *data->obj, prefix, bc_script_parse_mode_from_ctype(mode));
    return new bc_script_t{ new libbitcoin::chain::script(script) };
}

bool bc_script__is_enabled(uint32_t active_forks, bc_rule_fork_t flag)
{
    return libbitcoin::chain::script::is_enabled(
        active_forks, bc_rule_fork_from_ctype(flag));
}
bc_hash_digest_t* bc_script__generate_signature_hash(
    const bc_transaction_t* parent_tx, uint32_t input_index,
    const bc_script_t* script_code, uint8_t sighash_type)
{
    const auto hash = libbitcoin::chain::script::generate_signature_hash(
        *parent_tx->obj, input_index, *script_code->obj, sighash_type);
    return bc_create_hash_digest_Internal(hash);
}
bool bc_script__create_endorsement(
    bc_endorsement_t* out, const bc_ec_secret_t* secret,
    const bc_script_t* prevout_script, const bc_transaction_t* new_tx,
    uint32_t input_index, uint8_t sighash_type)
{
    return libbitcoin::chain::script::create_endorsement(
        *out->obj, *secret->obj, *prevout_script->obj, *new_tx->obj,
        input_index, sighash_type);
}
bool bc_script__check_signature(const bc_ec_signature_t* signature,
    uint8_t sighash_type, const bc_data_chunk_t* public_key,
    const bc_script_t* script_code, const bc_transaction_t* parent_tx,
    uint32_t input_index)
{
    return libbitcoin::chain::script::check_signature(
        *signature->obj, sighash_type, *public_key->obj,
        *script_code->obj, *parent_tx->obj, input_index);
}
bc_error_code_t* bc_script__verify(
    const bc_transaction_t* tx, uint32_t input_index,
    uint32_t flags)
{
    return new bc_error_code_t{ new std::error_code(
        libbitcoin::chain::script::verify(*tx->obj, input_index, flags)) };
}
bc_error_code_t* bc_script__verify_Script(
    const bc_transaction_t* tx, uint32_t input_index,
    const bc_script_t* prevout_script, uint32_t flags)
{
    return new bc_error_code_t{ new std::error_code(
        libbitcoin::chain::script::verify(
            *tx->obj, input_index, *prevout_script->obj, flags)) };
}

// Constructor
bc_script_t* bc_create_script()
{
    return new bc_script_t{ new libbitcoin::chain::script, true };
}
// Destructor
void bc_destroy_script(bc_script_t* self)
{
    if (self->delete_obj)
        delete self->obj;
    delete self;
}
// Member functions
bc_script_pattern_t bc_script__pattern(const bc_script_t* self)
{
    return bc_script_pattern_to_ctype(self->obj->pattern());
}
bool bc_script__is_raw_data(const bc_script_t* self)
{
    return self->obj->is_raw_data();
}
bool bc_script__from_data(bc_script_t* self, const bc_data_chunk_t* data,
    bool prefix, bc_script_parse_mode_t mode)
{
    return self->obj->from_data(*data->obj, prefix,
        bc_script_parse_mode_from_ctype(mode));
}
bc_data_chunk_t* bc_script__to_data(const bc_script_t* self, bool prefix)
{
    return bc_create_data_chunk_Internal(self->obj->to_data(prefix));
}

bool bc_script__from_string(bc_script_t* self, const char* human_readable)
{
    return self->obj->from_string(human_readable);
}
bc_string_t* bc_script__to_string(const bc_script_t* self, uint32_t flags)
{
    return bc_create_string_StdString(self->obj->to_string(flags));
}
bool bc_script__is_valid(const bc_script_t* self)
{
    return self->obj->is_valid();
}
void bc_script__reset(bc_script_t* self)
{
    self->obj->reset();
}
size_t bc_script__pay_script_hash_sigops(const bc_script_t* self,
    const bc_script_t* prevout)
{
    return self->obj->pay_script_hash_sigops(*prevout->obj);
}
size_t bc_script__sigops(const bc_script_t* self, bool serialized_script)
{
    return self->obj->sigops(serialized_script);
}
uint64_t bc_script__satoshi_content_size(const bc_script_t* self)
{
    return self->obj->satoshi_content_size();
}
uint64_t bc_script__serialized_size(const bc_script_t* self, bool prefix)
{
    return self->obj->serialized_size(prefix);
}

// Member variables
bc_operation_stack_t* bc_script__operations(const bc_script_t* self)
{
    return new bc_operation_stack_t{ &self->obj->operations, false };
}
void bc_script__set_operations(bc_script_t* self,
    const bc_operation_stack_t* operations)
{
    self->obj->operations = *operations->obj;
}

} // extern C

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

