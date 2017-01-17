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
#include <bitcoin/bitcoin/c/machine/sighash_algorithm.h>
#include <bitcoin/bitcoin/c/internal/machine/sighash_algorithm.hpp>

bc_sighash_algorithm_t bc_sighash_algorithm_to_ctype(
    libbitcoin::machine::sighash_algorithm value)
{
    switch (value)
    {
        case libbitcoin::machine::sighash_algorithm::all:
            return bc_sighash_algorithm__all;
        case libbitcoin::machine::sighash_algorithm::none:
            return bc_sighash_algorithm__none;
        case libbitcoin::machine::sighash_algorithm::single:
            return bc_sighash_algorithm__single;
        case libbitcoin::machine::sighash_algorithm::anyone_can_pay:
            return bc_sighash_algorithm__anyone_can_pay;
        case libbitcoin::machine::sighash_algorithm::all_anyone_can_pay:
            return bc_sighash_algorithm__all_anyone_can_pay;
        case libbitcoin::machine::sighash_algorithm::none_anyone_can_pay:
            return bc_sighash_algorithm__none_anyone_can_pay;
        case libbitcoin::machine::sighash_algorithm::single_anyone_can_pay:
            return bc_sighash_algorithm__single_anyone_can_pay;
    }
}
libbitcoin::machine::sighash_algorithm bc_sighash_algorithm_from_ctype(
    bc_sighash_algorithm_t value)
{
    switch (value)
    {
        case bc_sighash_algorithm__all:
            return libbitcoin::machine::sighash_algorithm::all;
        case bc_sighash_algorithm__none:
            return libbitcoin::machine::sighash_algorithm::none;
        case bc_sighash_algorithm__single:
            return libbitcoin::machine::sighash_algorithm::single;
        case bc_sighash_algorithm__anyone_can_pay:
            return libbitcoin::machine::sighash_algorithm::anyone_can_pay;
        case bc_sighash_algorithm__all_anyone_can_pay:
            return libbitcoin::machine::sighash_algorithm::all_anyone_can_pay;
        case bc_sighash_algorithm__none_anyone_can_pay:
            return libbitcoin::machine::sighash_algorithm::none_anyone_can_pay;
        case bc_sighash_algorithm__single_anyone_can_pay:
            return libbitcoin::machine::sighash_algorithm::single_anyone_can_pay;
    }
}

