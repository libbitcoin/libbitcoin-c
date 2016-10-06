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
#include <bitcoin/bitcoin.h>

// TODO: move this into the tests by source file organization.
BOOST_AUTO_TEST_SUITE(satoshi_words_c)

BOOST_AUTO_TEST_CASE(satoshi_words_mainnet_c)
{
    // Create mainnet genesis block.
    bc_block_t* block = bc_block__genesis_mainnet();

    // Genesis block contains a single coinbase transaction.
    bc_transaction_list_t* txs = bc_block__transactions(block);
    BOOST_REQUIRE_EQUAL(bc_transaction_list__size(txs), 1u);

    // Get first transaction in block (coinbase).
    bc_transaction_t* coinbase_tx = bc_transaction_list__at(txs, 0);

    // Coinbase tx has a single input.
    bc_input_list_t* inputs = bc_transaction__inputs(coinbase_tx);
    BOOST_REQUIRE_EQUAL(bc_input_list__size(inputs), 1u);
    bc_input_t* coinbase_input = bc_input_list__at(inputs, 0);

    // Convert the input script to its raw format.
    bc_script_t* coinbase_script = bc_input__script(coinbase_input);
    bc_data_chunk_t* raw_message = bc_script__to_data(coinbase_script, false);

    // Convert to a string after removing the 8 byte checksum.
    BOOST_REQUIRE_GT(bc_data_chunk__size(raw_message), 8u);
    bc_string_t* message = bc_create_string_Length(
        reinterpret_cast<const char*>(bc_data_chunk__cdata(raw_message) + 8),
        bc_data_chunk__size(raw_message) - 8);

    BOOST_REQUIRE(bc_string__equals_cstr(message,
        "The Times 03/Jan/2009 Chancellor on brink of second bailout for banks"));

    // We don't delete the objects stored in the vector.
    bc_destroy_string(message);
    bc_destroy_data_chunk(raw_message);
    bc_destroy_script(coinbase_script);
    bc_destroy_input_list(inputs);
    bc_destroy_transaction_list(txs);
    bc_destroy_block(block);
}

BOOST_AUTO_TEST_SUITE_END()
