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
#ifndef LIBBITCOIN_C_INTERNAL_CHAIN_SCRIPT_OPERATION_HPP
#define LIBBITCOIN_C_INTERNAL_CHAIN_SCRIPT_OPERATION_HPP

#include <bitcoin/bitcoin/c/chain/script/operation.h>

#include <vector>
#include <bitcoin/bitcoin/chain/script/operation.hpp>
#include <bitcoin/bitcoin/c/internal/utility/vector.hpp>

extern "C" {

BC_DECLARE_VECTOR_STRUCT(operation_stack, bc_operation_t);

struct bc_operation_t
{
    libbitcoin::chain::operation* obj;
};

}

// C++ convenience function
bc_script_pattern_t bc_script_pattern_to_ctype(
    libbitcoin::chain::script_pattern value);
libbitcoin::chain::script_pattern bc_script_pattern_from_ctype(
    bc_script_pattern_t value);

#endif

