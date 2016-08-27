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
#include <bitcoin/bitcoin/c/chain/script/operation.h>
#include <bitcoin/bitcoin/c/internal/chain/script/operation.hpp>

#include <bitcoin/bitcoin/c/internal/chain/script/opcode.hpp>
#include <bitcoin/bitcoin/c/internal/utility/vector.hpp>

extern "C" {

BC_IMPLEMENT_VECTOR(operation_stack, bc_operation_t, bc_destroy_operation);

bc_operation_t* bc_create_operation()
{
    return new bc_operation_t{ new libbitcoin::chain::operation };
}
void bc_destroy_operation(bc_operation_t* self)
{
    delete self->obj;
    delete self;
}

}

bc_script_pattern_t bc_script_pattern_to_ctype(
    libbitcoin::chain::script_pattern value)
{
    switch (value)
    {
        case libbitcoin::chain::script_pattern::null_data:
            return bc_script_pattern_null_data;

        case libbitcoin::chain::script_pattern::pay_multisig:
            return bc_script_pattern_pay_multisig;

        case libbitcoin::chain::script_pattern::pay_public_key:
            return bc_script_pattern_pay_public_key;

        case libbitcoin::chain::script_pattern::pay_key_hash:
            return bc_script_pattern_pay_key_hash;

        case libbitcoin::chain::script_pattern::pay_script_hash:
            return bc_script_pattern_pay_script_hash;

        case libbitcoin::chain::script_pattern::sign_multisig:
            return bc_script_pattern_sign_multisig;

        case libbitcoin::chain::script_pattern::sign_public_key:
            return bc_script_pattern_sign_public_key;

        case libbitcoin::chain::script_pattern::sign_key_hash:
            return bc_script_pattern_sign_key_hash;

        case libbitcoin::chain::script_pattern::sign_script_hash:
            return bc_script_pattern_sign_script_hash;

        case libbitcoin::chain::script_pattern::non_standard:
            return bc_script_pattern_non_standard;
    }
}

libbitcoin::chain::script_pattern bc_script_pattern_from_ctype(
    bc_script_pattern_t value)
{
    switch (value)
    {
        case bc_script_pattern_null_data:
            return libbitcoin::chain::script_pattern::null_data;

        case bc_script_pattern_pay_multisig:
            return libbitcoin::chain::script_pattern::pay_multisig;

        case bc_script_pattern_pay_public_key:
            return libbitcoin::chain::script_pattern::pay_public_key;

        case bc_script_pattern_pay_key_hash:
            return libbitcoin::chain::script_pattern::pay_key_hash;

        case bc_script_pattern_pay_script_hash:
            return libbitcoin::chain::script_pattern::pay_script_hash;

        case bc_script_pattern_sign_multisig:
            return libbitcoin::chain::script_pattern::sign_multisig;

        case bc_script_pattern_sign_public_key:
            return libbitcoin::chain::script_pattern::sign_public_key;

        case bc_script_pattern_sign_key_hash:
            return libbitcoin::chain::script_pattern::sign_key_hash;

        case bc_script_pattern_sign_script_hash:
            return libbitcoin::chain::script_pattern::sign_script_hash;

        case bc_script_pattern_non_standard:
            return libbitcoin::chain::script_pattern::non_standard;
    }
}

