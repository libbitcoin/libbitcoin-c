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
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t bc_payment_size();
BC_DECLARE_BYTE_ARRAY(payment);

typedef struct bc_payment_address_t bc_payment_address_t;
uint8_t bc_payment_address_mainnet_p2kh();
uint8_t bc_payment_address_mainnet_p2sh();
// TODO: extract - script type needed first

#if 0
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
// TODO: construct from script
#endif

#ifdef __cplusplus
}
#endif

#endif

