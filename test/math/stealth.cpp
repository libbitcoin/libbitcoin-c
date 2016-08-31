/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
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
#include <boost/test/unit_test.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/bitcoin.h>

using namespace bc;

BOOST_AUTO_TEST_SUITE(stealth_tests_c)

#define SCAN_PRIVATE "fa63521e333e4b9f6a98a142680d3aef4d8e7f79723ce0043691db55c36bd905"
#define SCAN_PUBLIC "034ea70b28d607bf3a2493102001cab35689cf2152530bf8bf8a5b594af6ae31d0"

#define SPEND_PRIVATE "dcc1250b51c0f03ae4e978e0256ede51dc1144e345c926262b9717b1bcc9bd1b"
#define SPEND_PUBLIC "03d5b3853bbee336b551ff999b0b1d656e65a7649037ae0dcb02b3c4ff5f29e5be"

#define EPHEMERAL_PRIVATE "5f70a77b32260a7a32c62242381fba2cf40c0e209e665a7959418eae4f2da22b"
#define EPHEMERAL_PUBLIC "0387ff9128d18ddcec0a8119589a62b88bc035cb9cd6db08ce5ff702a78ef8f922"

#define STEALTH_PRIVATE "280a9931c0a7b8f9bed96bad35f69a1431817fb77043fdff641ad48ce1e4411e"
#define STEALTH_PUBLIC "0305f6b99a44a2bdec8b484ffcee561cf9a0c3b7ea92ea8e6334e6fbc4f1c17899"

// $ bx ec-add 03d5b3853bbee336b551ff999b0b1d656e65a7649037ae0dcb02b3c4ff5f29e5be 4b4974266ee6c8bed9eff2cd1087bbc1101f17bad9c37814f8561b67f550c544 | bx ec-to-address
#define P2PKH_ADDRESS "1Gvq8pSTRocNLDyf858o4PL3yhZm5qQDgB"

// $ bx ec-add 03d5b3853bbee336b551ff999b0b1d656e65a7649037ae0dcb02b3c4ff5f29e5be 4b4974266ee6c8bed9eff2cd1087bbc1101f17bad9c37814f8561b67f550c544 | bx ec-to-address - v 111
// #define P2PKH_ADDRESS_TESTNET "mwSnRsXSEq3d7LTGqe7AtJYNqhATwHdhMb"

