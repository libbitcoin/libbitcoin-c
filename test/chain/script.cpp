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
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/test/unit_test.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/bitcoin.h>
#include <bitcoin/bitcoin/c/internal/chain/script/script.hpp>
#include <bitcoin/bitcoin/c/internal/chain/transaction.hpp>
#include "script.hpp"

using namespace bc;
using namespace bc::chain;

bool is_number(const std::string& token)
{
    if (boost::all(token, boost::is_digit()))
        return true;

    // Now check for negative numbers
    if (!boost::starts_with(token, "-"))
        return false;

    std::string numeric_part(token.begin() + 1, token.end());
    return boost::all(numeric_part, boost::is_digit());
}

bool is_hex_data(const std::string& token)
{
    if (!boost::starts_with(token, "0x"))
        return false;

    std::string hex_part(token.begin() + 2, token.end());
    return boost::all(hex_part, [](char c) { return is_base16(c); });
}

bool is_quoted_string(const std::string& token)
{
    if (token.size() < 2)
        return false;

    return boost::starts_with(token, "'") && boost::ends_with(token, "'");
}

chain::opcode token_to_opcode(const std::string& token)
{
    std::string lower_token = token;
    boost::algorithm::to_lower(lower_token);
    return chain::string_to_opcode(lower_token);
}

bool is_opcode(const std::string& token)
{
    return token_to_opcode(token) != chain::opcode::bad_operation;
}

bool is_opx(int64_t value)
{
    return value == -1 || (1 <= value && value <= 16);
}

