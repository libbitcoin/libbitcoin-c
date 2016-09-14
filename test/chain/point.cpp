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
#include <bitcoin/bitcoin.h>

BOOST_AUTO_TEST_SUITE(point_tests_c)

BOOST_AUTO_TEST_CASE(begin_end_test_c)
{
    // Skipping begin and end test. C++ iterators not implemented in C layer.
}

BOOST_AUTO_TEST_CASE(from_data_fails_c)
{
    bc_data_chunk_t* data = bc_create_data_chunk();
    bc_data_chunk_resize(data, 10);

    bc_point_t* instance = bc_create_point();

    BOOST_REQUIRE_EQUAL(false, bc_point_from_data(instance, data));
    BOOST_REQUIRE_EQUAL(false, bc_point_is_valid(instance));

    bc_destroy_point(instance);
    bc_destroy_data_chunk(data);
}

BOOST_AUTO_TEST_CASE(to_data_from_data_roundtrip_c)
{
    uint32_t index = 53213;
    bc_hash_digest_t* hash = bc_create_hash_digest_Array(
        bc_data_array_t{
            0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
            0x01, 0x01, 0xab, 0x11, 0x11, 0xcd, 0x11, 0x11,
            0x01, 0x10, 0x11, 0xab, 0x11, 0x11, 0xcd, 0x11,
            0x01, 0x11, 0x11, 0x11, 0xab, 0x11, 0x11, 0xcd
        });

    bc_point_t* initial = bc_create_point();
    bc_point_set_hash(initial, hash);
    bc_point_set_index(initial, index);

    BOOST_REQUIRE(bc_point_is_valid(initial));
    bc_hash_digest_t* initial_hash = bc_point_hash(initial);
    BOOST_REQUIRE(bc_hash_digest_equals(hash, initial_hash));
    bc_destroy_hash_digest(initial_hash);
    BOOST_REQUIRE(index == bc_point_index(initial));

    bc_point_t* point = bc_create_point();
    BOOST_REQUIRE(bc_point_not_equals(point, initial));
    bc_data_chunk_t* initial_data = bc_point_to_data(initial);
    BOOST_REQUIRE(bc_point_from_data(point, initial_data));
    bc_destroy_data_chunk(initial_data);
    BOOST_REQUIRE(bc_point_is_valid(point));
    BOOST_REQUIRE(bc_point_equals(point, initial));

    bc_destroy_point(point);
    bc_destroy_point(initial);
    bc_destroy_hash_digest(hash);
}

BOOST_AUTO_TEST_CASE(from_data_to_data_roundtrip_factory_data_chunk_c)
{
    bc_data_chunk_t* rawdata = bc_create_data_chunk();
    bc_decode_base16(rawdata,
        "46682488f0a721124a3905a1bb72445bf13493e2cd46c5c0c8db1c15afa0d58e00000000");

    const uint8_t rawbytes[] = {
        0x46, 0x68, 0x24, 0x88, 0xf0, 0xa7, 0x21, 0x12, 0x4a, 0x39, 0x05, 0xa1,
        0xbb, 0x72, 0x44, 0x5b, 0xf1, 0x34, 0x93, 0xe2, 0xcd, 0x46, 0xc5, 0xc0,
        0xc8, 0xdb, 0x1c, 0x15, 0xaf, 0xa0, 0xd5, 0x8e, 0x00, 0x00, 0x00, 0x00
    };
    bc_data_chunk_t* rawdata_cmp = bc_create_data_chunk_Array(
        rawbytes, sizeof(rawbytes));
    BOOST_REQUIRE(bc_data_chunk_equals(rawdata_cmp, rawdata));
    bc_destroy_data_chunk(rawdata_cmp);

    bc_point_t* point = bc_point_factory_from_data(rawdata);

    BOOST_REQUIRE(bc_point_is_valid(point));

    bc_hash_digest_t* point_hash = bc_point_hash(point);
    bc_string_t* hash_str = bc_encode_hash(point_hash);
    BOOST_REQUIRE(bc_string_equals_cstr(hash_str,
        "8ed5a0af151cdbc8c0c546cde29334f15b4472bba105394a1221a7f088246846"));
    bc_destroy_string(hash_str);
    bc_destroy_hash_digest(point_hash);

    BOOST_REQUIRE(bc_point_index(point) == 0);

    bc_data_chunk_t* output = bc_point_to_data(point);
    BOOST_REQUIRE(bc_data_chunk_equals(output, rawdata));
    bc_destroy_data_chunk(output);

    bc_destroy_point(point);
    bc_destroy_data_chunk(rawdata);
}

BOOST_AUTO_TEST_CASE(from_data_to_data_roundtrip_factory_stream_c)
{
    // Skipping stream test. Not implemented in C layer.
}

BOOST_AUTO_TEST_CASE(from_data_to_data_roundtrip_factory_reader_c)
{
    // Skipping stream test. Not implemented in C layer.
}

BOOST_AUTO_TEST_SUITE_END()

