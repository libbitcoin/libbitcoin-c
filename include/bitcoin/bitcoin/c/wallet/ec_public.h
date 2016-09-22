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
#ifndef LIBBITCOIN_C_WALLET_EC_PUBLIC_H
#define LIBBITCOIN_C_WALLET_EC_PUBLIC_H

#include <stdbool.h>
#include <stdint.h>
#include <bitcoin/bitcoin/c/math/elliptic_curve.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/wallet/ec_private.h>
#include <bitcoin/bitcoin/c/wallet/payment_address.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Use to pass an ec point as either ec_compressed or ec_uncompressed.
/// ec_public doesn't carry a version for address creation or base58 encoding.
typedef struct bc_ec_public_t bc_ec_public_t;

/// Static values
uint8_t bc_ec_public_compressed_even();
uint8_t bc_ec_public_compressed_odd();
uint8_t bc_ec_public_uncompressed();
uint8_t bc_ec_public_mainnet_p2kh();
/// Constructors.
bc_ec_public_t* bc_create_ec_public();
bc_ec_public_t* bc_create_ec_public_copy(const bc_ec_public_t* other);
bc_ec_public_t* bc_create_ec_public_Private(const bc_ec_private_t* secret);
bc_ec_public_t* bc_create_ec_public_Data(const bc_data_chunk_t* decoded);
bc_ec_public_t* bc_create_ec_public_String(const char* base16);
bc_ec_public_t* bc_create_ec_public_CompPoint(
    const bc_ec_compressed_t* point);
bc_ec_public_t* bc_create_ec_public_CompPoint_nocompress(
    const bc_ec_compressed_t* point);
bc_ec_public_t* bc_create_ec_public_UncompPoint(
    const bc_ec_uncompressed_t* point);
bc_ec_public_t* bc_create_ec_public_UncompPoint_nocompress(
    const bc_ec_uncompressed_t* point);
/// Destructor
void bc_destroy_ec_public(bc_ec_public_t* self);
/// Operators
bool bc_ec_public_less_than(const bc_ec_public_t* self,
    const bc_ec_public_t* other);
bool bc_ec_public_equals(const bc_ec_public_t* self,
    const bc_ec_public_t* other);
bool bc_ec_public_not_equals(const bc_ec_public_t* self,
    const bc_ec_public_t* other);
void bc_ec_public_copy(bc_ec_public_t* self, const bc_ec_public_t* other);
// Skipping stream operators.
bool bc_ec_public_is_valid(const bc_ec_public_t* self);
/// Serializer.
bc_string_t* bc_ec_public_encoded(const bc_ec_public_t* self);
/// Accessors.
bc_ec_compressed_t* bc_ec_public_point(const bc_ec_public_t* self);
// TODO: these 3 functions are undefined in libbitcoin -----------
//uint16_t bc_ec_public_version(const bc_ec_public_t* self);
//uint8_t bc_ec_public_payment_version(const bc_ec_public_t* self);
//uint8_t bc_ec_public_wif_version(const bc_ec_public_t* self);
// ---------------------------------------------------------------
bool bc_ec_public_compressed(const bc_ec_public_t* self);
/// Methods.
bool bc_ec_public_to_data(const bc_ec_public_t* self, bc_data_chunk_t* out);
bool bc_ec_public_to_uncompressed(
    const bc_ec_public_t* self, bc_ec_uncompressed_t* out);
bc_payment_address_t* bc_ec_public_to_payment_address(
    const bc_ec_public_t* self);
bc_payment_address_t* bc_ec_public_to_payment_address_Version(
    const bc_ec_public_t* self, uint8_t version);

#ifdef __cplusplus
}
#endif

#endif

