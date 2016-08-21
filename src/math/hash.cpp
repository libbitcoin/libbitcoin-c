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
#include <bitcoin/bitcoin/c/math/hash.h>

#include <bitcoin/bitcoin/math/hash.hpp>

extern "C" {

size_t bc_hash_size()
{
    return libbitcoin::hash_size;
}
size_t bc_half_hash_size()
{
    return libbitcoin::half_hash_size;
}
size_t bc_quarter_hash_size()
{
    return libbitcoin::quarter_hash_size;
}
size_t bc_long_hash_size()
{
    return libbitcoin::long_hash_size;
}
size_t bc_short_hash_size()
{
    return libbitcoin::short_hash_size;
}
size_t bc_mini_hash_size()
{
    return libbitcoin::mini_hash_size;
}

#define HASH_IMPL(hashname) \
    \
    struct bc_##hashname##_t \
    { \
        libbitcoin::hashname* obj; \
    }; \
    bc_##hashname##_t* create_##hashname() \
    { \
        bc_##hashname##_t* self = new bc_##hashname##_t; \
        self->obj = new libbitcoin::hashname; \
        return self; \
    } \
    void bc_destroy_##hashname(bc_##hashname##_t* self) \
    { \
        delete self->obj; \
        delete self; \
    } \
    uint8_t* bc_##hashname##_data(bc_##hashname##_t* self) \
    { \
        return self->obj->data(); \
    }

HASH_IMPL(hash_digest);
HASH_IMPL(half_hash);
HASH_IMPL(quarter_hash);
HASH_IMPL(long_hash);
HASH_IMPL(short_hash);
HASH_IMPL(mini_hash);

#undef HASH_IMPL

bc_hash_digest_t* bc_null_hash()
{
    bc_hash_digest_t* self = new bc_hash_digest_t;
    self->obj = new libbitcoin::hash_digest(libbitcoin::null_hash);
    return self;
}

}

