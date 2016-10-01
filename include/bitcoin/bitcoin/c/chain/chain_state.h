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

#include <bitcoin/bitcoin/c/chain/header.h>

#ifdef __cplusplus
extern "C" {
#endif

// Immutable vector of uint32_t
typedef struct bc_chain_state_versions_t bc_chain_state_versions_t;
// Constructor
bc_chain_state_versions_t* bc_create_chain_state_versions(
    const uint8_t* versions, size_t size);
// Destructor
void bc_destroy_chain_state_versions(bc_chain_state_versions_t* self);
// Member functions
size_t bc_chain_state_versions__size(const bc_chain_state_versions_t* self);
uint8_t bc_chain_state_versions__at(const bc_chain_state_versions_t* self,
    size_t pos);

typedef struct bc_chain_state_t bc_chain_state_t;

/// Constructors
// TODO: need checkpoints
//bc_chain_state_t* bc_create_chain_state(bool testnet,
/// Destructors
void bc_destroy_chain_state(bc_chain_state_t* self);

/// Properties.
size_t bc_chain_state__next_height(const bc_chain_state_t* self);
uint32_t bc_chain_state__enabled_forks(const bc_chain_state_t* self);
uint32_t bc_chain_state__minimum_version(const bc_chain_state_t* self);
uint32_t bc_chain_state__median_time_past(const bc_chain_state_t* self);
uint32_t bc_chain_state__work_required(const bc_chain_state_t* self);

/// Initialize enabled forks and minimum version for the given context.
void bc_chain_state__set_context(bc_chain_state_t* self,
    size_t height, const bc_chain_state_versions_t* history);

// TODO: need rule_fork in opcode.h
/// Determine it the flag is set in the active_forks member.
//bool bc_chain_state__is_enabled(rule_fork flag) const;

// TODO: need rule_fork in opcode.h
/// Determine it the flag is set and enabled for the given block's version.
//bool bc_chain_state__is_enabled(const header& header, rule_fork flag) const;

/// Determine if the block fails a checkpoint at next_height.
bool bc_chain_state__is_checkpoint_failure(
    const bc_chain_state_t* self, const bc_header_t* header);

/// This height requires full validation due to no checkpoint coverage.
bool bc_chain_state__use_full_validation(const bc_chain_state_t* self);

/// Use to initialize the history collection and parameterize the query.
uint32_t bc_chain_state__sample_size(const bc_chain_state_t* self);

#ifdef __cplusplus
}
#endif

#endif

