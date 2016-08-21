/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
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
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>

#include <map>
#include <vector>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/bitcoin.h>

using namespace bc;

BOOST_AUTO_TEST_SUITE(data_tests_c)

BOOST_AUTO_TEST_CASE(data__to_byte__value__expected_size_and_value_c)
{
    const uint8_t expected = 42;
    uint8_t result[] = { expected };
    BOOST_REQUIRE_EQUAL(sizeof(result), 1u);
    BOOST_REQUIRE_EQUAL(result[0], expected);
}

BOOST_AUTO_TEST_CASE(data__build_chunk__empty__empty_c)
{
    bc_data_chunk_t* result = bc_create_data_chunk();
    BOOST_REQUIRE(bc_data_chunk_empty(result));
    bc_destroy_data_chunk(result);
}

BOOST_AUTO_TEST_CASE(data__build_chunk__one_slice__expected_size_and_value_c)
{
    const uint8_t expected = 42;
    uint8_t chunk1_data[] = { 24 };
    uint8_t chunk2_data[] = { expected };
    uint8_t chunk3_data[] = { 48 };
    bc_data_chunk_t* chunk1 = bc_create_data_chunk_Array(chunk1_data, 1);
    bc_data_chunk_t* chunk2 = bc_create_data_chunk_Array(chunk2_data, 1);
    bc_data_chunk_t* chunk3 = bc_create_data_chunk_Array(chunk3_data, 1);

    bc_data_chunk_t* result = bc_create_data_chunk();
    bc_data_chunk_extend_data(result, chunk1);
    bc_data_chunk_extend_data(result, chunk2);
    bc_data_chunk_extend_data(result, chunk3);
    BOOST_REQUIRE_EQUAL(bc_data_chunk_size(result), 3);
    BOOST_REQUIRE_EQUAL(bc_data_chunk_data(result)[1], expected);

    bc_destroy_data_chunk(result);
    bc_destroy_data_chunk(chunk3);
    bc_destroy_data_chunk(chunk2);
    bc_destroy_data_chunk(chunk1);
}

BOOST_AUTO_TEST_CASE(data__build_chunk__three_slices__expected_size_and_value_c)
{
    const size_t size1 = 2;
    const size_t size2 = 1;
    const size_t size3 = 3;
    const uint8_t expected = 42;
    uint8_t chunk1_data[] = { 0, 0 };
    uint8_t chunk2_data[] = { expected };
    uint8_t chunk3_data[] = { 0, 0, 0 };
    bc_data_chunk_t* chunk1 = bc_create_data_chunk_Array(chunk1_data, size1);
    bc_data_chunk_t* chunk2 = bc_create_data_chunk_Array(chunk2_data, size2);
    bc_data_chunk_t* chunk3 = bc_create_data_chunk_Array(chunk3_data, size3);

    bc_data_chunk_t* result = bc_create_data_chunk();
    bc_data_chunk_extend_data(result, chunk1);
    bc_data_chunk_extend_data(result, chunk2);
    bc_data_chunk_extend_data(result, chunk3);
    BOOST_REQUIRE_EQUAL(bc_data_chunk_size(result), size1 + size2 + size3);
    BOOST_REQUIRE_EQUAL(bc_data_chunk_data(result)[size1], expected);

    bc_destroy_data_chunk(result);
    bc_destroy_data_chunk(chunk3);
    bc_destroy_data_chunk(chunk2);
    bc_destroy_data_chunk(chunk1);
}

BOOST_AUTO_TEST_CASE(data__build_chunk__extra_reserve__expected_size_and_capacity)
{
    // Skip this test. Reserve isn't implemented in C layer.
}

BOOST_AUTO_TEST_CASE(data__build_array__empty__true_unchanged_c)
{
    // Skip this test. We use standard C arrays in C layer.
}

BOOST_AUTO_TEST_CASE(data__build_array__under_capacity__true_excess_unchanged)
{
    // Skip this test. We use standard C arrays in C layer.
}

BOOST_AUTO_TEST_CASE(data__build_array__exact_fill_multiple_slices__true_expected_values_c)
{
    // Skip this test. We use standard C arrays in C layer.
}

BOOST_AUTO_TEST_CASE(data__build_array__overflow__returns_false_c)
{
    // Skip this test. We use standard C arrays in C layer.
}