void push_literal(data_chunk& raw_script, int64_t value)
{
    BITCOIN_ASSERT(is_opx(value));
    switch (value)
    {
        case -1:
            raw_script.push_back(static_cast<uint8_t>(chain::opcode::negative_1));
            return;

#define PUSH_X(n) \
        case n: \
            raw_script.push_back(static_cast<uint8_t>(chain::opcode::op_##n)); \
            return;

        PUSH_X(1);
        PUSH_X(2);
        PUSH_X(3);
        PUSH_X(4);
        PUSH_X(5);
        PUSH_X(6);
        PUSH_X(7);
        PUSH_X(8);
        PUSH_X(9);
        PUSH_X(10);
        PUSH_X(11);
        PUSH_X(12);
        PUSH_X(13);
        PUSH_X(14);
        PUSH_X(15);
        PUSH_X(16);
    }
}

void push_data(data_chunk& raw_script, const data_chunk& data)
{
    chain::opcode code;

    // pushdata1 = 76
    if (data.empty())
        code = chain::opcode::zero;
    else if (data.size() < 76)
        code = chain::opcode::special;
    else if (data.size() <= 0xff)
        code = chain::opcode::pushdata1;
    else if (data.size() <= 0xffff)
        code = chain::opcode::pushdata2;
    else
    {
        BOOST_REQUIRE_LE(data.size(), 0xffffffffu);
        code = chain::opcode::pushdata4;
    }

    chain::script tmp_script;
    tmp_script.operations.push_back(chain::operation{ code, data });
    data_chunk raw_tmp_script = tmp_script.to_data(false);
    extend_data(raw_script, raw_tmp_script);
}

static const auto sentinel = "__ENDING__";

bool parse_token(data_chunk& raw_script, data_chunk& raw_hex, std::string token)
{
    boost::trim(token);

    if (token.empty())
        return true;

    if (token == sentinel || !is_hex_data(token))
    {
        extend_data(raw_script, raw_hex);
        raw_hex.resize(0);
    }

    if (token == sentinel)
        return true;

    if (is_number(token))
    {
        const auto value = boost::lexical_cast<int64_t>(token);
        if (is_opx(value))
        {
            push_literal(raw_script, value);
        }
        else
        {
            script_number bignum(value);
            push_data(raw_script, bignum.data());
        }
    }
    else if (is_hex_data(token))
    {
        std::string hex_part(token.begin() + 2, token.end());
        data_chunk raw_data;
        if (!decode_base16(raw_data, hex_part))
            return false;

        extend_data(raw_hex, raw_data);
    }
    else if (is_quoted_string(token))
    {
        data_chunk inner_value(token.begin() + 1, token.end() - 1);
        push_data(raw_script, inner_value);
    }
    else if (is_opcode(token))
    {
        chain::opcode tokenized_opcode = token_to_opcode(token);
        raw_script.push_back(static_cast<uint8_t>(tokenized_opcode));
    }
    else
    {
        // see: stackoverflow.com/questions/15192332/boost-message-undefined
        BOOST_TEST_MESSAGE("Token parsing failed with: " << token);
        return false;
    }

    return true;
}

bool parse(chain::script& result_script, std::string format)
{
    boost::trim(format);
    if (format.empty())
        return true;

    data_chunk raw_hex;
    data_chunk raw_script;
    const auto tokens = split(format);
    for (const auto& token: tokens)
        if (!parse_token(raw_script, raw_hex, token))
            return false;

    parse_token(raw_script, raw_hex, sentinel);

    if (!result_script.from_data(raw_script, false, chain::script::parse_mode::strict))
        return false;

    if (result_script.operations.empty())
        return false;

    return true;
}

bc_transaction_t* new_tx(const script_test& test)
{
    script input_script;
    script output_script;

    if (!parse(input_script, test.input))
        return{};

    if (!parse(output_script, test.output))
        return{};

    input input;
    input.script = input_script;
    input.previous_output.cache.script = output_script;

    transaction tx;
    tx.inputs.push_back(std::move(input));
    return new bc_transaction_t{ new libbitcoin::chain::transaction(tx) };
}

BOOST_AUTO_TEST_SUITE(script_tests_c)

BOOST_AUTO_TEST_CASE(script__from_data__testnet_119058_non_parseable__fallback_c)
{
    bc_data_chunk_t* raw_script = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(raw_script, "0130323066643366303435313438356531306633383837363437356630643265396130393739343332353534313766653139316438623963623230653430643863333030326431373463336539306366323433393231383761313037623634373337633937333135633932393264653431373731636565613062323563633534353732653302ae"));

    bc_script_t* parsed = bc_create_script();
    BOOST_REQUIRE(bc_script__from_data(parsed,
        raw_script, false, bc_script_parse_mode__raw_data_fallback));

    bc_destroy_script(parsed);
    bc_destroy_data_chunk(raw_script);
}

BOOST_AUTO_TEST_CASE(script__from_data__parse__fails_c)
{
    bc_data_chunk_t* raw_script = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(raw_script, "3045022100ff1fc58dbd608e5e05846a8e6b45a46ad49878aef6879ad1a7cf4c5a7f853683022074a6a10f6053ab3cddc5620d169c7374cd42c1416c51b9744db2c8d9febfb84d01"));

    bc_script_t* parsed = bc_create_script();
    BOOST_REQUIRE(!bc_script__from_data(parsed,
        raw_script, true, bc_script_parse_mode__strict));

    bc_destroy_script(parsed);
    bc_destroy_data_chunk(raw_script);
}

BOOST_AUTO_TEST_CASE(script__from_data__to_data__roundtrips_c)
{
    bc_data_chunk_t* normal_output_script = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(normal_output_script, "76a91406ccef231c2db72526df9338894ccf9355e8f12188ac"));

    bc_script_t* out_script = bc_create_script();
    BOOST_REQUIRE(bc_script__from_data(out_script,
        normal_output_script, false, bc_script_parse_mode__raw_data_fallback));

    bc_data_chunk_t* roundtrip = bc_script__to_data(out_script, false);
    BOOST_REQUIRE(bc_data_chunk__equals(roundtrip, normal_output_script));

    bc_destroy_data_chunk(roundtrip);
    bc_destroy_script(out_script);
    bc_destroy_data_chunk(normal_output_script);
}

