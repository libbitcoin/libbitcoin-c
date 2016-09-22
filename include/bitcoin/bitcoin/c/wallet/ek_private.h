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
#ifndef LIBBITCOIN_C_WALLET_EK_PRIVATE_H
#define LIBBITCOIN_C_WALLET_EK_PRIVATE_H

#include <stdbool.h>
#include <bitcoin/bitcoin/c/utility/string.h>
#include <bitcoin/bitcoin/c/wallet/encrypted_keys.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Use to pass an encrypted private key.
typedef struct bc_ek_private_t bc_ek_private_t;
/// Constructors.
bc_ek_private_t* bc_create_ek_private_default();
bc_ek_private_t* bc_create_ek_private(const char* encoded);
bc_ek_private_t* bc_create_ek_private_Key(const bc_encrypted_private_t* key);
bc_ek_private_t* bc_create_ek_private_copy(const bc_ek_private_t* other);
/// Destructor
void bc_destroy_ek_private(bc_ek_private_t* self);

/// Operators.
bool bc_ek_private_less_than(
    const bc_ek_private_t* self, const bc_ek_private_t* other);
bool bc_ek_private_equals(
    const bc_ek_private_t* self, const bc_ek_private_t* other);
bool bc_ek_private_not_equals(
    const bc_ek_private_t* self, const bc_ek_private_t* other);
void bc_ek_private_copy(bc_ek_private_t* self, const bc_ek_private_t* other);

bool bc_ek_private_is_valid(const bc_ek_private_t* self);

/// Serializer.
bc_string_t* bc_ek_private_encoded(const bc_ek_private_t* self);

/// Accessors.
bc_encrypted_private_t* bc_ek_private_private_key(const bc_ek_private_t* self);

#ifdef __cplusplus
}
#endif

#endif

