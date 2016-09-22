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
#ifndef LIBBITCOIN_C_WALLET_MESSAGE_H
#define LIBBITCOIN_C_WALLET_MESSAGE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <bitcoin/bitcoin/c/math/elliptic_curve.h>
#include <bitcoin/bitcoin/c/math/hash.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/wallet/ec_private.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A message signature is an EC signature with one prefix byte.
 */
BC_DECLARE_BYTE_ARRAY(message_signature);

/**
 * Hashes a messages in preparation for signing.
 */
bc_hash_digest_t* bc_hash_message(const bc_data_chunk_t* message);

/**
 * Signs a message using deterministic signature.
 * @param[in] out_signature The signature in Bitcoin's own format.
 * This should be base64 encoded for presentation to the user.
 * @return true if wif is valid and signature encoding is successful.
 */
bool bc_sign_message(bc_message_signature_t* signature,
    const bc_data_chunk_t* message, const bc_ec_private_t* secret);

/**
 * Signs a message using deterministic signature.
 * @param[in] out_signature The signature in Bitcoin's own format.
 * This should be base64 encoded for presentation to the user.
 * @return true if wif is valid and signature encoding is successful.
 */
bool bc_sign_message_String(bc_message_signature_t* out_signature,
    const bc_data_chunk_t* message, const char* wif);

/**
 * Signs a message using deterministic signature.
 * @param[in] out_signature The signature in Bitcoin's own format.
 * This should be base64 encoded for presentation to the user.
 * @param[in] compressed true if the bitcoin address derived from the
 * private key is in compressed format.
 * @return true if signature encoding is successful.
 */
bool bc_sign_message_Secret(bc_message_signature_t* out_signature,
    const bc_data_chunk_t* message, const bc_ec_secret_t* secret);
bool bc_sign_message_Secret_nocompress(bc_message_signature_t* out_signature,
    const bc_data_chunk_t* message, const bc_ec_secret_t* secret);

/**
 * Verifies a message.
 * @param signature a message signature in Bitcoin's own format.
 * The user will generally provide this as a base64 string,
 * which the user interface must decode.
 * @return false if the signature does not match the address or if there are
 * any errors in the signature encoding.
 */
bool bc_verify_message(const bc_data_chunk_t* message,
    const bc_payment_address_t* address,
    const bc_message_signature_t* signature);

/// Exposed primarily for independent testability.
bool bc_recovery_id_to_magic(uint8_t* out_magic, uint8_t recovery_id,
    bool compressed);

/// Exposed primarily for independent testability.
bool bc_magic_to_recovery_id(uint8_t* out_recovery_id, bool* out_compressed,
    uint8_t magic);

#ifdef __cplusplus
}
#endif

#endif

