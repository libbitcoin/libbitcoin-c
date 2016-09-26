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

BOOST_AUTO_TEST_SUITE(binary_tests_c)

BOOST_AUTO_TEST_SUITE(binary__encoded_c)

BOOST_AUTO_TEST_CASE(prefix_encoded__32_bits__expected_value_c)
{
    const uint8_t blocks[] = { 0xba, 0xad, 0xf0, 0x0d };
    bc_binary_t* prefix = bc_create_binary_Blocks(32, blocks);
    bc_string_t* encoded = bc_binary__encoded(prefix);
    BOOST_REQUIRE(bc_string__equals_cstr(encoded,
        "10111010101011011111000000001101"));
    bc_destroy_string(encoded);
    bc_destroy_binary(prefix);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(binary__to_string_c)

BOOST_AUTO_TEST_CASE(prefix_to_string__32_bits__expected_value_c)
{
    // Ignoring stream test.
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(binary__shift_left_c)

BOOST_AUTO_TEST_CASE(shift_left_by_zero_c)
{
    size_t distance = 0;
    const uint8_t instance_blocks[] = { 0xAA, 0xAA, 0xAA };
    const uint8_t expected_blocks[] = { 0xAA, 0xAA };
    bc_binary_t* instance = bc_create_binary_Blocks(16, instance_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(16, expected_blocks);
    bc_binary__shift_left(instance, distance);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(shift_left_alternate_initial_c)
{
    size_t distance = 16;
    const uint8_t instance_blocks[] = { 0xAB, 0xCD, 0xEF };
    const uint8_t expected_blocks[] = { 0xEF };
    bc_binary_t* instance = bc_create_binary_Blocks(24, instance_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(8, expected_blocks);
    bc_binary__shift_left(instance, distance);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(shift_left_by_less_than_byte_c)
{
    size_t distance = 5;
    const uint8_t instance_blocks[] = { 0xAA, 0xAA, 0xAA };
    const uint8_t expected_blocks[] = { 0x55, 0x55, 0x40 };
    bc_binary_t* instance = bc_create_binary_Blocks(24, instance_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(19, expected_blocks);
    bc_binary__shift_left(instance, distance);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(shift_left_by_less_than_byte_to_byte_align_c)
{
    size_t distance = 5;
    const uint8_t instance_blocks[] = { 0xAA, 0xAA, 0xAA };
    const uint8_t expected_blocks[] = { 0x55, 0x55 };
    bc_binary_t* instance = bc_create_binary_Blocks(21, instance_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(16, expected_blocks);
    bc_binary__shift_left(instance, distance);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(shift_left_by_byte_single_c)
{
    size_t distance = 8;
    const uint8_t instance_blocks[] = { 0xAA, 0xAA, 0xAA };
    const uint8_t expected_blocks[] = { 0xAA, 0xAA };
    bc_binary_t* instance = bc_create_binary_Blocks(24, instance_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(16, expected_blocks);
    bc_binary__shift_left(instance, distance);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(shift_left_by_greater_than_byte_c)
{
    size_t distance = 13;
    const uint8_t instance_blocks[] = { 0xAA, 0xAA, 0xAA };
    const uint8_t expected_blocks[] = { 0x55, 0x40 };
    bc_binary_t* instance = bc_create_binary_Blocks(24, instance_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(11, expected_blocks);
    bc_binary__shift_left(instance, distance);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(shift_left_by_greater_than_byte_not_initially_aligned_c)
{
    size_t distance = 13;
    const uint8_t instance_blocks[] = { 0xAA, 0xAA, 0xAA };
    const uint8_t expected_blocks[] = { 0x50 };
    bc_binary_t* instance = bc_create_binary_Blocks(18, instance_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(5, expected_blocks);
    bc_binary__shift_left(instance, distance);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(shift_left_by_byte_multiple_c)
{
    size_t distance = 16;
    const uint8_t instance_blocks[] = { 0xAA, 0xAA, 0xAA };
    const uint8_t expected_blocks[] = { 0xAA };
    bc_binary_t* instance = bc_create_binary_Blocks(24, instance_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(8, expected_blocks);
    bc_binary__shift_left(instance, distance);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(shift_left_by_size_c)
{
    size_t distance = 24;
    const uint8_t instance_blocks[] = { 0xAA, 0xAA, 0xAA };
    const uint8_t expected_blocks[] = { };
    bc_binary_t* instance = bc_create_binary_Blocks(24, instance_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(0, expected_blocks);
    bc_binary__shift_left(instance, distance);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(shift_left_by_greater_than_size_c)
{
    size_t distance = 30;
    const uint8_t instance_blocks[] = { 0xAA, 0xAA, 0xAA };
    const uint8_t expected_blocks[] = { };
    bc_binary_t* instance = bc_create_binary_Blocks(24, instance_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(0, expected_blocks);
    bc_binary__shift_left(instance, distance);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(binary__shift_right_c)

BOOST_AUTO_TEST_CASE(shift_right_by_zero_c)
{
    size_t distance = 0;
    const uint8_t instance_blocks[] = { 0xAA, 0xAA, 0xAA };
    const uint8_t expected_blocks[] = { 0xAA, 0xAA };
    bc_binary_t* instance = bc_create_binary_Blocks(16, instance_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(16, expected_blocks);
    bc_binary__shift_right(instance, distance);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(shift_right_by_less_than_byte_c)
{
    size_t distance = 5;
    const uint8_t instance_blocks[] = { 0xAA, 0xAA, 0xAA };
    const uint8_t expected_blocks[] = { 0x05, 0x55, 0x55, 0x50 };
    bc_binary_t* instance = bc_create_binary_Blocks(24, instance_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(29, expected_blocks);
    bc_binary__shift_right(instance, distance);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(shift_right_by_less_than_byte_to_byte_align_c)
{
    size_t distance = 3;
    const uint8_t instance_blocks[] = { 0xAA, 0xAA, 0xAA };
    const uint8_t expected_blocks[] = { 0x15, 0x55, 0x55 };
    bc_binary_t* instance = bc_create_binary_Blocks(21, instance_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(24, expected_blocks);
    bc_binary__shift_right(instance, distance);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(shift_right_by_byte_single_c)
{
    size_t distance = 8;
    const uint8_t instance_blocks[] = { 0xAA, 0xAA, 0xAA };
    const uint8_t expected_blocks[] = { 0x00, 0xAA, 0xAA, 0xAA };
    bc_binary_t* instance = bc_create_binary_Blocks(24, instance_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(32, expected_blocks);
    bc_binary__shift_right(instance, distance);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(shift_right_by_greater_than_byte_c)
{
    size_t distance = 13;
    const uint8_t instance_blocks[] = { 0xAA, 0xAA, 0xAA };
    const uint8_t expected_blocks[] = { 0x00, 0x05, 0x55, 0x55, 0x50 };
    bc_binary_t* instance = bc_create_binary_Blocks(24, instance_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(37, expected_blocks);
    bc_binary__shift_right(instance, distance);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(shift_right_by_greater_than_byte_not_initially_aligned_c)
{
    size_t distance = 13;
    const uint8_t instance_blocks[] = { 0xAA, 0xAA, 0xAA };
    const uint8_t expected_blocks[] = { 0x00, 0x05, 0x55, 0x55, 0x54 };
    bc_binary_t* instance = bc_create_binary_Blocks(18, instance_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(31, expected_blocks);
    bc_binary__shift_right(instance, distance);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(shift_right_by_byte_multiple_c)
{
    size_t distance = 16;
    const uint8_t instance_blocks[] = { 0xAA, 0xAA, 0xAA };
    const uint8_t expected_blocks[] = { 0x00, 0x00, 0xAA, 0xAA, 0xAA };
    bc_binary_t* instance = bc_create_binary_Blocks(24, instance_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(40, expected_blocks);
    bc_binary__shift_right(instance, distance);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(shift_right_by_size_c)
{
    size_t distance = 24;
    const uint8_t instance_blocks[] = { 0xAA, 0xAA, 0xAA };
    const uint8_t expected_blocks[] = { 0x00, 0x00, 0x00, 0xAA, 0xAA, 0xAA };
    bc_binary_t* instance = bc_create_binary_Blocks(24, instance_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(48, expected_blocks);
    bc_binary__shift_right(instance, distance);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(shift_right_by_greater_than_size_c)
{
    size_t distance = 30;
    const uint8_t instance_blocks[] = { 0xAA, 0xAA, 0xAA };
    const uint8_t expected_blocks[] = { 0x00, 0x00, 0x00, 0x02, 0xAA, 0xAA, 0xA8 };
    bc_binary_t* instance = bc_create_binary_Blocks(24, instance_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(54, expected_blocks);
    bc_binary__shift_right(instance, distance);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(binary__append_c)

BOOST_AUTO_TEST_CASE(append_to_zero_length_c)
{
    const uint8_t instance_blocks[] = { 0x00 };
    const uint8_t augment_blocks[] = { 0xAA, 0xBB, 0xCC };
    const uint8_t expected_blocks[] = { 0xAA, 0xBB, 0xCC };
    bc_binary_t* instance = bc_create_binary_Blocks(0, instance_blocks);
    bc_binary_t* augment = bc_create_binary_Blocks(24, augment_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(24, expected_blocks);
    bc_binary__append(instance, augment);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(augment);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(append_zero_length_to_content_c)
{
    const uint8_t instance_blocks[] = { 0xAA, 0xBB, 0xCC };
    const uint8_t augment_blocks[] = {};
    const uint8_t expected_blocks[] = { 0xAA, 0xBB, 0xCC };
    bc_binary_t* instance = bc_create_binary_Blocks(24, instance_blocks);
    bc_binary_t* augment = bc_create_binary_Blocks(0, augment_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(24, expected_blocks);
    bc_binary__append(instance, augment);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(augment);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(append_byte_aligned_instances_c)
{
    const uint8_t instance_blocks[] = { 0xAA, 0xBB, 0xCC };
    const uint8_t augment_blocks[] = { 0xDD, 0xEE, 0xFF };
    const uint8_t expected_blocks[] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
    bc_binary_t* instance = bc_create_binary_Blocks(24, instance_blocks);
    bc_binary_t* augment = bc_create_binary_Blocks(24, augment_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(48, expected_blocks);
    bc_binary__append(instance, augment);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(augment);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(append_byte_nonaligned_instances_c)
{
    const uint8_t instance_blocks[] = { 0xAA, 0xBB, 0xCC };
    const uint8_t augment_blocks[] = { 0xDD, 0xEE };
    const uint8_t expected_blocks[] = { 0xAA, 0xBB, 0xCD, 0xDE, 0x80 };
    bc_binary_t* instance = bc_create_binary_Blocks(20, instance_blocks);
    bc_binary_t* augment = bc_create_binary_Blocks(13, augment_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(33, expected_blocks);
    bc_binary__append(instance, augment);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(augment);
    bc_destroy_binary(expected);
}

//
// prepend tests
//
BOOST_AUTO_TEST_CASE(prepend_to_zero_length_c)
{
    const uint8_t instance_blocks[] = { 0x00 };
    const uint8_t augment_blocks[] = { 0xAA, 0xBB, 0xCC };
    const uint8_t expected_blocks[] = { 0xAA, 0xBB, 0xCC };
    bc_binary_t* instance = bc_create_binary_Blocks(0, instance_blocks);
    bc_binary_t* augment = bc_create_binary_Blocks(24, augment_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(24, expected_blocks);
    bc_binary__prepend(instance, augment);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(augment);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(prepend_zero_length_to_content_c)
{
    const uint8_t instance_blocks[] = { 0xAA, 0xBB, 0xCC };
    const uint8_t augment_blocks[] = {};
    const uint8_t expected_blocks[] = { 0xAA, 0xBB, 0xCC };
    bc_binary_t* instance = bc_create_binary_Blocks(24, instance_blocks);
    bc_binary_t* augment = bc_create_binary_Blocks(0, augment_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(24, expected_blocks);
    bc_binary__prepend(instance, augment);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(augment);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(prepend_byte_aligned_instances_c)
{
    const uint8_t instance_blocks[] = { 0xAA, 0xBB, 0xCC };
    const uint8_t augment_blocks[] = { 0xDD, 0xEE, 0xFF };
    const uint8_t expected_blocks[] = { 0xDD, 0xEE, 0xFF, 0xAA, 0xBB, 0xCC };
    bc_binary_t* instance = bc_create_binary_Blocks(24, instance_blocks);
    bc_binary_t* augment = bc_create_binary_Blocks(24, augment_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(48, expected_blocks);
    bc_binary__prepend(instance, augment);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(augment);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(prepend_byte_nonaligned_instances_c)
{
    const uint8_t instance_blocks[] = { 0xAA, 0xBB, 0xCC };
    const uint8_t augment_blocks[] = { 0xDD, 0xEE };
    const uint8_t expected_blocks[] = { 0xDD, 0xED, 0x55, 0xDE, 0x00 };
    bc_binary_t* instance = bc_create_binary_Blocks(20, instance_blocks);
    bc_binary_t* augment = bc_create_binary_Blocks(13, augment_blocks);
    bc_binary_t* expected = bc_create_binary_Blocks(33, expected_blocks);
    bc_binary__prepend(instance, augment);
    BOOST_REQUIRE(bc_binary__equals(expected, instance));
    bc_destroy_binary(instance);
    bc_destroy_binary(augment);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(binary__substring_c)

BOOST_AUTO_TEST_CASE(substring_start_after_end_c)
{
    // Instance
    const uint8_t instance_blocks[] = { 0xAA, 0xBB, 0xCC };
    bc_binary_t* instance = bc_create_binary_Blocks(20, instance_blocks);
    const size_t start = 21;
    const size_t length = 10;
    // Expected
    const uint8_t expected_blocks[] = {};
    bc_binary_t* expected = bc_create_binary_Blocks(0, expected_blocks);
    // Substring result
    bc_binary_t* result = bc_binary__substring_Length(instance, start, length);
    BOOST_REQUIRE(bc_binary__equals(expected, result));
    bc_destroy_binary(result);
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(substring_length_zero_c)
{
    // Instance
    const uint8_t instance_blocks[] = { 0xAA, 0xBB, 0xCC };
    bc_binary_t* instance = bc_create_binary_Blocks(20, instance_blocks);
    const size_t start = 5;
    const size_t length = 0;
    // Expected
    const uint8_t expected_blocks[] = {};
    bc_binary_t* expected = bc_create_binary_Blocks(0, expected_blocks);
    // Substring result
    bc_binary_t* result = bc_binary__substring_Length(instance, start, length);
    BOOST_REQUIRE(bc_binary__equals(expected, result));
    bc_destroy_binary(result);
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(substring_byte_aligned_start_c)
{
    // Instance
    const uint8_t instance_blocks[] = { 0xAA, 0xBB, 0xCC };
    bc_binary_t* instance = bc_create_binary_Blocks(20, instance_blocks);
    const size_t start = 8;
    const size_t length = 10;
    // Expected
    const uint8_t expected_blocks[] = { 0xBB, 0xC0 };
    bc_binary_t* expected = bc_create_binary_Blocks(10, expected_blocks);
    // Substring result
    bc_binary_t* result = bc_binary__substring_Length(instance, start, length);
    BOOST_REQUIRE(bc_binary__equals(expected, result));
    bc_destroy_binary(result);
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(substring_byte_nonaligned_start_c)
{
    // Instance
    const uint8_t instance_blocks[] = { 0xAA, 0xBB, 0xCC };
    bc_binary_t* instance = bc_create_binary_Blocks(20, instance_blocks);
    const size_t start = 10;
    const size_t length = 10;
    // Expected
    const uint8_t expected_blocks[] = { 0xEF, 0x00 };
    bc_binary_t* expected = bc_create_binary_Blocks(10, expected_blocks);
    // Substring result
    bc_binary_t* result = bc_binary__substring_Length(instance, start, length);
    BOOST_REQUIRE(bc_binary__equals(expected, result));
    bc_destroy_binary(result);
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(substring_request_exceeds_string_c)
{
    // Instance
    const uint8_t instance_blocks[] = { 0xAA, 0xBB, 0xCC };
    bc_binary_t* instance = bc_create_binary_Blocks(20, instance_blocks);
    const size_t start = 10;
    const size_t length = 15;
    // Expected
    const uint8_t expected_blocks[] = { 0xEF, 0x00 };
    bc_binary_t* expected = bc_create_binary_Blocks(10, expected_blocks);
    // Substring result
    bc_binary_t* result = bc_binary__substring_Length(instance, start, length);
    BOOST_REQUIRE(bc_binary__equals(expected, result));
    bc_destroy_binary(result);
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_CASE(substring_implicit_length_c)
{
    // Instance
    const uint8_t instance_blocks[] = { 0xAA, 0xBB, 0xCC };
    bc_binary_t* instance = bc_create_binary_Blocks(20, instance_blocks);
    const size_t start = 10;
    // Expected
    const uint8_t expected_blocks[] = { 0xEF, 0x00 };
    bc_binary_t* expected = bc_create_binary_Blocks(10, expected_blocks);
    // Substring result
    bc_binary_t* result = bc_binary__substring(instance, start);
    BOOST_REQUIRE(bc_binary__equals(expected, result));
    bc_destroy_binary(result);
    bc_destroy_binary(instance);
    bc_destroy_binary(expected);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(binary__blocks_c)

BOOST_AUTO_TEST_CASE(string_to_prefix__32_bits__expected_value_c)
{
    const uint8_t blocks_data[] = { 0xba, 0xad, 0xf0, 0x0d };
    bc_data_chunk_t* blocks = bc_create_data_chunk_Array(blocks_data, 4);

    bc_binary_t* prefix = bc_create_binary_String(
        "10111010101011011111000000001101");

    bc_data_chunk_t* prefix_blocks = bc_binary__blocks(prefix);
    BOOST_REQUIRE(bc_data_chunk__equals(prefix_blocks, blocks));

    bc_destroy_data_chunk(prefix_blocks);
    bc_destroy_binary(prefix);
    bc_destroy_data_chunk(blocks);
}

BOOST_AUTO_TEST_CASE(prefix_to_bytes__32_bits__expected_value_c)
{
    const uint8_t blocks_data[] = { 0xba, 0xad, 0xf0, 0x0d };
    bc_data_chunk_t* blocks = bc_create_data_chunk_Array(blocks_data, 4);

    bc_binary_t* prefix = bc_create_binary_Blocks(32, blocks_data);

    bc_data_chunk_t* prefix_blocks = bc_binary__blocks(prefix);
    BOOST_REQUIRE(bc_data_chunk__equals(prefix_blocks, blocks));

    bc_destroy_data_chunk(prefix_blocks);
    bc_destroy_binary(prefix);
    bc_destroy_data_chunk(blocks);
}

BOOST_AUTO_TEST_CASE(bytes_to_prefix__zero_bits__round_trips_c)
{
    // Ignoring stream test.
}

BOOST_AUTO_TEST_CASE(prefix_to_bytes__zero_bits__round_trips_c)
{
    // Ignoring stream test.
}

BOOST_AUTO_TEST_CASE(bytes_to_prefix__one_bit__round_trips_c)
{
    // Ignoring stream test.
}

BOOST_AUTO_TEST_CASE(prefix_to_bytes__one_bit__round_trips_c)
{
    // Ignoring stream test.
}

BOOST_AUTO_TEST_CASE(bytes_to_prefix__two_bits_leading_zero__round_trips_c)
{
    // Ignoring stream test.
}

BOOST_AUTO_TEST_CASE(prefix_to_bytes__two_bits_leading_zero__round_trips_c)
{
    // Ignoring stream test.
}

BOOST_AUTO_TEST_CASE(bytes_to_prefix__two_bytes_leading_null_byte__round_trips_c)
{
    // Ignoring stream test.
}

BOOST_AUTO_TEST_CASE(prefix_to_bytes__two_bytes_leading_null_byte__round_trips_c)
{
    // Ignoring stream test.
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

