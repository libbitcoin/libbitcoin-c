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
#ifndef LIBBITCOIN_C_BASE_10_H
#define LIBBITCOIN_C_BASE_10_H

#include <stdbool.h>
#include <stdint.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>

#ifdef __cplusplus
extern "C" {
#endif

uint8_t bc_btc_decimal_places();
uint8_t bc_mbtc_decimal_places();
uint8_t bc_ubtc_decimal_places();

/**
 * Validates and parses an amount string according to the BIP 21 grammar.
 * @param decmial_places the location of the decimal point.
 * The default is 0, which treats the input as a normal integer.
 * @param strict true to treat fractional results as an error,
 * or false to round them upwards.
 * @return false for failure.
 */
bool bc_decode_base10(uint64_t* out, const char* amount);
bool bc_decode_base10_Places(uint64_t* out, const char* amount,
    uint8_t decimal_places);
bool bc_decode_base10_Places_nostrict(uint64_t* out, const char* amount,
    uint8_t decimal_places);

/**
 * Writes a Bitcoin amount to a string, following the BIP 21 grammar.
 * Avoids the rounding issues often seen with floating-point methods.
 * @param decmial_places the location of the decimal point.
 * The default is 0, which treats the input as a normal integer.
 */
bc_string_t* bc_encode_base10(uint64_t amount);
bc_string_t* bc_encode_base10_Places(uint64_t amount, uint8_t decimal_places);

#ifdef __cplusplus
}
#endif

#endif

