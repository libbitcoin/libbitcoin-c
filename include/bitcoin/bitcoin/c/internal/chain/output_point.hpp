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
#ifndef LIBBITCOIN_C_INTERNAL_CHAIN_OUTPUT_POINT_HPP
#define LIBBITCOIN_C_INTERNAL_CHAIN_OUTPUT_POINT_HPP

#include <bitcoin/bitcoin/c/chain/output_point.h>

#include <bitcoin/bitcoin/chain/output_point.hpp>
#include <bitcoin/bitcoin/c/internal/utility/vector.hpp>

extern "C" {

struct bc_output_point_validation_t
{
    libbitcoin::chain::output_point::validation_type* obj;
    const bool delete_obj;
};

struct bc_output_point_t
{
    libbitcoin::chain::output_point* obj;
    const bool delete_obj;
};

struct bc_points_info_t
{
    libbitcoin::chain::points_info* obj;
    const bool delete_obj;
};

struct bc_output_info_t
{
    libbitcoin::chain::output_info* obj;
    const bool delete_obj;
};

struct bc_output_info_list_t
{
    libbitcoin::chain::output_info::list* obj;
    const bool delete_obj;
};

} // extern C

#endif

