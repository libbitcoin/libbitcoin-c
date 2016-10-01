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
#include <boost/iostreams/stream.hpp>
#include <boost/test/unit_test.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/bitcoin.h>

using namespace bc;

BOOST_AUTO_TEST_SUITE(transaction_tests_c)

BOOST_AUTO_TEST_CASE(is_coinbase_returns_false_c)
{
    bc_transaction_t* instance = bc_create_transaction();
    BOOST_REQUIRE_EQUAL(false, bc_transaction__is_coinbase(instance));
    bc_destroy_transaction(instance);
}

BOOST_AUTO_TEST_CASE(is_coinbase_returns_true_c)
{
    bc_transaction_t* instance = bc_create_transaction();
    bc_input_list_t* inputs = bc_create_input_list();
    bc_input_t* input = bc_create_input();
    // previous output point
    bc_hash_digest_t* null_hash = bc_null_hash();
    bc_output_point_t* prevout = bc_create_output_point_Tuple(
        null_hash, bc_max_input_sequence());
    bc_destroy_hash_digest(null_hash);
    bc_input__set_previous_output(input, prevout);
    bc_destroy_output_point(prevout);
    // Add to list of inputs
    bc_input_list__push_back(inputs, &input);
    bc_transaction__set_inputs(instance, inputs);
    bc_destroy_input_list(inputs);
    BOOST_REQUIRE_EQUAL(true, bc_transaction__is_coinbase(instance));
    bc_destroy_transaction(instance);
}

BOOST_AUTO_TEST_CASE(is_final_locktime_zero_returns_true_c)
{
    uint64_t height = 100;
    uint32_t time = 100;
    bc_transaction_t* instance = bc_create_transaction();
    bc_transaction__set_locktime(instance, 0);
    BOOST_REQUIRE_EQUAL(true, bc_transaction__is_final(instance, height, time));
    bc_destroy_transaction(instance);
}

BOOST_AUTO_TEST_CASE(is_final_locktime_less_block_time_greater_threshold_returns_true_c)
{
    uint64_t height = bc_locktime_threshold() + 100;
    uint32_t time = 100;
    bc_transaction_t* instance = bc_create_transaction();
    bc_transaction__set_locktime(instance, bc_locktime_threshold() + 50);
    BOOST_REQUIRE_EQUAL(true, bc_transaction__is_final(instance, height, time));
    bc_destroy_transaction(instance);
}

BOOST_AUTO_TEST_CASE(is_final_locktime_less_block_height_less_threshold_returns_true_c)
{
    uint64_t height = 100;
    uint32_t time = 100;
    bc_transaction_t* instance = bc_create_transaction();
    bc_transaction__set_locktime(instance, 50);
    BOOST_REQUIRE_EQUAL(true, bc_transaction__is_final(instance, height, time));
    bc_destroy_transaction(instance);
}

BOOST_AUTO_TEST_CASE(is_final_locktime_input_not_final_returns_false_c)
{
    uint64_t height = 100;
    uint32_t time = 100;
    bc_transaction_t* instance = bc_create_transaction();
    bc_transaction__set_locktime(instance, 101);
    bc_input_list_t* inputs = bc_create_input_list();
    bc_input_t* input = bc_create_input();
    bc_input__set_sequence(input, 1);
    // Add to list of inputs
    bc_input_list__push_back(inputs, &input);
    bc_transaction__set_inputs(instance, inputs);
    bc_destroy_input_list(inputs);
    BOOST_REQUIRE_EQUAL(false, bc_transaction__is_final(instance, height, time));
    bc_destroy_transaction(instance);
}

BOOST_AUTO_TEST_CASE(is_final_locktime_inputs_final_returns_true_c)
{
    uint64_t height = 100;
    uint32_t time = 100;
    bc_transaction_t* instance = bc_create_transaction();
    bc_transaction__set_locktime(instance, 101);
    bc_input_list_t* inputs = bc_create_input_list();
    bc_input_t* input = bc_create_input();
    bc_input__set_sequence(input, bc_max_input_sequence());
    // Add to list of inputs
    bc_input_list__push_back(inputs, &input);
    bc_transaction__set_inputs(instance, inputs);
    bc_destroy_input_list(inputs);
    BOOST_REQUIRE_EQUAL(true, bc_transaction__is_final(instance, height, time));
    bc_destroy_transaction(instance);
}

BOOST_AUTO_TEST_CASE(is_locktime_conflict_locktime_zero_returns_false_c)
{
    bc_transaction_t* instance = bc_create_transaction();
    bc_transaction__set_locktime(instance, 0);
    BOOST_REQUIRE_EQUAL(false, bc_transaction__is_locktime_conflict(instance));
    bc_destroy_transaction(instance);
}

