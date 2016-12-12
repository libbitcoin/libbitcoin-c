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
#include <bitcoin/bitcoin/c/chain/compact.h>
#include <bitcoin/bitcoin/c/internal/chain/compact.hpp>

#include <bitcoin/bitcoin/c/internal/math/uint256.hpp>

extern "C" {

bc_compact_t* bc_create_compact(uint32_t compact)
{
    return new bc_compact_t{ new libbitcoin::chain::compact(compact) };
}
bc_compact_t* bc_create_compact_Uint256(const bc_uint256_t* big)
{
    return new bc_compact_t{ new libbitcoin::chain::compact(*big->obj) };
}
bc_compact_t* bc_create_compact_copy(const bc_compact_t* other)
{
    return new bc_compact_t{ new libbitcoin::chain::compact(*other->obj) };
}
void bc_destroy_compact(bc_compact_t* self)
{
    delete self->obj;
    delete self;
}

bool bc_compact__is_overflowed(const bc_compact_t* self)
{
    return self->obj->is_overflowed();
}

uint32_t bc_compact__normal(const bc_compact_t* self)
{
    return self->obj->normal();
}

bc_uint256_t* bc_compact__to_uint256(const bc_compact_t* self)
{
    return new bc_uint256_t{ new libbitcoin::uint256(*self->obj) };
}

} // extern C

