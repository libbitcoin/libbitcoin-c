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
void bc_destroy_hash_number(bc_hash_number_t* self)
{
    delete self->obj;
    delete self;
}

// Returns false if negative or overflowed.
bool bc_hash_number_set_compact(bc_hash_number_t* self, uint32_t compact)
{
    return self->obj->set_compact(compact);
}
uint32_t bc_hash_number_compact(const bc_hash_number_t* self)
{
    return self->obj->compact();
}
bc_hash_digest_t* bc_hash_number_hash(const bc_hash_number_t* self)
{
    return bc_create_hash_digest_Internal(self->obj->hash());
}

bc_hash_number_t* bc_hash_number_negate(const bc_hash_number_t* self)
{
    return new bc_hash_number_t{ new libbitcoin::hash_number(
        ~(*self->obj)) };
}

// int64_t resolves to this in Satoshi's GetNextWorkRequired()
void bc_hash_number_multiply(bc_hash_number_t* self, uint32_t value)
{
    *self->obj *= value;
}
void bc_hash_number_divide(bc_hash_number_t* self, uint32_t value)
{
    *self->obj /= value;
}
void bc_hash_number_shift_left(bc_hash_number_t* self, uint32_t shift)
{
    *self->obj <<= shift;
}

// Operators
void bc_hash_number_divide_HashNumber(bc_hash_number_t* self,
    const bc_hash_number_t* number_b)
{
    *self->obj /= *number_b->obj;
}
void bc_hash_number_add(bc_hash_number_t* self,
    const bc_hash_number_t* number_b)
{
    *self->obj += *number_b->obj;
}

bool bc_hash_number_greater_than(const bc_hash_number_t* self,
    const bc_hash_number_t* other)
{
    return *self->obj > *other->obj;
}
bool bc_hash_number_less_than_or_equals(const bc_hash_number_t* self,
    const bc_hash_number_t* other)
{
    return *self->obj <= *other->obj;
}
bool bc_hash_number_equals(const bc_hash_number_t* self, uint64_t value)
{
    return *self->obj == value;
}

} // extern C