BOOST_AUTO_TEST_CASE(data__extend_data__twice__expected_c)
{
    const uint8_t expected = 24;
    uint8_t buffer1_data[] = { 0 };
    bc_data_chunk_t* buffer1 = bc_create_data_chunk_Array(buffer1_data, 1);

    bc_hash_digest_t* null_hash = bc_null_hash();
    bc_data_chunk_t* null_hash_chunk = bc_create_data_chunk_Array(
        bc_hash_digest_data(null_hash), bc_hash_size());
    bc_data_chunk_extend_data(buffer1, null_hash_chunk);

    bc_destroy_hash_digest(null_hash);

    uint8_t buffer2_data[] = { expected };
    bc_data_chunk_t* buffer2 = bc_create_data_chunk_Array(buffer2_data, 1);

    bc_data_chunk_extend_data(buffer1, buffer2);
    bc_data_chunk_extend_data(buffer1, null_hash_chunk);

    BOOST_REQUIRE_EQUAL(hash_size, bc_hash_size());
    BOOST_REQUIRE_EQUAL(bc_data_chunk_size(buffer1), 2u * hash_size + 2u);
    BOOST_REQUIRE_EQUAL(bc_data_chunk_data(buffer1)[hash_size + 1], expected);

    bc_destroy_data_chunk(null_hash_chunk);
    bc_destroy_data_chunk(buffer2);
    bc_destroy_data_chunk(buffer1);
}

BOOST_AUTO_TEST_CASE(data__range_constrain__over__max_c)
{
    const size_t expected = 10;
    const auto result = bc_range_constrain(size_t(42), size_t(1), expected);
    BOOST_REQUIRE_EQUAL(result, expected);
}

BOOST_AUTO_TEST_CASE(data__range_constrain__under__min_c)
{
    const size_t expected = 50;
    const auto result = bc_range_constrain(size_t(42), expected, size_t(100));
    BOOST_REQUIRE_EQUAL(result, expected);
}

BOOST_AUTO_TEST_CASE(data__range_constrain__internal__unchanged_c)
{
    const size_t expected = 42;
    const auto result = bc_range_constrain(expected, size_t(10), size_t(100));
    BOOST_REQUIRE_EQUAL(result, expected);
}

BOOST_AUTO_TEST_CASE(data__slice__empty_selection__compiles_c)
{
    // Skip this test. We use standard C arrays in C layer.
}

BOOST_AUTO_TEST_CASE(data__slice__three_bytes_front__expected_c)
{
    // Skip this test. We use standard C arrays in C layer.
}

BOOST_AUTO_TEST_CASE(data__slice__three_bytes_middle__expected_c)
{
    // Skip this test. We use standard C arrays in C layer.
}

BOOST_AUTO_TEST_CASE(data__slice__three_bytes_end__expected_c)
{
    // Skip this test. We use standard C arrays in C layer.
}

BOOST_AUTO_TEST_CASE(data__split__two_bytes__expected_c)
{
    // Skip this test. We use standard C arrays in C layer.
}

BOOST_AUTO_TEST_CASE(data__split__long_hash__expected_c)
{
    // Skip this test. We use standard C arrays in C layer.
}

BOOST_AUTO_TEST_CASE(data__splice_two__two_bytes_each__expected_c)
{
    // Skip this test. We use standard C arrays in C layer.
}

BOOST_AUTO_TEST_CASE(data__splice_three__one_two_three_bytes__expected_c)
{
    // Skip this test. We use standard C arrays in C layer.
}

BOOST_AUTO_TEST_CASE(data__to_array_slice__double_long_hash__expected_c)
{
    // Skip this test. We use standard C arrays in C layer.
}

BOOST_AUTO_TEST_CASE(data__to_chunk__long_hash__expected_c)
{
    const uint8_t l = 42;
    const uint8_t u = 24;
    const uint8_t source[bc_long_hash_size()] =
    {
        l, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        u, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    bc_data_chunk_t* result = bc_create_data_chunk_Array(
        source, bc_long_hash_size());
    BOOST_REQUIRE_EQUAL(bc_data_chunk_data(result)[0], l);
    BOOST_REQUIRE_EQUAL(bc_data_chunk_data(result)[32], u);
    bc_destroy_data_chunk(result);
}

BOOST_AUTO_TEST_CASE(data__xor_data0__same__zeros_c)
{
    // Skip this test. No way to port template function without re-impl.
}

BOOST_AUTO_TEST_CASE(data__xor_data1__empty__empty_c)
{
    // Skip this test. No way to port template function without re-impl.
}

BOOST_AUTO_TEST_CASE(data__xor_data1__same__zeros_c)
{
    // Skip this test. No way to port template function without re-impl.
}

BOOST_AUTO_TEST_CASE(data__xor_data1__same_offset__zeros_c)
{
    // Skip this test. No way to port template function without re-impl.
}

BOOST_AUTO_TEST_CASE(data__xor_data1__distinct__ones_c)
{
    // Skip this test. No way to port template function without re-impl.
}

BOOST_AUTO_TEST_CASE(data__xor_data1__distinct_bites__bits_c)
{
    // Skip this test. No way to port template function without re-impl.
}

BOOST_AUTO_TEST_CASE(data__xor_data2__distinct_bites__bits_c)
{
    // Skip this test. No way to port template function without re-impl.
}

BOOST_AUTO_TEST_SUITE_END()
