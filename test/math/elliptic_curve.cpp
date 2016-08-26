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
#include <boost/test/unit_test.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/bitcoin.h>

using namespace bc;

BOOST_AUTO_TEST_SUITE(elliptic_curve_tests_c)

// Scenario 1
#define SECRET1 "8010b1bb119ad37d4b65a1022a314897b1b3614b345974332cb1b9582cf03536"
#define COMPRESSED1 "0309ba8621aefd3b6ba4ca6d11a4746e8df8d35d9b51b383338f627ba7fc732731"
#define UNCOMPRESSED1 "0409ba8621aefd3b6ba4ca6d11a4746e8df8d35d9b51b383338f627ba7fc7327318c3a6ec6acd33c36328b8fb4349b31671bcd3a192316ea4f6236ee1ae4a7d8c9"

// Scenario 2
#define COMPRESSED2 "03bc88a1bd6ebac38e9a9ed58eda735352ad10650e235499b7318315cc26c9b55b"
#define SIGHASH2 "ed8f9b40c2d349c8a7e58cebe79faa25c21b6bb85b874901f72a1b3f1ad0a67f"
#define SIGNATURE2 "3045022100bc494fbd09a8e77d8266e2abdea9aef08b9e71b451c7d8de9f63cda33a62437802206b93edd6af7c659db42c579eb34a3a4cb60c28b5a6bc86fd5266d42f6b8bb67d"

// Scenario 3
#define SECRET3 "ce8f4b713ffdd2658900845251890f30371856be201cd1f5b3d970f793634333"
#define SIGHASH3 "f89572635651b2e4f89778350616989183c98d1a721c911324bf9f17a0cf5bf0"
#define EC_SIGNATURE3 "4832febef8b31c7c922a15cb4063a43ab69b099bba765e24facef50dfbb4d057928ed5c6b6886562c2fe6972fd7c7f462e557129067542cce6b37d72e5ea5037"
#define DER_SIGNATURE3 "3044022057d0b4fb0df5cefa245e76ba9b099bb63aa46340cb152a927c1cb3f8befe324802203750eae5727db3e6cc4275062971552e467f7cfd7269fec2626588b6c6d58e92"

BOOST_AUTO_TEST_CASE(elliptic_curve__secret_to_public__positive__test_c)
{
    bc_ec_compressed_t* point = bc_create_ec_compressed();

    bc_data_chunk_t* secret_data = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(secret_data, SECRET1));
    BOOST_REQUIRE(bc_data_chunk_size(secret_data) == bc_ec_secret_size());
    bc_ec_secret_t* secret = bc_create_ec_secret_Data(
        bc_data_chunk_cdata(secret_data));
    bc_destroy_data_chunk(secret_data);

    BOOST_REQUIRE(bc_secret_to_public_compressed(point, secret));

    bc_data_chunk_t* point_data = bc_create_data_chunk_Array(
        bc_ec_compressed_cdata(point), bc_ec_compressed_size());
    bc_string_t* encoded = bc_encode_base16(point_data);
    BOOST_REQUIRE(bc_string_equals_cstr(encoded, COMPRESSED1));
    bc_destroy_string(encoded);
    bc_destroy_data_chunk(point_data);

    bc_destroy_ec_secret(secret);
    bc_destroy_ec_compressed(point);
}

BOOST_AUTO_TEST_CASE(elliptic_curve__decompress__positive__test_c)
{
    bc_ec_uncompressed_t* uncompressed = bc_create_ec_uncompressed();

    bc_data_chunk_t* compressed_data = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(compressed_data, COMPRESSED1));
    BOOST_REQUIRE(
        bc_data_chunk_size(compressed_data) == bc_ec_compressed_size());
    bc_ec_compressed_t* compressed = bc_create_ec_compressed_Data(
        bc_data_chunk_cdata(compressed_data));
    bc_destroy_data_chunk(compressed_data);

    BOOST_REQUIRE(bc_decompress(uncompressed, compressed));
    bc_destroy_ec_compressed(compressed);

    bc_data_chunk_t* point_data = bc_create_data_chunk_Array(
        bc_ec_uncompressed_cdata(uncompressed), bc_ec_uncompressed_size());
    bc_string_t* encoded = bc_encode_base16(point_data);
    BOOST_REQUIRE(bc_string_equals_cstr(encoded, UNCOMPRESSED1));
    bc_destroy_string(encoded);
    bc_destroy_data_chunk(point_data);

    bc_destroy_ec_uncompressed(uncompressed);
}

