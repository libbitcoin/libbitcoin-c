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

BOOST_AUTO_TEST_SUITE(block_tests_c)

BOOST_AUTO_TEST_CASE(from_data_fails_c)
{
    bc_data_chunk_t* data = bc_create_data_chunk();
    bc_data_chunk_resize(data, 10);
    bc_block_t* instance = bc_create_block();

    BOOST_REQUIRE_EQUAL(false, bc_block_from_data(instance, data));
    BOOST_REQUIRE_EQUAL(false, bc_block_is_valid(instance));

    bc_destroy_block(instance);
    bc_destroy_data_chunk(data);
}

BOOST_AUTO_TEST_CASE(block__genesis__mainnet__valid_structure_c)
{
    bc_block_t* genesis = bc_block_genesis_mainnet();
    BOOST_REQUIRE(bc_block_is_valid(genesis));

    bc_transaction_list_t* txs = bc_block_transactions(genesis);
    BOOST_REQUIRE_EQUAL(bc_transaction_list_size(txs), 1u);

    bc_hash_digest_t* root = bc_block_generate_merkle_root(txs);
    bc_destroy_transaction_list(txs);

    bc_header_t* header = bc_block_header(genesis);
    bc_hash_digest_t* header_merkle = bc_header_merkle(header);
    BOOST_REQUIRE(bc_hash_digest_equals(root, header_merkle));
    bc_destroy_hash_digest(header_merkle);
    bc_destroy_hash_digest(root);
    bc_destroy_header(header);

    bc_destroy_block(genesis);
}

BOOST_AUTO_TEST_CASE(block__genesis__testnet__valid_structure_c)
{
    bc_block_t* genesis = bc_block_genesis_testnet();
    BOOST_REQUIRE(bc_block_is_valid(genesis));

    bc_transaction_list_t* txs = bc_block_transactions(genesis);
    BOOST_REQUIRE_EQUAL(bc_transaction_list_size(txs), 1u);

    bc_hash_digest_t* root = bc_block_generate_merkle_root(txs);
    bc_destroy_transaction_list(txs);

    bc_header_t* header = bc_block_header(genesis);
    bc_hash_digest_t* header_merkle = bc_header_merkle(header);
    BOOST_REQUIRE(bc_hash_digest_equals(root, header_merkle));
    bc_destroy_hash_digest(header_merkle);
    bc_destroy_hash_digest(root);
    bc_destroy_header(header);

    bc_destroy_block(genesis);
}

BOOST_AUTO_TEST_CASE(roundtrip_mainnet_genesis_block_serialization_factory_data_chunk_c)
{
    bc_block_t* genesis = bc_block_genesis_mainnet();
    BOOST_REQUIRE_EQUAL(bc_block_serialized_size(genesis), 285u);

    bc_header_t* genesis_header = bc_block_header(genesis);
    BOOST_REQUIRE_EQUAL(
        bc_header_serialized_size_without_transaction_count(genesis_header),
        80u);

    // Save genesis block.
    bc_data_chunk_t* raw_block = bc_block_to_data(genesis);
    BOOST_REQUIRE_EQUAL(bc_data_chunk_size(raw_block), 285u);

    // Reload genesis block.
    bc_block_t* block = bc_block_factory_from_data(raw_block);
    bc_header_t* block_header = bc_block_header(block);

    BOOST_REQUIRE(bc_block_is_valid(block));

    BOOST_REQUIRE_EQUAL(
        bc_header_version(genesis_header),
        bc_header_version(block_header));

    bc_hash_digest_t* genesis_prevhash = bc_header_previous_block_hash(
        genesis_header);
    bc_hash_digest_t* block_prevhash = bc_header_previous_block_hash(
        block_header);
    BOOST_REQUIRE(bc_hash_digest_equals(genesis_prevhash, block_prevhash));
    bc_destroy_hash_digest(genesis_prevhash);
    bc_destroy_hash_digest(block_prevhash);

    bc_hash_digest_t* genesis_merkle = bc_header_previous_block_hash(
        genesis_header);
    bc_hash_digest_t* block_merkle = bc_header_previous_block_hash(
        block_header);
    BOOST_REQUIRE(bc_hash_digest_equals(genesis_merkle, block_merkle));
    bc_destroy_hash_digest(genesis_merkle);
    bc_destroy_hash_digest(block_merkle);

    BOOST_REQUIRE_EQUAL(
        bc_header_timestamp(genesis_header),
        bc_header_timestamp(block_header));

    BOOST_REQUIRE_EQUAL(
        bc_header_bits(genesis_header),
        bc_header_bits(block_header));

    BOOST_REQUIRE_EQUAL(
        bc_header_nonce(genesis_header),
        bc_header_nonce(block_header));

    BOOST_REQUIRE(bc_header_equals(genesis_header, block_header));

    bc_destroy_header(block_header);
    bc_destroy_block(block);
    bc_destroy_data_chunk(raw_block);
    bc_destroy_header(genesis_header);
    bc_destroy_block(genesis);
}

