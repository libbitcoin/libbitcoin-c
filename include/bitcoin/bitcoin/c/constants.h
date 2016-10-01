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
#ifndef LIBBITCOIN_C_CONSTANTS_H
#define LIBBITCOIN_C_CONSTANTS_H

#include <stddef.h>
#include <stdint.h>
#include <bitcoin/bitcoin/c/math/hash_number.h>

#ifdef __cplusplus
extern "C" {
#endif

const char* bc_user_agent();

// Generic constants.
int64_t bc_min_int64();
int64_t bc_max_int64();
int32_t bc_min_int32();
int32_t bc_max_int32();
uint64_t bc_max_uint64();
uint32_t bc_max_uint32();
uint16_t bc_max_uint16();
uint8_t bc_max_uint8();
uint64_t bc_max_size_t();
uint8_t bc_byte_bits();

// Consensus sentinels.
//-----------------------------------------------------------------------------

uint32_t bc_no_previous_output();
uint32_t bc_max_input_sequence();

// Various consensus constants.
//-----------------------------------------------------------------------------

size_t bc_min_coinbase_size();
size_t bc_max_coinbase_size();
size_t bc_median_time_past_blocks();
size_t bc_max_block_size();
size_t bc_max_block_sigops();
size_t bc_reward_interval();
size_t bc_coinbase_maturity();
size_t bc_time_stamp_future_hours();
size_t bc_max_work_bits();
size_t bc_locktime_threshold();

// Timespan constants.
//-----------------------------------------------------------------------------

size_t bc_retargeting_factor();
size_t bc_target_spacing_seconds();
size_t bc_target_timespan_seconds();

// The target number of blocks for 2 weeks of work (2016 blocks).
size_t bc_retargeting_interval();

// The upper and lower bounds for the retargeting timespan.
size_t bc_timespan_lower_bound();
size_t bc_timespan_upper_bound();

// Fork constants.
//-----------------------------------------------------------------------------

// Consensus rule change activation and enforcement parameters.
size_t bc_bip65_version();
size_t bc_bip66_version();
size_t bc_bip34_version();
size_t bc_first_version();

// Testnet activation parameters.
size_t bc_testnet_active();
size_t bc_testnet_enforce();
size_t bc_testnet_sample();

// Mainnet activation parameters.
size_t bc_mainnet_active();
size_t bc_mainnet_enforce();
size_t bc_mainnet_sample();

// Block 173805 is the first mainnet block after date-based activation.
// Block 514 is the first testnet block after date-based activation.
size_t bc_mainnet_bip16_activation_height();
size_t bc_testnet_bip16_activation_height();

// github.com/bitcoin/bips/blob/master/bip-0030.mediawiki#specification
size_t bc_mainnet_bip30_exception_height1();
size_t bc_mainnet_bip30_exception_height2();
size_t bc_testnet_bip30_exception_height1();
size_t bc_testnet_bip30_exception_height2();

// Network protocol constants.
//-----------------------------------------------------------------------------

size_t bc_command_size();
size_t bc_max_inventory_count();

// Currency unit constants (uint64_t).
//-----------------------------------------------------------------------------

uint64_t bc_initial_block_reward();
uint64_t bc_satoshi_per_bitcoin();

uint64_t bc_max_money();

#ifdef __cplusplus
}
#endif

#endif