BOOST_AUTO_TEST_CASE(stealth_round_trip_c)
{
    bc_ec_secret_t* expected_stealth_private = bc_create_ec_secret_Base16(
        STEALTH_PRIVATE);
    BOOST_REQUIRE(expected_stealth_private);

    // Receiver generates a new scan private.
    bc_ec_secret_t* scan_private = bc_create_ec_secret_Base16(SCAN_PRIVATE);
    BOOST_REQUIRE(scan_private);

    bc_ec_compressed_t* scan_public = bc_create_ec_compressed();
    BOOST_REQUIRE(bc_secret_to_public_compressed(scan_public, scan_private));

    bc_string_t* scan_public_encoded =
        bc_ec_compressed_encode_base16(scan_public);
    BOOST_REQUIRE(bc_string_equals_cstr(scan_public_encoded, SCAN_PUBLIC));
    bc_destroy_string(scan_public_encoded);

    // Receiver generates a new spend private.
    bc_ec_secret_t* spend_private = bc_create_ec_secret_Base16(SPEND_PRIVATE);
    BOOST_REQUIRE(spend_private);

    bc_ec_compressed_t* spend_public = bc_create_ec_compressed();
    BOOST_REQUIRE(bc_secret_to_public_compressed(spend_public, spend_private));

    bc_string_t* spend_public_encoded =
        bc_ec_compressed_encode_base16(spend_public);
    BOOST_REQUIRE(bc_string_equals_cstr(spend_public_encoded, SPEND_PUBLIC));
    bc_destroy_string(spend_public_encoded);

    // Sender generates a new ephemeral key.
    bc_ec_secret_t* ephemeral_private = bc_create_ec_secret_Base16(
        EPHEMERAL_PRIVATE);
    BOOST_REQUIRE(ephemeral_private);

    bc_ec_compressed_t* ephemeral_public = bc_create_ec_compressed();
    BOOST_REQUIRE(bc_secret_to_public_compressed(
        ephemeral_public, ephemeral_private));

    bc_string_t* ephemeral_public_encoded =
        bc_ec_compressed_encode_base16(ephemeral_public);
    BOOST_REQUIRE(bc_string_equals_cstr(ephemeral_public_encoded, EPHEMERAL_PUBLIC));
    bc_destroy_string(ephemeral_public_encoded);

    // Sender derives stealth public, requiring ephemeral private.
    bc_ec_compressed_t* sender_public = bc_create_ec_compressed();
    BOOST_REQUIRE(bc_uncover_stealth_Public(
        sender_public, scan_public, ephemeral_private, spend_public));
    bc_string_t* sender_public_encoded = bc_ec_compressed_encode_base16(
        sender_public);
    BOOST_REQUIRE(bc_string_equals_cstr(
        sender_public_encoded, STEALTH_PUBLIC));
    bc_destroy_string(sender_public_encoded);
    bc_destroy_ec_compressed(sender_public);

    // Receiver derives stealth public, requiring scan private.
    bc_ec_compressed_t* receiver_public = bc_create_ec_compressed();
    BOOST_REQUIRE(bc_uncover_stealth_Public(
        receiver_public, ephemeral_public, scan_private, spend_public));
    bc_string_t* receiver_public_encoded = bc_ec_compressed_encode_base16(
        receiver_public);
    BOOST_REQUIRE(bc_string_equals_cstr(
        receiver_public_encoded, STEALTH_PUBLIC));
    bc_destroy_string(receiver_public_encoded);
    bc_destroy_ec_compressed(receiver_public);

    // Only reciever can derive stealth private, as it requires
    // both scan and spend private.
    bc_ec_secret_t* stealth_private = bc_create_ec_secret();
    BOOST_REQUIRE(bc_uncover_stealth_Secret(
        stealth_private, ephemeral_public, scan_private, spend_private));

    // This shows that both parties have actually generated stealth public.
    bc_ec_compressed_t* stealth_public = bc_create_ec_compressed();
    BOOST_REQUIRE(bc_secret_to_public_compressed(
        stealth_public, stealth_private));
    bc_string_t* stealth_public_encoded = bc_ec_compressed_encode_base16(
        stealth_public);
    BOOST_REQUIRE(bc_string_equals_cstr(
        stealth_public_encoded, STEALTH_PUBLIC));
    bc_destroy_string(stealth_public_encoded);

    // Both parties therefore have the ability to generate the p2pkh address.
    // versioning: stealth_address::main corresponds to payment_address::main_p2pkh
    // TODO: need ec_point constructor for payment_address first
#if 0
    wallet::payment_address address(stealth_public, wallet::payment_address::mainnet_p2kh);
    BOOST_REQUIRE_EQUAL(address.encoded(), P2PKH_ADDRESS);
#endif

    bc_destroy_ec_compressed(stealth_public);
    bc_destroy_ec_compressed(spend_public);
    bc_destroy_ec_compressed(scan_public);
    bc_destroy_ec_compressed(ephemeral_public);
    bc_destroy_ec_secret(stealth_private);
    bc_destroy_ec_secret(spend_private);
    bc_destroy_ec_secret(scan_private);
    bc_destroy_ec_secret(ephemeral_private);
    bc_destroy_ec_secret(expected_stealth_private);
}

