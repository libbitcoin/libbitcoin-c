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
#ifndef LIBBITCOIN_C_INTERNAL_HASH_HPP
#define LIBBITCOIN_C_INTERNAL_HASH_HPP

#include <bitcoin/bitcoin/math/hash.hpp>

extern "C" {

#define BC_DECLARE_HASH_INTERNAL(hashtype) \
    \
    struct bc_##hashtype##_t \
    { \
        libbitcoin::hashtype* obj; \
    }; \
    \
    bc_##hashtype##_t* bc_create_##hashtype##_Internal( \
        const libbitcoin::hashtype& value);

BC_DECLARE_HASH_INTERNAL(hash_digest);
BC_DECLARE_HASH_INTERNAL(half_hash);
BC_DECLARE_HASH_INTERNAL(quarter_hash);
BC_DECLARE_HASH_INTERNAL(long_hash);
BC_DECLARE_HASH_INTERNAL(short_hash);
BC_DECLARE_HASH_INTERNAL(mini_hash);

#undef HASH_STRUCT

}

#endif

