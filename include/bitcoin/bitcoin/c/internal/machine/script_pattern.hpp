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
#ifndef LIBBITCOIN_C_INTERNAL_MACHINE_SCRIPT_PATTERN_HPP
#define LIBBITCOIN_C_INTERNAL_MACHINE_SCRIPT_PATTERN_HPP

#include <bitcoin/bitcoin/c/machine/script_pattern.h>

#include <bitcoin/bitcoin/machine/script_pattern.hpp>

// C++ convenience function
bc_script_pattern_t bc_script_pattern_to_ctype(
    libbitcoin::machine::script_pattern value);
libbitcoin::machine::script_pattern bc_script_pattern_from_ctype(
    bc_script_pattern_t value);

#endif

