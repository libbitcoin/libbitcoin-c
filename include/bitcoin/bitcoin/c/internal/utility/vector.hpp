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

#define BC_DECLARE_VECTOR_STRUCT(typename, itemtype) \
    \
    struct bc_##typename##_t \
    { \
        typedef std::function<void (itemtype*)> deleter_func_type; \
        typedef std::unique_ptr<itemtype, deleter_func_type> uniqptr_type; \
        typedef std::vector<uniqptr_type> list_type; \
        list_type* obj; \
    };

#define BC_IMPLEMENT_VECTOR_METHODS(typename, itemtype, delete_function) \
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
    itemtype* bc_##typename##__at(bc_##typename##_t* self, size_t pos) \
    { \
        return self->obj->at(pos).get(); \
    } \
    const itemtype* bc_##typename##__const_at(const bc_##typename##_t* self, \
        size_t pos) \
    { \
        return self->obj->at(pos).get(); \
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
        size_t pos, itemtype** obj) \
    { \
        bc_##typename##_t::uniqptr_type item(*obj, delete_function); \
        self->obj->insert(self->obj->begin() + pos, std::move(item)); \
        *obj = NULL; \
    } \
    void bc_##typename##__push_back(bc_##typename##_t* self, itemtype** obj) \
    { \
        bc_##typename##_t::uniqptr_type item(*obj, delete_function); \
        self->obj->push_back(std::move(item)); \
        *obj = NULL; \
    } \
    void bc_##typename##__insert_noconsume(bc_##typename##_t* self, \
        size_t pos, itemtype* obj) \
    { \
        bc_##typename##_t::uniqptr_type item(obj, delete_function); \
        self->obj->insert(self->obj->begin() + pos, std::move(item)); \
    } \
    void bc_##typename##__push_back_noconsume(bc_##typename##_t* self, \
        itemtype* obj) \
    { \
        bc_##typename##_t::uniqptr_type item(obj, delete_function); \
        self->obj->push_back(std::move(item)); \
    } \
    void bc_##typename##__resize(bc_##typename##_t* self, size_t count) \
    { \
        self->obj->resize(count); \
    }

// C++ convenience functions
template <typename ResultType, typename WrapperType,
    typename WrapperSizeFunc, typename WrapperAtFunc>
ResultType bc_vector_from_ctype(const WrapperType* c_vector,
    WrapperSizeFunc size_func, WrapperAtFunc at_func);

template <typename WrapperType, typename ItemType, typename VectorType,
    typename CreateFunc, typename PushFunc>
WrapperType* bc_vector_to_ctype(const VectorType& vector_obj,
    CreateFunc create_func, PushFunc push_func);

#define BC_DECLARE_VECTOR_CONVERSION_FUNCTIONS( \
    wrappername, originaltype) \
    \
    originaltype bc_##wrappername##_from_ctype( \
        const bc_##wrappername##_t* stack); \
    \
    bc_##wrappername##_t* bc_##wrappername##_to_ctype( \
        const originaltype& stack);

#define BC_IMPLEMENT_VECTOR_CONVERSION_FUNCTIONS( \
    wrappername, itemtype, originaltype) \
    \
    originaltype bc_##wrappername##_from_ctype( \
        const bc_##wrappername##_t* stack) \
    { \
        return bc_vector_from_ctype< \
            originaltype, bc_##wrappername##_t>( \
                stack, \
                bc_##wrappername##__size, \
                bc_##wrappername##__const_at); \
    } \
    \
    bc_##wrappername##_t* bc_##wrappername##_to_ctype( \
        const originaltype& stack) \
    { \
        return bc_vector_to_ctype<bc_##wrappername##_t, itemtype>( \
                stack, \
                bc_create_##wrappername, \
                bc_##wrappername##__push_back); \
    }

#define BC_DECLARE_VECTOR_INTERNAL( \
    typename, itemtype, originaltype) \
    \
    extern "C" { \
        BC_DECLARE_VECTOR_STRUCT(typename, itemtype); \
    } \
    BC_DECLARE_VECTOR_CONVERSION_FUNCTIONS(typename, originaltype);

#define BC_IMPLEMENT_VECTOR( \
    typename, itemtype, delete_function, originaltype) \
    \
    extern "C" { \
        BC_IMPLEMENT_VECTOR_METHODS(typename, itemtype, delete_function); \
    } \
    BC_IMPLEMENT_VECTOR_CONVERSION_FUNCTIONS( \
        typename, itemtype, originaltype);

#include <bitcoin/bitcoin/c/internal/impl/utility/vector.ipp>

#endif