BOOST_AUTO_TEST_CASE(verify_string_constructor_c)
{
    const std::string value = "01100110000";
    bc_binary_t* prefix = bc_create_binary_String(value.data());
    BOOST_REQUIRE_EQUAL(value.size(), bc_binary_size(prefix));
    for (size_t i = 0; i < value.size(); ++i)
    {
        const auto comparison = value[i] == '1';
        BOOST_REQUIRE_EQUAL(bc_binary_at(prefix, i), comparison);
    }
    bc_destroy_binary(prefix);
}

// Binary as a value on the left, padded with zeros to the right.
BOOST_AUTO_TEST_CASE(compare_constructor_results_c)
{
    std::string value = "01100111000";
    bc_binary_t* prefix = bc_create_binary_String(value.data());
    BOOST_REQUIRE_EQUAL(value.size(), bc_binary_size(prefix));
    const uint8_t blocks_data[] = { 0x67, 0x00 };
    bc_data_chunk_t* blocks = bc_create_data_chunk_Array(blocks_data, 2);
    bc_binary_t* prefix2 = bc_create_binary_Blocks(
        value.size(), bc_data_chunk_cdata(blocks));
    BOOST_REQUIRE(bc_binary_equals(prefix, prefix2));
    bc_destroy_data_chunk(blocks);
    bc_destroy_binary(prefix);
    bc_destroy_binary(prefix2);
}

BOOST_AUTO_TEST_CASE(bitfield_test1_c)
{
    bc_binary_t* prefix = bc_create_binary_String("01100111001");
    const uint8_t raw_bitfield[] = { 0x67, 0x20, 0x00, 0x0 };
    BOOST_REQUIRE_GE(sizeof(raw_bitfield) * 8, bc_binary_size(prefix));
    bc_binary_t* compare = bc_create_binary_Blocks(
        bc_binary_size(prefix), raw_bitfield);
    BOOST_REQUIRE(bc_binary_equals(prefix, compare));
    bc_destroy_binary(compare);
    bc_destroy_binary(prefix);
}

BOOST_AUTO_TEST_CASE(bitfield_test2_c)
{
    const uint8_t blocks[] = { 0x8b, 0xf4, 0x1c, 0x69 };
    bc_binary_t* prefix = bc_create_binary_Blocks(27, blocks);
    const uint8_t raw_bitfield[] = { 0x8b, 0xf4, 0x1c, 0x79 };
    BOOST_REQUIRE_GE(sizeof(raw_bitfield) * 8, bc_binary_size(prefix));
    bc_binary_t* compare = bc_create_binary_Blocks(
        bc_binary_size(prefix), raw_bitfield);
    BOOST_REQUIRE(bc_binary_equals(prefix, compare));
    bc_destroy_binary(compare);
    bc_destroy_binary(prefix);
}

BOOST_AUTO_TEST_CASE(bitfield_test3_c)
{
    const uint8_t blocks[] = { 0x69, 0x1c, 0xf4, 0x8b };
    bc_binary_t* prefix = bc_create_binary_Blocks(32, blocks);
    const uint8_t raw_bitfield[] = { 0x69, 0x1c, 0xf4, 0x8b };
    bc_binary_t* compare = bc_create_binary_Blocks(
        bc_binary_size(prefix), raw_bitfield);
    BOOST_REQUIRE(bc_binary_equals(prefix, compare));
    bc_destroy_binary(compare);
    bc_destroy_binary(prefix);
}

BOOST_AUTO_TEST_CASE(bitfield_test4_c)
{
    const uint8_t blocks[] = { 0x69, 0x1c, 0xf4, 0x8b };
    bc_binary_t* prefix = bc_create_binary_Blocks(29, blocks);
    const uint8_t raw_bitfield[] = { 0x69, 0x1c, 0xf4, 0x8b };
    bc_binary_t* compare = bc_create_binary_Blocks(
        bc_binary_size(prefix), raw_bitfield);
    BOOST_REQUIRE(bc_binary_equals(prefix, compare));
    bc_destroy_binary(compare);
    bc_destroy_binary(prefix);
}

BOOST_AUTO_TEST_SUITE_END()