BOOST_AUTO_TEST_CASE(script__from_data__to_data_weird__roundtrips_c)
{
    bc_data_chunk_t* weird_raw_script = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(weird_raw_script,
        "0c49206c69656b20636174732e483045022100c7387f64e1f4"
        "cf654cae3b28a15f7572106d6c1319ddcdc878e636ccb83845"
        "e30220050ebf440160a4c0db5623e0cb1562f46401a7ff5b87"
        "7aa03415ae134e8c71c901534d4f0176519c6375522103b124"
        "c48bbff7ebe16e7bd2b2f2b561aa53791da678a73d2777cc1c"
        "a4619ab6f72103ad6bb76e00d124f07a22680e39debd4dc4bd"
        "b1aa4b893720dd05af3c50560fdd52af67529c63552103b124"
        "c48bbff7ebe16e7bd2b2f2b561aa53791da678a73d2777cc1c"
        "a4619ab6f721025098a1d5a338592bf1e015468ec5a8fafc1f"
        "c9217feb5cb33597f3613a2165e9210360cfabc01d52eaaeb3"
        "976a5de05ff0cfa76d0af42d3d7e1b4c233ee8a00655ed2103"
        "f571540c81fd9dbf9622ca00cfe95762143f2eab6b65150365"
        "bb34ac533160432102bc2b4be1bca32b9d97e2d6fb255504f4"
        "bc96e01aaca6e29bfa3f8bea65d8865855af672103ad6bb76e"
        "00d124f07a22680e39debd4dc4bdb1aa4b893720dd05af3c50"
        "560fddada820a4d933888318a23c28fb5fc67aca8530524e20"
        "74b1d185dbf5b4db4ddb0642848868685174519c6351670068"));

    bc_script_t* weird = bc_create_script();
    BOOST_REQUIRE(bc_script__from_data(weird,
        weird_raw_script, false, bc_script_parse_mode__raw_data_fallback));

    bc_data_chunk_t* roundtrip_result = bc_script__to_data(weird, false);
    BOOST_REQUIRE(bc_data_chunk__equals(roundtrip_result, weird_raw_script));

    bc_destroy_data_chunk(roundtrip_result);
    bc_destroy_script(weird);
    bc_destroy_data_chunk(weird_raw_script);
}

BOOST_AUTO_TEST_CASE(script__is_raw_data_operations_size_not_equal_one_returns_false_c)
{
    bc_script_t* instance = bc_create_script();
    BOOST_REQUIRE(!bc_script__is_raw_data(instance));
    bc_destroy_script(instance);
}

BOOST_AUTO_TEST_CASE(script__is_raw_data_code_not_equal_raw_data_returns_false_c)
{
    bc_script_t* instance = bc_create_script();

    bc_operation_stack_t* ops = bc_create_operation_stack();

    bc_operation_t* operation = bc_create_operation();
    bc_operation__set_code(operation, bc_opcode__vernotif);
    // stack takes ownership of the object
    bc_operation_stack__push_back(ops, &operation);
    BOOST_REQUIRE(operation == NULL);

    bc_script__set_operations(instance, ops);
    bc_destroy_operation_stack(ops);

    BOOST_REQUIRE(!bc_script__is_raw_data(instance));
    bc_destroy_script(instance);
}

BOOST_AUTO_TEST_CASE(script__is_raw_data_returns_true_c)
{
    bc_script_t* instance = bc_create_script();

    bc_operation_stack_t* ops = bc_create_operation_stack();

    bc_operation_t* operation = bc_create_operation();
    bc_operation__set_code(operation, bc_opcode__raw_data);
    // stack takes ownership of the object
    bc_operation_stack__push_back(ops, &operation);
    BOOST_REQUIRE(operation == NULL);

    bc_script__set_operations(instance, ops);
    bc_destroy_operation_stack(ops);

    BOOST_REQUIRE(bc_script__is_raw_data(instance));
    bc_destroy_script(instance);
}