BOOST_AUTO_TEST_CASE(is_locktime_conflict_input_sequence_not_maximum_returns_false_c)
{
    bc_transaction_t* instance = bc_create_transaction();
    bc_transaction__set_locktime(instance, 2143);
    bc_input_list_t* inputs = bc_create_input_list();
    bc_input_t* input = bc_create_input();
    bc_input__set_sequence(input, 1);
    // Add to list of inputs
    bc_input_list__push_back(inputs, &input);
    bc_transaction__set_inputs(instance, inputs);
    bc_destroy_input_list(inputs);
    BOOST_REQUIRE_EQUAL(false, bc_transaction__is_locktime_conflict(instance));
    bc_destroy_transaction(instance);
}

BOOST_AUTO_TEST_CASE(is_locktime_conflict_no_inputs_returns_true_c)
{
    bc_transaction_t* instance = bc_create_transaction();
    bc_transaction__set_locktime(instance, 2143);
    BOOST_REQUIRE_EQUAL(true, bc_transaction__is_locktime_conflict(instance));
    bc_destroy_transaction(instance);
}

BOOST_AUTO_TEST_CASE(is_locktime_conflict_input_max_sequence_returns_true_c)
{
    bc_transaction_t* instance = bc_create_transaction();
    bc_transaction__set_locktime(instance, 2143);
    bc_input_list_t* inputs = bc_create_input_list();
    bc_input_t* input = bc_create_input();
    bc_input__set_sequence(input, bc_max_input_sequence());
    // Add to list of inputs
    bc_input_list__push_back(inputs, &input);
    bc_transaction__set_inputs(instance, inputs);
    bc_destroy_input_list(inputs);
    BOOST_REQUIRE_EQUAL(true, bc_transaction__is_locktime_conflict(instance));
    bc_destroy_transaction(instance);
}

BOOST_AUTO_TEST_CASE(total_output_value_returns_zero_c)
{
    bc_transaction_t* instance = bc_create_transaction();
    BOOST_REQUIRE_EQUAL(0u, bc_transaction__total_output_value(instance));
    bc_destroy_transaction(instance);
}

BOOST_AUTO_TEST_CASE(total_output_value_returns_positive_c)
{
    uint64_t expected = 1234;
    bc_transaction_t* instance = bc_create_transaction();
    bc_output_list_t* outputs = bc_create_output_list();
    bc_output_t* output;
    // Output 1
    output = bc_create_output();
    bc_output__set_value(output, 1200);
    bc_output_list__push_back(outputs, &output);
    // Output 2
    output = bc_create_output();
    bc_output__set_value(output, 34);
    bc_output_list__push_back(outputs, &output);
    bc_transaction__set_outputs(instance, outputs);
    bc_destroy_output_list(outputs);
    BOOST_REQUIRE_EQUAL(expected, bc_transaction__total_output_value(instance));
    bc_destroy_transaction(instance);
}

BOOST_AUTO_TEST_CASE(from_data_fails_c)
{
    bc_data_chunk_t* data = bc_create_data_chunk();
    bc_data_chunk__resize(data, 2);

    bc_transaction_t* instance = bc_create_transaction();

    BOOST_REQUIRE_EQUAL(false, bc_transaction__from_data(instance, data));
    BOOST_REQUIRE_EQUAL(false, bc_transaction__is_valid(instance));

    bc_destroy_transaction(instance);
    bc_destroy_data_chunk(data);
}

BOOST_AUTO_TEST_CASE(from_data_valid_junk_c)
{
    bc_data_chunk_t* junk = bc_create_data_chunk();
    bc_decode_base16(junk,
        "000000000000005739943a9c29a1955dfae2b3f37de547005bfb9535192e5fb0"
        "000000000000005739943a9c29a1955dfae2b3f37de547005bfb9535192e5fb0");

    bc_transaction_t* tx = bc_create_transaction();
    BOOST_REQUIRE(bc_transaction__from_data(tx, junk));
    bc_destroy_transaction(tx);

    bc_destroy_data_chunk(junk);
}

BOOST_AUTO_TEST_CASE(case_1_factory_data_chunk_c)
{
    bc_hash_digest_t* tx_hash = bc_hash_literal(
        &"bf7c3f5a69a78edd81f3eff7e93a37fb2d7da394d48db4d85e7e5353b9b8e270");

    bc_data_chunk_t* raw_tx = bc_create_data_chunk();
    bc_decode_base16(raw_tx,
        "0100000001f08e44a96bfb5ae63eda1a6620adae37ee37ee4777fb0336e1bbbc"
        "4de65310fc010000006a473044022050d8368cacf9bf1b8fb1f7cfd9aff63294"
        "789eb1760139e7ef41f083726dadc4022067796354aba8f2e02363c5e510aa7e"
        "2830b115472fb31de67d16972867f13945012103e589480b2f746381fca01a9b"
        "12c517b7a482a203c8b2742985da0ac72cc078f2ffffffff02f0c9c467000000"
        "001976a914d9d78e26df4e4601cf9b26d09c7b280ee764469f88ac80c4600f00"
        "0000001976a9141ee32412020a324b93b1a1acfdfff6ab9ca8fac288ac000000"
        "00");
    BOOST_REQUIRE_EQUAL(bc_data_chunk__size(raw_tx), 225u);

    bc_transaction_t* tx = bc_transaction__factory_from_data(raw_tx);
    BOOST_REQUIRE(bc_transaction__is_valid(tx));
    BOOST_REQUIRE_EQUAL(bc_transaction__serialized_size(tx), 225u);
    bc_hash_digest_t* tx_hash_cmp = bc_transaction__hash(tx);
    BOOST_REQUIRE(bc_hash_digest__equals(tx_hash_cmp, tx_hash));
    bc_destroy_hash_digest(tx_hash_cmp);

    // Re-save tx and compare against original.
    BOOST_REQUIRE_EQUAL(bc_transaction__serialized_size(tx),
        bc_data_chunk__size(raw_tx));
    bc_data_chunk_t* resave = bc_transaction__to_data(tx);
    BOOST_REQUIRE(bc_data_chunk__equals(resave, raw_tx));
    bc_destroy_data_chunk(resave);

    bc_destroy_transaction(tx);
    bc_destroy_data_chunk(raw_tx);
    bc_destroy_hash_digest(tx_hash);
}

