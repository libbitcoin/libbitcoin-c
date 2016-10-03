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
#ifndef LIBBITCOIN_C_INTERNAL_CHAIN_SCRIPT_OPCODE_HPP
#define LIBBITCOIN_C_INTERNAL_CHAIN_SCRIPT_OPCODE_HPP

#include <bitcoin/bitcoin/c/chain/script/opcode.h>

#include <bitcoin/bitcoin/chain/script/opcode.hpp>

// C++ convenience function
bc_opcode_t bc_opcode_to_ctype(libbitcoin::chain::opcode value);
libbitcoin::chain::opcode bc_opcode_from_ctype(bc_opcode_t value);

bc_rule_fork_t bc_rule_fork_to_ctype(
    libbitcoin::chain::rule_fork rule);
libbitcoin::chain::rule_fork bc_rule_fork_from_ctype(
    bc_rule_fork_t rule);

#endif


