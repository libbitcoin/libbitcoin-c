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
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/bitcoin.h>

using namespace bc;
using namespace bc::wallet;

BOOST_AUTO_TEST_SUITE(hd_private_tests_c)

// TODO: test altchain

#define SHORT_SEED "000102030405060708090a0b0c0d0e0f"
#define LONG_SEED "fffcf9f6f3f0edeae7e4e1dedbd8d5d2cfccc9c6c3c0bdbab7b4b1aeaba8a5a29f9c999693908d8a8784817e7b7875726f6c696663605d5a5754514e4b484542"

BOOST_AUTO_TEST_CASE(hd_private__encoded__round_trip__expected_c)
{
    static const auto encoded = "xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi";
    bc_hd_private_t* key = bc_create_hd_private_String(encoded);
    bc_string_t* reencoded = bc_hd_private_encoded(key);
    BOOST_REQUIRE(bc_string_equals_cstr(reencoded, encoded));
    bc_destroy_string(reencoded);
    bc_destroy_hd_private(key);
}

BOOST_AUTO_TEST_CASE(hd_private__derive_private__short_seed__expected_c)
{
    bc_data_chunk_t* seed = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(seed, SHORT_SEED));

    bc_hd_private_t* m = bc_create_hd_private_Seed(
        seed, bc_hd_private_mainnet());
    bc_hd_private_t* m0h = bc_hd_private_derive_private(
        m, bc_hd_first_hardened_key());
    bc_hd_private_t* m0h1 = bc_hd_private_derive_private(
        m0h, 1);
    bc_hd_private_t* m0h12h = bc_hd_private_derive_private(
        m0h1, 2 + bc_hd_first_hardened_key());
    bc_hd_private_t* m0h12h2 = bc_hd_private_derive_private(
        m0h12h, 2);
    bc_hd_private_t* m0h12h2x = bc_hd_private_derive_private(
        m0h12h2, 1000000000);

    bc_string_t* m_encoded = bc_hd_private_encoded(m);
    BOOST_REQUIRE(bc_string_equals_cstr(m_encoded,
        "xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi"));

    bc_string_t* m0h_encoded = bc_hd_private_encoded(m0h);
    BOOST_REQUIRE(bc_string_equals_cstr(m0h_encoded,
        "xprv9uHRZZhk6KAJC1avXpDAp4MDc3sQKNxDiPvvkX8Br5ngLNv1TxvUxt4cV1rGL5hj6KCesnDYUhd7oWgT11eZG7XnxHrnYeSvkzY7d2bhkJ7"));

    bc_string_t* m0h1_encoded = bc_hd_private_encoded(m0h1);
    BOOST_REQUIRE(bc_string_equals_cstr(m0h1_encoded,
        "xprv9wTYmMFdV23N2TdNG573QoEsfRrWKQgWeibmLntzniatZvR9BmLnvSxqu53Kw1UmYPxLgboyZQaXwTCg8MSY3H2EU4pWcQDnRnrVA1xe8fs"));

    bc_string_t* m0h12h_encoded = bc_hd_private_encoded(m0h12h);
    BOOST_REQUIRE(bc_string_equals_cstr(m0h12h_encoded,
        "xprv9z4pot5VBttmtdRTWfWQmoH1taj2axGVzFqSb8C9xaxKymcFzXBDptWmT7FwuEzG3ryjH4ktypQSAewRiNMjANTtpgP4mLTj34bhnZX7UiM"));

    bc_string_t* m0h12h2_encoded = bc_hd_private_encoded(m0h12h2);
    BOOST_REQUIRE(bc_string_equals_cstr(m0h12h2_encoded,
        "xprvA2JDeKCSNNZky6uBCviVfJSKyQ1mDYahRjijr5idH2WwLsEd4Hsb2Tyh8RfQMuPh7f7RtyzTtdrbdqqsunu5Mm3wDvUAKRHSC34sJ7in334"));

    bc_string_t* m0h12h2x_encoded = bc_hd_private_encoded(m0h12h2x);
    BOOST_REQUIRE(bc_string_equals_cstr(m0h12h2x_encoded,
        "xprvA41z7zogVVwxVSgdKUHDy1SKmdb533PjDz7J6N6mV6uS3ze1ai8FHa8kmHScGpWmj4WggLyQjgPie1rFSruoUihUZREPSL39UNdE3BBDu76"));

    bc_destroy_string(m_encoded);
    bc_destroy_string(m0h_encoded);
    bc_destroy_string(m0h1_encoded);
    bc_destroy_string(m0h12h_encoded);
    bc_destroy_string(m0h12h2_encoded);
    bc_destroy_string(m0h12h2x_encoded);

    bc_destroy_hd_private(m);
    bc_destroy_hd_private(m0h);
    bc_destroy_hd_private(m0h1);
    bc_destroy_hd_private(m0h12h);
    bc_destroy_hd_private(m0h12h2);
    bc_destroy_hd_private(m0h12h2x);

    bc_destroy_data_chunk(seed);
}