BOOST_AUTO_TEST_CASE(elliptic_curve__sign__positive__test_c)
{
    bc_ec_signature_t* signature = bc_create_ec_signature();

    bc_hash_digest_t* secret_literal = bc_hash_literal(&SECRET3);
    bc_ec_secret_t* secret = bc_create_ec_secret_Data(
        bc_hash_digest_cdata(secret_literal));
    bc_destroy_hash_digest(secret_literal);

    bc_hash_digest_t* sighash = bc_hash_literal(&SIGHASH3);

    BOOST_REQUIRE(bc_sign(signature, secret, sighash));

    bc_data_chunk_t* signature_data = bc_create_data_chunk_Array(
        bc_ec_signature_cdata(signature), bc_ec_signature_size());
    bc_string_t* result = bc_encode_base16(signature_data);
    bc_destroy_data_chunk(signature_data);

    bc_destroy_ec_signature(signature);

    BOOST_REQUIRE(bc_string_equals_cstr(result, EC_SIGNATURE3));
}

BOOST_AUTO_TEST_CASE(elliptic_curve__encode_signature__positive__test_c)
{
    bc_der_signature_t* out = bc_create_data_chunk();
    
    bc_data_chunk_t* signature_data = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(signature_data, EC_SIGNATURE3));
    bc_ec_signature_t* signature = bc_create_ec_signature_Data(
        bc_data_chunk_cdata(signature_data));
    bc_destroy_data_chunk(signature_data);

    BOOST_REQUIRE(bc_encode_signature(out, signature));

    bc_string_t* result = bc_encode_base16(out);
    BOOST_REQUIRE(bc_string_equals_cstr(result, DER_SIGNATURE3));

    bc_destroy_data_chunk(out);
}

BOOST_AUTO_TEST_CASE(elliptic_curve__sign__round_trip_positive__test_c)
{
    bc_ec_compressed_t* point = bc_create_ec_compressed();
    bc_ec_signature_t* signature = bc_create_ec_signature();

    uint8_t data_bytes[] = { 'd', 'a', 't', 'a' };
    bc_data_chunk_t* data = bc_create_data_chunk_Array(data_bytes, 4);
    bc_hash_digest_t* hash = bc_bitcoin_hash(data);
    bc_destroy_data_chunk(data);

    bc_hash_digest_t* secret_literal = bc_hash_literal(&SECRET1);
    bc_ec_secret_t* secret = bc_create_ec_secret_Data(
        bc_hash_digest_cdata(secret_literal));
    bc_destroy_hash_digest(secret_literal);

    BOOST_REQUIRE(bc_secret_to_public_compressed(point, secret));
    BOOST_REQUIRE(bc_sign(signature, secret, hash));
    BOOST_REQUIRE(bc_verify_signature_compressed(point, hash, signature));

    bc_destroy_ec_secret(secret);
    bc_destroy_hash_digest(hash);
    bc_destroy_ec_signature(signature);
    bc_destroy_ec_compressed(point);
}

