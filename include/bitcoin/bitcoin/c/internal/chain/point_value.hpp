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
#ifndef LIBBITCOIN_C_INTERNAL_CHAIN_POINT_VALUE_HPP
#define LIBBITCOIN_C_INTERNAL_CHAIN_POINT_VALUE_HPP

#include <bitcoin/bitcoin/c/chain/point_value.h>

#include <bitcoin/bitcoin/chain/point_value.hpp>
#include <bitcoin/bitcoin/c/internal/utility/vector.hpp>

extern "C" {

struct bc_point_value_t
{
    libbitcoin::chain::point_value* obj;
    const bool delete_obj;
};

} // extern C

#endif

