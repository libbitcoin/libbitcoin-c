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
#include <bitcoin/bitcoin/c/machine/script_pattern.h>
#include <bitcoin/bitcoin/c/internal/machine/script_pattern.hpp>

bc_script_pattern_t bc_script_pattern_to_ctype(
    libbitcoin::machine::script_pattern value)
{
    switch (value)
    {
        case libbitcoin::machine::script_pattern::null_data:
            return bc_script_pattern__null_data;

        case libbitcoin::machine::script_pattern::pay_multisig:
            return bc_script_pattern__pay_multisig;

        case libbitcoin::machine::script_pattern::pay_public_key:
            return bc_script_pattern__pay_public_key;

        case libbitcoin::machine::script_pattern::pay_key_hash:
            return bc_script_pattern__pay_key_hash;

        case libbitcoin::machine::script_pattern::pay_script_hash:
            return bc_script_pattern__pay_script_hash;

        case libbitcoin::machine::script_pattern::sign_multisig:
            return bc_script_pattern__sign_multisig;

        case libbitcoin::machine::script_pattern::sign_public_key:
            return bc_script_pattern__sign_public_key;

        case libbitcoin::machine::script_pattern::sign_key_hash:
            return bc_script_pattern__sign_key_hash;

        case libbitcoin::machine::script_pattern::sign_script_hash:
            return bc_script_pattern__sign_script_hash;

        case libbitcoin::machine::script_pattern::non_standard:
            return bc_script_pattern__non_standard;
    }
}

libbitcoin::machine::script_pattern bc_script_pattern_from_ctype(
    bc_script_pattern_t value)
{
    switch (value)
    {
        case bc_script_pattern__null_data:
            return libbitcoin::machine::script_pattern::null_data;

        case bc_script_pattern__pay_multisig:
            return libbitcoin::machine::script_pattern::pay_multisig;

        case bc_script_pattern__pay_public_key:
            return libbitcoin::machine::script_pattern::pay_public_key;

        case bc_script_pattern__pay_key_hash:
            return libbitcoin::machine::script_pattern::pay_key_hash;

        case bc_script_pattern__pay_script_hash:
            return libbitcoin::machine::script_pattern::pay_script_hash;

        case bc_script_pattern__sign_multisig:
            return libbitcoin::machine::script_pattern::sign_multisig;

        case bc_script_pattern__sign_public_key:
            return libbitcoin::machine::script_pattern::sign_public_key;

        case bc_script_pattern__sign_key_hash:
            return libbitcoin::machine::script_pattern::sign_key_hash;

        case bc_script_pattern__sign_script_hash:
            return libbitcoin::machine::script_pattern::sign_script_hash;

        case bc_script_pattern__non_standard:
            return libbitcoin::machine::script_pattern::non_standard;
    }
}

