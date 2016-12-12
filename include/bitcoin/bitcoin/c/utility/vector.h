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
    /*****Do not delete the objects returned by these accessors.*****/ \
    itemtype* bc_##typename##__at(bc_##typename##_t* self, size_t pos); \
    const itemtype* bc_##typename##__const_at(const bc_##typename##_t* self, \
        size_t pos); \
    /****************************************************************/ \
    size_t bc_##typename##__size(const bc_##typename##_t* self); \
    bool bc_##typename##__empty(const bc_##typename##_t* self); \
    void bc_##typename##__clear(bc_##typename##_t* self); \
    void bc_##typename##__erase(bc_##typename##_t* self, size_t pos); \
    void bc_##typename##__insert(bc_##typename##_t* self, \
        size_t pos, itemtype* obj); \
    void bc_##typename##__push_back(bc_##typename##_t* self, itemtype* obj); \
    /* Methods that don't try to consume the passed pointer, but
       the semantics remain the same as the normal push_back() */ \
    void bc_##typename##__insert_consume(bc_##typename##_t* self, \
        size_t pos, itemtype** obj); \
    void bc_##typename##__push_back_consume(bc_##typename##_t* self, \
        itemtype** obj); \
    void bc_##typename##__resize(bc_##typename##_t* self, size_t count);

#define BC_DECLARE_INT_VECTOR(typename, itemtype) \
    typedef struct bc_##typename##_t bc_##typename##_t; \
    bc_##typename##_t* bc_create_##typename(); \
    void bc_destroy_##typename(bc_##typename##_t* self); \
    itemtype bc_##typename##__at(bc_##typename##_t* self, size_t pos); \
    size_t bc_##typename##__size(const bc_##typename##_t* self); \
    bool bc_##typename##__empty(const bc_##typename##_t* self); \
    void bc_##typename##__clear(bc_##typename##_t* self); \
    void bc_##typename##__erase(bc_##typename##_t* self, size_t pos); \
    void bc_##typename##__insert(bc_##typename##_t* self, \
        size_t pos, itemtype obj); \
    void bc_##typename##__push_back(bc_##typename##_t* self, itemtype obj); \
    void bc_##typename##__resize(bc_##typename##_t* self, size_t count);

#ifdef __cplusplus
}
#endif

#endif