BOOST_AUTO_TEST_CASE(script__factory_from_data_chunk_test_c)
{
    bc_data_chunk_t* raw = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(raw, "76a914fc7b44566256621affb1541cc9d59f08336d276b88ac"));

    bc_script_t* instance = bc_script__factory_from_data(
        raw, false, bc_script_parse_mode__strict);
    BOOST_REQUIRE(bc_script__is_valid(instance));

    bc_destroy_script(instance);
    bc_destroy_data_chunk(raw);
}

BOOST_AUTO_TEST_CASE(script__factory_from_data_stream_test_c)
{
    // Skip this test. We don't have streams in C API.
}

BOOST_AUTO_TEST_CASE(script__factory_from_data_reader_test_c)
{
    // Skip this test. We don't have streams in C API.
}

bool tx_inputs_empty(const bc_transaction_t* tx)
{
    bc_input_list_t* inputs = bc_transaction__inputs(tx);
    bool is_empty = bc_input_list__empty(inputs);
    bc_destroy_input_list(inputs);
    return is_empty;
}

// Valid pay-to-script-hash scripts are valid regardless of context,
// however after bip16 activation the scripts have additional constraints.
BOOST_AUTO_TEST_CASE(script__bip16__valid_c)
{
    for (const auto& test: valid_bip16_scripts)
    {
        bc_transaction_t* tx = new_tx(test);
        //BOOST_CHECK_MESSAGE(!tx_inputs_empty(tx), test.description);
        bc_destroy_transaction(tx);
        // These are valid prior to and after BIP16 activation.
        //BOOST_CHECK_MESSAGE(run_script(test, tx, bc_rule_fork__no_rules), test.description);
        //BOOST_CHECK_MESSAGE(run_script(test, tx, bc_rule_fork__bip16_rule), test.description);
        //BOOST_CHECK_MESSAGE(run_script(test, tx, bc_rule_fork__all_rules), test.description);
    }
}

BOOST_AUTO_TEST_CASE(script__bip16__invalidated_c)
{
    for (const auto& test: invalidated_bip16_scripts)
    {
        bc_transaction_t* tx = new_tx(test);
        bc_destroy_transaction(tx);
        // These are valid prior to BIP16 activation and invalid after.
        //BOOST_CHECK_MESSAGE(run_script(test, tx, bc_rule_fork__no_rules), test.description);
        //BOOST_CHECK_MESSAGE(!run_script(test, tx, bc_rule_fork__bip16_rule), test.description);
        //BOOST_CHECK_MESSAGE(!run_script(test, tx, bc_rule_fork__all_rules), test.description);
    }
}

// Prior to bip65 activation op_nop2 always returns true, but after it becomes a locktime comparer.
BOOST_AUTO_TEST_CASE(script__bip65__valid_c)
{
    bc_transaction_t* tx = bc_create_transaction();
    bc_transaction__set_locktime(tx, 500000042);

    bc_input_list_t* inputs = bc_create_input_list();
    bc_input_t* input = bc_create_input();
    bc_input__set_sequence(input, 42);
    bc_input_list__push_back(inputs, &input);
    bc_transaction__set_inputs(tx, inputs);
    bc_destroy_input_list(inputs);

    for (const auto& test: valid_bip65_scripts)
    {
        bc_transaction_t* tx = new_tx(test);
        bc_destroy_transaction(tx);
        // These are valid prior to and after BIP65 activation.
        //BOOST_CHECK_MESSAGE(run_script(test, tx, bc_rule_fork__no_rules), test.description);
        //BOOST_CHECK_MESSAGE(run_script(test, tx, bc_rule_fork__bip65_rule), test.description);
        //BOOST_CHECK_MESSAGE(run_script(test, tx, bc_rule_fork__all_rules), test.description);
    }
    bc_destroy_transaction(tx);
}

