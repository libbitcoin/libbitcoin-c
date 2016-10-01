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
#include <bitcoin/bitcoin/c/internal/chain/chain_state.hpp>

#include <bitcoin/bitcoin/c/internal/chain/header.hpp>

extern "C" {

bc_chain_state_versions_t* bc_create_chain_state_versions(
    const uint8_t* versions, size_t size)
{
    return new bc_chain_state_versions_t{
        new libbitcoin::chain::chain_state::versions(
            versions, versions + size) };
}
// Destructor
void bc_destroy_chain_state_versions(bc_chain_state_versions_t* self)
{
    delete self->obj;
    delete self;
}
// Member functions
size_t bc_chain_state_versions__size(const bc_chain_state_versions_t* self)
{
    return self->obj->size();
}
uint8_t bc_chain_state_versions__at(const bc_chain_state_versions_t* self,
    size_t pos)
{
    return self->obj->at(pos);
}

void bc_destroy_chain_state(bc_chain_state_t* self)
{
    delete self->obj;
    delete self;
}

size_t bc_chain_state__next_height(const bc_chain_state_t* self)
{
    return self->obj->next_height();
}
uint32_t bc_chain_state__enabled_forks(const bc_chain_state_t* self)
{
    return self->obj->enabled_forks();
}
uint32_t bc_chain_state__minimum_version(const bc_chain_state_t* self)
{
    return self->obj->minimum_version();
}
uint32_t bc_chain_state__median_time_past(const bc_chain_state_t* self)
{
    return self->obj->median_time_past();
}
uint32_t bc_chain_state__work_required(const bc_chain_state_t* self)
{
    return self->obj->work_required();
}

void bc_chain_state__set_context(bc_chain_state_t* self,
    size_t height, const bc_chain_state_versions_t* history)
{
    return self->obj->set_context(height, *history->obj);
}

bool bc_chain_state__is_checkpoint_failure(
    const bc_chain_state_t* self, const bc_header_t* header)
{
    return self->obj->is_checkpoint_failure(*header->obj);
}

bool bc_chain_state__use_full_validation(const bc_chain_state_t* self)
{
    return self->obj->use_full_validation();
}

uint32_t bc_chain_state__sample_size(const bc_chain_state_t* self)
{
    return self->obj->sample_size;
}

} // extern C

