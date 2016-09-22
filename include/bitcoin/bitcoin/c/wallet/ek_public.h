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
#ifndef LIBBITCOIN_C_WALLET_EK_PUBLIC_H
#define LIBBITCOIN_C_WALLET_EK_PUBLIC_H

#include <stdbool.h>
#include <bitcoin/bitcoin/c/utility/string.h>
#include <bitcoin/bitcoin/c/wallet/encrypted_keys.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Use to pass an encrypted public key.
typedef struct bc_ek_public_t bc_ek_public_t;
/// Constructors.
bc_ek_public_t* bc_create_ek_public_default();
bc_ek_public_t* bc_create_ek_public(const char* encoded);
bc_ek_public_t* bc_create_ek_public_Key(const bc_encrypted_public_t* key);
bc_ek_public_t* bc_create_ek_public_copy(const bc_ek_public_t* other);
/// Destructor
void bc_destroy_ek_public(bc_ek_public_t* self);

/// Operators.
bool bc_ek_public_less_than(
    const bc_ek_public_t* self, const bc_ek_public_t* other);
bool bc_ek_public_equals(
    const bc_ek_public_t* self, const bc_ek_public_t* other);
bool bc_ek_public_not_equals(
    const bc_ek_public_t* self, const bc_ek_public_t* other);
void bc_ek_public_copy(bc_ek_public_t* self, const bc_ek_public_t* other);

bool bc_ek_public_is_valid(const bc_ek_public_t* self);

/// Serializer.
bc_string_t* bc_ek_public_encoded(const bc_ek_public_t* self);

/// Accessors.
bc_encrypted_public_t* bc_ek_public_public_key(const bc_ek_public_t* self);

#ifdef __cplusplus
}
#endif

#endif

