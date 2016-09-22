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
#ifndef LIBBITCOIN_C_WALLET_EK_TOKEN_H
#define LIBBITCOIN_C_WALLET_EK_TOKEN_H

#include <stdbool.h>
#include <bitcoin/bitcoin/c/utility/string.h>
#include <bitcoin/bitcoin/c/wallet/encrypted_keys.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Serialization helper to convert between base58 string and bip38 token.
 */
typedef struct bc_ek_token_t bc_ek_token_t;
/// Constructors.
bc_ek_token_t* bc_create_ek_token_default();
bc_ek_token_t* bc_create_ek_token(const char* encoded);
bc_ek_token_t* bc_create_ek_token_Token(const bc_encrypted_token_t* key);
bc_ek_token_t* bc_create_ek_token_copy(const bc_ek_token_t* other);
/// Destructor
void bc_destroy_ek_token(bc_ek_token_t* self);

/// Operators.
bool bc_ek_token_less_than(
    const bc_ek_token_t* self, const bc_ek_token_t* other);
bool bc_ek_token_equals(
    const bc_ek_token_t* self, const bc_ek_token_t* other);
bool bc_ek_token_not_equals(
    const bc_ek_token_t* self, const bc_ek_token_t* other);
void bc_ek_token_copy(bc_ek_token_t* self, const bc_ek_token_t* other);

bool bc_ek_token_is_valid(const bc_ek_token_t* self);

/// Serializer.
bc_string_t* bc_ek_token_encoded(const bc_ek_token_t* self);

/// Accessors.
bc_encrypted_token_t* bc_ek_token_token(const bc_ek_token_t* self);

#ifdef __cplusplus
}
#endif

#endif