BOOST_AUTO_TEST_CASE(hd_private__derive_public__short_seed__expected_c)
{
    bc_data_chunk_t* seed = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(seed, SHORT_SEED));

    bc_hd_private_t* m = bc_create_hd_private_Seed(
        seed, bc_hd_private_mainnet());
    bc_hd_private_t* m0h = bc_hd_private_derive_private(
        m, bc_hd_first_hardened_key());
    bc_hd_private_t* m0h1 = bc_hd_private_derive_private(
        m0h, 1);
    bc_hd_private_t* m0h12h = bc_hd_private_derive_private(
        m0h1, 2 + bc_hd_first_hardened_key());
    bc_hd_private_t* m0h12h2 = bc_hd_private_derive_private(
        m0h12h, 2);
    bc_hd_private_t* m0h12h2x = bc_hd_private_derive_private(
        m0h12h2, 1000000000);

    bc_hd_public_t* m_pub = bc_hd_private_to_public(m);
    bc_hd_public_t* m0h_pub = bc_hd_private_derive_public(
        m, bc_hd_first_hardened_key());
    bc_hd_public_t* m0h1_pub = bc_hd_private_derive_public(
        m0h, 1);
    bc_hd_public_t* m0h12h_pub = bc_hd_private_derive_public(
        m0h1, 2 + bc_hd_first_hardened_key());
    bc_hd_public_t* m0h12h2_pub = bc_hd_private_derive_public(
        m0h12h, 2);
    bc_hd_public_t* m0h12h2x_pub = bc_hd_private_derive_public(
        m0h12h2, 1000000000);

    bc_string_t* m_pub_encoded = bc_hd_public_encoded(m_pub);
    BOOST_REQUIRE(bc_string_equals_cstr(m_pub_encoded,
        "xpub661MyMwAqRbcFtXgS5sYJABqqG9YLmC4Q1Rdap9gSE8NqtwybGhePY2gZ29ESFjqJoCu1Rupje8YtGqsefD265TMg7usUDFdp6W1EGMcet8"));

    bc_string_t* m0h_pub_encoded = bc_hd_public_encoded(m0h_pub);
    BOOST_REQUIRE(bc_string_equals_cstr(m0h_pub_encoded,
        "xpub68Gmy5EdvgibQVfPdqkBBCHxA5htiqg55crXYuXoQRKfDBFA1WEjWgP6LHhwBZeNK1VTsfTFUHCdrfp1bgwQ9xv5ski8PX9rL2dZXvgGDnw"));

    bc_string_t* m0h1_pub_encoded = bc_hd_public_encoded(m0h1_pub);
    BOOST_REQUIRE(bc_string_equals_cstr(m0h1_pub_encoded,
        "xpub6ASuArnXKPbfEwhqN6e3mwBcDTgzisQN1wXN9BJcM47sSikHjJf3UFHKkNAWbWMiGj7Wf5uMash7SyYq527Hqck2AxYysAA7xmALppuCkwQ"));

    bc_string_t* m0h12h_pub_encoded = bc_hd_public_encoded(m0h12h_pub);
    BOOST_REQUIRE(bc_string_equals_cstr(m0h12h_pub_encoded,
        "xpub6D4BDPcP2GT577Vvch3R8wDkScZWzQzMMUm3PWbmWvVJrZwQY4VUNgqFJPMM3No2dFDFGTsxxpG5uJh7n7epu4trkrX7x7DogT5Uv6fcLW5"));

    bc_string_t* m0h12h2_pub_encoded = bc_hd_public_encoded(m0h12h2_pub);
    BOOST_REQUIRE(bc_string_equals_cstr(m0h12h2_pub_encoded,
        "xpub6FHa3pjLCk84BayeJxFW2SP4XRrFd1JYnxeLeU8EqN3vDfZmbqBqaGJAyiLjTAwm6ZLRQUMv1ZACTj37sR62cfN7fe5JnJ7dh8zL4fiyLHV"));

    bc_string_t* m0h12h2x_pub_encoded = bc_hd_public_encoded(m0h12h2x_pub);
    BOOST_REQUIRE(bc_string_equals_cstr(m0h12h2x_pub_encoded,
        "xpub6H1LXWLaKsWFhvm6RVpEL9P4KfRZSW7abD2ttkWP3SSQvnyA8FSVqNTEcYFgJS2UaFcxupHiYkro49S8yGasTvXEYBVPamhGW6cFJodrTHy"));

    bc_destroy_string(m_pub_encoded);
    bc_destroy_string(m0h_pub_encoded);
    bc_destroy_string(m0h1_pub_encoded);
    bc_destroy_string(m0h12h_pub_encoded);
    bc_destroy_string(m0h12h2_pub_encoded);
    bc_destroy_string(m0h12h2x_pub_encoded);

    bc_destroy_hd_private(m);
    bc_destroy_hd_private(m0h);
    bc_destroy_hd_private(m0h1);
    bc_destroy_hd_private(m0h12h);
    bc_destroy_hd_private(m0h12h2);
    bc_destroy_hd_private(m0h12h2x);

    bc_destroy_hd_public(m_pub);
    bc_destroy_hd_public(m0h_pub);
    bc_destroy_hd_public(m0h1_pub);
    bc_destroy_hd_public(m0h12h_pub);
    bc_destroy_hd_public(m0h12h2_pub);
    bc_destroy_hd_public(m0h12h2x_pub);

    bc_destroy_data_chunk(seed);
}

