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
    all = 0x01,

    /// Signs all of the inputs but none of the outputs, allowing anyone to
    /// change where the satoshis are going unless other signatures using 
    /// other signature hash flags protect the outputs.
    none = 0x02,

    /// The only output signed is the one corresponding to this input (the
    /// output with the same output index number as this input), ensuring
    /// nobody can change your part of the transaction but allowing other 
    /// signers to change their part of the transaction. The corresponding 
    /// output must exist or the value '1' will be signed, breaking the
    /// security scheme. This input, as well as other inputs, are included
    /// in the signature. The sequence numbers of other inputs are not
    /// included in the signature, and can be updated.
    single = 0x03,

    /// The above types can be modified with this flag, creating three new
    /// combined types.
    anyone_can_pay = 0x80,

    /// Signs all of the outputs but only this one input, and it also allows
    /// anyone to add or remove other inputs, so anyone can contribute
    /// additional satoshis but they cannot change how many satoshis are
    /// sent nor where they go.
    all_anyone_can_pay = all | anyone_can_pay,

    /// Signs only this one input and allows anyone to add or remove other
    /// inputs or outputs, so anyone who gets a copy of this input can spend
    /// it however they'd like.
    none_anyone_can_pay = none | anyone_can_pay,

    /// Signs this one input and its corresponding output. Allows anyone to
    /// add or remove other inputs.
    single_anyone_can_pay = single | anyone_can_pay,

    /// Used to mask off the anyone_can_pay flag to access the enumeration.
    mask = ~anyone_can_pay

} bc_signature_hash_algorithm_t;

typedef enum bc_script_parse_mode_t
{
    bc_script_parse_mode_strict,
    bc_script_parse_mode_raw_data,
    bc_script_parse_mode_raw_data_fallback

} bc_script_parse_mode_t;

typedef struct bc_script_t bc_script_t;
// Static functions
bc_script_t* bc_script_factory_from_data(const bc_data_chunk_t* data,
    bool prefix, bc_script_parse_mode_t mode);
// TODO: need transaction type for
//   verify
//   gen sighash
//   create endorsement
bool bc_script_is_active(uint32_t flags, bc_script_context_t flag);
//   checksig
// Constructor
bc_script_t* bc_create_script();
// Destructor
void bc_destroy_script(bc_script_t* self);
// Member functions
bc_script_pattern_t bc_script_pattern(const bc_script_t* self);
bool bc_script_is_raw_data(const bc_script_t* self);
bool bc_script_from_data(bc_script_t* self, const bc_data_chunk_t* data,
    bool prefix, bc_script_parse_mode_t mode);
bc_data_chunk_t* bc_script_to_data(const bc_script_t* self, bool prefix);
bool bc_script_from_string(bc_script_t* self, const char* human_readable);
bc_string_t* bc_script_to_string(const bc_script_t* self, uint32_t flags);
bool bc_script_is_valid(const bc_script_t* self);
void bc_script_reset(bc_script_t* self);
uint64_t bc_script_satoshi_content_size(const bc_script_t* self);
uint64_t bc_script_serialized_size(const bc_script_t* self, bool prefix);
// Member variables
bc_operation_stack_t* bc_script_operations(const bc_script_t* self);
void bc_script_set_operations(const bc_script_t* self,
    const bc_operation_stack_t* operations);

#ifdef __cplusplus
}
#endif

#endif

