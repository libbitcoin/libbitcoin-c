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
#include <bitcoin/bitcoin/c/chain/point.h>
#include <bitcoin/bitcoin/c/internal/chain/point.hpp>

#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>
#include <bitcoin/bitcoin/c/internal/utility/vector.hpp>

BC_IMPLEMENT_VECTOR(chain_point_list, bc_point_t, bc_destroy_point,
    libbitcoin::chain::point::list);

extern "C" {

// Constructor
bc_point_indexes_t* bc_create_point_indexes(
    const uint32_t* indexes, size_t size)
{
    return new bc_point_indexes_t{ new libbitcoin::chain::point::indexes(
        indexes, indexes + size) };
}
// Destructor
void bc_destroy_point_indexes(bc_point_indexes_t* self)
{
    delete self->obj;
    delete self;
}
// Member functions
size_t bc_point_indexes_size(const bc_point_indexes_t* self)
{
    return self->obj->size();
}
uint32_t bc_point_indexes_at(const bc_point_indexes_t* self, size_t pos)
{
    return self->obj->at(pos);
}

// Static functions
bc_point_t* bc_point_factory_from_data(const bc_data_chunk_t* data)
{
    return new bc_point_t{ new libbitcoin::chain::point(
        libbitcoin::chain::point::factory_from_data(*data->obj)) };
}
uint64_t bc_point_satoshi_fixed_size()
{
    return libbitcoin::chain::point::satoshi_fixed_size();
}
// Constructor
bc_point_t* bc_create_point()
{
    return new bc_point_t{ new libbitcoin::chain::point };
}
// Destructor
void bc_destroy_point(bc_point_t* self)
{
    delete self->obj;
    delete self;
}
// Member functions
uint64_t bc_point_checksum(const bc_point_t* self)
{
    return self->obj->checksum();
}
bool bc_point_is_null(const bc_point_t* self)
{
    return self->obj->is_null();
}
bool bc_point_from_data(bc_point_t* self, const bc_data_chunk_t* data)
{
    return self->obj->from_data(*data->obj);
}
bc_data_chunk_t* bc_point_to_data(const bc_point_t* self)
{
    return bc_create_data_chunk_Internal(self->obj->to_data());
}
bc_string_t* bc_point_to_string(const bc_point_t* self)
{
    return bc_create_string_StdString(self->obj->to_string());
}
bool bc_point_is_valid(const bc_point_t* self)
{
    return self->obj->is_valid();
}
void bc_point_reset(bc_point_t* self)
{
    self->obj->reset();
}
uint64_t bc_point_serialized_size(const bc_point_t* self)
{
    return self->obj->serialized_size();
}
// Member variables
bc_hash_digest_t* bc_point_hash(const bc_point_t* self)
{
    return bc_create_hash_digest_Internal(self->obj->hash);
}
void bc_point_set_hash(bc_point_t* self, const bc_hash_digest_t* hash)
{
    self->obj->hash = *hash->obj;
}
uint32_t bc_point_index(const bc_point_t* self)
{
    return self->obj->index;
}
void bc_point_set_index(bc_point_t* self, uint32_t index)
{
    self->obj->index = index;
}
// Operators
bool bc_point_equals(const bc_point_t* left, const bc_point_t* right)
{
    return *left->obj == *right->obj;
}
bool bc_point_not_equals(const bc_point_t* left, const bc_point_t* right)
{
    return *left->obj != *right->obj;
}

bc_points_info_t* bc_create_points_info()
{
    return new bc_points_info_t{ new libbitcoin::chain::points_info };
}
void bc_destroy_points_info(bc_points_info_t* self)
{
    delete self->obj;
    delete self;
}
bc_chain_point_list_t* bc_points_info_points(const bc_points_info_t* self)
{
    return bc_chain_point_list_to_ctype(self->obj->points);
}
void bc_points_info_set_points(bc_points_info_t* self,
    const bc_chain_point_list_t* points)
{
    self->obj->points = bc_chain_point_list_from_ctype(points);
}
uint64_t bc_points_info_change(const bc_points_info_t* self)
{
    return self->obj->change;
}
void bc_points_info_set_change(bc_points_info_t* self, uint64_t change)
{
    self->obj->change = change;
}

} // extern C