BOOST_AUTO_TEST_CASE(hd_private__derive_private__long_seed__expected_c)
{
    bc_data_chunk_t* seed = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(seed, LONG_SEED));

    bc_hd_private_t* m = bc_create_hd_private_Seed(
        seed, bc_hd_private_mainnet());
    bc_hd_private_t* m0 = bc_hd_private_derive_private(
        m, 0);
    bc_hd_private_t* m0xH = bc_hd_private_derive_private(
        m0, 2147483647 + bc_hd_first_hardened_key());
    bc_hd_private_t* m0xH1 = bc_hd_private_derive_private(
        m0xH, 1);
    bc_hd_private_t* m0xH1yH = bc_hd_private_derive_private(
        m0xH1, 2147483646 + bc_hd_first_hardened_key());
    bc_hd_private_t* m0xH1yH2 = bc_hd_private_derive_private(
        m0xH1yH, 2);

    bc_string_t* m_encoded = bc_hd_private_encoded(m);
    BOOST_REQUIRE(bc_string_equals_cstr(m_encoded,
        "xprv9s21ZrQH143K31xYSDQpPDxsXRTUcvj2iNHm5NUtrGiGG5e2DtALGdso3pGz6ssrdK4PFmM8NSpSBHNqPqm55Qn3LqFtT2emdEXVYsCzC2U"));

    bc_string_t* m0_encoded = bc_hd_private_encoded(m0);
    BOOST_REQUIRE(bc_string_equals_cstr(m0_encoded,
        "xprv9vHkqa6EV4sPZHYqZznhT2NPtPCjKuDKGY38FBWLvgaDx45zo9WQRUT3dKYnjwih2yJD9mkrocEZXo1ex8G81dwSM1fwqWpWkeS3v86pgKt"));

    bc_string_t* m0xH_encoded = bc_hd_private_encoded(m0xH);
    BOOST_REQUIRE(bc_string_equals_cstr(m0xH_encoded,
        "xprv9wSp6B7kry3Vj9m1zSnLvN3xH8RdsPP1Mh7fAaR7aRLcQMKTR2vidYEeEg2mUCTAwCd6vnxVrcjfy2kRgVsFawNzmjuHc2YmYRmagcEPdU9"));

    bc_string_t* m0xH1_encoded = bc_hd_private_encoded(m0xH1);
    BOOST_REQUIRE(bc_string_equals_cstr(m0xH1_encoded,
        "xprv9zFnWC6h2cLgpmSA46vutJzBcfJ8yaJGg8cX1e5StJh45BBciYTRXSd25UEPVuesF9yog62tGAQtHjXajPPdbRCHuWS6T8XA2ECKADdw4Ef"));

    bc_string_t* m0xH1yH_encoded = bc_hd_private_encoded(m0xH1yH);
    BOOST_REQUIRE(bc_string_equals_cstr(m0xH1yH_encoded,
        "xprvA1RpRA33e1JQ7ifknakTFpgNXPmW2YvmhqLQYMmrj4xJXXWYpDPS3xz7iAxn8L39njGVyuoseXzU6rcxFLJ8HFsTjSyQbLYnMpCqE2VbFWc"));

    bc_string_t* m0xH1yH2_encoded = bc_hd_private_encoded(m0xH1yH2);
    BOOST_REQUIRE(bc_string_equals_cstr(m0xH1yH2_encoded,
        "xprvA2nrNbFZABcdryreWet9Ea4LvTJcGsqrMzxHx98MMrotbir7yrKCEXw7nadnHM8Dq38EGfSh6dqA9QWTyefMLEcBYJUuekgW4BYPJcr9E7j"));

    bc_destroy_string(m_encoded);
    bc_destroy_string(m0_encoded);
    bc_destroy_string(m0xH_encoded);
    bc_destroy_string(m0xH1_encoded);
    bc_destroy_string(m0xH1yH_encoded);
    bc_destroy_string(m0xH1yH2_encoded);

    bc_destroy_hd_private(m);
    bc_destroy_hd_private(m0);
    bc_destroy_hd_private(m0xH);
    bc_destroy_hd_private(m0xH1);
    bc_destroy_hd_private(m0xH1yH);
    bc_destroy_hd_private(m0xH1yH2);

    bc_destroy_data_chunk(seed);
}

