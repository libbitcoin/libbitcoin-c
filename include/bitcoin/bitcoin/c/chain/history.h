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
#ifndef LIBBITCOIN_C_CHAIN_HISTORY_H
#define LIBBITCOIN_C_CHAIN_HISTORY_H

#include <bitcoin/bitcoin/c/chain/point.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Use "kind" for union differentiation.
typedef enum bc_point_kind_t
{
    bc_point_kind_output = 0,
    bc_point_kind_spend = 1

} bc_point_kind_t;

/// This structure models the client-server protocol in v1/v2/v3.
/// The height value here is 64 bit, but 32 bits on the wire.
typedef struct bc_history_compact_t bc_history_compact_t;
BC_DECLARE_VECTOR(history_compact_list, bc_history_compact_t);

// Constructor
bc_history_compact_t* bc_create_history_compact();
// Destructor
void bc_destroy_history_compact(bc_history_compact_t* self);
// Member variables
// The type of point (output or spend).
bc_point_kind_t bc_history_compact_kind(const bc_history_compact_t* self);
void bc_history_compact_set_kind(bc_history_compact_t* self,
    bc_point_kind_t kind);
/// The point that identifies the record.
bc_point_t* bc_history_compact_point(const bc_history_compact_t* self);
void bc_history_compact_set_point(bc_history_compact_t* self,
    const bc_point_t* point);
/// The height of the point.
uint64_t bc_history_compact_height(const bc_history_compact_t* self);
void bc_history_compact_set_height(bc_history_compact_t* self,
    uint64_t height);
/// If output, then satoshi value of output.
uint64_t bc_history_compact_value(const bc_history_compact_t* self);
void bc_history_compact_set_value(bc_history_compact_t* self,
    uint64_t value);
/// If spend, then checksum hash of previous output point
/// To match up this row with the output, recompute the
/// checksum from the output row with spend_checksum(row.point)
uint64_t bc_history_compact_previous_checksum(
    const bc_history_compact_t* self);
void bc_history_compact_set_previous_checksum(bc_history_compact_t* self,
    uint64_t previous_checksum);

/// This structure is used between client and API callers in v3.
/// This structure models the client-server protocol in v1/v2.
/// The height values here are 64 bit, but 32 bits on the wire.
typedef struct bc_history_t bc_history_t;
BC_DECLARE_VECTOR(history_list, bc_history_t);

// Constructor
bc_history_t* bc_create_history();
// Destructor
void bc_destroy_history(bc_history_t* self);
// Member variables
/// If there is no output this is null_hash:max.
bc_output_point_t* bc_history_output(const bc_history_t* self);
void bc_history_set_output(bc_history_t* self,
    const bc_output_point_t* output);
uint64_t bc_history_output_height(const bc_history_t* self);
void bc_history_set_output_height(bc_history_t* self, uint64_t output_height);
/// The satoshi value of the output.
uint64_t bc_history_value(const bc_history_t* self);
void bc_history_set_value(bc_history_t* self, uint64_t value);
/// If there is no spend this is null_hash:max.
bc_input_point_t* bc_history_spend(const bc_history_t* self);
void bc_history_set_spend(bc_history_t* self, const bc_input_point_t* spend);
/// The height of the spend or max if no spend.
uint64_t bc_history_spend_height(const bc_history_t* self);
void bc_history_set_spend_height(bc_history_t* self, uint64_t spend_height);
/// During expansion this value temporarily doubles as a checksum.
uint64_t bc_history_temporary_checksum(const bc_history_t* self);
void bc_history_set_temporary_checksum(bc_history_t* self,
    uint64_t temporary_checksum);

#ifdef __cplusplus
}
#endif

#endif