BOOST_AUTO_TEST_CASE(roundtrip_mainnet_genesis_block_serialization_factory_stream_c)
{
    const auto genesis = bc::chain::block::genesis_mainnet();
    BOOST_REQUIRE_EQUAL(genesis.serialized_size(), 285u);
    BOOST_REQUIRE_EQUAL(genesis.header.serialized_size(false), 80u);

    // Save genesis block.
    auto raw_block = genesis.to_data();
    BOOST_REQUIRE_EQUAL(std::distance(raw_block.begin(), raw_block.end()), 285u);
    BOOST_REQUIRE_EQUAL(raw_block.size(), 285u);

    // Reload genesis block.
    data_source stream(raw_block);
    const auto block = chain::block::factory_from_data(stream);

    BOOST_REQUIRE(block.is_valid());
    BOOST_REQUIRE(genesis.header.version == block.header.version);
    BOOST_REQUIRE(genesis.header.previous_block_hash == block.header.previous_block_hash);
    BOOST_REQUIRE(genesis.header.merkle == block.header.merkle);
    BOOST_REQUIRE(genesis.header.timestamp == block.header.timestamp);
    BOOST_REQUIRE(genesis.header.bits == block.header.bits);
    BOOST_REQUIRE(genesis.header.nonce == block.header.nonce);
    BOOST_REQUIRE(genesis.header == block.header);

    // Verify merkle root from transactions.
    const auto merkle = chain::block::generate_merkle_root(block.transactions);
    BOOST_REQUIRE(genesis.header.merkle == merkle);
}

BOOST_AUTO_TEST_CASE(roundtrip_mainnet_genesis_block_serialization_factory_reader_c)
{
    // Skipped stream test. Not implemented in C layer.
}

BOOST_AUTO_TEST_CASE(generate_merkle_root_block_with_zero_transactions_matches_null_hash_c)
{
    bc_transaction_list_t* empty_txs = bc_create_transaction_list();
    bc_hash_digest_t* empty_merkle = bc_block_generate_merkle_root(empty_txs);
    bc_hash_digest_t* null_hash = bc_null_hash();
    BOOST_REQUIRE(bc_hash_digest_equals(empty_merkle, null_hash));
    bc_destroy_hash_digest(empty_merkle);
    bc_destroy_hash_digest(null_hash);
    bc_destroy_transaction_list(empty_txs);
}

