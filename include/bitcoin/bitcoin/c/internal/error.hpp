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
#ifndef LIBBITCOIN_C_INTERNAL_ERROR_HPP
#define LIBBITCOIN_C_INTERNAL_ERROR_HPP

#include <bitcoin/bitcoin/error.hpp>

extern "C" {

struct bc_error_code_t
{
    std::error_code* obj;
};

} // extern C

// C++ convenience functions
bc_error_t bc_error_code_to_ctype(libbitcoin::error::error_code_t value);
libbitcoin::error::error_code_t bc_error_code_from_ctype(bc_error_t value);

#endif

