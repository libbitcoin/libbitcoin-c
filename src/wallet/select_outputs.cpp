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
#include <bitcoin/bitcoin/c/wallet/select_outputs.h>

#include <bitcoin/bitcoin/wallet/select_outputs.hpp>
#include <bitcoin/bitcoin/c/internal/chain/output.hpp>
#include <bitcoin/bitcoin/c/internal/chain/point.hpp>
#include <bitcoin/bitcoin/c/internal/chain/points_value.hpp>

extern "C" {

void bc_select_outputs__select(bc_points_value_t* out,
    const bc_points_value_t* unspent, uint64_t minimum_value)
{
    libbitcoin::wallet::select_outputs::select(
        *out->obj, *unspent->obj, minimum_value);
}

void bc_select_outputs__select_Alg(bc_points_value_t* out,
    const bc_points_value_t* unspent, uint64_t minimum_value,
    bc_select_outputs__algorithm_t option)
{
    libbitcoin::wallet::select_outputs::algorithm option_conv;
    if (option == bc_select_outputs__algorithm__greedy)
        option_conv = libbitcoin::wallet::select_outputs::algorithm::greedy;
    else if (option == bc_select_outputs__algorithm__individual)
        option_conv = libbitcoin::wallet::select_outputs::algorithm::individual;
    else
        BITCOIN_ASSERT(false);
    libbitcoin::wallet::select_outputs::select(
        *out->obj, *unspent->obj, minimum_value, option_conv);
}

}

