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

BOOST_AUTO_TEST_SUITE(checksum_tests_c)

// TODO: add append_checksum<> tests.
// TODO: add build_checked_array<> tests.

BOOST_AUTO_TEST_CASE(checksum__append_checksum__size__increased_by_checksum_size_c)
{
    bc_data_chunk_t* data = bc_create_data_chunk_Array(
        bc_data_array_t{ 0, 0, 0, 0, 0 }, 5);
    const size_t data_size = bc_data_chunk__size(data);
    bc_append_checksum(data);
    BOOST_REQUIRE_EQUAL(
        bc_data_chunk__size(data), data_size + bc_checksum_size());
    bc_destroy_data_chunk(data);
}

BOOST_AUTO_TEST_CASE(checksum__append_checksum__empty__valid_c)
{
    bc_data_chunk_t* data = bc_create_data_chunk_Array(
        bc_data_array_t{}, 0);
    size_t checksum = bc_data_chunk__size(data);
    bc_append_checksum(data);
    const uint8_t* cdata = bc_data_chunk__cdata(data);
    BOOST_REQUIRE_EQUAL(cdata[checksum++], 0x5du);
    BOOST_REQUIRE_EQUAL(cdata[checksum++], 0xf6u);
    BOOST_REQUIRE_EQUAL(cdata[checksum++], 0xe0u);
    BOOST_REQUIRE_EQUAL(cdata[checksum++], 0xe2u);
    bc_destroy_data_chunk(data);
}

BOOST_AUTO_TEST_CASE(checksum__append_checksum__not_empty__valid_c)
{
    bc_data_chunk_t* data = bc_create_data_chunk_Array(
        bc_data_array_t{ 0, 0, 0, 0, 0 }, 5);
    size_t checksum = bc_data_chunk__size(data);
    bc_append_checksum(data);
    const uint8_t* cdata = bc_data_chunk__cdata(data);
    BOOST_REQUIRE_EQUAL(cdata[checksum++], 0x79u);
    BOOST_REQUIRE_EQUAL(cdata[checksum++], 0x01u);
    BOOST_REQUIRE_EQUAL(cdata[checksum++], 0xafu);
    BOOST_REQUIRE_EQUAL(cdata[checksum++], 0x93u);
    bc_destroy_data_chunk(data);
}

BOOST_AUTO_TEST_CASE(checksum__bitcoin_checksum__always__valid_c)
{
    bc_data_chunk_t* data = bc_create_data_chunk_Array(
        bc_data_array_t{ 0, 0, 0, 0, 0 }, 5);
    const uint32_t result = bc_bitcoin_checksum(data);
    BOOST_REQUIRE_EQUAL(result, 0x93af0179u);
    bc_destroy_data_chunk(data);
}

BOOST_AUTO_TEST_CASE(checksum__build_checked_array__empty__valid_c)
{
    // Skipping build_checked_array test.
    // Template function not implemented in C layer.
}

BOOST_AUTO_TEST_CASE(checksum__build_checked_array__not_empty__valid_c)
{
    // Skipping build_checked_array test.
    // Template function not implemented in C layer.
}

BOOST_AUTO_TEST_CASE(checksum__build_checked_array__overflow__false_c)
{
    // Skipping build_checked_array test.
    // Template function not implemented in C layer.
}

BOOST_AUTO_TEST_CASE(checksum__insert_checksum__empty__valid_c)
{
    // Skipping insert_checksum test.
    // Template function not implemented in C layer.
}

BOOST_AUTO_TEST_CASE(checksum__insert_checksum__not_empty__valid_c)
{
    // Skipping insert_checksum test.
    // Template function not implemented in C layer.
}

BOOST_AUTO_TEST_CASE(checksum__insert_checksum__underflow__false_c)
{
    // Skipping insert_checksum test.
    // Template function not implemented in C layer.
}

BOOST_AUTO_TEST_CASE(checksum__verify_checksum__underflow__false_c)
{
    bc_data_chunk_t* data = bc_create_data_chunk_Array(
        bc_data_array_t{ 0, 0, 0 }, 3);
    BOOST_REQUIRE(!bc_verify_checksum(data));
    bc_destroy_data_chunk(data);
}

BOOST_AUTO_TEST_CASE(checksum__verify_checksum__not_set__false_c)
{
    bc_data_chunk_t* data = bc_create_data_chunk_Array(
        bc_data_array_t{ 0, 0, 0, 0, 0 }, 5);
    BOOST_REQUIRE(!bc_verify_checksum(data));
    bc_destroy_data_chunk(data);
}

BOOST_AUTO_TEST_CASE(checksum__verify_checksum__added__true_c)
{
    bc_data_chunk_t* data = bc_create_data_chunk_Array(
        bc_data_array_t{ 0, 0, 0, 0, 0 }, 5);
    bc_append_checksum(data);
    BOOST_REQUIRE(bc_verify_checksum(data));
    bc_destroy_data_chunk(data);
}

BOOST_AUTO_TEST_CASE(checksum__verify_checksum__invalidated__false_c)
{
    bc_data_chunk_t* data = bc_create_data_chunk_Array(
        bc_data_array_t{ 0, 0, 0, 0, 0 }, 5);
    const size_t data_size = bc_data_chunk__size(data);
    bc_append_checksum(data);
    bc_data_chunk__data(data)[data_size] = 42;
    BOOST_REQUIRE(!bc_verify_checksum(data));
    bc_destroy_data_chunk(data);
}

BOOST_AUTO_TEST_SUITE_END()