BOOST_AUTO_TEST_CASE(case_2_factory_data_chunk_c)
{
    bc_hash_digest_t* tx_hash = bc_hash_literal(
        &"8a6d9302fbe24f0ec756a94ecfc837eaffe16c43d1e68c62dfe980d99eea556f");

    bc_data_chunk_t* raw_tx = bc_create_data_chunk();
    bc_decode_base16(raw_tx,
        "010000000364e62ad837f29617bafeae951776e7a6b3019b2da37827921548d1"
        "a5efcf9e5c010000006b48304502204df0dc9b7f61fbb2e4c8b0e09f3426d625"
        "a0191e56c48c338df3214555180eaf022100f21ac1f632201154f3c69e1eadb5"
        "9901a34c40f1127e96adc31fac6ae6b11fb4012103893d5a06201d5cf61400e9"
        "6fa4a7514fc12ab45166ace618d68b8066c9c585f9ffffffff54b755c39207d4"
        "43fd96a8d12c94446a1c6f66e39c95e894c23418d7501f681b010000006b4830"
        "4502203267910f55f2297360198fff57a3631be850965344370f732950b47795"
        "737875022100f7da90b82d24e6e957264b17d3e5042bab8946ee5fc676d15d91"
        "5da450151d36012103893d5a06201d5cf61400e96fa4a7514fc12ab45166ace6"
        "18d68b8066c9c585f9ffffffff0aa14d394a1f0eaf0c4496537f8ab9246d9663"
        "e26acb5f308fccc734b748cc9c010000006c493046022100d64ace8ec2d5feeb"
        "3e868e82b894202db8cb683c414d806b343d02b7ac679de7022100a2dcd39940"
        "dd28d4e22cce417a0829c1b516c471a3d64d11f2c5d754108bdc0b012103893d"
        "5a06201d5cf61400e96fa4a7514fc12ab45166ace618d68b8066c9c585f9ffff"
        "ffff02c0e1e400000000001976a914884c09d7e1f6420976c40e040c30b2b622"
        "10c3d488ac20300500000000001976a914905f933de850988603aafeeb2fd7fc"
        "e61e66fe5d88ac00000000");
    BOOST_REQUIRE_EQUAL(bc_data_chunk__size(raw_tx), 523u);

    bc_transaction_t* tx = bc_transaction__factory_from_data(raw_tx);
    BOOST_REQUIRE(bc_transaction__is_valid(tx));
    bc_hash_digest_t* tx_hash_cmp = bc_transaction__hash(tx);
    BOOST_REQUIRE(bc_hash_digest__equals(tx_hash_cmp, tx_hash));
    bc_destroy_hash_digest(tx_hash_cmp);

    // Re-save tx and compare against original.
    BOOST_REQUIRE_EQUAL(bc_transaction__serialized_size(tx),
        bc_data_chunk__size(raw_tx));
    bc_data_chunk_t* resave = bc_transaction__to_data(tx);
    BOOST_REQUIRE(bc_data_chunk__equals(resave, raw_tx));
    bc_destroy_data_chunk(resave);

    bc_destroy_transaction(tx);
    bc_destroy_data_chunk(raw_tx);
    bc_destroy_hash_digest(tx_hash);
}

BOOST_AUTO_TEST_CASE(case_1_factory_stream_c)
{
    // Skipping stream test. Not implemented in C layer.
}

BOOST_AUTO_TEST_CASE(case_2_factory_stream_c)
{
    // Skipping stream test. Not implemented in C layer.
}

BOOST_AUTO_TEST_CASE(case_1_factory_reader_c)
{
    // Skipping stream test. Not implemented in C layer.
}

BOOST_AUTO_TEST_CASE(case_2_factory_reader_c)
{
    // Skipping stream test. Not implemented in C layer.
}

BOOST_AUTO_TEST_SUITE_END()

