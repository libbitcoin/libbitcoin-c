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
#ifndef LIBBITCOIN_C_WALLET_SELECT_OUTPUTS_H
#define LIBBITCOIN_C_WALLET_SELECT_OUTPUTS_H

#include <stdint.h>
#include <bitcoin/bitcoin/c/chain/points_value.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Algorithm summary:
///
/// greedy: returns the first available unspent output that is the
/// minimum greater than the specified amount if any.  if there
/// are none, it returns a set of the largest outputs (in desc
/// order to minimize the number of inputs) that are smaller than
/// the specified amount and the amount of change.
///
/// individual: returns a set of individual unspent outputs that
/// satisfy the specified amount.  For example, setting amount to
/// 0 will return all unspent outputs since any of them can
/// satisfy that amount.  The change amount will always be 0.
typedef enum bc_select_outputs__algorithm_t
{
    bc_select_outputs__algorithm__greedy,
    bc_select_outputs__algorithm__individual
} bc_select_outputs__algorithm_t;

void bc_select_outputs__select(bc_points_value_t* out,
    const bc_points_value_t* unspent, uint64_t minimum_value);

void bc_select_outputs__select_Alg(bc_points_value_t* out,
    const bc_points_value_t* unspent, uint64_t minimum_value,
    bc_select_outputs__algorithm_t option);

#ifdef __cplusplus
}
#endif

#endif

