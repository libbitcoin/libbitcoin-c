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
#include <bitcoin/bitcoin/c/chain/point_iterator.h>
#include <bitcoin/bitcoin/c/internal/chain/point_iterator.hpp>

#include <bitcoin/bitcoin/c/internal/chain/point.hpp>

extern "C" {

// Constructors
bc_point_iterator_t* bc_create_point_iterator(const bc_point_t* value)
{
    return new bc_point_iterator_t{ new libbitcoin::chain::point_iterator(
        *value->obj) };
}
bc_point_iterator_t* bc_create_point_iterator_End(
    const bc_point_t* value, bool end)
{
    return new bc_point_iterator_t{ new libbitcoin::chain::point_iterator(
        *value->obj, end) };
}
bc_point_iterator_t* bc_create_point_iterator_Offset(
    const bc_point_t* value, uint8_t offset)
{
    return new bc_point_iterator_t{ new libbitcoin::chain::point_iterator(
        *value->obj, offset) };
}
// Destructor
void bc_destroy_point_iterator(bc_point_iterator_t* self)
{
    delete self->obj;
    delete self;
}

// Operators
bool bc_point_iterator__is_valid(const bc_point_iterator_t* self)
{
    return static_cast<bool>(*self->obj);
}
uint8_t bc_point_iterator__access(const bc_point_iterator_t* self)
{
    return *(*self->obj);
}
bool bc_point_iterator__equals(
    const bc_point_iterator_t* self, const bc_point_iterator_t* other)
{
    return *self->obj == *other->obj;
}
bool bc_point_iterator__not_equals(
    const bc_point_iterator_t* self, const bc_point_iterator_t* other)
{
    return *self->obj != *other->obj;
}
void bc_point_iterator__increment(bc_point_iterator_t* self)
{
    ++(*self->obj);
}
void bc_point_iterator__decrement(bc_point_iterator_t* self)
{
    --(*self->obj);
}

} // extern C

