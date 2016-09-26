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
#include <bitcoin/bitcoin/c/math/hash_number.h>
#include <bitcoin/bitcoin/c/internal/math/hash_number.hpp>

#include <bitcoin/bitcoin/math/hash_number.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>

extern "C" {

bc_hash_number_t* bc_create_hash_number()
{
    return new bc_hash_number_t{ new libbitcoin::hash_number };
}
bc_hash_number_t* bc_create_hash_number_Value(uint64_t value)
{
    return new bc_hash_number_t{ new libbitcoin::hash_number(value) };
}
bc_hash_number_t* bc_create_hash_number_Hash(const bc_hash_digest_t* value)
{
    return new bc_hash_number_t{ new libbitcoin::hash_number(*value->obj) };
}
void bc_destroy_hash_number(bc_hash_number_t* self)
{
    delete self->obj;
    delete self;
}

/// Properties.
bc_hash_digest_t* bc_hash_number__hash(const bc_hash_number_t* self)
{
    return bc_create_hash_digest_Internal(self->obj->hash());
}
bool bc_hash_number__set_compact(bc_hash_number_t* self, uint32_t compact)
{
    return self->obj->set_compact(compact);
}
uint32_t bc_hash_number__compact(const bc_hash_number_t* self)
{
    return self->obj->compact();
}

/// Copy Operators.
bc_hash_number_t* bc_hash_number__negate(const bc_hash_number_t* self)
{
    return new bc_hash_number_t{ new libbitcoin::hash_number(
        ~(*self->obj)) };
}

/// Change Operators.
void bc_hash_number__shift_left(bc_hash_number_t* self, uint32_t value)
{
    *self->obj <<= value;
}
void bc_hash_number__multiply(bc_hash_number_t* self, uint32_t value)
{
    *self->obj *= value;
}
void bc_hash_number__divide(bc_hash_number_t* self, uint32_t value)
{
    *self->obj /= value;
}
void bc_hash_number__divide_HashNumber(bc_hash_number_t* self,
    const bc_hash_number_t* value)
{
    *self->obj /= *value->obj;
}
void bc_hash_number__add(bc_hash_number_t* self,
    const bc_hash_number_t* value)
{
    *self->obj += *value->obj;
}

/// Comparison Operators.
bool bc_hash_number__equals(const bc_hash_number_t* self, uint64_t value)
{
    return *self->obj == value;
}
bool bc_hash_number__not_equals(const bc_hash_number_t* self, uint64_t value)
{
    return *self->obj != value;
}
bool bc_hash_number__greater_than(const bc_hash_number_t* self,
    const bc_hash_number_t* value)
{
    return *self->obj > *value->obj;
}
bool bc_hash_number__less_than(const bc_hash_number_t* self,
    const bc_hash_number_t* value)
{
    return *self->obj < *value->obj;
}
bool bc_hash_number__greater_than_or_equals(const bc_hash_number_t* self,
    const bc_hash_number_t* value)
{
    return *self->obj >= *value->obj;
}
bool bc_hash_number__less_than_or_equals(const bc_hash_number_t* self,
    const bc_hash_number_t* value)
{
    return *self->obj <= *value->obj;
}

} // extern C

