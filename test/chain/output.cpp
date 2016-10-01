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

const char* valid_raw_output_hex =
    "20300500000000001976a914905f933de850988603aafeeb2fd7fce61e66fe5d88ac";

BOOST_AUTO_TEST_SUITE(output_tests_c)

BOOST_AUTO_TEST_CASE(from_data_fails_c)
{
    bc_data_chunk_t* data = bc_create_data_chunk();
    bc_data_chunk__resize(data, 2);

    bc_output_t* instance = bc_create_output();

    BOOST_REQUIRE_EQUAL(false, bc_output__from_data(instance, data));
    BOOST_REQUIRE_EQUAL(false, bc_output__is_valid(instance));

    bc_destroy_output(instance);
    bc_destroy_data_chunk(data);
}

BOOST_AUTO_TEST_CASE(factory_data_chunk_success_c)
{
    bc_data_chunk_t* valid_raw_output = bc_create_data_chunk();
    bc_decode_base16(valid_raw_output, valid_raw_output_hex);

    bc_output_t* instance = bc_output__factory_from_data(valid_raw_output);
    BOOST_REQUIRE(bc_output__is_valid(instance));
    BOOST_REQUIRE_EQUAL(bc_output__serialized_size(instance),
        bc_data_chunk__size(valid_raw_output));

    // Re-save and compare against original.
    bc_data_chunk_t* resave = bc_output__to_data(instance);
    BOOST_REQUIRE_EQUAL(bc_data_chunk__size(resave),
        bc_data_chunk__size(valid_raw_output));
    BOOST_REQUIRE(bc_data_chunk__equals(resave, valid_raw_output));

    bc_destroy_output(instance);
    bc_destroy_data_chunk(valid_raw_output);
}

BOOST_AUTO_TEST_CASE(factory_stream_success_c)
{
    // Skipping istream test. Not implemented in C layer.
}

BOOST_AUTO_TEST_CASE(factory_reader_success_c)
{
    // Skipping istream test. Not implemented in C layer.
}

BOOST_AUTO_TEST_SUITE_END()

