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
#ifndef LIBBITCOIN_C_WALLET_ENCRYPTED_KEYS_H
#define LIBBITCOIN_C_WALLET_ENCRYPTED_KEYS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <bitcoin/bitcoin/c/math/elliptic_curve.h>
#include <bitcoin/bitcoin/c/utility/data.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The maximum lot and sequence values for encrypted key token creation.
 */
uint32_t bc_ek_max_lot();
uint32_t bc_ek_max_sequence();

/**
 * A seed for use in creating an intermediate passphrase (token).
 */
BC_DECLARE_BYTE_ARRAY(ek_salt);

/**
 * A seed for use in creating an intermediate passphrase (token).
 */
BC_DECLARE_BYTE_ARRAY(ek_entropy);

/**
 * A seed for use in creating a key pair.
 */
BC_DECLARE_BYTE_ARRAY(ek_seed);

/**
 * An intermediate passphrase (token) type (checked but not base58 encoded).
 */
size_t bc_encrypted_token_encoded_size();
size_t bc_encrypted_token_decoded_size();
BC_DECLARE_BYTE_ARRAY(encrypted_token);

/**
 * An encrypted private key type (checked but not base58 encoded).
 */
size_t bc_ek_private_encoded_size();
size_t bc_ek_private_decoded_size();
BC_DECLARE_BYTE_ARRAY(encrypted_private);

/**
 * DEPRECATED
 * An encrypted public key type (checked but not base58 encoded).
 * This is refered to as a confirmation code in bip38.
 */
size_t bc_encrypted_public_encoded_size();
size_t bc_encrypted_public_decoded_size();
BC_DECLARE_BYTE_ARRAY(encrypted_public);

// BIP38
// It is requested that the unused flag bytes NOT be used for denoting that
// the key belongs to an alt-chain [This shoud read "flag bits"].
typedef enum bc_ek_flag_t
{
    bc_ek_flag__lot_sequence_key = 1 << 2,
    bc_ek_flag__ec_compressed_key = 1 << 5,
    bc_ek_flag__ec_non_multiplied_low = 1 << 6,
    bc_ek_flag__ec_non_multiplied_high = 1 << 7,

    /// Two bits are used to represent "not multiplied".
    bc_ek_flag__ec_non_multiplied = (
        bc_ek_flag__ec_non_multiplied_low | bc_ek_flag__ec_non_multiplied_high)

} bc_ek_flag_t;

// TODO: these calls require ICU
#if 0

/**
 * Create an intermediate passphrase for subsequent key pair generation.
 * @param[out] out_token   The new intermediate passphrase.
 * @param[in]  passphrase  A passphrase for use in the encryption.
 * @param[in]  entropy     A random value for use in the encryption.
 * @return false if the token could not be created from the entropy.
 */
bool bc_create_token(bc_encrypted_token_t* out_token,
    const char* passphrase, const bc_ek_entropy_t* entropy);

/**
 * Create an intermediate passphrase for subsequent key pair generation.
 * @param[out] out_token   The new intermediate passphrase.
 * @param[in]  passphrase  A passphrase for use in the encryption.
 * @param[in]  salt        A random value for use in the encryption.
 * @param[in]  lot         A lot, max allowed value 1048575 (2^20-1).
 * @param[in]  sequence    A sequence, max allowed value 4095 (2^12-1).
 * @return false if the lot and/or sequence are out of range or the token
 * could not be created from the entropy.
 */
bool bc_create_token_Salt(bc_encrypted_token_t* out_token,
    const char* passphrase, const bc_ek_salt_t* salt, uint32_t lot,
    uint32_t sequence);

#endif

/**
 * Create an encrypted private key from an intermediate passphrase.
 * The `out_point` paramter is always compressed, so to use it it should be 
 * decompressed as necessary to match the state of the `compressed` parameter.
 * @param[out] out_private  The new encrypted private key.
 * @param[out] out_point    The ec compressed public key of the new key pair.
 * @param[in]  token        An intermediate passphrase string.
 * @param[in]  seed         A random value for use in the encryption.
 * @param[in]  version      The coin address version byte.
 * @param[in]  compressed   Set true to associate ec public key compression.
 * @return false if the token checksum is not valid.
 */
bool bc_create_key_pair(bc_encrypted_private_t* out_private,
    bc_ec_compressed_t* out_point, const bc_encrypted_token_t* token,
    const bc_ek_seed_t* seed, uint8_t version);
bool bc_create_key_pair_nocompress(bc_encrypted_private_t* out_private,
    bc_ec_compressed_t* out_point, const bc_encrypted_token_t* token,
    const bc_ek_seed_t* seed, uint8_t version);

#ifdef __cplusplus
}
#endif

#endif

