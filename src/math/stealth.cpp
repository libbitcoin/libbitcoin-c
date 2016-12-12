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
#include <bitcoin/bitcoin/c/math/stealth.h>

#include <bitcoin/bitcoin/math/stealth.hpp>
#include <bitcoin/bitcoin/c/internal/chain/script.hpp>
#include <bitcoin/bitcoin/c/internal/math/elliptic_curve.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/utility/binary.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>

extern "C" {

uint8_t bc_ephemeral_public_key_sign()
{
    return libbitcoin::ephemeral_public_key_sign;
}

/// Determine if the script is a null-data script of at least 32 data bytes.
bool bc_is_stealth_script(const bc_script_t* script)
{
    return libbitcoin::is_stealth_script(*script->obj);
}

/// Convert a stealth info script to a prefix usable for stealth.
bool bc_to_stealth_prefix(uint32_t* out_prefix, const bc_script_t* script)
{
    return libbitcoin::to_stealth_prefix(*out_prefix, *script->obj);
}

/// Create a valid stealth ephemeral private key from the provided seed.
bool bc_create_ephemeral_key(bc_ec_secret_t* out_secret,
    const bc_data_chunk_t* seed)
{
    return libbitcoin::create_ephemeral_key(*out_secret->obj, *seed->obj);
}

/// Create an ephemeral public key from the provided seed with the
/// null-data script data value that produces the desired filter prefix.
bool bc_create_stealth_data(bc_data_chunk_t* out_stealth_data,
    bc_ec_secret_t* out_secret, const bc_binary_t* filter,
    const bc_data_chunk_t* seed)
{
    return libbitcoin::create_stealth_data(*out_stealth_data->obj,
        *out_secret->obj, *filter->obj, *seed->obj);
}

/// Extract the stealth ephemeral public key from an output script.
bool bc_extract_ephemeral_key(
    bc_ec_compressed_t* out_ephemeral_public_key, const bc_script_t* script)
{
    return libbitcoin::extract_ephemeral_key(
        *out_ephemeral_public_key->obj, *script->obj);
}

/// Extract the unsigned stealth ephemeral public key from an output script.
bool bc_extract_ephemeral_key_Hash(
    bc_hash_digest_t* out_unsigned_ephemeral_key, const bc_script_t* script)
{
    return libbitcoin::extract_ephemeral_key(
        *out_unsigned_ephemeral_key->obj, *script->obj);
}

/// Calculate the shared secret.
bool bc_shared_secret(bc_ec_secret_t* out_shared, const bc_ec_secret_t* secret,
    const bc_ec_compressed_t* point)
{
    return libbitcoin::shared_secret(
        *out_shared->obj, *secret->obj, *point->obj);
}

/// Uncover the stealth public key.
bool bc_uncover_stealth_Public(bc_ec_compressed_t* out_stealth,
    const bc_ec_compressed_t* ephemeral_or_scan,
    const bc_ec_secret_t* scan_or_ephemeral,
    const bc_ec_compressed_t* spend)
{
    return libbitcoin::uncover_stealth(*out_stealth->obj,
        *ephemeral_or_scan->obj, *scan_or_ephemeral->obj, *spend->obj);
}

/// Uncover the stealth secret.
bool bc_uncover_stealth_Secret(bc_ec_secret_t* out_stealth,
    const bc_ec_compressed_t* ephemeral_or_scan,
    const bc_ec_secret_t* scan_or_ephemeral,
    const bc_ec_secret_t* spend)
{
    return libbitcoin::uncover_stealth(*out_stealth->obj,
        *ephemeral_or_scan->obj, *scan_or_ephemeral->obj, *spend->obj);
}

} // extern C

