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

BOOST_AUTO_TEST_SUITE(base_16_tests_c)

BOOST_AUTO_TEST_CASE(base16_literal_test_c)
{
    // Skip this test. Use bc_decode_base16 instead.
}

BOOST_AUTO_TEST_CASE(base16_odd_length_invalid_test_c)
{
    const auto& hex_str = "10a7fd15cb45bda9e90e19a15";
    bc_data_chunk_t* data = bc_create_data_chunk();
    BOOST_REQUIRE(!bc_decode_base16(data, hex_str));
    bc_destroy_data_chunk(data);
}

BOOST_AUTO_TEST_CASE(base16_short_hash_test_c)
{
    const auto& hex_str = "f85beb6356d0813ddb0dbb14230a249fe931a135";
    bc_data_chunk_t* hash = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(hash, hex_str));

    bc_string_t* encoded = bc_encode_base16(hash);
    bc_string_t* hex = bc_create_string(hex_str);
    BOOST_REQUIRE(bc_string__equals(encoded, hex));
    bc_destroy_string(encoded);
    bc_destroy_string(hex);

    const uint8_t expected_data[] =
    {
       0xf8, 0x5b, 0xeb, 0x63, 0x56, 0xd0, 0x81, 0x3d, 0xdb, 0x0d,
       0xbb, 0x14, 0x23, 0x0a, 0x24, 0x9f, 0xe9, 0x31, 0xa1, 0x35
    };
    bc_data_chunk_t* expected = bc_create_data_chunk_Array(
        expected_data, bc_short_hash_size());
    BOOST_REQUIRE(bc_data_chunk__equals(hash, expected));
    bc_destroy_data_chunk(expected);
    bc_destroy_data_chunk(hash);
}

// TODO: this should be tested for correctness, not just round-tripping.
BOOST_AUTO_TEST_CASE(base16_round_trip_test_c)
{
    const auto& hex_str = "10a7fd15cb45bda9e90e19a15f";
    bc_data_chunk_t* data = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(data, hex_str));

    bc_string_t* encoded = bc_encode_base16(data);
    bc_string_t* hex = bc_create_string(hex_str);
    BOOST_REQUIRE(bc_string__equals(encoded, hex));
    bc_destroy_string(encoded);
    bc_destroy_string(hex);

    bc_destroy_data_chunk(data);
}

BOOST_AUTO_TEST_CASE(base16_array_test_c)
{
    // Skip this test. We use standard C arrays in C layer.
}

BOOST_AUTO_TEST_SUITE_END()
