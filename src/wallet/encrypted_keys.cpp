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
#include <bitcoin/bitcoin/c/wallet/encrypted_keys.h>
#include <bitcoin/bitcoin/c/internal/wallet/encrypted_keys.hpp>

#include <bitcoin/bitcoin/c/internal/math/elliptic_curve.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>

// Define these aliases so the macros for implementing byte array will work
namespace libbitcoin {
namespace wallet {
    BC_CONSTEXPR uint8_t encrypted_token_size = encrypted_token_decoded_size;
    BC_CONSTEXPR uint8_t encrypted_private_size = ek_private_decoded_size;
    BC_CONSTEXPR uint8_t encrypted_public_size = encrypted_public_decoded_size;
} // namespace wallet
} // namespace libbitcoin

extern "C" {

BC_IMPLEMENT_BYTE_ARRAY__CUSTOM_NAMESPACE(ek_salt, libbitcoin::wallet);

BC_IMPLEMENT_BYTE_ARRAY__CUSTOM_NAMESPACE(ek_entropy, libbitcoin::wallet);

BC_IMPLEMENT_BYTE_ARRAY__CUSTOM_NAMESPACE(ek_seed, libbitcoin::wallet);

size_t bc_encrypted_token_encoded_size()
{
    return libbitcoin::wallet::encrypted_token_encoded_size;
}
size_t bc_encrypted_token_decoded_size()
{
    return libbitcoin::wallet::encrypted_token_decoded_size;
}
BC_IMPLEMENT_BYTE_ARRAY__CUSTOM_NAMESPACE(
    encrypted_token, libbitcoin::wallet);

size_t bc_ek_private_encoded_size()
{
    return libbitcoin::wallet::ek_private_encoded_size;
}
size_t bc_ek_private_decoded_size()
{
    return libbitcoin::wallet::ek_private_decoded_size;
}
BC_IMPLEMENT_BYTE_ARRAY__CUSTOM_NAMESPACE(
    encrypted_private, libbitcoin::wallet);

size_t bc_encrypted_public_encoded_size()
{
    return libbitcoin::wallet::encrypted_public_encoded_size;
}
size_t bc_encrypted_public_decoded_size()
{
    return libbitcoin::wallet::encrypted_public_decoded_size;
}
BC_IMPLEMENT_BYTE_ARRAY__CUSTOM_NAMESPACE(
    encrypted_public, libbitcoin::wallet);

// TODO: these calls require ICU
#if 0

bool bc_create_token(bc_encrypted_token_t* out_token,
    const char* passphrase, const bc_ek_entropy_t* entropy)
{
    return libbitcoin::wallet::create_token(*out_token->obj,
        passphrase, *entropy->obj);
}

bool bc_create_token_Salt(bc_encrypted_token_t* out_token,
    const char* passphrase, const bc_ek_salt_t* salt, uint32_t lot,
    uint32_t sequence)
{
    return libbitcoin::wallet::create_token(*out_token->obj,
        passphrase, *salt->obj, lot, sequence);
}

#endif

bool bc_create_key_pair(bc_encrypted_private_t* out_private,
    bc_ec_compressed_t* out_point, const bc_encrypted_token_t* token,
    const bc_ek_seed_t* seed, uint8_t version)
{
    return libbitcoin::wallet::create_key_pair(*out_private->obj,
        *out_point->obj, *token->obj, *seed->obj, version);
}
bool bc_create_key_pair_nocompress(bc_encrypted_private_t* out_private,
    bc_ec_compressed_t* out_point, const bc_encrypted_token_t* token,
    const bc_ek_seed_t* seed, uint8_t version)
{
}

}

