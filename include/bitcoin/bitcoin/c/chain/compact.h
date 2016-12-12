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
#ifndef LIBBITCOIN_C_CHAIN_COMPACT_H
#define LIBBITCOIN_C_CHAIN_COMPACT_H

#include <bitcoin/bitcoin/c/math/uint256.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_compact_t bc_compact_t;

// Constructors
bc_compact_t* bc_create_compact(uint32_t compact);
bc_compact_t* bc_create_compact_Uint256(const bc_uint256_t* big);
bc_compact_t* bc_create_compact_copy(const bc_compact_t* other);
// Destructor
void bc_destroy_compact(bc_compact_t* self);

// Methods
/// True if construction overflowed.
bool bc_compact__is_overflowed(const bc_compact_t* self);

/// Consensus-normalized compact number value.
/// This is derived from the construction parameter.
uint32_t bc_compact__normal(const bc_compact_t* self);

/// Big number that the compact number represents.
/// This is either saved or generated from the construction parameter.
bc_uint256_t* bc_compact__to_uint256(const bc_compact_t* self);

#ifdef __cplusplus
}
#endif

#endif

