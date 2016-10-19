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
#ifndef LIBBITCOIN_C_WALLET_HD_PRIVATE_KEY_H
#define LIBBITCOIN_C_WALLET_HD_PRIVATE_KEY_H

#include <stdbool.h>
#include <stdint.h>
#include <bitcoin/bitcoin/c/wallet/hd_public.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>
#include <bitcoin/bitcoin/c/math/elliptic_curve.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_hd_private_t bc_hd_private_t;
uint64_t bc_hd_private__mainnet();
uint64_t bc_hd_private__testnet();
uint32_t bc_hd_private__to_prefix(uint64_t prefixes);
uint64_t bc_hd_private__to_prefixes(
    uint32_t private_prefix, uint32_t public_prefix);
/// Constructors.
bc_hd_private_t* bc_create_hd_private();
bc_hd_private_t* bc_create_hd_private_copy(const bc_hd_private_t* other);
bc_hd_private_t* bc_create_hd_private_Seed(
    const bc_data_chunk_t* seed, uint64_t prefixes);
bc_hd_private_t* bc_create_hd_private_Key(
    const bc_hd_key_t* key);
bc_hd_private_t* bc_create_hd_private_Key_Prefixes(
    const bc_hd_key_t* key, uint64_t prefixes);
bc_hd_private_t* bc_create_hd_private_Key_Prefix(
    const bc_hd_key_t* key, uint32_t public_prefix);
bc_hd_private_t* bc_create_hd_private_String(
    const char* encoded);
bc_hd_private_t* bc_create_hd_private_String_Prefixes(
    const char* encoded, uint64_t prefixes);
bc_hd_private_t* bc_create_hd_private_String_Prefix(
    const char* encoded, uint32_t public_prefix);
void bc_destroy_hd_private(bc_hd_private_t* self);
/// Operators.
bool bc_hd_private__less_than(
    bc_hd_private_t* self, const bc_hd_private_t* other);
bool bc_hd_private__equals(
    bc_hd_private_t* self, const bc_hd_private_t* other);
bool bc_hd_private__not_equals(
    bc_hd_private_t* self, const bc_hd_private_t* other);
bc_hd_public_t* bc_hd_private__hd_public_Base(bc_hd_private_t* self);
// Simply returns itself again
bc_hd_private_t* bc_hd_private__copy(
    bc_hd_private_t* self, const bc_hd_private_t* other);
// istream and ostream operators ignored.
/// Serializer.
bc_string_t* bc_hd_private__encoded(const bc_hd_private_t* self);
/// Accessors.
bc_ec_secret_t* bc_hd_private__secret(const bc_hd_private_t* self);
/// Methods.
bc_hd_key_t* bc_hd_private__to_hd_key(const bc_hd_private_t* self);
bc_hd_public_t* bc_hd_private__to_public(const bc_hd_private_t* self);
bc_hd_private_t* bc_hd_private__derive_private(
    const bc_hd_private_t* self, uint32_t index);
bc_hd_public_t* bc_hd_private__derive_public(
    const bc_hd_private_t* self, uint32_t index);

#ifdef __cplusplus
}
#endif

#endif

