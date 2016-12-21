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
#include <bitcoin/bitcoin/c/internal/machine/rule_fork.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/utility/vector.hpp>

extern "C" {

#define BC_CHAIN_STATE_UINT32_VECTOR(name) \
    BC_IMPLEMENT_INT_VECTOR(chain_state_##name, uint32_t, \
        libbitcoin::chain::chain_state::name)

BC_CHAIN_STATE_UINT32_VECTOR(bitss)
BC_CHAIN_STATE_UINT32_VECTOR(versions)
BC_CHAIN_STATE_UINT32_VECTOR(timestamps)

#undef BC_CHAIN_STATE_UINT32_VECTOR

void bc_destroy_chain_state(bc_chain_state_t* self)
{
    delete self->obj;
    delete self;
}

size_t bc_chain_state__height(const bc_chain_state_t* self)
{
    return self->obj->height();
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

bool bc_chain_state__is_valid(const bc_chain_state_t* self)
{
    return self->obj->is_valid();
}

bool bc_chain_state__is_enabled(const bc_chain_state_t* self,
    bc_rule_fork_t fork)
{
    const auto fork_conv = bc_rule_fork_from_ctype(fork);
    return self->obj->is_enabled(fork_conv);
}

bool bc_chain_state__is_checkpoint_conflict(
    const bc_chain_state_t* self, const bc_hash_digest_t* hash)
{
    return self->obj->is_checkpoint_conflict(*hash->obj);
}

bool bc_chain_state__is_under_checkpoint(const bc_chain_state_t* self)
{
    return self->obj->is_under_checkpoint();
}

} // extern C

