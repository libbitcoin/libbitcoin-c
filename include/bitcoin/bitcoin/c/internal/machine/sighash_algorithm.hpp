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
#ifndef LIBBITCOIN_C_INTERNAL_MACHINE_SIGHASH_ALGORITHM_HPP
#define LIBBITCOIN_C_INTERNAL_MACHINE_SIGHASH_ALGORITHM_HPP

#include <bitcoin/bitcoin/c/machine/sighash_algorithm.h>

#include <bitcoin/bitcoin/machine/sighash_algorithm.hpp>

// C++ convenience function
bc_sighash_algorithm_t bc_sighash_algorithm_to_ctype(
    libbitcoin::machine::sighash_algorithm value);
libbitcoin::machine::sighash_algorithm bc_sighash_algorithm_from_ctype(
    bc_sighash_algorithm_t value);

#endif

