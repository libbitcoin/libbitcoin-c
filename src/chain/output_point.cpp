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
#include <bitcoin/bitcoin/c/chain/output_point.h>
#include <bitcoin/bitcoin/c/internal/chain/output_point.hpp>

#include <bitcoin/bitcoin/c/internal/chain/output.hpp>
#include <bitcoin/bitcoin/c/internal/chain/point.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/utility/vector.hpp>

extern "C" {

BC_IMPLEMENT_VECTOR(output_info_list, bc_output_info_t,
    bc_destroy_output_info, libbitcoin::chain::output_info::list);

uint64_t bc_output_point__not_coinbase()
{
    return libbitcoin::chain::output_point::not_coinbase;
}

bc_output_point_t* bc_create_output_point()
{
    return new bc_output_point_t{ new libbitcoin::chain::output_point, true };
}
bc_output_point_t* bc_create_output_point_copy(const bc_output_point_t* other)
{
    return new bc_output_point_t{ new libbitcoin::chain::output_point(
        *other->obj), true };
}
bc_output_point_t* bc_create_output_point_Point(const bc_point_t* value)
{
    return new bc_output_point_t{ new libbitcoin::chain::output_point(
        *value->obj), true };
}
bc_output_point_t* bc_create_output_point_Tuple(
    const bc_hash_digest_t* hash, uint32_t index)
{
    return new bc_output_point_t{ new libbitcoin::chain::output_point(
        *hash->obj, index), true };
}

void bc_destroy_output_point(bc_output_point_t* self)
{
    if (self->delete_obj)
        delete self->obj;
    delete self;
}

bool bc_output_point__equals(const bc_output_point_t* self,
    const bc_output_point_t* other)
{
    return *self->obj == *other->obj;
}
bool bc_output_point__not_equals(const bc_output_point_t* self,
    const bc_output_point_t* other)
{
    return *self->obj != *other->obj;
}

bc_point_t* bc_output_point__point_Base(bc_output_point_t* self)
{
    return new bc_point_t{
        static_cast<libbitcoin::chain::point*>(self->obj), false };
}

void bc_output_point__reset(bc_output_point_t* self)
{
    self->obj->reset();
}

bool bc_output_point__is_cached(const bc_output_point_t* self)
{
    return self->obj->is_cached();
}

bool bc_output_point__is_mature(const bc_output_point_t* self,
    size_t target_height)
{
    return self->obj->is_mature(target_height);
}

bool bc_output_point__spent(const bc_output_point_t* self)
{
    return self->obj->spent;
}
void bc_output_point__set_spent(bc_output_point_t* self, bool spent)
{
    self->obj->spent = spent;
}

bool bc_output_point__confirmed(const bc_output_point_t* self)
{
    return self->obj->confirmed;
}
void bc_output_point__set_confirmed(bc_output_point_t* self, bool confirmed)
{
    self->obj->confirmed = confirmed;
}

size_t bc_output_point__height(const bc_output_point_t* self)
{
    return self->obj->height;
}
void bc_output_point__set_height(bc_output_point_t* self, size_t height)
{
    self->obj->height = height;
}

bc_output_t* bc_output_point__cache(const bc_output_point_t* self)
{
    return new bc_output_t{ &self->obj->cache, false };
}
void bc_output_point__set_cache(bc_output_point_t* self,
    const bc_output_t* cache)
{
    self->obj->cache = *cache->obj;
}

bc_points_info_t* bc_create_points_info()
{
    return new bc_points_info_t{ new libbitcoin::chain::points_info, true };
}
void bc_destroy_points_info(bc_points_info_t* self)
{
    if (self->delete_obj)
        delete self->obj;
    delete self;
}
bc_chain_point_list_t* bc_points_info__points(const bc_points_info_t* self)
{
    return new bc_chain_point_list_t{ &self->obj->points, false };
}
void bc_points_info__set_points(bc_points_info_t* self,
    const bc_chain_point_list_t* points)
{
    self->obj->points = *points->obj;
}
uint64_t bc_points_info__change(const bc_points_info_t* self)
{
    return self->obj->change;
}
void bc_points_info__set_change(bc_points_info_t* self, uint64_t change)
{
    self->obj->change = change;
}

bc_output_info_t* bc_create_output_info()
{
    return new bc_output_info_t{ new libbitcoin::chain::output_info, true };
}
void bc_destroy_output_info(bc_output_info_t* self)
{
    if (self->delete_obj)
        delete self->obj;
    delete self;
}
bc_output_point_t* bc_output_info__point(const bc_output_info_t* self)
{
    return new bc_output_point_t{ &self->obj->point, false };
}
void bc_output_info__set_point(bc_output_info_t* self,
    const bc_output_point_t* point)
{
    self->obj->point = *point->obj;
}
uint64_t bc_output_info__value(const bc_output_info_t* self)
{
    return self->obj->value;
}
void bc_output_info__set_value(bc_output_info_t* self, uint64_t value)
{
    self->obj->value = value;
}

} // extern C

