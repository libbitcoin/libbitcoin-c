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
#ifndef LIBBITCOIN_C_INTERNAL_UTILITY_VECTOR_IPP
#define LIBBITCOIN_C_INTERNAL_UTILITY_VECTOR_IPP

// C++ convenience functions
template <typename ResultType, typename WrapperType,
    typename WrapperSizeFunc, typename WrapperAtFunc>
ResultType bc_vector_from_ctype(const WrapperType* c_vector,
    WrapperSizeFunc size_func, WrapperAtFunc at_func)
{
    ResultType result;
    for (size_t i = 0; i < size_func(c_vector); ++i)
    {
        const auto obj = at_func(c_vector, i)->obj;
        result.push_back(typename ResultType::value_type(*obj));
    }
    return result;
}

template <typename WrapperType, typename ItemType, typename VectorType,
    typename CreateFunc, typename PushFunc>
WrapperType* bc_vector_to_ctype(const VectorType& vector_obj,
    CreateFunc create_func, PushFunc push_func)
{
    WrapperType* result = create_func();
    for (const auto item: vector_obj)
    {
        ItemType* c_item = new ItemType{
            new typename VectorType::value_type(item) };
        push_func(result, &c_item);
    }
    return result;
}

#endif

