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
#include <bitcoin/bitcoin/c/machine/opcode.h>
#include <bitcoin/bitcoin/c/internal/machine/opcode.hpp>

#include <bitcoin/bitcoin/machine/opcode.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>

extern "C" {

bc_string_t* bc_opcode_to_string(bc_opcode_t value, uint32_t active_forks)
{
    const auto value_converted = bc_opcode_from_ctype(value);
    return bc_create_string_StdString(
        libbitcoin::machine::opcode_to_string(value_converted, active_forks));
}

bool bc_opcode_from_string(bc_opcode_t* out_code, const char* value)
{
    libbitcoin::machine::opcode code;
    bool result = libbitcoin::machine::opcode_from_string(code, value);
    *out_code = bc_opcode_to_ctype(code);
    return result;
}

bc_string_t* bc_opcode_to_hexadecimal(bc_opcode_t code)
{
    const auto value_converted = bc_opcode_from_ctype(code);
    return bc_create_string_StdString(
        libbitcoin::machine::opcode_to_hexadecimal(value_converted));
}

bool bc_opcode_from_hexadecimal(bc_opcode_t* out_code, const char* value)
{
    libbitcoin::machine::opcode code;
    bool result = libbitcoin::machine::opcode_from_hexadecimal(code, value);
    *out_code = bc_opcode_to_ctype(code);
    return result;
}

} // extern C

bc_opcode_t bc_opcode_to_ctype(libbitcoin::machine::opcode value)
{
    return static_cast<bc_opcode_t>(value);
}
libbitcoin::machine::opcode bc_opcode_from_ctype(bc_opcode_t value)
{
    return static_cast<libbitcoin::machine::opcode>(value);
}

