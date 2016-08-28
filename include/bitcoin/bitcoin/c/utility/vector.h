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
#ifndef LIBBITCOIN_C_UTILITY_VECTOR_H
#define LIBBITCOIN_C_UTILITY_VECTOR_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BC_DECLARE_VECTOR(typename, itemtype) \
    typedef struct bc_##typename##_t bc_##typename##_t; \
    bc_##typename##_t* bc_create_##typename(); \
    void bc_destroy_##typename(bc_##typename##_t* self); \
    itemtype* bc_##typename##_at(bc_##typename##_t* self, size_t pos); \
    const itemtype* bc_##typename##_const_at(const bc_##typename##_t* self, \
        size_t pos); \
    size_t bc_##typename##_size(const bc_##typename##_t* self); \
    void bc_##typename##_clear(bc_##typename##_t* self); \
    void bc_##typename##_erase(bc_##typename##_t* self, size_t pos); \
    void bc_##typename##_insert(bc_##typename##_t* self, \
        size_t pos, itemtype** obj); \
    void bc_##typename##_push_back(bc_##typename##_t* self, itemtype** obj); \
    void bc_##typename##_resize(bc_##typename##_t* self, size_t count);

#ifdef __cplusplus
}
#endif

#endif

