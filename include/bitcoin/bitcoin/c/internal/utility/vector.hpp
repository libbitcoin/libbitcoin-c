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

extern "C" {

#define BC_DECLARE_VECTOR_STRUCT(typename, itemtype) \
    \
    struct bc_##typename##_t \
    { \
        typedef std::function<void (itemtype*)> deleter_func_type; \
        typedef std::unique_ptr<itemtype, deleter_func_type> uniqptr_type; \
        typedef std::vector<uniqptr_type> list_type; \
        list_type* obj; \
    };

#define BC_IMPLEMENT_VECTOR(typename, itemtype, delete_function) \
    \
    bc_##typename##_t* bc_create_##typename() \
    { \
        return new bc_##typename##_t{ new bc_##typename##_t::list_type }; \
    } \
    void bc_destroy_##typename(bc_##typename##_t* self) \
    { \
        delete self->obj; \
        delete self; \
    } \
    itemtype* bc_##typename##_at(bc_##typename##_t* self, size_t pos) \
    { \
        return self->obj->at(pos).get(); \
    } \
    const itemtype* bc_##typename##_const_at(const bc_##typename##_t* self, \
        size_t pos) \
    { \
        return self->obj->at(pos).get(); \
    } \
    size_t bc_##typename##_size(const bc_##typename##_t* self) \
    { \
        return self->obj->size(); \
    } \
    void bc_##typename##_clear(bc_##typename##_t* self) \
    { \
        self->obj->clear(); \
    } \
    void bc_##typename##_erase(bc_##typename##_t* self, size_t pos) \
    { \
        self->obj->erase(self->obj->begin() + pos); \
    } \
    void bc_##typename##_insert(bc_##typename##_t* self, \
        size_t pos, itemtype* obj) \
    { \
        bc_##typename##_t::uniqptr_type item(obj, delete_function); \
        self->obj->insert(self->obj->begin() + pos, std::move(item)); \
    } \
    void bc_##typename##_push_back(bc_##typename##_t* self, itemtype* obj) \
    { \
        bc_##typename##_t::uniqptr_type item(obj, delete_function); \
        self->obj->push_back(std::move(item)); \
    } \
    void bc_##typename##_resize(bc_##typename##_t* self, size_t count) \
    { \
        self->obj->resize(count); \
    }

}

#endif

