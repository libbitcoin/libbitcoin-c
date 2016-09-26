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
#include <bitcoin/bitcoin/c/formats/base_10.h>

#include <bitcoin/bitcoin/formats/base_10.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>

extern "C" {

uint8_t bc_btc_decimal_places()
{
    return libbitcoin::btc_decimal_places;
}
uint8_t bc_mbtc_decimal_places()
{
    return libbitcoin::mbtc_decimal_places;
}
uint8_t bc_ubtc_decimal_places()
{
    return libbitcoin::ubtc_decimal_places;
}

bool bc_decode_base10(uint64_t* out, const char* amount)
{
    return libbitcoin::decode_base10(*out, amount);
}
bool bc_decode_base10_Places(uint64_t* out, const char* amount,
    uint8_t decimal_places)
{
    return libbitcoin::decode_base10(*out, amount, decimal_places);
}
bool bc_decode_base10_Places_nostrict(uint64_t* out, const char* amount,
    uint8_t decimal_places)
{
    return libbitcoin::decode_base10(*out, amount, decimal_places, false);
}

bc_string_t* bc_encode_base10(uint64_t amount)
{
    return bc_create_string_StdString(
        libbitcoin::encode_base10(amount));
}
bc_string_t* bc_encode_base10_Places(uint64_t amount, uint8_t decimal_places)
{
    return bc_create_string_StdString(
        libbitcoin::encode_base10(amount, decimal_places));
}

} // extern C

