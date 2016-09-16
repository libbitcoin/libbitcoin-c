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
#include <boost/test/unit_test.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/bitcoin.h>

using namespace bc;

BOOST_AUTO_TEST_SUITE(base_64_tests_c)

#define BASE64_MURRAY "TXVycmF5IFJvdGhiYXJk"
#define BASE64_DATA_MURRAY \
{ \
    0x4d, 0x75, 0x72, 0x72, 0x61, 0x79, 0x20, \
    0x52, 0x6f, 0x74, 0x68, 0x62, 0x61, 0x72, 0x64 \
}

#define BASE64_BOOK "TWFuLCBFY29ub215IGFuZCBTdGF0ZQ=="
#define BASE64_DATA_BOOK \
{ \
    0x4d, 0x61, 0x6e, 0x2c, 0x20, 0x45, 0x63, \
    0x6f, 0x6e, 0x6f, 0x6d, 0x79, 0x20, 0x61, \
    0x6e, 0x64, 0x20, 0x53, 0x74, 0x61, 0x74, 0x65 \
}

BOOST_AUTO_TEST_CASE(encode_base64_empty_test_c)
{
    bc_data_chunk_t* decoded = bc_create_data_chunk();
    bc_string_t* encoded = bc_encode_base64(decoded);
    BOOST_REQUIRE(bc_string_equals_cstr(encoded, ""));
    bc_destroy_string(encoded);
    bc_destroy_data_chunk(decoded);
}

BOOST_AUTO_TEST_CASE(decode_base64_empty_test_c)
{
    bc_data_chunk_t* result = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base64(result, ""));
    bc_data_chunk_t* empty_data = bc_create_data_chunk();
    BOOST_REQUIRE(bc_data_chunk_equals(result, empty_data));
    bc_destroy_data_chunk(empty_data);
    bc_destroy_data_chunk(result);
}

BOOST_AUTO_TEST_CASE(encode_base64_test_c)
{
    const uint8_t decoded_data[] = BASE64_DATA_MURRAY;
    bc_data_chunk_t* decoded = bc_create_data_chunk_Array(
        decoded_data, sizeof(decoded_data));
    bc_string_t* encoded = bc_encode_base64(decoded);
    BOOST_REQUIRE(bc_string_equals_cstr(encoded, BASE64_MURRAY));
    bc_destroy_string(encoded);
    bc_destroy_data_chunk(decoded);
}

BOOST_AUTO_TEST_CASE(decode_base64_valid_test_c)
{
    bc_data_chunk_t* result = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base64(result, BASE64_MURRAY));
    const uint8_t decoded_data[] = BASE64_DATA_MURRAY;
    bc_data_chunk_t* decoded = bc_create_data_chunk_Array(
        decoded_data, sizeof(decoded_data));
    BOOST_REQUIRE(bc_data_chunk_equals(result, decoded));
    bc_destroy_data_chunk(decoded);
    bc_destroy_data_chunk(result);
}

BOOST_AUTO_TEST_CASE(encode_base64_padded_test_c)
{
    const uint8_t decoded_data[] = BASE64_DATA_BOOK;
    bc_data_chunk_t* decoded = bc_create_data_chunk_Array(
        decoded_data, sizeof(decoded_data));
    bc_string_t* encoded = bc_encode_base64(decoded);
    BOOST_REQUIRE(bc_string_equals_cstr(encoded, BASE64_BOOK));
    bc_destroy_string(encoded);
    bc_destroy_data_chunk(decoded);
}

BOOST_AUTO_TEST_CASE(decode_base64_padded_valid_test_c)
{
    bc_data_chunk_t* result = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base64(result, BASE64_BOOK));
    const uint8_t decoded_data[] = BASE64_DATA_BOOK;
    bc_data_chunk_t* decoded = bc_create_data_chunk_Array(
        decoded_data, sizeof(decoded_data));
    BOOST_REQUIRE(bc_data_chunk_equals(result, decoded));
    bc_destroy_data_chunk(decoded);
    bc_destroy_data_chunk(result);
}

BOOST_AUTO_TEST_CASE(decode_base64_invalid_test_c)
{
    bc_data_chunk_t* result = bc_create_data_chunk();
    BOOST_REQUIRE(!bc_decode_base64(result, "!@#$%^&*()"));
    bc_destroy_data_chunk(result);
}

BOOST_AUTO_TEST_SUITE_END()

