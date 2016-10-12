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
#ifndef LIBBITCOIN_C_INTERNAL_CHAIN_POINT_HPP
#define LIBBITCOIN_C_INTERNAL_CHAIN_POINT_HPP

#include <bitcoin/bitcoin/c/chain/point.h>

#include <bitcoin/bitcoin/chain/point.hpp>
#include <bitcoin/bitcoin/c/internal/utility/vector.hpp>

extern "C" {

struct bc_point_indexes_t
{
    libbitcoin::chain::point::indexes* obj;
    const bool delete_obj;
};

struct bc_point_t
{
    libbitcoin::chain::point* obj;
    const bool delete_obj;
};

struct bc_chain_point_list_t
{
    libbitcoin::chain::point::list* obj;
    const bool delete_obj;
};

} // extern C

#endif

