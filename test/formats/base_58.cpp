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
#include <string>
#include <bitcoin/bitcoin.h>

BOOST_AUTO_TEST_SUITE(base_58_tests_c)

void encdec_test(const char* hex, const char* encoded)
{
    bc_data_chunk_t* data = bc_create_data_chunk();
    bc_data_chunk_t* decoded = bc_create_data_chunk();

    BOOST_REQUIRE(bc_decode_base16(data, hex));

    bc_string_t* reencoded = bc_encode_base58(data);
    BOOST_REQUIRE(bc_string__equals_cstr(reencoded, encoded));
    bc_destroy_string(reencoded);

    BOOST_REQUIRE(bc_decode_base58(decoded, encoded));
    BOOST_REQUIRE(bc_data_chunk__equals(decoded, data));

    bc_destroy_data_chunk(data);
    bc_destroy_data_chunk(decoded);
}

BOOST_AUTO_TEST_CASE(base58_test_c)
{
    encdec_test("", "");
    encdec_test("61", "2g");
    encdec_test("626262", "a3gV");
    encdec_test("636363", "aPEr");
    encdec_test("73696d706c792061206c6f6e6720737472696e67", "2cFupjhnEsSn59qHXstmK2ffpLv2");
    encdec_test("00eb15231dfceb60925886b67d065299925915aeb172c06647", "1NS17iag9jJgTHD1VXjvLCEnZuQ3rJDE9L");
    encdec_test("516b6fcd0f", "ABnLTmg");
    encdec_test("bf4f89001e670274dd", "3SEo3LWLoPntC");
    encdec_test("572e4794", "3EFU7m");
    encdec_test("ecac89cad93923c02321", "EJDM8drfXA6uyA");
    encdec_test("10c8511e", "Rt5zm");
    encdec_test("00000000000000000000", "1111111111");
}

BOOST_AUTO_TEST_CASE(base58_address_test_c)
{
    const uint8_t pk_data[] =
    {
        0x00, 0x5c, 0xc8, 0x7f, 0x4a, 0x3f, 0xdf, 0xe3,
        0xa2, 0x34, 0x6b, 0x69, 0x53, 0x26, 0x7c, 0xa8,
        0x67, 0x28, 0x26, 0x30, 0xd3, 0xf9, 0xb7, 0x8e,
        0x64
    };
    bc_data_chunk_t* pubkey = bc_create_data_chunk_Array(
        pk_data, sizeof(pk_data));

    const char* address = "19TbMSWwHvnxAKy12iNm3KdbGfzfaMFViT";
    bc_string_t* encoded = bc_encode_base58(pubkey);
    BOOST_REQUIRE(bc_string__equals_cstr(encoded, address));
    bc_destroy_string(encoded);

    bc_data_chunk_t* decoded = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base58(decoded, address));
    BOOST_REQUIRE(bc_data_chunk__equals(decoded, pubkey));

    bc_destroy_data_chunk(decoded);
    bc_destroy_data_chunk(pubkey);
}

BOOST_AUTO_TEST_CASE(is_b58_c)
{
    const std::string base58_chars = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
    for (char ch: base58_chars)
    {
        BOOST_REQUIRE(bc_is_base58_Char(ch));
    }

    const std::string non_base58_chars = "0OIl+- //#";
    for (char ch: non_base58_chars)
    {
        BOOST_REQUIRE(!bc_is_base58_Char(ch));
    }

    BOOST_REQUIRE(bc_is_base58("abcdjkk11"));
    BOOST_REQUIRE(!bc_is_base58("abcdjkk011"));
}

BOOST_AUTO_TEST_CASE(base58_array_test_c)
{
    // Skipping byte array test. Not implemented in C layer.
}

BOOST_AUTO_TEST_SUITE_END()

