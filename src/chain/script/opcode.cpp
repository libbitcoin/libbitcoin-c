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
#include <bitcoin/bitcoin/c/chain/script/opcode.h>
#include <bitcoin/bitcoin/c/internal/chain/script/opcode.hpp>

#include <bitcoin/bitcoin/chain/script/opcode.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>

extern "C" {

bc_string_t* opcode_to_string(bc_opcode_t value, uint32_t flags)
{
    const auto value_converted = bc_opcode_from_ctype(value);
    return bc_create_string_StdString(
        libbitcoin::chain::opcode_to_string(value_converted, flags));
}
bc_opcode_t string_to_opcode(const char* value)
{
    return bc_opcode_to_ctype(
        libbitcoin::chain::string_to_opcode(value));
}
bc_opcode_t data_to_opcode(const bc_data_chunk_t* value)
{
    return bc_opcode_to_ctype(
        libbitcoin::chain::data_to_opcode(*value->obj));
}

}

bc_opcode_t bc_opcode_to_ctype(libbitcoin::chain::opcode value)
{
    return static_cast<bc_opcode_t>(value);
}
libbitcoin::chain::opcode bc_opcode_from_ctype(bc_opcode_t value)
{
    return static_cast<libbitcoin::chain::opcode>(value);
}