BOOST_AUTO_TEST_CASE(script__bip65__invalid_c)
{
    bc_transaction_t* tx = bc_create_transaction();
    bc_transaction__set_locktime(tx, 99);

    bc_input_list_t* inputs = bc_create_input_list();
    bc_input_t* input = bc_create_input();
    bc_input__set_sequence(input, 42);
    bc_input_list__push_back(inputs, &input);
    bc_transaction__set_inputs(tx, inputs);
    bc_destroy_input_list(inputs);

    for (const auto& test: invalid_bip65_scripts)
    {
        bc_transaction_t* tx = new_tx(test);
        bc_destroy_transaction(tx);
        // These are invalid prior to and after BIP65 activation.
        //BOOST_CHECK_MESSAGE(!run_script(test, tx, bc_rule_fork__no_rules), test.description);
        //BOOST_CHECK_MESSAGE(!run_script(test, tx, bc_rule_fork__bip65_rule), test.description);
        //BOOST_CHECK_MESSAGE(!run_script(test, tx, bc_rule_fork__all_rules), test.description);
    }
    bc_destroy_transaction(tx);
}

BOOST_AUTO_TEST_CASE(script__bip65__invalidated_c)
{
    bc_transaction_t* tx = bc_create_transaction();
    bc_transaction__set_locktime(tx, 99);

    bc_input_list_t* inputs = bc_create_input_list();
    bc_input_t* input = bc_create_input();
    bc_input__set_sequence(input, 42);
    bc_input_list__push_back(inputs, &input);
    bc_transaction__set_inputs(tx, inputs);
    bc_destroy_input_list(inputs);

    for (const auto& test: invalidated_bip65_scripts)
    {
        bc_transaction_t* tx = new_tx(test);
        bc_destroy_transaction(tx);
        // These are valid prior to BIP65 activation and invalid after.
        //BOOST_CHECK_MESSAGE(run_script(test, tx, bc_rule_fork__no_rules), test.description);
        //BOOST_CHECK_MESSAGE(!run_script(test, tx, bc_rule_fork__bip65_rule), test.description);
        //BOOST_CHECK_MESSAGE(!run_script(test, tx, bc_rule_fork__all_rules), test.description);
    }
    bc_destroy_transaction(tx);
}

// These are scripts potentially affected by bip66 (but should not be).
BOOST_AUTO_TEST_CASE(script__multisig__valid_c)
{
    bc_transaction_t* tx = bc_create_transaction();
    for (const auto& test: valid_multisig_scripts)
    {
        bc_transaction_t* tx = new_tx(test);
        bc_destroy_transaction(tx);
        // These are always valid.
        //BOOST_CHECK_MESSAGE(run_script(test, tx, bc_rule_fork__no_rules), test.description);
        //BOOST_CHECK_MESSAGE(run_script(test, tx, bc_rule_fork__bip66_rule), test.description);
        //BOOST_CHECK_MESSAGE(run_script(test, tx, bc_rule_fork__all_rules), test.description);
    }
    bc_destroy_transaction(tx);
}

// These are scripts potentially affected by bip66 (but should not be).
BOOST_AUTO_TEST_CASE(script__multisig__invalid_c)
{
    bc_transaction_t* tx = bc_create_transaction();
    for (const auto& test: invalid_multisig_scripts)
    {
        bc_transaction_t* tx = new_tx(test);
        bc_destroy_transaction(tx);
        // These are always invalid.
        //BOOST_CHECK_MESSAGE(!run_script(test, tx, bc_rule_fork__no_rules), test.description);
        //BOOST_CHECK_MESSAGE(!run_script(test, tx, bc_rule_fork__bip66_rule), test.description);
        //BOOST_CHECK_MESSAGE(!run_script(test, tx, bc_rule_fork__all_rules), test.description);
    }
    bc_destroy_transaction(tx);
}

BOOST_AUTO_TEST_CASE(rule_fork__free__valid_c)
{
    bc_transaction_t* tx = bc_create_transaction();
    for (const auto& test: valid_context_free_scripts)
    {
        bc_transaction_t* tx = new_tx(test);
        bc_destroy_transaction(tx);
        // These are always valid.
        //BOOST_CHECK_MESSAGE(run_script(test, tx, bc_rule_fork__no_rules), test.description);
        //BOOST_CHECK_MESSAGE(run_script(test, tx, bc_rule_fork__all_rules), test.description);
    }
    bc_destroy_transaction(tx);
}