BOOST_AUTO_TEST_CASE(elliptic_curve__sign__round_trip_negative__test_c)
{
    bc_ec_compressed_t* point = bc_create_ec_compressed();
    bc_ec_signature_t* signature = bc_create_ec_signature();

    uint8_t data_bytes[] = { 'd', 'a', 't', 'a' };
    bc_data_chunk_t* data = bc_create_data_chunk_Array(data_bytes, 4);
    bc_hash_digest_t* hash = bc_bitcoin_hash(data);
    bc_destroy_data_chunk(data);

    bc_hash_digest_t* secret_literal = bc_hash_literal(&SECRET1);
    bc_ec_secret_t* secret = bc_create_ec_secret_Data(
        bc_hash_digest_cdata(secret_literal));
    bc_destroy_hash_digest(secret_literal);

    BOOST_REQUIRE(bc_secret_to_public_compressed(point, secret));
    BOOST_REQUIRE(bc_sign(signature, secret, hash));

    // Invalidate the positive test.
    bc_hash_digest_data(hash)[0] = 0;
    BOOST_REQUIRE(!bc_verify_signature_compressed(point, hash, signature));

    bc_destroy_ec_secret(secret);
    bc_destroy_hash_digest(hash);
    bc_destroy_ec_signature(signature);
    bc_destroy_ec_compressed(point);
}

BOOST_AUTO_TEST_CASE(elliptic_curve__verify_signature__positive__test_c)
{
    bc_ec_signature_t* signature = bc_create_ec_signature();
    const bool strict = false;
    bc_hash_digest_t* sighash = bc_hash_literal(&SIGHASH2);

    bc_data_chunk_t* point_data = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(point_data, COMPRESSED2));
    BOOST_REQUIRE(
        bc_data_chunk_size(point_data) == bc_ec_compressed_size());
    bc_ec_compressed_t* point = bc_create_ec_compressed_Data(
        bc_data_chunk_cdata(point_data));
    bc_destroy_data_chunk(point_data);

    bc_der_signature_t* distinguished = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(distinguished, SIGNATURE2));
    BOOST_REQUIRE(bc_parse_signature(signature, distinguished, strict));
    BOOST_REQUIRE(bc_verify_signature_compressed(point, sighash, signature));

    bc_destroy_data_chunk(distinguished);
    bc_destroy_ec_compressed(point);
    bc_destroy_hash_digest(sighash);
    bc_destroy_ec_signature(signature);
}

BOOST_AUTO_TEST_CASE(elliptic_curve__verify_signature__negative__test_c)
{
    bc_ec_signature_t* signature = bc_create_ec_signature();
    const bool strict = false;
    bc_hash_digest_t* sighash = bc_hash_literal(&SIGHASH2);

    bc_data_chunk_t* point_data = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(point_data, COMPRESSED2));
    BOOST_REQUIRE(
        bc_data_chunk_size(point_data) == bc_ec_compressed_size());
    bc_ec_compressed_t* point = bc_create_ec_compressed_Data(
        bc_data_chunk_cdata(point_data));
    bc_destroy_data_chunk(point_data);

    bc_der_signature_t* distinguished = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(distinguished, SIGNATURE2));
    BOOST_REQUIRE(bc_parse_signature(signature, distinguished, strict));

    // Invalidate the positive test.
    bc_ec_signature_data(signature)[10] = 110;
    BOOST_REQUIRE(!bc_verify_signature_compressed(point, sighash, signature));

    bc_destroy_data_chunk(distinguished);
    bc_destroy_ec_compressed(point);
    bc_destroy_hash_digest(sighash);
    bc_destroy_ec_signature(signature);
}

