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
#ifndef LIBBITCOIN_C_CHAIN_SCRIPT_SCRIPT_H
#define LIBBITCOIN_C_CHAIN_SCRIPT_SCRIPT_H

#include <bitcoin/bitcoin/c/chain/script/opcode.h>
#include <bitcoin/bitcoin/c/chain/script/operation.h>
#include <bitcoin/bitcoin/c/error.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Signature hash types.
/// Comments from: bitcoin.org/en/developer-guide#standard-transactions
typedef enum bc_signature_hash_algorithm_t
{
    /// The default, signs all the inputs and outputs, protecting everything
    /// except the signature scripts against modification.
    bc_signature_hash_algorithm__all = 0x01,

    /// Signs all of the inputs but none of the outputs, allowing anyone to
    /// change where the satoshis are going unless other signatures using 
    /// other signature hash flags protect the outputs.
    bc_signature_hash_algorithm__none = 0x02,

    /// The only output signed is the one corresponding to this input (the
    /// output with the same output index number as this input), ensuring
    /// nobody can change your part of the transaction but allowing other 
    /// signers to change their part of the transaction. The corresponding 
    /// output must exist or the value '1' will be signed, breaking the
    /// security scheme. This input, as well as other inputs, are included
    /// in the signature. The sequence numbers of other inputs are not
    /// included in the signature, and can be updated.
    bc_signature_hash_algorithm__single = 0x03,

    /// The above types can be modified with this flag, creating three new
    /// combined types.
    bc_signature_hash_algorithm__anyone_can_pay = 0x80,

    /// Signs all of the outputs but only this one input, and it also allows
    /// anyone to add or remove other inputs, so anyone can contribute
    /// additional satoshis but they cannot change how many satoshis are
    /// sent nor where they go.
    bc_signature_hash_algorithm__all_anyone_can_pay =
        bc_signature_hash_algorithm__all |
        bc_signature_hash_algorithm__anyone_can_pay,

    /// Signs only this one input and allows anyone to add or remove other
    /// inputs or outputs, so anyone who gets a copy of this input can spend
    /// it however they'd like.
    bc_signature_hash_algorithm__none_anyone_can_pay =
        bc_signature_hash_algorithm__none |
        bc_signature_hash_algorithm__anyone_can_pay,

    /// Signs this one input and its corresponding output. Allows anyone to
    /// add or remove other inputs.
    bc_signature_hash_algorithm__single_anyone_can_pay =
        bc_signature_hash_algorithm__single |
        bc_signature_hash_algorithm__anyone_can_pay,

    /// Used to mask off the anyone_can_pay flag to access the enumeration.
    bc_signature_hash_algorithm__mask =
        ~bc_signature_hash_algorithm__anyone_can_pay

} bc_signature_hash_algorithm_t;

typedef enum bc_script_parse_mode_t
{
    bc_script_parse_mode__strict,
    bc_script_parse_mode__raw_data,
    bc_script_parse_mode__raw_data_fallback

} bc_script_parse_mode_t;

// Forward declaration for methods below.
typedef struct bc_transaction_t bc_transaction_t;

typedef struct bc_script_t bc_script_t;
// Static functions
bc_script_t* bc_script__factory_from_data(const bc_data_chunk_t* data,
    bool prefix, bc_script_parse_mode_t mode);

bool bc_script__is_enabled(uint32_t active_forks, bc_rule_fork_t flag);
bc_hash_digest_t* bc_script__generate_signature_hash(
    const bc_transaction_t* parent_tx, uint32_t input_index,
    const bc_script_t* script_code, uint8_t sighash_type);
bool bc_script__create_endorsement(
    bc_endorsement_t* out, const bc_ec_secret_t* secret,
    const bc_script_t* prevout_script, const bc_transaction_t* new_tx,
    uint32_t input_index, uint8_t sighash_type);
bool bc_script__check_signature(const bc_ec_signature_t* signature,
    uint8_t sighash_type, const bc_data_chunk_t* public_key,
    const bc_script_t* script_code, const bc_transaction_t* parent_tx,
    uint32_t input_index);
bc_error_code_t* bc_script__verify(
    const bc_transaction_t* tx, uint32_t input_index,
    uint32_t flags);
bc_error_code_t* bc_script__verify_Script(
    const bc_transaction_t* tx, uint32_t input_index,
    const bc_script_t* prevout_script, uint32_t flags);

// Constructor
bc_script_t* bc_create_script();
// Destructor
void bc_destroy_script(bc_script_t* self);

// Member functions
bc_script_pattern_t bc_script__pattern(const bc_script_t* self);
bool bc_script__is_raw_data(const bc_script_t* self);
bool bc_script__from_data(bc_script_t* self, const bc_data_chunk_t* data,
    bool prefix, bc_script_parse_mode_t mode);
bc_data_chunk_t* bc_script__to_data(const bc_script_t* self, bool prefix);

bool bc_script__from_string(bc_script_t* self, const char* human_readable);
bc_string_t* bc_script__to_string(const bc_script_t* self, uint32_t flags);
bool bc_script__is_valid(const bc_script_t* self);
void bc_script__reset(bc_script_t* self);
size_t bc_script__pay_script_hash_sigops(const bc_script_t* self,
    const bc_script_t* prevout);
size_t bc_script__sigops(const bc_script_t* self, bool serialized_script);
uint64_t bc_script__satoshi_content_size(const bc_script_t* self);
uint64_t bc_script__serialized_size(const bc_script_t* self, bool prefix);

// Member variables
bc_operation_stack_t* bc_script__operations(const bc_script_t* self);
void bc_script__set_operations(bc_script_t* self,
    const bc_operation_stack_t* operations);

#ifdef __cplusplus
}
#endif

#endif

