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

size_t bc_command_size()
{
    return libbitcoin::command_size;
}

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

// Consensus constants.
uint32_t bc_reward_interval()
{
    return libbitcoin::reward_interval;
}
uint32_t bc_coinbase_maturity()
{
    return libbitcoin::coinbase_maturity;
}
uint32_t bc_initial_block_reward()
{
    return libbitcoin::initial_block_reward;
}
uint32_t bc_max_work_bits()
{
    return libbitcoin::max_work_bits;
}
uint32_t bc_max_input_sequence()
{
    return libbitcoin::max_input_sequence;
}

// Ignore constexpr functions

// Threshold for nLockTime: below this value it is interpreted as block number,
// otherwise as UNIX timestamp. [Tue Nov 5 00:53:20 1985 UTC]
uint32_t bc_locktime_threshold()
{
    return libbitcoin::locktime_threshold;
}

uint64_t bc_max_money()
{
    return libbitcoin::max_money();
}

uint32_t bc_no_timestamp()
{
    return libbitcoin::no_timestamp;
}
uint16_t bc_unspecified_ip_port()
{
    return libbitcoin::unspecified_ip_port;
}

bc_hash_number_t* max_target()
{
    return new bc_hash_number_t{ new libbitcoin::hash_number(
        libbitcoin::max_target()) };
}

} // extern C

