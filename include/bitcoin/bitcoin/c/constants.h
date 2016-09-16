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

size_t bc_command_size();

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

// Consensus constants.
uint32_t bc_reward_interval();
uint32_t bc_coinbase_maturity();
uint32_t bc_initial_block_reward();
uint32_t bc_max_work_bits();
uint32_t bc_max_input_sequence();

// Threshold for nLockTime: below this value it is interpreted as block number,
// otherwise as UNIX timestamp. [Tue Nov 5 00:53:20 1985 UTC]
uint32_t bc_locktime_threshold();

uint64_t bc_max_money();

// For configuration settings initialization.
// settings enum ignored for now.

typedef enum bc_services_t
{
    // The node is capable of serving the block chain.
    bc_services_node_network = (1 << 0),

    // Requires version >= 70004 (bip64)
    // The node is capable of responding to the getutxo protocol request.
    bc_services_node_utxo = (1 << 1),

    // Requires version >= 70011 (proposed)
    // The node is capable and willing to handle bloom-filtered connections.
    bc_services_bloom_filters = (1 << 2)
} bc_services_t;

uint32_t bc_no_timestamp();
uint16_t bc_unspecified_ip_port();

// TODO: message::ip_address unspecified_ip_address
// TODO: message::network_address unspecified_network_address

bc_hash_number_t* bc_max_target();

#ifdef __cplusplus
}
#endif

#endif

