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

BOOST_AUTO_TEST_SUITE(base_10_tests)

#define TEST_AMOUNT(NAME, EXPECTED, AMOUNT) \
BOOST_AUTO_TEST_CASE(parse_amount_##NAME##_test) \
{ \
    uint64_t result, expected = EXPECTED; \
    BOOST_REQUIRE(bc_decode_base10(&result, AMOUNT, 0)); \
    BOOST_REQUIRE_EQUAL(result, expected); \
}

#define TEST_AMOUNT_PLACES(NAME, EXPECTED, AMOUNT, DECIMAL_PLACES) \
BOOST_AUTO_TEST_CASE(parse_amount_##NAME##_test) \
{ \
    uint64_t result, expected = EXPECTED; \
    BOOST_REQUIRE(bc_decode_base10(&result, AMOUNT, DECIMAL_PLACES)); \
    BOOST_REQUIRE_EQUAL(result, expected); \
}

#define TEST_AMOUNT_NONSTRICT(NAME, EXPECTED, AMOUNT, DECIMAL_PLACES) \
BOOST_AUTO_TEST_CASE(parse_amount_##NAME##_test) \
{ \
    uint64_t result, expected = EXPECTED; \
    BOOST_REQUIRE(bc_decode_base10_nonstrict(&result, AMOUNT, DECIMAL_PLACES)); \
    BOOST_REQUIRE_EQUAL(result, expected); \
}

#define TEST_FORMAT(NAME, EXPECTED, ...) \
BOOST_AUTO_TEST_CASE(format_amount_##NAME##_test) \
{ \
    bc_string_t* result = bc_encode_base10(__VA_ARGS__); \
    BOOST_REQUIRE(bc_string_equals_cstr(result, EXPECTED)); \
    bc_destroy_string(result); \
}

// Limits:
TEST_AMOUNT(zero, 0, "0")
TEST_AMOUNT(max_uint64, bc_max_uint64(), "18446744073709551615")

// Max money:
TEST_AMOUNT_PLACES(max_money, bc_max_money(), "20999999.9769", bc_btc_decimal_places())
TEST_AMOUNT_PLACES(overflow_max_money, bc_max_money() + 1, "20999999.97690001", bc_btc_decimal_places())

// Decimal points:
TEST_AMOUNT_PLACES(pure_integer, 42, "42.0", 0)
TEST_AMOUNT_PLACES(no_decimal, 1000000, "10", bc_mbtc_decimal_places())
TEST_AMOUNT_PLACES(normal_decimal, 420000, "4.2", bc_mbtc_decimal_places())
TEST_AMOUNT_PLACES(leading_decimal, 50000, ".5", bc_mbtc_decimal_places())
TEST_AMOUNT_PLACES(trailing_decial, 500000, "5.", bc_mbtc_decimal_places())
TEST_AMOUNT_PLACES(extra_zeros, 1002000, "010.020", bc_mbtc_decimal_places())
TEST_AMOUNT_PLACES(harmless_zeros, 1, "0.0000100", bc_mbtc_decimal_places())
TEST_AMOUNT(decimal_point_only, 0, ".")

// Rounding:
TEST_AMOUNT_NONSTRICT(pure_integer_rounding, 1, ".1", 0)
TEST_AMOUNT_NONSTRICT(rounding, 11, "0.101", bc_ubtc_decimal_places())
TEST_AMOUNT_NONSTRICT(rounding_carry, 1000, "9.991", bc_ubtc_decimal_places())
TEST_AMOUNT(zero_past_max, max_uint64, "18446744073709551615.0")

// Format errors:
BOOST_AUTO_TEST_CASE(parse_amount_lexical_cast_fail_test)
{
    uint64_t result;
    BOOST_REQUIRE(!bc_decode_base10(&result, "0.-1", 0));
}
BOOST_AUTO_TEST_CASE(parse_amount_extra_decimal_test)
{
    uint64_t result;
    BOOST_REQUIRE(!bc_decode_base10(&result, "0.0.0", 0));
}
BOOST_AUTO_TEST_CASE(parse_amount_bad_characters_test)
{
    uint64_t result;
    BOOST_REQUIRE(!bc_decode_base10(&result, "0x0ff", 0));
}

// Numeric errors:
BOOST_AUTO_TEST_CASE(parse_amount_overflow_test)
{
    uint64_t result;
    BOOST_REQUIRE(!bc_decode_base10(&result, "18446744073709551616", 0));
}
BOOST_AUTO_TEST_CASE(parse_amount_rounding_overflow_test)
{
    uint64_t result;
    BOOST_REQUIRE(!bc_decode_base10_nonstrict(
        &result, "18446744073709551615.1", 0));
}
BOOST_AUTO_TEST_CASE(parse_amount_fractional_amount_test)
{
    uint64_t result;
    BOOST_REQUIRE(!bc_decode_base10(
        &result, "0.999999999", bc_btc_decimal_places()));
}

// Limits:
TEST_FORMAT(zero, "0", 0, 0)
TEST_FORMAT(max_uint64, "18446744073709551615", bc_max_uint64(), 0)

// Max money:
TEST_FORMAT(max_money, "20999999.9769", bc_max_money(), bc_btc_decimal_places())
TEST_FORMAT(overflow_max_money, "20999999.97690001", bc_max_money() + 1, bc_btc_decimal_places())

// Decimal points:
TEST_FORMAT(pure_integer, "42", 42, 0)
TEST_FORMAT(no_decimal, "10", 1000000, bc_mbtc_decimal_places())
TEST_FORMAT(normal_decimal, "4.2", 420000, bc_mbtc_decimal_places())
TEST_FORMAT(leading_zero, "0.42", 42000, bc_mbtc_decimal_places())
TEST_FORMAT(internal_leading_zero, "0.042", 4200, bc_mbtc_decimal_places())

BOOST_AUTO_TEST_SUITE_END()

