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
#ifndef LIBBITCOIN_C_INTERNAL_CHAIN_SCRIPT_HPP
#define LIBBITCOIN_C_INTERNAL_CHAIN_SCRIPT_HPP

#include <bitcoin/bitcoin/c/chain/script.h>

#include <bitcoin/bitcoin/chain/script.hpp>

extern "C" {

struct bc_script_t
{
    libbitcoin::chain::script* obj;
    const bool delete_obj;
};

} // extern C

// C++ convenience functions
/*
bc_signature_hash_algorithm_t bc_signature_hash_algorithm_to_ctype(
    libbitcoin::chain::signature_hash_algorithm alg);

libbitcoin::chain::signature_hash_algorithm
    bc_signature_hash_algorithm_from_ctype(bc_signature_hash_algorithm_t alg);

bc_script_parse_mode_t bc_script_parse_mode_to_ctype(
    libbitcoin::chain::script::parse_mode mode);

libbitcoin::chain::script::parse_mode bc_script_parse_mode_from_ctype(
    bc_script_parse_mode_t mode);
*/

#endif