BOOST_AUTO_TEST_CASE(elliptic_curve__ec_add__positive__test_c)
{
    const uint8_t secret1_data[] = { 1, 2, 3 };
    bc_ec_secret_t* secret1 = bc_create_ec_secret();
    memset(bc_ec_secret_data(secret1), 0, bc_ec_secret_size());
    std::copy(std::begin(secret1_data), std::end(secret1_data),
        bc_ec_secret_data(secret1));

    const uint8_t secret2_data[] = { 3, 2, 1 };
    bc_ec_secret_t* secret2 = bc_create_ec_secret();
    memset(bc_ec_secret_data(secret2), 0, bc_ec_secret_size());
    std::copy(std::begin(secret2_data), std::end(secret2_data),
        bc_ec_secret_data(secret2));

    bc_ec_compressed_t* public1 = bc_create_ec_compressed();
    BOOST_REQUIRE(bc_secret_to_public_compressed(public1, secret1));
    BOOST_REQUIRE(bc_ec_add(secret1, secret2));

    bc_data_chunk_t* secret1_chunk = bc_create_data_chunk_Array(
        bc_ec_secret_cdata(secret1), bc_ec_secret_size());
    bc_string_t* encoded = bc_encode_base16(secret1_chunk);
    BOOST_REQUIRE(bc_string_equals_cstr(encoded, "0404040000000000000000000000000000000000000000000000000000000000"));
    bc_destroy_string(encoded);
    bc_destroy_data_chunk(secret1_chunk);

    bc_ec_compressed_t* public2 = bc_create_ec_compressed();
    BOOST_REQUIRE(bc_secret_to_public_compressed(public2, secret1));
    BOOST_REQUIRE(bc_ec_add_compressed(public1, secret2));
    BOOST_REQUIRE(memcmp(
        bc_ec_compressed_cdata(public1), bc_ec_compressed_cdata(public2),
        bc_ec_compressed_size()) == 0);
}

BOOST_AUTO_TEST_CASE(elliptic_curve__ec_add__negative__test_c)
{
    // = n - 1
    bc_data_chunk_t* secret1_data = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(secret1_data,
        "fffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364140"));
    BOOST_REQUIRE(bc_data_chunk_size(secret1_data) == bc_ec_secret_size());
    bc_ec_secret_t* secret1 = bc_create_ec_secret_Data(
        bc_data_chunk_cdata(secret1_data));
    bc_destroy_data_chunk(secret1_data);

    bc_ec_secret_t* secret2 = bc_create_ec_secret();
    memset(bc_ec_secret_data(secret2), 0, bc_ec_secret_size());
    bc_ec_secret_data(secret2)[0] = 0;
    bc_ec_secret_data(secret2)[31] = 1;

    bc_ec_compressed_t* public1 = bc_create_ec_compressed();
    BOOST_REQUIRE(bc_secret_to_public_compressed(public1, secret1));
    BOOST_REQUIRE(!bc_ec_add(secret1, secret2));
    BOOST_REQUIRE(!bc_ec_add_compressed(public1, secret2));

    bc_destroy_ec_compressed(public1);
    bc_destroy_ec_secret(secret1);
    bc_destroy_ec_secret(secret2);
}

BOOST_AUTO_TEST_CASE(elliptic_curve__ec_multiply_test_c)
{
    bc_ec_secret_t* secret1 = bc_create_ec_secret();
    bc_ec_secret_t* secret2 = bc_create_ec_secret();
    memset(bc_ec_secret_data(secret1), 0, bc_ec_secret_size());
    memset(bc_ec_secret_data(secret2), 0, bc_ec_secret_size());
    bc_ec_secret_data(secret1)[31] = 11;
    bc_ec_secret_data(secret2)[31] = 22;

    bc_ec_compressed_t* public1 = bc_create_ec_compressed();
    BOOST_REQUIRE(bc_secret_to_public_compressed(public1, secret1));
    BOOST_REQUIRE(bc_ec_multiply(secret1, secret2));
    BOOST_REQUIRE_EQUAL(bc_ec_secret_data(secret1)[31], 242u);
    BOOST_REQUIRE(bc_ec_multiply_compressed(public1, secret2));

    bc_ec_compressed_t* public2 = bc_create_ec_compressed();
    BOOST_REQUIRE(bc_secret_to_public_compressed(public2, secret1));
    BOOST_REQUIRE(memcmp(
        bc_ec_compressed_cdata(public1), bc_ec_compressed_cdata(public2),
        bc_ec_compressed_size()) == 0);
}

BOOST_AUTO_TEST_SUITE_END()

