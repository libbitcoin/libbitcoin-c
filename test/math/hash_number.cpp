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

using namespace libbitcoin;

BOOST_AUTO_TEST_SUITE(hash_number_tests_c)

BOOST_AUTO_TEST_CASE(hash_number__simple__test_c)
{
    bc_hash_number_t* target = bc_create_hash_number();
    uint32_t bits = 486604799;
    bc_hash_number__set_compact(target, bits);
    bc_hash_digest_t* block_hash = bc_hash_literal(
        &"00000000b873e79784647a6c82962c70d228557d24a747ea4d1b8bbe878e1206");

    bc_hash_number_t* value = bc_create_hash_number_Value(0);
    BOOST_REQUIRE(!bc_hash_number__less_than_or_equals(target, value));
    bc_destroy_hash_number(value);

    bc_hash_number_t* maximum = bc_create_hash_number();
    BOOST_REQUIRE(bc_hash_number__set_compact(maximum, bc_max_work_bits()));
    BOOST_REQUIRE(!bc_hash_number__greater_than(target, maximum));
    bc_destroy_hash_number(maximum);

    bc_hash_number_t* our_value = bc_create_hash_number_Hash(block_hash);
    BOOST_REQUIRE(!bc_hash_number__greater_than(our_value, target));
    bc_destroy_hash_number(our_value);

    bc_destroy_hash_digest(block_hash);
    bc_destroy_hash_number(target);
}

//BOOST_AUTO_TEST_CASE(hash_number__work__test)
//{
//    hash_number orphan_work = 0;
//    BOOST_REQUIRE_EQUAL(encode_base16(orphan_work.hash()), encode_base16(null_hash));
//    orphan_work += block_work(486604799);
//    BOOST_REQUIRE_EQUAL(encode_base16(orphan_work.hash()),
//        "0100010001000000000000000000000000000000000000000000000000000000");
//    hash_number main_work = 0;
//    BOOST_REQUIRE(!(orphan_work <= main_work));
//}

BOOST_AUTO_TEST_SUITE_END()