BOOST_AUTO_TEST_CASE(generate_merkle_root_block_with_multiple_transactions_matches_historic_data_c)
{
    // encodes the 100,000 block data.
    bc_block_t* block100k = bc_create_block();

    bc_header_t* header = bc_create_header();
    bc_header_set_version(header, 1u);

    bc_hash_digest_t* prevblkhash = bc_create_hash_digest();
    bc_decode_hash(prevblkhash,
        "00000000000ae3b3a73a5ffd5963e56376ad29364a75f006eeee2d053106117f");
    bc_header_set_previous_block_hash(header, prevblkhash);
    bc_destroy_hash_digest(prevblkhash);

    bc_hash_digest_t* merkle = bc_create_hash_digest();
    bc_decode_hash(merkle,
        "448211dcf4e9bf254a427e96fabce05f1744ae7b6deba8472171d9276899555f");
    bc_header_set_merkle(header, merkle);
    bc_destroy_hash_digest(merkle);

    bc_header_set_timestamp(header, 1287094230);
    bc_header_set_bits(header, 456101533);
    bc_header_set_nonce(header, 719871722);

    bc_transaction_list_t* txs = bc_create_transaction_list();
    bc_transaction_t* tx = NULL;
    bc_data_chunk_t* tx_data = NULL;

    tx = bc_create_transaction();
    tx_data = bc_create_data_chunk();
    bc_decode_base16(tx_data,
        "010000000100000000000000000000000000000000000000000000000000000000000"
        "00000ffffffff07049d8e2f1b0114ffffffff0100f2052a0100000043410437b36a72"
        "21bc977dce712728a954e3b5d88643ed5aef46660ddcfeeec132724cd950c1fdd008a"
        "d4a2dfd354d6af0ff155fc17c1ee9ef802062feb07ef1d065f0ac00000000");
    bc_transaction_from_data(tx, tx_data);
    bc_destroy_data_chunk(tx_data);
    bc_transaction_list_push_back(txs, &tx);
    // transaction_list has taken possession of the tx
    BOOST_REQUIRE(!tx);

    tx = bc_create_transaction();
    tx_data = bc_create_data_chunk();
    bc_decode_base16(tx_data,
        "0100000001260fd102fab456d6b169f6af4595965c03c2296ecf25bfd8790e7aa29b4"
        "04eff010000008c493046022100c56ad717e07229eb93ecef2a32a42ad041832ffe66"
        "bd2e1485dc6758073e40af022100e4ba0559a4cebbc7ccb5d14d1312634664bac46f3"
        "6ddd35761edaae20cefb16f01410417e418ba79380f462a60d8dd12dcef8ebfd7ab17"
        "41c5c907525a69a8743465f063c1d9182eea27746aeb9f1f52583040b1bc341b31ca0"
        "388139f2f323fd59f8effffffff0200ffb2081d0000001976a914fc7b44566256621a"
        "ffb1541cc9d59f08336d276b88ac80f0fa02000000001976a914617f0609c9fabb545"
        "105f7898f36b84ec583350d88ac00000000");
    bc_transaction_from_data(tx, tx_data);
    bc_destroy_data_chunk(tx_data);
    bc_transaction_list_push_back(txs, &tx);
    // transaction_list has taken possession of the tx
    BOOST_REQUIRE(!tx);

    tx = bc_create_transaction();
    tx_data = bc_create_data_chunk();
    bc_decode_base16(tx_data,
        "010000000122cd6da26eef232381b1a670aa08f4513e9f91a9fd129d912081a3dd138"
        "cb013010000008c4930460221009339c11b83f234b6c03ebbc4729c2633cbc8cbd0d1"
        "5774594bfedc45c4f99e2f022100ae0135094a7d651801539df110a028d65459d24bc"
        "752d7512bc8a9f78b4ab368014104a2e06c38dc72c4414564f190478e3b0d01260f09"
        "b8520b196c2f6ec3d06239861e49507f09b7568189efe8d327c3384a4e488f8c53448"
        "4835f8020b3669e5aebffffffff0200ac23fc060000001976a914b9a2c9700ff95195"
        "16b21af338d28d53ddf5349388ac00743ba40b0000001976a914eb675c349c474bec8"
        "dea2d79d12cff6f330ab48788ac00000000");
    bc_transaction_from_data(tx, tx_data);
    bc_destroy_data_chunk(tx_data);
    bc_transaction_list_push_back(txs, &tx);
    // transaction_list has taken possession of the tx
    BOOST_REQUIRE(!tx);

    bc_block_set_header(block100k, header);
    bc_block_set_transactions(block100k, txs);
    bc_destroy_header(header);
    bc_destroy_transaction_list(txs);
    BOOST_REQUIRE(bc_block_is_valid(block100k));

    header = bc_block_header(block100k);
    txs = bc_block_transactions(block100k);
    for (size_t i = 0; i < bc_transaction_list_size(txs); ++i)
    {
        tx = bc_transaction_list_at(txs, i);
        BOOST_REQUIRE(bc_transaction_is_valid(tx));

        bc_input_list_t* inputs = bc_transaction_inputs(tx);
        for (size_t j = 0; j < bc_input_list_size(inputs); ++j)
        {
            const bc_input_t* input = bc_input_list_const_at(inputs, j);
            BOOST_REQUIRE(bc_input_is_valid(input));

            bc_script_t* script = bc_input_script(input);
            BOOST_REQUIRE(bc_script_is_valid(script));
            bc_destroy_script(script);
        }
        bc_destroy_input_list(inputs);

        bc_output_list_t* outputs = bc_transaction_outputs(tx);
        for (size_t j = 0; j < bc_output_list_size(outputs); ++j)
        {
            const bc_output_t* output = bc_output_list_const_at(outputs, j);
            BOOST_REQUIRE(bc_output_is_valid(output));

            bc_script_t* script = bc_output_script(output);
            BOOST_REQUIRE(bc_script_is_valid(script));
            bc_destroy_script(script);
        }
        bc_destroy_output_list(outputs);
    }

    bc_hash_digest_t* header_merkle = bc_header_merkle(header);
    bc_hash_digest_t* txs_merkle = bc_block_generate_merkle_root(txs);
    BOOST_REQUIRE(bc_hash_digest_equals(header_merkle, txs_merkle));
    bc_destroy_hash_digest(header_merkle);
    bc_destroy_hash_digest(txs_merkle);

    bc_destroy_header(header);
    bc_destroy_transaction_list(txs);

    bc_destroy_block(block100k);
}

BOOST_AUTO_TEST_SUITE_END()

