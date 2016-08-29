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
#ifndef LIBBITCOIN_C_WALLET_STEALTH_ADDRESS_H
#define LIBBITCOIN_C_WALLET_STEALTH_ADDRESS_H

#include <stdbool.h>
#include <stdint.h>
#include <bitcoin/bitcoin/c/math/elliptic_curve.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_stealth_address_t bc_stealth_address_t;

/// Static values
uint8_t bc_stealth_address_mainnet_p2kh();
uint8_t bc_stealth_address_reuse_key_flag();
uint8_t bc_stealth_address_max_filter_bits();

/// Constructors.
bc_stealth_address_t* bc_create_stealth_address();
bc_stealth_address_t* bc_create_stealth_address_Data(
    const bc_data_chunk_t* decoded);
bc_stealth_address_t* bc_create_stealth_address_String(const char* encoded);
bc_stealth_address_t* bc_create_stealth_address_copy(
    const bc_stealth_address_t* other);
// TODO: need binary type
//bc_stealth_address_t* bc_create_stealth_address_Options();

/// Destructor
void bc_destroy_stealth_address(bc_stealth_address_t* self);

/// Operators.
bool bc_stealth_address_less_than(const bc_stealth_address_t* self,
    const bc_stealth_address_t* other);
bool bc_stealth_address_equals(const bc_stealth_address_t* self,
    const bc_stealth_address_t* other);
bool bc_stealth_address_not_equals(const bc_stealth_address_t* self,
    const bc_stealth_address_t* other);
bc_stealth_address_t* bc_stealth_address_copy(
    bc_stealth_address_t* self, const bc_stealth_address_t* other);
// Stream operators ignored.

/// Cast operators.
bool bc_stealth_address_is_initialized(const bc_stealth_address_t* self);

/// Serializer.
bc_string_t* bc_stealth_address_encoded(const bc_stealth_address_t* self);

/// Accessors.
uint8_t bc_stealth_address_version(const bc_stealth_address_t* self);
bc_ec_compressed_t* bc_stealth_address_scan_key(
    const bc_stealth_address_t* self);
bc_point_list_t* bc_stealth_address_spend_keys(
    const bc_stealth_address_t* self);
uint8_t bc_stealth_address_signatures(const bc_stealth_address_t* self);
// TODO: binary type needed for filter

/// Methods.
bc_data_chunk_t* bc_stealth_address_to_chunk(
    const bc_stealth_address_t* self);

#ifdef __cplusplus
}
#endif

#endif

