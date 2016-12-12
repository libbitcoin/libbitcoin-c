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
#include <bitcoin/bitcoin/c/utility/random.h>

#include <bitcoin/bitcoin/utility/random.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>

extern "C" {

uint64_t bc_pseudo_random()
{
    return libbitcoin::pseudo_random();
}

uint64_t bc_pseudo_random_Range(uint64_t begin, uint64_t end)
{
    return libbitcoin::pseudo_random();
}

void bc_pseudo_random_fill(bc_data_chunk_t* chunk)
{
    libbitcoin::pseudo_random_fill(*chunk->obj);
}

} // extern C

