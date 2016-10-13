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
#include <bitcoin/bitcoin/c/chain/output.h>
#include <bitcoin/bitcoin/c/chain/output_point.h>

#ifdef __cplusplus
extern "C" {
#endif

void bc_select_outputs__select(bc_points_info_t* out,
    const bc_output_info_list_t* unspent, uint64_t minimum_value);

#ifdef __cplusplus
}
#endif

#endif

