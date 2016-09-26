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
#include <bitcoin/bitcoin/c/chain/spend.h>
#include <bitcoin/bitcoin/c/internal/chain/spend.hpp>

#include <bitcoin/bitcoin/c/internal/chain/point.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>

/*
BC_IMPLEMENT_VECTOR(spend_info_list, bc_spend_info_t,
    bc_destroy_spend_info, libbitcoin::chain::spend_info::list);
*/

extern "C" {

/*
// Constructor
bc_spend_t* bc_create_spend()
{
    return new bc_spend_t{ new libbitcoin::chain::spend };
}
// Destructor
void bc_destroy_spend(bc_spend_t* self)
{
    delete self->obj;
    delete self;
}
// Member variables
bool bc_spend_valid(const bc_spend_t* self)
{
    return self->obj->valid;
}
void bc_spend_set_valid(bc_spend_t* self, bool valid)
{
    self->obj->valid = valid;
}
uint32_t bc_spend_index(const bc_spend_t* self)
{
    return self->obj->index;
}
void bc_spend_set_index(bc_spend_t* self, uint32_t index)
{
    self->obj->index = index;
}
bc_hash_digest_t* bc_spend_hash(const bc_spend_t* self)
{
    return bc_create_hash_digest_Internal(self->obj->hash);
}
void bc_spend_set_hash(bc_spend_t* self, const bc_hash_digest_t* hash)
{
    self->obj->hash = *hash->obj;
}

// Constructor
bc_spend_info_t* bc_create_spend_info()
{
    return new bc_spend_info_t{ new libbitcoin::chain::spend_info };
}
// Destructor
void bc_destroy_spend_info(bc_spend_info_t* self)
{
    delete self->obj;
    delete self;
}
// Member variables
bc_input_point_t* bc_spend_info_point(const bc_spend_info_t* self)
{
    return new bc_input_point_t{ new libbitcoin::chain::input_point(
        self->obj->point) };
}
void bc_spend_info_set_point(bc_spend_info_t* self,
    const bc_input_point_t* point)
{
    self->obj->point = *point->obj;
}
bc_output_point_t* bc_spend_info_previous_output(const bc_spend_info_t* self)
{
    return new bc_output_point_t{ new libbitcoin::chain::output_point(
        self->obj->previous_output) };
}
void bc_spend_info_set_previous_output(bc_spend_info_t* self,
    const bc_output_point_t* previous_output)
{
    self->obj->previous_output = *previous_output->obj;
}
*/

} // extern C

