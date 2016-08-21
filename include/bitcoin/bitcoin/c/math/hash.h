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
#ifndef LIBBITCOIN_C_HASH_H
#define LIBBITCOIN_C_HASH_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Common bitcoin hash container sizes.
size_t bc_hash_size();
size_t bc_half_hash_size();
size_t bc_quarter_hash_size();
size_t bc_long_hash_size();
size_t bc_short_hash_size();
size_t bc_mini_hash_size();

// Common bitcoin hash containers.
#define DECLARE_HASH_TYPE(hashname) \
    typedef struct bc_##hashname##_t bc_##hashname##_t; \
    bc_##hashname##_t* create_##hashname(); \
    void bc_destroy_##hashname(bc_##hashname##_t* self); \
    uint8_t* bc_##hashname##_data(bc_##hashname##_t* self);

DECLARE_HASH_TYPE(hash_digest);
DECLARE_HASH_TYPE(half_hash);
DECLARE_HASH_TYPE(quarter_hash);
DECLARE_HASH_TYPE(long_hash);
DECLARE_HASH_TYPE(short_hash);
DECLARE_HASH_TYPE(mini_hash);

#undef DECLARE_HASH_TYPE

// You must use bc_destroy_hash_digest() to delete the result.
bc_hash_digest_t* bc_null_hash();

// Lists of common bitcoin hashes.

#ifdef __cplusplus
}
#endif

#endif