BOOST_AUTO_TEST_CASE(rule_fork__free__invalid_c)
{
    for (const auto& test: invalid_context_free_scripts)
    {
        bc_transaction_t* tx = bc_create_transaction();
        bc_destroy_transaction(tx);
        // These are always invalid.
        //BOOST_CHECK_MESSAGE(!run_script(test, tx, bc_rule_fork__no_rules), test.description);
        //BOOST_CHECK_MESSAGE(!run_script(test, tx, bc_rule_fork__all_rules), test.description);
    }
}

// These are special tests for checksig.
BOOST_AUTO_TEST_CASE(script__checksig__uses_one_hash_c)
{
    // input 315ac7d4c26d69668129cc352851d9389b4a6868f1509c6c8b66bead11e2619f:1
    bc_data_chunk_t* tx_data = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(tx_data, "0100000002dc38e9359bd7da3b58386204e186d9408685f427f5e513666db735aa8a6b2169000000006a47304402205d8feeb312478e468d0b514e63e113958d7214fa572acd87079a7f0cc026fc5c02200fa76ea05bf243af6d0f9177f241caf606d01fcfd5e62d6befbca24e569e5c27032102100a1a9ca2c18932d6577c58f225580184d0e08226d41959874ac963e3c1b2feffffffffdc38e9359bd7da3b58386204e186d9408685f427f5e513666db735aa8a6b2169010000006b4830450220087ede38729e6d35e4f515505018e659222031273b7366920f393ee3ab17bc1e022100ca43164b757d1a6d1235f13200d4b5f76dd8fda4ec9fc28546b2df5b1211e8df03210275983913e60093b767e85597ca9397fb2f418e57f998d6afbbc536116085b1cbffffffff0140899500000000001976a914fcc9b36d38cf55d7d5b4ee4dddb6b2c17612f48c88ac00000000"));
    bc_transaction_t* parent_tx = bc_create_transaction();
    bc_transaction__from_data(parent_tx, tx_data);

    bc_data_chunk_t* distinguished = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(distinguished, "30450220087ede38729e6d35e4f515505018e659222031273b7366920f393ee3ab17bc1e022100ca43164b757d1a6d1235f13200d4b5f76dd8fda4ec9fc28546b2df5b1211e8df"));

    bc_data_chunk_t* pubkey = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(pubkey, "0275983913e60093b767e85597ca9397fb2f418e57f998d6afbbc536116085b1cb"));

    bc_data_chunk_t* script_data = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(script_data, "76a91433cef61749d11ba2adf091a5e045678177fe3a6d88ac"));

    bc_script_t* script_code = bc_create_script();
    const bool prefix = false;
    BOOST_REQUIRE(bc_script__from_data(script_code, script_data, prefix, bc_script_parse_mode__strict));

    bc_ec_signature_t* signature = bc_create_ec_signature();
    const bool strict = true;
    const uint32_t input_index = 1;
    BOOST_REQUIRE(bc_parse_signature(signature, distinguished, strict));
    BOOST_REQUIRE(bc_script__check_signature(signature,
        bc_signature_hash_algorithm__single, pubkey, script_code,
        parent_tx, input_index));

    bc_destroy_ec_signature(signature);
    bc_destroy_script(script_code);
    bc_destroy_data_chunk(script_data);
    bc_destroy_data_chunk(pubkey);
    bc_destroy_data_chunk(distinguished);
    bc_destroy_transaction(parent_tx);
    bc_destroy_data_chunk(tx_data);
}

