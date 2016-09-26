/**
 * Copyright (c) 2011-2016 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-client.
 *
 * libbitcoin-client is free software: you can redistribute it and/or
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
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <bitcoin/bitcoin.h>

BOOST_AUTO_TEST_SUITE(base_85_tests_c)

#define BASE85_ENCODED "HelloWorld"
#define BASE85_DECODED \
{ \
    0x86, 0x4F, 0xD2, 0x6F, 0xB5, 0x59, 0xF7, 0x5B \
}

#define BASE85_ENCODED_INVALID_CHAR "Test\n"
#define BASE85_ENCODED_INVALID_LENGTH "Hello World"
#define BASE85_DECODED_INVALID \
{ \
    0x86, 0x4F, 0xD2, 0x6F, 0xB5, 0x59, 0xF7, 0x5B, 0x42 \
}

BOOST_AUTO_TEST_CASE(encode_base85_empty_test_c)
{
    bc_string_t* encoded = bc_create_string_default();
    bc_data_chunk_t* empty_data = bc_create_data_chunk();
    BOOST_REQUIRE(bc_encode_base85(encoded, empty_data));
    BOOST_REQUIRE(bc_string__empty(encoded));
    bc_destroy_data_chunk(empty_data);
    bc_destroy_string(encoded);
}

BOOST_AUTO_TEST_CASE(decode_base85_empty_test_c)
{
    bc_data_chunk_t* result = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base85(result, ""));
    BOOST_REQUIRE(bc_data_chunk__empty(result));
    bc_destroy_data_chunk(result);
}

BOOST_AUTO_TEST_CASE(encode_base85_valid_test_c)
{
    bc_string_t* encoded = bc_create_string_default();
    const uint8_t decoded_data[] = BASE85_DECODED;
    bc_data_chunk_t* decoded = bc_create_data_chunk_Array(
        decoded_data, sizeof(decoded_data));
    BOOST_REQUIRE(bc_encode_base85(encoded, decoded));
    BOOST_REQUIRE(bc_string__equals_cstr(encoded, BASE85_ENCODED));
    bc_destroy_data_chunk(decoded);
    bc_destroy_string(encoded);
}

BOOST_AUTO_TEST_CASE(encode_base85_invalid_test_c)
{
    bc_string_t* encoded = bc_create_string_default();
    const uint8_t decoded_data[] = BASE85_DECODED_INVALID;
    bc_data_chunk_t* decoded = bc_create_data_chunk_Array(
        decoded_data, sizeof(decoded_data));
    BOOST_REQUIRE(!bc_encode_base85(encoded, decoded));
    BOOST_REQUIRE(bc_string__empty(encoded));
    bc_destroy_data_chunk(decoded);
    bc_destroy_string(encoded);
}

BOOST_AUTO_TEST_CASE(decode_base85_valid_test_c)
{
    bc_data_chunk_t* result = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base85(result, BASE85_ENCODED));
    const uint8_t decoded_data[] = BASE85_DECODED;
    bc_data_chunk_t* decoded = bc_create_data_chunk_Array(
        decoded_data, sizeof(decoded_data));
    BOOST_REQUIRE(bc_data_chunk__equals(result, decoded));
    bc_destroy_data_chunk(decoded);
    bc_destroy_data_chunk(result);
}

BOOST_AUTO_TEST_CASE(decode_base85_invalid_char_test_c)
{
    bc_data_chunk_t* result = bc_create_data_chunk();
    BOOST_REQUIRE(!bc_decode_base85(result, BASE85_ENCODED_INVALID_CHAR));
    BOOST_REQUIRE(bc_data_chunk__empty(result));
    bc_destroy_data_chunk(result);
}

BOOST_AUTO_TEST_CASE(decode_base85_invalid_length_test_c)
{
    bc_data_chunk_t* result = bc_create_data_chunk();
    BOOST_REQUIRE(!bc_decode_base85(result, BASE85_ENCODED_INVALID_LENGTH));
    BOOST_REQUIRE(bc_data_chunk__empty(result));
    bc_destroy_data_chunk(result);
}

// The semicolon is not in the Z85 alphabet, and such characters are treated as
// valid but with zero value in the reference implementation.
BOOST_AUTO_TEST_CASE(decode_base85_outside_alphabet_test_c)
{
    bc_data_chunk_t* result = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base85(result, ";;;;;"));
    const uint8_t decoded_data[] = { 0, 0, 0, 0 };
    bc_data_chunk_t* decoded = bc_create_data_chunk_Array(
        decoded_data, sizeof(decoded_data));
    BOOST_REQUIRE(bc_data_chunk__equals(result, decoded));
    bc_destroy_data_chunk(decoded);
    bc_destroy_data_chunk(result);
}

BOOST_AUTO_TEST_SUITE_END()

