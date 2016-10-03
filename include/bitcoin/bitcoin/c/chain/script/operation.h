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
#ifndef LIBBITCOIN_C_CHAIN_SCRIPT_OPERATION_H
#define LIBBITCOIN_C_CHAIN_SCRIPT_OPERATION_H

#include <bitcoin/bitcoin/c/chain/script/opcode.h>
#include <bitcoin/bitcoin/c/math/elliptic_curve.h>
#include <bitcoin/bitcoin/c/math/hash.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>
#include <bitcoin/bitcoin/c/utility/vector.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Script patterms.
/// Comments from: bitcoin.org/en/developer-guide#signature-hash-types
typedef enum bc_script_pattern_t
{
    /// Null Data
    /// Pubkey Script: OP_RETURN <0 to 80 bytes of data> (formerly 40 bytes)
    /// Null data scripts cannot be spent, so there's no signature script.
    bc_script_pattern__null_data,

    /// Pay to Multisig [BIP11]
    /// Pubkey script: <m> <A pubkey>[B pubkey][C pubkey...] <n> OP_CHECKMULTISIG
    /// Signature script: OP_0 <A sig>[B sig][C sig...]
    bc_script_pattern__pay_multisig,

    /// Pay to Public Key (obsolete)
    bc_script_pattern__pay_public_key,

    /// Pay to Public Key Hash [P2PKH]
    /// Pubkey script: OP_DUP OP_HASH160 <PubKeyHash> OP_EQUALVERIFY OP_CHECKSIG
    /// Signature script: <sig> <pubkey>
    bc_script_pattern__pay_key_hash,

    /// Pay to Script Hash [P2SH/BIP16]
    /// The redeem script may be any pay type, but only multisig makes sense.
    /// Pubkey script: OP_HASH160 <Hash160(redeemScript)> OP_EQUAL
    /// Signature script: <sig>[sig][sig...] <redeemScript>
    bc_script_pattern__pay_script_hash,

    /// Sign Multisig script [BIP11]
    bc_script_pattern__sign_multisig,

    /// Sign Public Key (obsolete)
    bc_script_pattern__sign_public_key,

    /// Sign Public Key Hash [P2PKH]
    bc_script_pattern__sign_key_hash,

    /// Sign Script Hash [P2SH/BIP16]
    bc_script_pattern__sign_script_hash,

    /// The script is valid but does not conform to the standard tempaltes.
    /// Such scripts are always accepted if they are mined into blocks, but
    /// transactions with non-standard scripts may not be forwarded by peers.
    bc_script_pattern__non_standard

} bc_script_pattern_t;

typedef struct bc_operation_t bc_operation_t;

BC_DECLARE_VECTOR(operation_stack, bc_operation_t);

size_t bc_operation__max_null_data_size();
bc_operation_t* bc_operation__factory_from_data(const bc_data_chunk_t* data);
bool bc_operation__is_push_only(const bc_operation_stack_t* operations);
/// unspendable pattern (standard)
bool bc_operation__is_null_data_pattern(const bc_operation_stack_t* ops);
/// payment script patterns (standard)
bool bc_operation__is_pay_multisig_pattern(const bc_operation_stack_t* ops);
bool bc_operation__is_public_key_pattern(const bc_operation_stack_t* ops);
bool bc_operation__is_pay_key_hash_pattern(const bc_operation_stack_t* ops);
bool bc_operation__is_pay_script_hash_pattern(const bc_operation_stack_t* ops);
/// signature script patterns (standard)
bool bc_operation__is_sign_multisig_pattern(const bc_operation_stack_t* ops);
bool bc_operation__is_sign_public_key_pattern(const bc_operation_stack_t* ops);
bool bc_operation__is_sign_key_hash_pattern(const bc_operation_stack_t* ops);
bool bc_operation__is_sign_script_hash_pattern(const bc_operation_stack_t* ops);
/// stack factories
bc_operation_stack_t* bc_operation__to_null_data_pattern(
    const bc_data_chunk_t* data);
bc_operation_stack_t* bc_operation__to_pay_multisig_pattern_PointList(
    uint8_t signatures,
    const bc_point_list_t* points);
bc_operation_stack_t* bc_operation__to_pay_multisig_pattern(
    uint8_t signatures,
    const bc_data_stack_t* points);
bc_operation_stack_t* bc_operation__to_pay_public_key_pattern(
    const bc_data_chunk_t* point);
bc_operation_stack_t* bc_operation_to_pay_key_hash_pattern(
    const bc_short_hash_t* hash);
bc_operation_stack_t* bc_operation__to_pay_script_hash_pattern(
    const bc_short_hash_t* hash);

bc_operation_t* bc_create_operation();
void bc_destroy_operation(bc_operation_t* self);

// Class members
bool bc_operation__from_data(bc_operation_t* self, const bc_data_chunk_t* data);
bc_data_chunk_t* bc_operation__to_data(const bc_operation_t* self);
bc_string_t* bc_operation__to_string(
    const bc_operation_t* self, uint32_t flags);
bool bc_operation__is_valid(const bc_operation_t* self);
void bc_operation__reset(bc_operation_t* self);
uint64_t bc_operation__serialized_size(const bc_operation_t* self);

bc_opcode_t bc_operation__code(const bc_operation_t* self);
void bc_operation__set_code(bc_operation_t* self, bc_opcode_t code);
bc_data_chunk_t* bc_operation__data(const bc_operation_t* self);
void bc_operation__set_data(bc_operation_t* self, bc_data_chunk_t* data);

#ifdef __cplusplus
}
#endif

#endif

