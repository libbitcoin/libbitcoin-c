/**
 * Copyright (c) 2011-2016 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * libbitcoin is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
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
#include "hash.hpp"

#include <boost/test/unit_test.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/bitcoin.h>

using namespace bc;

BOOST_AUTO_TEST_SUITE(hash_tests_c)

BOOST_AUTO_TEST_CASE(sha1_hash_test_c)
{
    for (const auto& result: sha1_tests)
    {
        bc_data_chunk_t* data = bc_create_data_chunk();
        BOOST_REQUIRE(bc_decode_base16(data, result.input.data()));

        bc_short_hash_t* hash = bc_sha1_hash(data);

        bc_data_chunk_t* hash_chunk = bc_create_data_chunk_Array(
            bc_short_hash__data(hash), bc_short_hash_size());
        bc_string_t* encoded = bc_encode_base16(hash_chunk);
        bc_destroy_data_chunk(hash_chunk);

        BOOST_REQUIRE(bc_string__equals_cstr(encoded, result.result.data()));

        bc_destroy_string(encoded);
        bc_destroy_short_hash(hash);
        bc_destroy_data_chunk(data);
    }
}

BOOST_AUTO_TEST_CASE(ripemd_hash_test_c)
{
    for (const auto& result: ripemd_tests)
    {
        bc_data_chunk_t* data = bc_create_data_chunk();
        BOOST_REQUIRE(bc_decode_base16(data, result.input.data()));

        bc_short_hash_t* hash = bc_ripemd160_hash(data);

        bc_data_chunk_t* hash_chunk = bc_create_data_chunk_Array(
            bc_short_hash__data(hash), bc_short_hash_size());
        bc_string_t* encoded = bc_encode_base16(hash_chunk);
        bc_destroy_data_chunk(hash_chunk);

        BOOST_REQUIRE(bc_string__equals_cstr(encoded, result.result.data()));

        bc_destroy_string(encoded);
        bc_destroy_short_hash(hash);
        bc_destroy_data_chunk(data);
    }

    {
        const uint8_t data1[] = { 110 };
        bc_data_chunk_t* chunk1 = bc_create_data_chunk_Array(data1, 1);
        bc_short_hash_t* ripemd_hash1 = bc_bitcoin_short_hash(chunk1);

        bc_data_chunk_t* hash_chunk = bc_create_data_chunk_Array(
            bc_short_hash__data(ripemd_hash1), bc_short_hash_size());
        bc_string_t* encoded = bc_encode_base16(hash_chunk);
        bc_destroy_data_chunk(hash_chunk);

        BOOST_REQUIRE(bc_string__equals_cstr(encoded,
            "17d040b739d639c729daaf627eaff88cfe4207f4"));

        bc_destroy_string(encoded);
        bc_destroy_short_hash(ripemd_hash1);
        bc_destroy_data_chunk(chunk1);
    }

    {
        bc_data_chunk_t* chunk2 = bc_create_data_chunk();
        BOOST_REQUIRE(bc_decode_base16(chunk2,
            "020641fde3a85beb8321033516de7ec01c35de96e945bf76c3768784a905471986"));
        bc_short_hash_t* ripemd_hash2 = bc_bitcoin_short_hash(chunk2);

        bc_data_chunk_t* hash_chunk = bc_create_data_chunk_Array(
            bc_short_hash__data(ripemd_hash2), bc_short_hash_size());
        bc_string_t* encoded = bc_encode_base16(hash_chunk);
        bc_destroy_data_chunk(hash_chunk);

        BOOST_REQUIRE(bc_string__equals_cstr(encoded,
            "c23e37c6fad06deab545f952992c8f28cb02bbe5"));

        bc_destroy_string(encoded);
        bc_destroy_short_hash(ripemd_hash2);
        bc_destroy_data_chunk(chunk2);
    }
}

BOOST_AUTO_TEST_CASE(sha256_hash_test_c)
{
    for (const auto& result: sha256_tests)
    {
        bc_data_chunk_t* data = bc_create_data_chunk();
        BOOST_REQUIRE(bc_decode_base16(data, result.input.data()));

        bc_hash_digest_t* hash = bc_sha256_hash(data);

        bc_data_chunk_t* hash_chunk = bc_create_data_chunk_Array(
            bc_hash_digest__data(hash), bc_hash_size());
        bc_string_t* encoded = bc_encode_base16(hash_chunk);
        bc_destroy_data_chunk(hash_chunk);

        BOOST_REQUIRE(bc_string__equals_cstr(encoded, result.result.data()));

        bc_destroy_string(encoded);
        bc_destroy_hash_digest(hash);
        bc_destroy_data_chunk(data);
    }
}

BOOST_AUTO_TEST_CASE(hmac_sha256_hash_test_c)
{
    uint8_t chunk_data[] = { 'd', 'a', 't', 'a' };
    uint8_t key_data[] = { 'k', 'e', 'y' };

    bc_data_chunk_t* data = bc_create_data_chunk_Array(chunk_data, 4);
    bc_data_chunk_t* key = bc_create_data_chunk_Array(key_data, 3);

    bc_hash_digest_t* hash = bc_hmac_sha256_hash(data, key);

    bc_data_chunk_t* hash_chunk = bc_create_data_chunk_Array(
        bc_hash_digest__data(hash), bc_hash_size());
    bc_string_t* encoded = bc_encode_base16(hash_chunk);
    bc_destroy_data_chunk(hash_chunk);

    BOOST_REQUIRE(bc_string__equals_cstr(encoded,
        "5031fe3d989c6d1537a013fa6e739da23463fdaec3b70137d828e36ace221bd0"));

    bc_destroy_string(encoded);
    bc_destroy_hash_digest(hash);
    bc_destroy_data_chunk(data);
    bc_destroy_data_chunk(key);
}

BOOST_AUTO_TEST_CASE(hmac_sha512_hash_test_c)
{
    uint8_t chunk_data[] = { 'd', 'a', 't', 'a' };
    uint8_t key_data[] = { 'k', 'e', 'y' };

    bc_data_chunk_t* data = bc_create_data_chunk_Array(chunk_data, 4);
    bc_data_chunk_t* key = bc_create_data_chunk_Array(key_data, 3);

    bc_long_hash_t* hash = bc_hmac_sha512_hash(data, key);

    bc_data_chunk_t* hash_chunk = bc_create_data_chunk_Array(
        bc_long_hash__data(hash), bc_long_hash_size());
    bc_string_t* encoded = bc_encode_base16(hash_chunk);
    bc_destroy_data_chunk(hash_chunk);

    BOOST_REQUIRE(bc_string__equals_cstr(encoded,
        "3c5953a18f7303ec653ba170ae334fafa08e3846f2efe317b87efce82376253cb52a8c31ddcde5a3a2eee183c2b34cb91f85e64ddbc325f7692b199473579c58"));

    bc_destroy_string(encoded);
    bc_destroy_long_hash(hash);
    bc_destroy_data_chunk(data);
    bc_destroy_data_chunk(key);
}

BOOST_AUTO_TEST_CASE(sha512_hash_test_c)
{
    uint8_t chunk_data[] = { 'd', 'a', 't', 'a' };
    bc_data_chunk_t* data = bc_create_data_chunk_Array(chunk_data, 4);

    bc_long_hash_t* hash = bc_sha512_hash(data);

    bc_data_chunk_t* hash_chunk = bc_create_data_chunk_Array(
        bc_long_hash__data(hash), bc_long_hash_size());
    bc_string_t* encoded = bc_encode_base16(hash_chunk);
    bc_destroy_data_chunk(hash_chunk);

    BOOST_REQUIRE(bc_string__equals_cstr(encoded,
        "77c7ce9a5d86bb386d443bb96390faa120633158699c8844c30b13ab0bf92760b7e4416aea397db91b4ac0e5dd56b8ef7e4b066162ab1fdc088319ce6defc876"));

    bc_destroy_string(encoded);
    bc_destroy_long_hash(hash);
    bc_destroy_data_chunk(data);
}

BOOST_AUTO_TEST_CASE(pkcs5_pbkdf2_hmac_sha512_test_c)
{
    for (const auto& result: pkcs5_pbkdf2_hmac_sha512_tests)
    {
        bc_data_chunk_t* passphrase = bc_create_data_chunk_Array(
            reinterpret_cast<const uint8_t*>(result.passphrase.data()),
            result.passphrase.length());
        bc_data_chunk_t* salt = bc_create_data_chunk_Array(
            reinterpret_cast<const uint8_t*>(result.salt.data()),
            result.salt.length());

        bc_long_hash_t* hash = bc_pkcs5_pbkdf2_hmac_sha512(
            passphrase, salt, result.iterations);

        bc_data_chunk_t* hash_chunk = bc_create_data_chunk_Array(
            bc_long_hash__data(hash), bc_long_hash_size());
        bc_string_t* encoded = bc_encode_base16(hash_chunk);
        bc_destroy_data_chunk(hash_chunk);

        BOOST_REQUIRE(bc_string__equals_cstr(encoded, result.result.data()));

        bc_destroy_string(encoded);
        bc_destroy_long_hash(hash);
        bc_destroy_data_chunk(salt);
        bc_destroy_data_chunk(passphrase);
    }
}

BOOST_AUTO_TEST_SUITE_END()