BOOST_AUTO_TEST_CASE(script__checksig__normal_c)
{
    // input 315ac7d4c26d69668129cc352851d9389b4a6868f1509c6c8b66bead11e2619f:0
    bc_data_chunk_t* tx_data = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(tx_data, "0100000002dc38e9359bd7da3b58386204e186d9408685f427f5e513666db735aa8a6b2169000000006a47304402205d8feeb312478e468d0b514e63e113958d7214fa572acd87079a7f0cc026fc5c02200fa76ea05bf243af6d0f9177f241caf606d01fcfd5e62d6befbca24e569e5c27032102100a1a9ca2c18932d6577c58f225580184d0e08226d41959874ac963e3c1b2feffffffffdc38e9359bd7da3b58386204e186d9408685f427f5e513666db735aa8a6b2169010000006b4830450220087ede38729e6d35e4f515505018e659222031273b7366920f393ee3ab17bc1e022100ca43164b757d1a6d1235f13200d4b5f76dd8fda4ec9fc28546b2df5b1211e8df03210275983913e60093b767e85597ca9397fb2f418e57f998d6afbbc536116085b1cbffffffff0140899500000000001976a914fcc9b36d38cf55d7d5b4ee4dddb6b2c17612f48c88ac00000000"));
    bc_transaction_t* parent_tx = bc_create_transaction();
    bc_transaction__from_data(parent_tx, tx_data);

    bc_data_chunk_t* distinguished = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(distinguished, "304402205d8feeb312478e468d0b514e63e113958d7214fa572acd87079a7f0cc026fc5c02200fa76ea05bf243af6d0f9177f241caf606d01fcfd5e62d6befbca24e569e5c27"));
    
    bc_data_chunk_t* pubkey = bc_create_data_chunk();
    bc_decode_base16(pubkey, "02100a1a9ca2c18932d6577c58f225580184d0e08226d41959874ac963e3c1b2fe");

    bc_data_chunk_t* script_data = bc_create_data_chunk();
    bc_decode_base16(script_data, "76a914fcc9b36d38cf55d7d5b4ee4dddb6b2c17612f48c88ac");

    bc_script_t* script_code = bc_create_script();
    static const bool prefix = false;
    BOOST_REQUIRE(bc_script__from_data(script_code, script_data, prefix, bc_script_parse_mode__strict));

    bc_ec_signature_t* signature = bc_create_ec_signature();
    const bool strict = true;
    const uint32_t input_index = 0;
    BOOST_REQUIRE(bc_parse_signature(signature, distinguished, strict));
    BOOST_REQUIRE(bc_script__check_signature(signature,
        bc_signature_hash_algorithm__single, pubkey, script_code,
        parent_tx, input_index));

    bc_destroy_ec_signature(signature);
    bc_destroy_script(script_code);
    bc_destroy_data_chunk(script_data);
    bc_destroy_data_chunk(pubkey);
    bc_destroy_data_chunk(distinguished);
    bc_destroy_transaction(parent_tx);
    bc_destroy_data_chunk(tx_data);
}

BOOST_AUTO_TEST_CASE(script__create_endorsement__single_input_single_output__expected_c)
{
    bc_data_chunk_t* tx_data = bc_create_data_chunk();
    bc_decode_base16(tx_data, "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000");
    bc_transaction_t* new_tx = bc_create_transaction();
    bc_transaction__from_data(new_tx, tx_data);

    bc_script_t* prevout_script = bc_create_script();
    BOOST_REQUIRE(bc_script__from_string(prevout_script, "dup hash160 [ 88350574280395ad2c3e2ee20e322073d94e5e40 ] equalverify checksig"));

    bc_hash_digest_t* secret_data = bc_hash_literal(&"ce8f4b713ffdd2658900845251890f30371856be201cd1f5b3d970f793634333");
    bc_ec_secret_t* secret = bc_create_ec_secret_Data(
        bc_hash_digest__cdata(secret_data));
    bc_destroy_hash_digest(secret_data);

    bc_endorsement_t* out = bc_create_data_chunk();
    const uint32_t input_index = 0;
    const uint8_t sighash_type = bc_signature_hash_algorithm__all;
    BOOST_REQUIRE(bc_script__create_endorsement(
        out, secret, prevout_script, new_tx, input_index, sighash_type));

    bc_string_t* result = bc_encode_base16(out);
    const auto expected = "3045022100e428d3cc67a724cb6cfe8634aa299e58f189d9c46c02641e936c40cc16c7e8ed0220083949910fe999c21734a1f33e42fca15fb463ea2e08f0a1bccd952aacaadbb801";
    BOOST_REQUIRE(bc_string__equals_cstr(result, expected));
    bc_destroy_string(result);

    bc_destroy_data_chunk(out);
    bc_destroy_ec_secret(secret);
    bc_destroy_script(prevout_script);
    bc_destroy_transaction(new_tx);
    bc_destroy_data_chunk(tx_data);
}

