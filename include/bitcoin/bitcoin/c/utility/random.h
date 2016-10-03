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
#ifndef LIBBITCOIN_C_UTILITY_RANDOM_H
#define LIBBITCOIN_C_UTILITY_RANDOM_H

#include <stdint.h>
#include <bitcoin/bitcoin/c/utility/data.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Generate a pseudo random number within the domain.
 * @return  The 64 bit number (use % to subset domain).
 */
uint64_t bc_pseudo_random();

/**
 * Generate a non-zero pseudo random number within the domain.
 * @return  The 64 bit number (use % to subset domain).
 */
uint64_t bc_nonzero_pseudo_random();

/**
 * Fill a buffer with randomness using the default random engine.
 * @param[in]  chunk  The buffer to fill with randomness.
 */
void bc_pseudo_random_fill(bc_data_chunk_t* chunk);

#ifdef __cplusplus
}
#endif

#endif

