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
#ifndef LIBBITCOIN_C_INTERNAL_UTILITY_VECTOR_HPP
#define LIBBITCOIN_C_INTERNAL_UTILITY_VECTOR_HPP

#include <functional>
#include <memory>
#include <vector>

#define BC_IMPLEMENT_VECTOR(typename, itemtype, delete_function, list_type) \
    \
    bc_##typename##_t* bc_create_##typename() \
    { \
        return new bc_##typename##_t{ new list_type, true }; \
    } \
    void bc_destroy_##typename(bc_##typename##_t* self) \
    { \
        if (self->delete_obj) \
            delete self->obj; \
        delete self; \
    } \
    itemtype* bc_##typename##__at(bc_##typename##_t* self, size_t pos) \
    { \
        return new itemtype{ &self->obj->at(pos), false }; \
    } \
    const itemtype* bc_##typename##__const_at(const bc_##typename##_t* self, \
        size_t pos) \
    { \
        return new itemtype{ &self->obj->at(pos), false }; \
    } \
    size_t bc_##typename##__size(const bc_##typename##_t* self) \
    { \
        return self->obj->size(); \
    } \
    bool bc_##typename##__empty(const bc_##typename##_t* self) \
    { \
        return self->obj->empty(); \
    } \
    void bc_##typename##__clear(bc_##typename##_t* self) \
    { \
        self->obj->clear(); \
    } \
    void bc_##typename##__erase(bc_##typename##_t* self, size_t pos) \
    { \
        self->obj->erase(self->obj->begin() + pos); \
    } \
    void bc_##typename##__insert(bc_##typename##_t* self, \
        size_t pos, itemtype* obj) \
    { \
        self->obj->insert(self->obj->begin() + pos, *obj->obj); \
    } \
    void bc_##typename##__push_back(bc_##typename##_t* self, itemtype* obj) \
    { \
        self->obj->push_back(*obj->obj); \
    } \
    void bc_##typename##__insert_consume(bc_##typename##_t* self, \
        size_t pos, itemtype** obj) \
    { \
        bc_##typename##__insert(self, pos, *obj); \
        delete_function(*obj); \
        *obj = nullptr; \
    } \
    void bc_##typename##__push_back_consume(bc_##typename##_t* self, \
        itemtype** obj) \
    { \
        bc_##typename##__push_back(self, *obj); \
        delete_function(*obj); \
        *obj = nullptr; \
    } \
    void bc_##typename##__resize(bc_##typename##_t* self, size_t count) \
    { \
        self->obj->resize(count); \
    } \
    \
    bc_##typename##_t* bc_create_##typename##_Internal( \
        const list_type& value) \
    { \
        return new bc_##typename##_t{ new list_type(value), true }; \
    }

#define BC_IMPLEMENT_INT_VECTOR(typename, itemtype, list_type) \
    \
    bc_##typename##_t* bc_create_##typename() \
    { \
        return new bc_##typename##_t{ new list_type, true }; \
    } \
    void bc_destroy_##typename(bc_##typename##_t* self) \
    { \
        if (self->delete_obj) \
            delete self->obj; \
        delete self; \
    } \
    itemtype bc_##typename##__at(bc_##typename##_t* self, size_t pos) \
    { \
        return self->obj->at(pos); \
    } \
    size_t bc_##typename##__size(const bc_##typename##_t* self) \
    { \
        return self->obj->size(); \
    } \
    bool bc_##typename##__empty(const bc_##typename##_t* self) \
    { \
        return self->obj->empty(); \
    } \
    void bc_##typename##__clear(bc_##typename##_t* self) \
    { \
        self->obj->clear(); \
    } \
    void bc_##typename##__erase(bc_##typename##_t* self, size_t pos) \
    { \
        self->obj->erase(self->obj->begin() + pos); \
    } \
    void bc_##typename##__insert(bc_##typename##_t* self, \
        size_t pos, itemtype obj) \
    { \
        self->obj->insert(self->obj->begin() + pos, obj); \
    } \
    void bc_##typename##__push_back(bc_##typename##_t* self, itemtype obj) \
    { \
        self->obj->push_back(obj); \
    } \
    void bc_##typename##__resize(bc_##typename##_t* self, size_t count) \
    { \
        self->obj->resize(count); \
    } \
    \
    bc_##typename##_t* bc_create_##typename##_Internal( \
        const list_type& value) \
    { \
        return new bc_##typename##_t{ new list_type(value), true }; \
    }

#endif