BOOST_AUTO_TEST_CASE(script__create_endorsement__single_input_no_output__expected_c)
{
    bc_data_chunk_t* tx_data = bc_create_data_chunk();
    bc_decode_base16(tx_data, "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970000000000ffffffff0000000000");
    bc_transaction_t* new_tx = bc_create_transaction();
    bc_transaction__from_data(new_tx, tx_data);

    bc_script_t* prevout_script = bc_create_script();
    BOOST_REQUIRE(bc_script__from_string(prevout_script, "dup hash160 [ 88350574280395ad2c3e2ee20e322073d94e5e40 ] equalverify checksig"));

    bc_hash_digest_t* secret_data = bc_hash_literal(&"ce8f4b713ffdd2658900845251890f30371856be201cd1f5b3d970f793634333");
    bc_ec_secret_t* secret = bc_create_ec_secret_Data(
        bc_hash_digest__cdata(secret_data));
    bc_destroy_hash_digest(secret_data);

    bc_endorsement_t* out = bc_create_data_chunk();
    const uint32_t input_index = 0;
    const uint8_t sighash_type = bc_signature_hash_algorithm__all;
    BOOST_REQUIRE(bc_script__create_endorsement(
        out, secret, prevout_script, new_tx, input_index, sighash_type));

    bc_string_t* result = bc_encode_base16(out);
    const auto expected = "3045022100ba57820be5f0b93a0d5b880fbf2a86f819d959ecc24dc31b6b2d4f6ed286f253022071ccd021d540868ee10ca7634f4d270dfac7aea0d5912cf2b104111ac9bc756b01";
    BOOST_REQUIRE(bc_string__equals_cstr(result, expected));
    bc_destroy_string(result);

    bc_destroy_data_chunk(out);
    bc_destroy_ec_secret(secret);
    bc_destroy_script(prevout_script);
    bc_destroy_transaction(new_tx);
    bc_destroy_data_chunk(tx_data);
}

BOOST_AUTO_TEST_CASE(script__generate_signature_hash__all__expected_c)
{
    bc_data_chunk_t* tx_data = bc_create_data_chunk();
    bc_decode_base16(tx_data, "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970000000000ffffffff0000000000");
    bc_transaction_t* new_tx = bc_create_transaction();
    bc_transaction__from_data(new_tx, tx_data);

    bc_script_t* prevout_script = bc_create_script();
    BOOST_REQUIRE(bc_script__from_string(prevout_script, "dup hash160 [ 88350574280395ad2c3e2ee20e322073d94e5e40 ] equalverify checksig"));

    bc_endorsement_t* out = bc_create_data_chunk();
    const uint32_t input_index = 0;
    const uint8_t sighash_type = bc_signature_hash_algorithm__all;
    bc_hash_digest_t* sighash = bc_script__generate_signature_hash(
        new_tx, input_index, prevout_script, sighash_type);

    bc_string_t* result = bc_hash_digest__encode_base16(sighash);
    const auto expected = "f89572635651b2e4f89778350616989183c98d1a721c911324bf9f17a0cf5bf0";
    BOOST_REQUIRE(bc_string__equals_cstr(result, expected));
    bc_destroy_string(result);

    bc_destroy_hash_digest(sighash);
    bc_destroy_data_chunk(out);
    bc_destroy_script(prevout_script);
    bc_destroy_transaction(new_tx);
    bc_destroy_data_chunk(tx_data);
}

BOOST_AUTO_TEST_SUITE_END()
