/**
 * Copyright (c) 2011-2015 libwallet developers (see AUTHORS)
 *
 * This file is part of libwallet.
 *
 * libwallet is free software: you can redistribute it and/or modify
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
#include <boost/optional.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/bitcoin.h>

using namespace bc;
using namespace bc::wallet;

BOOST_AUTO_TEST_SUITE(bitcoin_uri_tests_c)

// Constructors
// ----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(bitcoin_uri__construct__uninitialized__false_c)
{
    bc_bitcoin_uri_t* uri = bc_create_bitcoin_uri_default();
    BOOST_REQUIRE(!bc_bitcoin_uri_is_initialized(uri));
    bc_destroy_bitcoin_uri(uri);
}

BOOST_AUTO_TEST_CASE(bitcoin_uri__construct__initialized__true_c)
{
    bc_bitcoin_uri_t* uri = bc_create_bitcoin_uri("bitcoin:");
    BOOST_REQUIRE(bc_bitcoin_uri_is_initialized(uri));
    bc_destroy_bitcoin_uri(uri);
}

BOOST_AUTO_TEST_CASE(bitcoin_uri__construct__scheme_mixed_case__normalized_c)
{
    bc_bitcoin_uri_t* uri = bc_create_bitcoin_uri("bitcOin:");
    bc_string_t* encoded = bc_bitcoin_uri_encoded(uri);
    bc_destroy_bitcoin_uri(uri);
    BOOST_REQUIRE(bc_string_equals_cstr(encoded, "bitcoin:"));
}

BOOST_AUTO_TEST_CASE(bitcoin_uri__construct__invalid_scheme__false_c)
{
    bc_bitcoin_uri_t* uri = bc_create_bitcoin_uri("fedcoin:");
    BOOST_REQUIRE(!bc_bitcoin_uri_is_initialized(uri));
    bc_destroy_bitcoin_uri(uri);
}

BOOST_AUTO_TEST_CASE(bitcoin_uri__construct__payment_address_only__false_c)
{
    bc_bitcoin_uri_t* uri = bc_create_bitcoin_uri(
        "113Pfw4sFqN1T5kXUnKbqZHMJHN9oyjtgD");
    BOOST_REQUIRE(!bc_bitcoin_uri_is_initialized(uri));
    bc_destroy_bitcoin_uri(uri);
}

BOOST_AUTO_TEST_CASE(bitcoin_uri__construct__stealth_address_only__false_c)
{
    bc_bitcoin_uri_t* uri = bc_create_bitcoin_uri(
        "hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7evZkira2i");
    BOOST_REQUIRE(!bc_bitcoin_uri_is_initialized(uri));
    bc_destroy_bitcoin_uri(uri);
}

BOOST_AUTO_TEST_CASE(bitcoin_uri__construct__fragment__false_c)
{
    bc_bitcoin_uri_t* uri = bc_create_bitcoin_uri("bitcoin:#satoshi");
    BOOST_REQUIRE(!bc_bitcoin_uri_is_initialized(uri));
    bc_destroy_bitcoin_uri(uri);
}

BOOST_AUTO_TEST_CASE(bitcoin_uri__construct__strict__test_c)
{
    bc_bitcoin_uri_t* uri = bc_create_bitcoin_uri(
        "bitcoin:?label=Some テスト");
    BOOST_REQUIRE(!bc_bitcoin_uri_is_initialized(uri));
    bc_destroy_bitcoin_uri(uri);
}

BOOST_AUTO_TEST_CASE(bitcoin_uri__construct__not_strict__test_c)
{
    bc_bitcoin_uri_t* uri = bc_create_bitcoin_uri_nonstrict(
        "bitcoin:?label=Some テスト");
    BOOST_REQUIRE(bc_bitcoin_uri_is_initialized(uri));
    bc_destroy_bitcoin_uri(uri);
}

// Setters
// ----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(bitcoin_uri__set_path__payment_address__expected_encoding_c)
{
    const auto expected_payment = "113Pfw4sFqN1T5kXUnKbqZHMJHN9oyjtgD";
    const auto expected_uri = std::string("bitcoin:") + expected_payment;

    bc_bitcoin_uri_t* uri = bc_create_bitcoin_uri_default();
    bc_bitcoin_uri_set_path(uri, expected_payment);

    bc_string_t* encoded = bc_bitcoin_uri_encoded(uri);
    BOOST_REQUIRE(bc_string_equals_cstr(encoded, expected_uri.data()));
    bc_destroy_string(encoded);

    bc_destroy_bitcoin_uri(uri);
}

BOOST_AUTO_TEST_CASE(bitcoin_uri__set_path__stealth_address__expected_encoding_c)
{
    const auto expected_payment = "hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7evZkira2i";
    const auto expected_uri = std::string("bitcoin:") + expected_payment;

    bc_bitcoin_uri_t* uri = bc_create_bitcoin_uri_default();
    bc_bitcoin_uri_set_path(uri, expected_payment);

    bc_string_t* encoded = bc_bitcoin_uri_encoded(uri);
    BOOST_REQUIRE(bc_string_equals_cstr(encoded, expected_uri.data()));
    bc_destroy_string(encoded);

    bc_destroy_bitcoin_uri(uri);
}

BOOST_AUTO_TEST_CASE(bitcoin_uri__set_path__reset_stealth_after_payment__expected_encoding_c)
{
    // TODO: payment and stealth for bitcoin uri class
    const auto expected_stealth = "hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7evZkira2i";
    const auto expected_uri = std::string("bitcoin:") + expected_stealth;

    bitcoin_uri uri;
    const auto payment = payment_address("113Pfw4sFqN1T5kXUnKbqZHMJHN9oyjtgD");
    BOOST_REQUIRE(payment);
    uri.set_address(payment);
    uri.set_address(stealth_address(expected_stealth));
    BOOST_REQUIRE_EQUAL(uri.encoded(), expected_uri);
}

BOOST_AUTO_TEST_CASE(bitcoin_uri__set_path__reset_payment_after_stealth__expected_encoding_c)
{
    // TODO: payment and stealth for bitcoin uri class
    const auto expected_payment = "113Pfw4sFqN1T5kXUnKbqZHMJHN9oyjtgD";
    const auto expected_uri = std::string("bitcoin:") + expected_payment;

    bitcoin_uri uri;
    const auto stealth = stealth_address("hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7evZkira2i");
    BOOST_REQUIRE(stealth);
    uri.set_address(stealth);
    uri.set_address(payment_address(expected_payment));
    BOOST_REQUIRE_EQUAL(uri.encoded(), expected_uri);
}

BOOST_AUTO_TEST_CASE(bitcoin_uri__set_path__reset_path__false_c)
{
    // TODO: payment and stealth for bitcoin uri class
    const auto expected_payment = "113Pfw4sFqN1T5kXUnKbqZHMJHN9oyjtgD";
    const auto expected_uri = std::string("bitcoin:") + expected_payment;

    bitcoin_uri uri;
    uri.set_address(stealth_address("hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7evZkira2i"));

    // The set_path will not reset a path. This is necessary to catch failures in non-strict parsing.
    BOOST_REQUIRE(!uri.set_path(expected_payment));
}

BOOST_AUTO_TEST_CASE(bitcoin_uri__set_amount__reset_amount__latter_amount_c)
{
    bc_bitcoin_uri_t* uri = bc_create_bitcoin_uri_default();
    bc_bitcoin_uri_set_amount(uri, 10000000000);
    bc_bitcoin_uri_set_amount(uri, 120000);

    bc_string_t* encoded = bc_bitcoin_uri_encoded(uri);
    BOOST_REQUIRE(bc_string_equals_cstr(encoded, "bitcoin:?amount=0.0012"));
    bc_destroy_string(encoded);

    bc_destroy_bitcoin_uri(uri);
}

BOOST_AUTO_TEST_CASE(bitcoin_uri__all_setters__complex_uri__expected_encoding_c)
{
    bc_bitcoin_uri_t* uri = bc_create_bitcoin_uri_default();
    bc_bitcoin_uri_set_path(uri, "113Pfw4sFqN1T5kXUnKbqZHMJHN9oyjtgD");
    bc_bitcoin_uri_set_amount(uri, 120000);
    bc_bitcoin_uri_set_label(uri, "&=\n");
    bc_bitcoin_uri_set_message(uri, "hello bitcoin");
    bc_bitcoin_uri_set_r(uri, "http://example.com?purchase=shoes&user=bob");

    bc_string_t* encoded = bc_bitcoin_uri_encoded(uri);
    BOOST_REQUIRE(bc_string_equals_cstr(encoded,
        "bitcoin:113Pfw4sFqN1T5kXUnKbqZHMJHN9oyjtgD?"
        "amount=0.0012&"
        "label=%26%3D%0A&"
        "message=hello%20bitcoin&"
        "r=http://example.com?purchase%3Dshoes%26user%3Dbob"));
    bc_destroy_string(encoded);

    bc_destroy_bitcoin_uri(uri);
}

BOOST_AUTO_TEST_CASE(bitcoin_uri__set_parameter__amount_denormalized__normalized_c)
{
    bc_bitcoin_uri_t* uri = bc_create_bitcoin_uri_default();
    BOOST_REQUIRE(bc_bitcoin_uri_set_parameter(uri, "amount", ".0012"));

    bc_string_t* encoded = bc_bitcoin_uri_encoded(uri);
    BOOST_REQUIRE(bc_string_equals_cstr(encoded, "bitcoin:?amount=0.0012"));
    bc_destroy_string(encoded);

    bc_destroy_bitcoin_uri(uri);
}

// Getters
// ----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(bitcoin_uri__amount__set__expected_c)
{
    bc_bitcoin_uri_t* uri = bc_create_bitcoin_uri("bitcoin:?amount=0.0012");
    BOOST_REQUIRE_EQUAL(bc_bitcoin_uri_amount(uri), 120000u);
    bc_destroy_bitcoin_uri(uri);
}

BOOST_AUTO_TEST_CASE(bitcoin_uri__label__escaped__expected_c)
{
    bc_bitcoin_uri_t* uri = bc_create_bitcoin_uri("bitcoin:?label=%26%3D%0A");
    bc_string_t* label = bc_bitcoin_uri_label(uri);
    BOOST_REQUIRE(bc_string_equals_cstr(label, "&=\n"));
    bc_destroy_string(label);
    bc_destroy_bitcoin_uri(uri);
}

BOOST_AUTO_TEST_CASE(bitcoin_uri__message__escaped__expected_c)
{
    bc_bitcoin_uri_t* uri = bc_create_bitcoin_uri("bitcoin:?message=hello%20bitcoin");
    bc_string_t* message = bc_bitcoin_uri_message(uri);
    BOOST_REQUIRE(bc_string_equals_cstr(message, "hello bitcoin"));
    bc_destroy_string(message);
    bc_destroy_bitcoin_uri(uri);
}

BOOST_AUTO_TEST_CASE(bitcoin_uri__r__escaped__expected_c)
{
    bc_bitcoin_uri_t* uri = bc_create_bitcoin_uri("bitcoin:?r=http://example.com?purchase%3Dshoes%26user%3Dbob");
    bc_string_t* r = bc_bitcoin_uri_r(uri);
    BOOST_REQUIRE(bc_string_equals_cstr(r,
        "http://example.com?purchase=shoes&user=bob"));
    bc_destroy_string(r);
    bc_destroy_bitcoin_uri(uri);
}

BOOST_AUTO_TEST_CASE(bitcoin_uri__payment__valid__expected_c)
{
    const auto expected_payment = "113Pfw4sFqN1T5kXUnKbqZHMJHN9oyjtgD";
    const auto expected_uri = std::string("bitcoin:") + expected_payment;
    bc_bitcoin_uri_t* uri = bc_create_bitcoin_uri(expected_uri.data());
    bc_payment_address_t* payment = bc_bitcoin_uri_payment(uri);
    bc_string_t* encoded = bc_payment_address_encoded(payment);
    BOOST_REQUIRE(bc_string_equals_cstr(encoded, expected_payment));
    bc_destroy_string(encoded);
    bc_destroy_payment_address(payment);
    bc_destroy_bitcoin_uri(uri);
}

BOOST_AUTO_TEST_CASE(bitcoin_uri__stealth__valid__expected_c)
{
    // TODO: no stealth yet
    const auto expected_stealth = "hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7evZkira2i";
    const auto expected_uri = std::string("bitcoin:") + expected_stealth;
    BOOST_REQUIRE_EQUAL(bitcoin_uri(expected_uri).stealth().encoded(), expected_stealth);
}

BOOST_AUTO_TEST_CASE(bitcoin_uri__address__payment__expected_c)
{
    const auto expected_payment = "113Pfw4sFqN1T5kXUnKbqZHMJHN9oyjtgD";
    const auto expected_uri = std::string("bitcoin:") + expected_payment;

    bc_bitcoin_uri_t* uri = bc_create_bitcoin_uri(expected_uri.data());
    bc_string_t* address = bc_bitcoin_uri_address(uri);
    BOOST_REQUIRE(bc_string_equals_cstr(address, expected_payment));
    bc_destroy_string(address);
    bc_destroy_bitcoin_uri(uri);
}

BOOST_AUTO_TEST_CASE(bitcoin_uri__address__stealth__expected_c)
{
    const auto expected_stealth = "hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7evZkira2i";
    const auto expected_uri = std::string("bitcoin:") + expected_stealth;

    bc_bitcoin_uri_t* uri = bc_create_bitcoin_uri(expected_uri.data());
    bc_string_t* address = bc_bitcoin_uri_address(uri);
    BOOST_REQUIRE(bc_string_equals_cstr(address, expected_stealth));
    bc_destroy_string(address);
    bc_destroy_bitcoin_uri(uri);
}

BOOST_AUTO_TEST_CASE(bitcoin_uri__parameter_amount__denormalized__normalized_c)
{
    bc_bitcoin_uri_t* uri = bc_create_bitcoin_uri("bitcoin:?amount=.0012");
    bc_string_t* value = bc_bitcoin_uri_parameter(uri, "amount");
    BOOST_REQUIRE(bc_string_equals_cstr(value, "0.0012"));
    bc_destroy_string(value);
    bc_destroy_bitcoin_uri(uri);
}

BOOST_AUTO_TEST_CASE(bitcoin_uri__parameters_all__complex_uri__expected_c)
{
    bc_bitcoin_uri_t* uri = bc_create_bitcoin_uri(
        "bitcoin:113Pfw4sFqN1T5kXUnKbqZHMJHN9oyjtgD?"
        "amount=0.0012&"
        "label=%26%3D%0A&"
        "message=hello%20bitcoin&"
        "r=http://example.com?purchase%3Dshoes%26user%3Dbob");

    bc_string_t* address = bc_bitcoin_uri_address(uri);
    BOOST_REQUIRE(bc_string_equals_cstr(address,
        "113Pfw4sFqN1T5kXUnKbqZHMJHN9oyjtgD"));
    bc_destroy_string(address);

    bc_string_t* value = NULL;

    value = bc_bitcoin_uri_parameter(uri, "amount");
    BOOST_REQUIRE(bc_string_equals_cstr(value, "0.0012"));
    bc_destroy_string(value);

    value = bc_bitcoin_uri_parameter(uri, "label");
    BOOST_REQUIRE(bc_string_equals_cstr(value, "&=\n"));
    bc_destroy_string(value);

    value = bc_bitcoin_uri_parameter(uri, "message");
    BOOST_REQUIRE(bc_string_equals_cstr(value, "hello bitcoin"));
    bc_destroy_string(value);

    value = bc_bitcoin_uri_parameter(uri, "r");
    BOOST_REQUIRE(bc_string_equals_cstr(value, "http://example.com?purchase=shoes&user=bob"));
    bc_destroy_string(value);

    bc_destroy_bitcoin_uri(uri);
}

BOOST_AUTO_TEST_SUITE_END()

