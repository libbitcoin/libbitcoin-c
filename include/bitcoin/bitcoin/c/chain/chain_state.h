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
#ifndef LIBBITCOIN_C_CHAIN_CHAIN_STATE_H
#define LIBBITCOIN_C_CHAIN_CHAIN_STATE_H

#include <bitcoin/bitcoin/c/machine/rule_fork.h>
#include <bitcoin/bitcoin/c/math/hash.h>

#ifdef __cplusplus
extern "C" {
#endif

// Forward declaration for bc_header_t;
typedef struct bc_header_t bc_header_t;

#define BC_CHAIN_STATE_UINT32_VECTOR(name) \
    BC_DECLARE_INT_VECTOR(chain_state_##name, uint32_t);

BC_CHAIN_STATE_UINT32_VECTOR(bitss)
BC_CHAIN_STATE_UINT32_VECTOR(versions)
BC_CHAIN_STATE_UINT32_VECTOR(timestamps)

#undef BC_CHAIN_STATE_UINT32_VECTOR

typedef struct bc_chain_state_t bc_chain_state_t;

/// Constructors
// TODO: need checkpoints
//bc_chain_state_t* bc_create_chain_state(bool testnet,
/// Destructors
void bc_destroy_chain_state(bc_chain_state_t* self);

/// Properties.
size_t bc_chain_state__height(const bc_chain_state_t* self);
uint32_t bc_chain_state__enabled_forks(const bc_chain_state_t* self);
uint32_t bc_chain_state__minimum_version(const bc_chain_state_t* self);
uint32_t bc_chain_state__median_time_past(const bc_chain_state_t* self);
uint32_t bc_chain_state__work_required(const bc_chain_state_t* self);

/// Construction with zero height or any empty array causes invalid state.
bool bc_chain_state__is_valid(const bc_chain_state_t* self);

/// Determine if the fork is set for this block.
bool bc_chain_state__is_enabled(const bc_chain_state_t* self,
    bc_rule_fork_t fork);

/// Determine if this block hash fails a checkpoint at this height.
bool bc_chain_state__is_checkpoint_conflict(
    const bc_chain_state_t* self, const bc_hash_digest_t* hash);

/// This block height is less than or equal to that of the top checkpoint.
bool bc_chain_state__is_under_checkpoint(const bc_chain_state_t* self);

#ifdef __cplusplus
}
#endif

#endif

