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
#ifndef LIBBITCOIN_C_WALLET_PAYMENT_ADDRESS_H
#define LIBBITCOIN_C_WALLET_PAYMENT_ADDRESS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <bitcoin/bitcoin/c/chain/script/script.h>
#include <bitcoin/bitcoin/c/math/hash.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_ec_public_t bc_ec_public_t;
typedef struct bc_ec_private_t bc_ec_private_t;

size_t bc_payment_size();
BC_DECLARE_BYTE_ARRAY(payment);

typedef struct bc_payment_address_t bc_payment_address_t;
uint8_t bc_payment_address__mainnet_p2kh();
uint8_t bc_payment_address__mainnet_p2sh();

/// Extract a payment address from an input or output script.
/// The address will be invalid if and only if the script type is not
/// supported or the script is itself invalid.
bc_payment_address_t* bc_payment_address__extract(
    const bc_script_t* script);
bc_payment_address_t* bc_payment_address__extract_Options(
    const bc_script_t* script, uint8_t p2kh_version, uint8_t p2sh_version);

bc_payment_address_t* bc_create_payment_address();
bc_payment_address_t* bc_create_payment_address_Payment(
    const bc_payment_t* decoded);
bc_payment_address_t* bc_create_payment_address_Secret(
    const bc_ec_private_t* secret);
bc_payment_address_t* bc_create_payment_address_String(
    const char* address);
bc_payment_address_t* bc_create_payment_address_copy(
    const bc_payment_address_t* other);
bc_payment_address_t* bc_create_payment_address_Hash(
    const bc_short_hash_t* hash);
bc_payment_address_t* bc_create_payment_address_Hash_Version(
    const bc_short_hash_t* hash, uint8_t version);
bc_payment_address_t* bc_create_payment_address_Point(
    const bc_ec_public_t* point);
bc_payment_address_t* bc_create_payment_address_Point_Version(
    const bc_ec_public_t* point, uint8_t version);
bc_payment_address_t* bc_create_payment_address_Script(
    const bc_script_t* script);
bc_payment_address_t* bc_create_payment_address_Script_Version(
    const bc_script_t* script, uint8_t version);
void bc_destroy_payment_address(bc_payment_address_t* self);

/// Operators.
bool bc_payment_address__less_than(
    const bc_payment_address_t* self, const bc_payment_address_t* other);
bool bc_payment_address__equals(
    const bc_payment_address_t* self, const bc_payment_address_t* other);
bool bc_payment_address__not_equals(
    const bc_payment_address_t* self, const bc_payment_address_t* other);
bc_payment_address_t* bc_payment_address__copy(
    bc_payment_address_t* self, const bc_payment_address_t* other);
// stream operators ignored.

/// Cast operators.
bool bc_payment_address__is_valid(const bc_payment_address_t* self);

/// Serializer.
bc_string_t* bc_payment_address__encoded(const bc_payment_address_t* self);

/// Accessors.
uint8_t bc_payment_address__version(const bc_payment_address_t* self);
bc_short_hash_t* bc_payment_address__hash(const bc_payment_address_t* self);

/// Methods.
bc_payment_t* bc_payment_address__payment(const bc_payment_address_t* self);

#ifdef __cplusplus
}
#endif

#endif

