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
#ifndef LIBBITCOIN_C_HASH_H
#define LIBBITCOIN_C_HASH_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <bitcoin/bitcoin/c/math/uint256.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>
#include <bitcoin/bitcoin/c/utility/vector.h>

#ifdef __cplusplus
extern "C" {
#endif

// Common bitcoin hash container sizes.
size_t bc_hash_size();
size_t bc_half_hash_size();
size_t bc_quarter_hash_size();
size_t bc_long_hash_size();
size_t bc_short_hash_size();
size_t bc_mini_hash_size();

// Common bitcoin hash containers.
#define BC_DECLARE_HASH_TYPE(hashtype) \
    typedef struct bc_##hashtype##_t bc_##hashtype##_t; \
    bc_##hashtype##_t* bc_create_##hashtype(); \
    bc_##hashtype##_t* bc_create_##hashtype##_Array(const uint8_t* data); \
    void bc_destroy_##hashtype(bc_##hashtype##_t* self); \
    uint8_t* bc_##hashtype##__data(bc_##hashtype##_t* self); \
    const uint8_t* bc_##hashtype##__cdata(const bc_##hashtype##_t* self); \
    bc_string_t* bc_##hashtype##__encode_base16( \
        const bc_##hashtype##_t* self); \
    bool bc_##hashtype##__equals(const bc_##hashtype##_t* self, \
        const bc_##hashtype##_t* other); \

BC_DECLARE_HASH_TYPE(hash_digest);
BC_DECLARE_HASH_TYPE(half_hash);
BC_DECLARE_HASH_TYPE(quarter_hash);
BC_DECLARE_HASH_TYPE(long_hash);
BC_DECLARE_HASH_TYPE(short_hash);
BC_DECLARE_HASH_TYPE(mini_hash);

#undef BC_DECLARE_HASH_TYPE

// Lists of common bitcoin hashes.
BC_DECLARE_VECTOR(hash_list, bc_hash_digest_t);
BC_DECLARE_VECTOR(half_hash_list, bc_half_hash_t);
BC_DECLARE_VECTOR(quarter_hash_list, bc_quarter_hash_t);
BC_DECLARE_VECTOR(long_hash_list, bc_long_hash_t);
BC_DECLARE_VECTOR(short_hash_list, bc_short_hash_t);
BC_DECLARE_VECTOR(mini_hash_list, bc_mini_hash_t);

// You must use bc_destroy_hash_digest() to delete the result.
bc_hash_digest_t* bc_null_hash();
bc_half_hash_t* bc_null_half_hash();
bc_quarter_hash_t* bc_null_quarter_hash();
bc_long_hash_t* bc_null_long_hash();
bc_short_hash_t* bc_null_short_hash();
bc_mini_hash_t* bc_null_mini_hash();

bc_uint256_t* to_uint256(const bc_hash_digest_t* hash);

/// Generate a scrypt hash of specified length.
bc_data_chunk_t* bc_scrypt(
    const bc_data_chunk_t* data, const bc_data_chunk_t* salt,
    uint64_t N, uint32_t p, uint32_t r, size_t length);

/// Generate a bitcoin hash.
bc_hash_digest_t* bc_bitcoin_hash(const bc_data_chunk_t* data);

/// Generate a bitcoin short hash.
bc_short_hash_t* bc_bitcoin_short_hash(const bc_data_chunk_t* data);

/// Generate a ripemd160 hash
bc_short_hash_t* bc_ripemd160_hash(const bc_data_chunk_t* data);
bc_data_chunk_t* bc_ripemd160_hash_chunk(const bc_data_chunk_t* data);

/// Generate a sha1 hash.
bc_short_hash_t* bc_sha1_hash(const bc_data_chunk_t* data);
bc_data_chunk_t* bc_sha1_hash_chunk(const bc_data_chunk_t* data);

/// Generate a sha256 hash.
bc_hash_digest_t* bc_sha256_hash(const bc_data_chunk_t* data);
bc_data_chunk_t* bc_sha256_hash_chunk(const bc_data_chunk_t* data);

/// Generate a sha256 hash.
/// This hash function was used in electrum seed stretching (obsoleted).
bc_hash_digest_t* bc_sha256_hash_Double(
    const bc_data_chunk_t* first, const bc_data_chunk_t* second);

// Generate a hmac sha256 hash.
bc_hash_digest_t* bc_hmac_sha256_hash(
    const bc_data_chunk_t* data, const bc_data_chunk_t* key);

/// Generate a sha512 hash.
bc_long_hash_t* bc_sha512_hash(const bc_data_chunk_t* data);

/// Generate a hmac sha512 hash.
bc_long_hash_t* bc_hmac_sha512_hash(
    const bc_data_chunk_t* data, const bc_data_chunk_t* key);

/// Generate a pkcs5 pbkdf2 hmac sha512 hash.
bc_long_hash_t* bc_pkcs5_pbkdf2_hmac_sha512(
    const bc_data_chunk_t* passphrase,
    const bc_data_chunk_t* salt, size_t iterations);

#ifdef __cplusplus
}
#endif

#endif

