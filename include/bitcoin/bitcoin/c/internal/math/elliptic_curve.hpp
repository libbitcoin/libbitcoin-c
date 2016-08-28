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
#ifndef LIBBITCOIN_C_INTERNAL_ELLIPTIC_CURVE_HPP
#define LIBBITCOIN_C_INTERNAL_ELLIPTIC_CURVE_HPP

#include <bitcoin/bitcoin/math/elliptic_curve.hpp>
#include <bitcoin/bitcoin/c/internal/utility/vector.hpp>

BC_DECLARE_VECTOR_INTERNAL(point_list, bc_ec_compressed_t,
    libbitcoin::point_list);

extern "C" {

struct bc_ec_secret_t
{
    libbitcoin::ec_secret* obj;
};

struct bc_ec_compressed_t
{
    libbitcoin::ec_compressed* obj;
};

struct bc_ec_uncompressed_t
{
    libbitcoin::ec_uncompressed* obj;
};

struct bc_ec_signature_t
{
    libbitcoin::ec_signature* obj;
};

struct bc_recoverable_signature_t
{
    libbitcoin::recoverable_signature* obj;
};

} // extern C

#endif

