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
#include <bitcoin/bitcoin/c/wallet/message.h>
#include <bitcoin/bitcoin/c/internal/wallet/message.hpp>

#include <bitcoin/bitcoin/c/internal/math/elliptic_curve.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/wallet/ec_private.hpp>
#include <bitcoin/bitcoin/c/internal/wallet/payment_address.hpp>

extern "C" {

BC_IMPLEMENT_BYTE_ARRAY__CUSTOM_NAMESPACE(
    message_signature, libbitcoin::wallet);

bc_hash_digest_t* bc_hash_message(const bc_data_chunk_t* message)
{
    return bc_create_hash_digest_Internal(
        libbitcoin::wallet::hash_message(*message->obj));
}

bool bc_sign_message(bc_message_signature_t* signature,
    const bc_data_chunk_t* message, const bc_ec_private_t* secret)
{
    return libbitcoin::wallet::sign_message(*signature->obj,
        *message->obj, *secret->obj);
}

bool bc_sign_message_String(bc_message_signature_t* out_signature,
    const bc_data_chunk_t* message, const char* wif)
{
    return libbitcoin::wallet::sign_message(*out_signature->obj,
        *message->obj, wif);
}

bool bc_sign_message_Secret(bc_message_signature_t* out_signature,
    const bc_data_chunk_t* message, const bc_ec_secret_t* secret)
{
    return libbitcoin::wallet::sign_message(*out_signature->obj,
        *message->obj, *secret->obj);
}
bool bc_sign_message_Secret_nocompress(bc_message_signature_t* out_signature,
    const bc_data_chunk_t* message, const bc_ec_secret_t* secret)
{
    return libbitcoin::wallet::sign_message(*out_signature->obj,
        *message->obj, *secret->obj, false);
}

bool bc_verify_message(const bc_data_chunk_t* message,
    const bc_payment_address_t* address,
    const bc_message_signature_t* signature)
{
    return libbitcoin::wallet::verify_message(*message->obj, *address->obj,
        *signature->obj);
}

bool bc_recovery_id_to_magic(uint8_t* out_magic, uint8_t recovery_id,
    bool compressed)
{
    return libbitcoin::wallet::recovery_id_to_magic(
        *out_magic, recovery_id, compressed);
}

bool bc_magic_to_recovery_id(uint8_t* out_recovery_id, bool* out_compressed,
    uint8_t magic)
{
    return libbitcoin::wallet::magic_to_recovery_id(
        *out_recovery_id, *out_compressed, magic);
}

}