BOOST_AUTO_TEST_CASE(hd_private__derive_public__long_seed__expected_c)
{
    bc_data_chunk_t* seed = bc_create_data_chunk();
    BOOST_REQUIRE(bc_decode_base16(seed, LONG_SEED));

    bc_hd_private_t* m = bc_create_hd_private_Seed(
        seed, bc_hd_private_mainnet());
    bc_hd_private_t* m0 = bc_hd_private_derive_private(
        m, 0);
    bc_hd_private_t* m0xH = bc_hd_private_derive_private(
        m0, 2147483647 + bc_hd_first_hardened_key());
    bc_hd_private_t* m0xH1 = bc_hd_private_derive_private(
        m0xH, 1);
    bc_hd_private_t* m0xH1yH = bc_hd_private_derive_private(
        m0xH1, 2147483646 + bc_hd_first_hardened_key());
    bc_hd_private_t* m0xH1yH2 = bc_hd_private_derive_private(
        m0xH1yH, 2);

    bc_hd_public_t* m_pub = bc_hd_private_to_public(m);
    bc_hd_public_t* m0_pub = bc_hd_private_derive_public(
        m, 0);
    bc_hd_public_t* m0xH_pub = bc_hd_private_derive_public(
        m0, 2147483647 + bc_hd_first_hardened_key());
    bc_hd_public_t* m0xH1_pub = bc_hd_private_derive_public(
        m0xH, 1);
    bc_hd_public_t* m0xH1yH_pub = bc_hd_private_derive_public(
        m0xH1, 2147483646 + bc_hd_first_hardened_key());
    bc_hd_public_t* m0xH1yH2_pub = bc_hd_private_derive_public(
        m0xH1yH, 2);

    bc_string_t* m_pub_encoded = bc_hd_public_encoded(m_pub);
    BOOST_REQUIRE(bc_string_equals_cstr(m_pub_encoded,
        "xpub661MyMwAqRbcFW31YEwpkMuc5THy2PSt5bDMsktWQcFF8syAmRUapSCGu8ED9W6oDMSgv6Zz8idoc4a6mr8BDzTJY47LJhkJ8UB7WEGuduB"));

    bc_string_t* m0_pub_encoded = bc_hd_public_encoded(m0_pub);
    BOOST_REQUIRE(bc_string_equals_cstr(m0_pub_encoded,
        "xpub69H7F5d8KSRgmmdJg2KhpAK8SR3DjMwAdkxj3ZuxV27CprR9LgpeyGmXUbC6wb7ERfvrnKZjXoUmmDznezpbZb7ap6r1D3tgFxHmwMkQTPH"));

    bc_string_t* m0xH_pub_encoded = bc_hd_public_encoded(m0xH_pub);
    BOOST_REQUIRE(bc_string_equals_cstr(m0xH_pub_encoded,
        "xpub6ASAVgeehLbnwdqV6UKMHVzgqAG8Gr6riv3Fxxpj8ksbH9ebxaEyBLZ85ySDhKiLDBrQSARLq1uNRts8RuJiHjaDMBU4Zn9h8LZNnBC5y4a"));

    bc_string_t* m0xH1_pub_encoded = bc_hd_public_encoded(m0xH1_pub);
    BOOST_REQUIRE(bc_string_equals_cstr(m0xH1_pub_encoded,
        "xpub6DF8uhdarytz3FWdA8TvFSvvAh8dP3283MY7p2V4SeE2wyWmG5mg5EwVvmdMVCQcoNJxGoWaU9DCWh89LojfZ537wTfunKau47EL2dhHKon"));

    bc_string_t* m0xH1yH_pub_encoded = bc_hd_public_encoded(m0xH1yH_pub);
    BOOST_REQUIRE(bc_string_equals_cstr(m0xH1yH_pub_encoded,
        "xpub6ERApfZwUNrhLCkDtcHTcxd75RbzS1ed54G1LkBUHQVHQKqhMkhgbmJbZRkrgZw4koxb5JaHWkY4ALHY2grBGRjaDMzQLcgJvLJuZZvRcEL"));

    bc_string_t* m0xH1yH2_pub_encoded = bc_hd_public_encoded(m0xH1yH2_pub);
    BOOST_REQUIRE(bc_string_equals_cstr(m0xH1yH2_pub_encoded,
        "xpub6FnCn6nSzZAw5Tw7cgR9bi15UV96gLZhjDstkXXxvCLsUXBGXPdSnLFbdpq8p9HmGsApME5hQTZ3emM2rnY5agb9rXpVGyy3bdW6EEgAtqt"));

    bc_destroy_string(m_pub_encoded);
    bc_destroy_string(m0_pub_encoded);
    bc_destroy_string(m0xH_pub_encoded);
    bc_destroy_string(m0xH1_pub_encoded);
    bc_destroy_string(m0xH1yH_pub_encoded);
    bc_destroy_string(m0xH1yH2_pub_encoded);

    bc_destroy_hd_public(m_pub);
    bc_destroy_hd_public(m0_pub);
    bc_destroy_hd_public(m0xH_pub);
    bc_destroy_hd_public(m0xH1_pub);
    bc_destroy_hd_public(m0xH1yH_pub);
    bc_destroy_hd_public(m0xH1yH2_pub);

    bc_destroy_hd_private(m);
    bc_destroy_hd_private(m0);
    bc_destroy_hd_private(m0xH);
    bc_destroy_hd_private(m0xH1);
    bc_destroy_hd_private(m0xH1yH);
    bc_destroy_hd_private(m0xH1yH2);

    bc_destroy_data_chunk(seed);
}

BOOST_AUTO_TEST_SUITE_END()

