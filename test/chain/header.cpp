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
#include <boost/iostreams/stream.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/bitcoin.h>

using namespace bc;

BOOST_AUTO_TEST_SUITE(header_tests_c)

BOOST_AUTO_TEST_CASE(from_data_fails_c)
{
    bc_data_chunk_t* data = bc_create_data_chunk();
    bc_data_chunk__resize(data, 10);
    bc_header_t* header = bc_create_header();

    BOOST_REQUIRE_EQUAL(false, bc_header__from_data(header, data));
    BOOST_REQUIRE_EQUAL(false, bc_header__is_valid(header));

    bc_destroy_header(header);
    bc_destroy_data_chunk(data);
}

BOOST_AUTO_TEST_CASE(roundtrip_to_data_factory_from_data_stream_c)
{
    // Skipping istream test. Not implemented in C layer.
}

BOOST_AUTO_TEST_CASE(roundtrip_to_data_factory_from_data_reader_c)
{
    // Skipping istream test. Not implemented in C layer.
}

BOOST_AUTO_TEST_CASE(roundtrip_to_data_factory_from_data_reader_without_transaction_count_does_not_match_c)
{
    // Skipping istream test. Not implemented in C layer.
}

BOOST_AUTO_TEST_CASE(roundtrip_to_data_factory_from_data_reader_with_transaction_count_matches_c)
{
    // Skipping istream test. Not implemented in C layer.
}

BOOST_AUTO_TEST_SUITE_END()

