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

const char* valid_raw_input_hex =
    "54b755c39207d443fd96a8d12c94446a1c6f66e39c95e894c23418d7501f681b01000"
    "0006b48304502203267910f55f2297360198fff57a3631be850965344370f732950b4"
    "7795737875022100f7da90b82d24e6e957264b17d3e5042bab8946ee5fc676d15d915"
    "da450151d36012103893d5a06201d5cf61400e96fa4a7514fc12ab45166ace618d68b"
    "8066c9c585f9ffffffff";

BOOST_AUTO_TEST_SUITE(input_tests_c)

BOOST_AUTO_TEST_CASE(from_data_fails_c)
{
    bc_data_chunk_t* data = bc_create_data_chunk();
    bc_data_chunk__resize(data, 2);

    bc_input_t* instance = bc_create_input();

    BOOST_REQUIRE_EQUAL(false, bc_input__from_data(instance, data));
    BOOST_REQUIRE_EQUAL(false, bc_input__is_valid(instance));

    bc_destroy_input(instance);
    bc_destroy_data_chunk(data);
}

BOOST_AUTO_TEST_CASE(from_data_valid_junk_c)
{
    bc_data_chunk_t* junk = bc_create_data_chunk();
    bc_decode_base16(junk,
        "000000000000005739943a9c29a1955dfae2b3f37de547005bfb9535192e5fb0"
        "000000000000005739943a9c29a1955dfae2b3f37de547005bfb9535192e5fb0");
    // data_chunk_stream_host host(junk);
    bc_input_t* instance = bc_create_input();
    BOOST_REQUIRE(bc_input__from_data(instance, junk));
    bc_destroy_input(instance);
    bc_destroy_data_chunk(junk);
}

BOOST_AUTO_TEST_CASE(factory_data_chunk_success_c)
{
    bc_data_chunk_t* valid_raw_input = bc_create_data_chunk();
    bc_decode_base16(valid_raw_input, valid_raw_input_hex);

    bc_input_t* instance = bc_input__factory_from_data(valid_raw_input);
    BOOST_REQUIRE(bc_input__is_valid(instance));
    BOOST_REQUIRE_EQUAL(bc_input__serialized_size(instance),
        bc_data_chunk__size(valid_raw_input));

    // Re-save and compare against original.
    bc_data_chunk_t* resave = bc_input__to_data(instance);
    BOOST_REQUIRE_EQUAL(bc_data_chunk__size(resave),
        bc_data_chunk__size(valid_raw_input));
    BOOST_REQUIRE(bc_data_chunk__equals(resave, valid_raw_input));

    bc_destroy_input(instance);
    bc_destroy_data_chunk(valid_raw_input);
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

