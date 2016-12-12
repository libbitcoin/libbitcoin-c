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
#ifndef LIBBITCOIN_C_WALLET_EC_PRIVATE_H
#define LIBBITCOIN_C_WALLET_EC_PRIVATE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <bitcoin/bitcoin/c/math/elliptic_curve.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/wallet/payment_address.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Private keys with public key compression metadata:
BC_DECLARE_BYTE_ARRAY(wif_uncompressed);

BC_DECLARE_BYTE_ARRAY(wif_compressed);

/// Use to pass an ec secret with compresson and version information.
typedef struct bc_ec_private_t bc_ec_private_t;

/// Static values
uint8_t bc_ec_private__compressed_sentinel();

// WIF carries a compression flag for payment address generation but
// assumes a mapping to payment address version. This is insufficient
// as a parameterized mapping is required, so we use the same technique as
// with hd keys, merging the two necessary values into one version.
uint8_t bc_ec_private__mainnet_wif();
uint8_t bc_ec_private__mainnet_p2kh();
uint16_t bc_ec_private__mainnet();

uint8_t bc_ec_private__testnet_wif();
uint8_t bc_ec_private__testnet_p2kh();
uint16_t bc_ec_private__testnet();

/// Static functions
uint8_t bc_ec_private__to_address_prefix(uint16_t version);
uint8_t bc_ec_private__to_wif_prefix(uint16_t version);
// Unfortunately can't use this below to define mainnet (MSVC).
uint8_t bc_ec_private__to_version(uint8_t address, uint8_t wif);

/// Constructors
bc_ec_private_t* bc_create_ec_private();
bc_ec_private_t* bc_create_ec_private_copy(const bc_ec_private_t* other);
bc_ec_private_t* bc_create_ec_private_String(
    const char* wif);
bc_ec_private_t* bc_create_ec_private_String_Version(
    const char* wif, uint8_t version);
bc_ec_private_t* bc_create_ec_private_WifComp(
    const bc_wif_compressed_t* wif);
bc_ec_private_t* bc_create_ec_private_WifComp_Version(
    const bc_wif_compressed_t* wif, uint8_t version);
bc_ec_private_t* bc_create_ec_private_WifUncomp(
    const bc_wif_uncompressed_t* wif);
bc_ec_private_t* bc_create_ec_private_WifUncomp_Version(
    const bc_wif_uncompressed_t* wif, uint8_t version);
/// The version is 16 bits. The most significant byte is the WIF prefix and
/// the least significant byte is the address perfix. 0x8000 by default.
bc_ec_private_t* bc_create_ec_private_Secret(
    const bc_ec_secret_t* secret);
bc_ec_private_t* bc_create_ec_private_Secret_Version(
    const bc_ec_secret_t* secret, uint16_t version);
bc_ec_private_t* bc_create_ec_private_Secret_Version_nocompress(
    const bc_ec_secret_t* secret, uint16_t version);

/// Destructor
void bc_destroy_ec_private(bc_ec_private_t* self);

/// Operators.
bool bc_ec_private__less_than(const bc_ec_private_t* self,
    const bc_ec_private_t* other);
bool bc_ec_private__equals(const bc_ec_private_t* self,
    const bc_ec_private_t* other);
bool bc_ec_private__not_equals(const bc_ec_private_t* self,
    const bc_ec_private_t* other);
void bc_ec_private__copy(bc_ec_private_t* self, const bc_ec_private_t* other);
// Skipping stream operators

/// Cast operators.
bool bc_ec_private__is_valid(const bc_ec_private_t* self);

/// Serializer.
bc_string_t* bc_ec_private__encoded(const bc_ec_private_t* self);

/// Accessors.
bc_ec_secret_t* bc_ec_private__secret(const bc_ec_private_t* self);
uint16_t bc_ec_private__version(const bc_ec_private_t* self);
uint8_t bc_ec_private__payment_version(const bc_ec_private_t* self);
uint8_t bc_ec_private__wif_version(const bc_ec_private_t* self);
bool bc_ec_private__compressed(const bc_ec_private_t* self);

/// Methods.
// TODO: ec_public to_public() const
bc_payment_address_t* bc_ec_private__to_payment_address(
    const bc_ec_private_t* self);

#ifdef __cplusplus
}
#endif

#endif

