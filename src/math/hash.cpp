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
#include <bitcoin/bitcoin/c/math/hash.h>

#include <bitcoin/bitcoin/formats/base_16.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>

extern "C" {

size_t bc_hash_size()
{
    return libbitcoin::hash_size;
}
size_t bc_half_hash_size()
{
    return libbitcoin::half_hash_size;
}
size_t bc_quarter_hash_size()
{
    return libbitcoin::quarter_hash_size;
}
size_t bc_long_hash_size()
{
    return libbitcoin::long_hash_size;
}
size_t bc_short_hash_size()
{
    return libbitcoin::short_hash_size;
}
size_t bc_mini_hash_size()
{
    return libbitcoin::mini_hash_size;
}

#define HASH_IMPL(hashtype) \
    \
    bc_##hashtype##_t* bc_create_##hashtype() \
    { \
        bc_##hashtype##_t* self = new bc_##hashtype##_t; \
        self->obj = new libbitcoin::hashtype; \
        return self; \
    } \
    bc_##hashtype##_t* bc_create_##hashtype##_Array(const uint8_t* data) \
    { \
        bc_##hashtype##_t* self = bc_create_##hashtype(); \
        std::copy(data, data + self->obj->size(), self->obj->begin()); \
        return self; \
    } \
    void bc_destroy_##hashtype(bc_##hashtype##_t* self) \
    { \
        delete self->obj; \
        delete self; \
    } \
    uint8_t* bc_##hashtype##_data(bc_##hashtype##_t* self) \
    { \
        return self->obj->data(); \
    } \
    const uint8_t* bc_##hashtype##_cdata(const bc_##hashtype##_t* self) \
    { \
        return self->obj->data(); \
    } \
    bc_string_t* bc_##hashtype##_encode_base16( \
        const bc_##hashtype##_t* self) \
    { \
        return bc_create_string_StdString( \
            libbitcoin::encode_base16(*self->obj)); \
    } \
    bool bc_##hashtype##_equals(const bc_##hashtype##_t* self, \
        const bc_##hashtype##_t* other) \
    { \
        return *self->obj == *other->obj; \
    } \
    \
    /* Internal constructor for this unit. */ \
    bc_##hashtype##_t* bc_create_##hashtype##_Internal( \
        const libbitcoin::hashtype& value) \
    { \
        bc_##hashtype##_t* self = new bc_##hashtype##_t; \
        self->obj = new libbitcoin::hashtype(value); \
        return self; \
    }

HASH_IMPL(hash_digest);
HASH_IMPL(half_hash);
HASH_IMPL(quarter_hash);
HASH_IMPL(long_hash);
HASH_IMPL(short_hash);
HASH_IMPL(mini_hash);

#undef HASH_IMPL

bc_hash_digest_t* bc_null_hash()
{
    return bc_create_hash_digest_Internal(libbitcoin::null_hash);
}
bc_half_hash_t* bc_null_half_hash()
{
    return bc_create_half_hash_Internal(libbitcoin::null_half_hash);
}
bc_quarter_hash_t* bc_null_quarter_hash()
{
    return bc_create_quarter_hash_Internal(libbitcoin::null_quarter_hash);
}
bc_long_hash_t* bc_null_long_hash()
{
    return bc_create_long_hash_Internal(libbitcoin::null_long_hash);
}
bc_short_hash_t* bc_null_short_hash()
{
    return bc_create_short_hash_Internal(libbitcoin::null_short_hash);
}
bc_mini_hash_t* bc_null_mini_hash()
{
    return bc_create_mini_hash_Internal(libbitcoin::null_mini_hash);
}

bc_short_hash_t* bc_ripemd160_hash(const bc_data_chunk_t* data)
{
    return bc_create_short_hash_Internal(
        libbitcoin::ripemd160_hash(*data->obj));
}

bc_short_hash_t* bc_sha1_hash(const bc_data_chunk_t* data)
{
    return bc_create_short_hash_Internal(
        libbitcoin::sha1_hash(*data->obj));
}

bc_hash_digest_t* bc_sha256_hash(const bc_data_chunk_t* data)
{
    return bc_create_hash_digest_Internal(
        libbitcoin::sha256_hash(*data->obj));
}

bc_hash_digest_t* bc_sha256_hash_double(
    const bc_data_chunk_t* first, const bc_data_chunk_t* second)
{
    return bc_create_hash_digest_Internal(
        libbitcoin::sha256_hash(*first->obj, *second->obj));
}

bc_hash_digest_t* bc_hmac_sha256_hash(
    const bc_data_chunk_t* data, const bc_data_chunk_t* key)
{
    return bc_create_hash_digest_Internal(
        libbitcoin::hmac_sha256_hash(*data->obj, *key->obj));
}

bc_long_hash_t* bc_sha512_hash(const bc_data_chunk_t* data)
{
    return bc_create_long_hash_Internal(
        libbitcoin::sha512_hash(*data->obj));
}

bc_long_hash_t* bc_hmac_sha512_hash(
    const bc_data_chunk_t* data, const bc_data_chunk_t* key)
{
    return bc_create_long_hash_Internal(
        libbitcoin::hmac_sha512_hash(*data->obj, *key->obj));
}

bc_long_hash_t* bc_pkcs5_pbkdf2_hmac_sha512(
    const bc_data_chunk_t* passphrase,
    const bc_data_chunk_t* salt, size_t iterations)
{
    return bc_create_long_hash_Internal(
        libbitcoin::pkcs5_pbkdf2_hmac_sha512(
            *passphrase->obj, *salt->obj, iterations));
}

bc_hash_digest_t* bc_bitcoin_hash(const bc_data_chunk_t* data)
{
    return bc_create_hash_digest_Internal(
        libbitcoin::bitcoin_hash(*data->obj));
}

bc_short_hash_t* bc_bitcoin_short_hash(const bc_data_chunk_t* data)
{
    return bc_create_short_hash_Internal(
        libbitcoin::bitcoin_short_hash(*data->obj));
}

bc_data_chunk_t* bc_scrypt(
    const bc_data_chunk_t* data, const bc_data_chunk_t* salt,
    uint64_t N, uint32_t p, uint32_t r, size_t length)
{
    auto result_chunk = libbitcoin::scrypt(
        *data->obj, *salt->obj, N, p, r, length);
    bc_data_chunk_t* result = bc_create_data_chunk_Array(
        result_chunk.data(), result_chunk.size());
    return result;
}

} // extern C

