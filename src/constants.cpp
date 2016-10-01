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
#include <bitcoin/bitcoin/c/constants.h>

#include <bitcoin/bitcoin/constants.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash_number.hpp>

extern "C" {

const char* bc_user_agent()
{
    return BC_USER_AGENT;
}

// Generic constants.
int64_t bc_min_int64()
{
    return libbitcoin::min_int64;
}
int64_t bc_max_int64()
{
    return libbitcoin::max_int64;
}
int32_t bc_min_int32()
{
    return libbitcoin::min_int32;
}
int32_t bc_max_int32()
{
    return libbitcoin::max_int32;
}
uint64_t bc_max_uint64()
{
    return libbitcoin::max_uint64;
}
uint32_t bc_max_uint32()
{
    return libbitcoin::max_uint32;
}
uint16_t bc_max_uint16()
{
    return libbitcoin::max_uint16;
}
uint8_t bc_max_uint8()
{
    return libbitcoin::max_uint8;
}
uint64_t bc_max_size_t()
{
    return libbitcoin::max_size_t;
}
uint8_t bc_byte_bits()
{
    return libbitcoin::byte_bits;
}

// Consensus sentinels.

uint32_t bc_no_previous_output()
{
    return libbitcoin::no_previous_output;
}
uint32_t bc_max_input_sequence()
{
    return libbitcoin::max_input_sequence;
}

// Various consensus constants.

size_t bc_min_coinbase_size()
{
    return libbitcoin::min_coinbase_size;
}
size_t bc_max_coinbase_size()
{
    return libbitcoin::max_coinbase_size;
}
size_t bc_median_time_past_blocks()
{
    return libbitcoin::median_time_past_blocks;
}
size_t bc_max_block_size()
{
    return libbitcoin::max_block_size;
}
size_t bc_max_block_sigops()
{
    return libbitcoin::max_block_sigops;
}
size_t bc_reward_interval()
{
    return libbitcoin::reward_interval;
}
size_t bc_coinbase_maturity()
{
    return libbitcoin::coinbase_maturity;
}
size_t bc_time_stamp_future_hours()
{
    return libbitcoin::time_stamp_future_hours;
}
size_t bc_max_work_bits()
{
    return libbitcoin::max_work_bits;
}
size_t bc_locktime_threshold()
{
    return libbitcoin::locktime_threshold;
}

size_t bc_retargeting_factor()
{
    return libbitcoin::retargeting_factor;
}
size_t bc_target_spacing_seconds()
{
    return libbitcoin::target_spacing_seconds;
}
size_t bc_target_timespan_seconds()
{
    return libbitcoin::target_timespan_seconds;
}

// The target number of blocks for 2 weeks of work (2016 blocks).
size_t bc_retargeting_interval()
{
    return libbitcoin::retargeting_interval;
}

// The upper and lower bounds for the retargeting timespan.
size_t bc_timespan_lower_bound()
{
    return libbitcoin::timespan_lower_bound;
}
size_t bc_timespan_upper_bound()
{
    return libbitcoin::timespan_upper_bound;
}

// Fork constants.
//-----------------------------------------------------------------------------

// Consensus rule change activation and enforcement parameters.
size_t bc_bip65_version()
{
    return libbitcoin::bip65_version;
}
size_t bc_bip66_version()
{
    return libbitcoin::bip66_version;
}
size_t bc_bip34_version()
{
    return libbitcoin::bip34_version;
}
size_t bc_first_version()
{
    return libbitcoin::first_version;
}

// Testnet activation parameters.
size_t bc_testnet_active()
{
    return libbitcoin::testnet_active;
}
size_t bc_testnet_enforce()
{
    return libbitcoin::testnet_enforce;
}
size_t bc_testnet_sample()
{
    return libbitcoin::testnet_sample;
}

// Mainnet activation parameters.
size_t bc_mainnet_active()
{
    return libbitcoin::mainnet_active;
}
size_t bc_mainnet_enforce()
{
    return libbitcoin::mainnet_enforce;
}
size_t bc_mainnet_sample()
{
    return libbitcoin::mainnet_sample;
}

// Block 173805 is the first mainnet block after date-based activation.
// Block 514 is the first testnet block after date-based activation.
size_t bc_mainnet_bip16_activation_height()
{
    return libbitcoin::mainnet_bip16_activation_height;
}
size_t bc_testnet_bip16_activation_height()
{
    return libbitcoin::testnet_bip16_activation_height;
}

// github.com/bitcoin/bips/blob/master/bip-0030.mediawiki#specification
size_t bc_mainnet_bip30_exception_height1()
{
    return libbitcoin::mainnet_bip30_exception_height1;
}
size_t bc_mainnet_bip30_exception_height2()
{
    return libbitcoin::mainnet_bip30_exception_height2;
}
size_t bc_testnet_bip30_exception_height1()
{
    return libbitcoin::testnet_bip30_exception_height1;
}
size_t bc_testnet_bip30_exception_height2()
{
    return libbitcoin::testnet_bip30_exception_height2;
}

// Network protocol constants.
//-----------------------------------------------------------------------------

size_t bc_command_size()
{
    return libbitcoin::command_size;
}
size_t bc_max_inventory_count()
{
    return libbitcoin::max_inventory_count;
}

// Currency unit constants (uint64_t).
//-----------------------------------------------------------------------------

uint64_t bc_initial_block_reward()
{
    return libbitcoin::initial_block_reward;
}
uint64_t bc_satoshi_per_bitcoin()
{
    return libbitcoin::satoshi_per_bitcoin;
}

uint64_t bc_max_money()
{
    return libbitcoin::max_money();
}

} // extern C

