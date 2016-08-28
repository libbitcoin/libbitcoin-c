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
#ifndef LIBBITCOIN_C_WALLET_BITCOIN_URI_H
#define LIBBITCOIN_C_WALLET_BITCOIN_URI_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <bitcoin/bitcoin/c/utility/string.h>
#include <bitcoin/bitcoin/c/wallet/payment_address.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_bitcoin_uri_t bc_bitcoin_uri_t;
bc_bitcoin_uri_t* bc_create_bitcoin_uri_default();
bc_bitcoin_uri_t* bc_create_bitcoin_uri_copy(const bc_bitcoin_uri_t* other);
bc_bitcoin_uri_t* bc_create_bitcoin_uri(const char* uri);
bc_bitcoin_uri_t* bc_create_bitcoin_uri_nonstrict(const char* uri);
void bc_destroy_bitcoin_uri(bc_bitcoin_uri_t* self);
/// Operators.
bool bc_bitcoin_uri_less_than(
    const bc_bitcoin_uri_t* self, const bc_bitcoin_uri_t* other);
bool bc_bitcoin_uri_equals(
    const bc_bitcoin_uri_t* self, const bc_bitcoin_uri_t* other);
bool bc_bitcoin_uri_not_equals(
    const bc_bitcoin_uri_t* self, const bc_bitcoin_uri_t* other);
bc_bitcoin_uri_t* bc_bitcoin_uri_copy(
    bc_bitcoin_uri_t* self, const bc_bitcoin_uri_t* other);
// stream operators ignored
/// Test whether the URI has been initialized.
bool bc_bitcoin_uri_is_initialized(const bc_bitcoin_uri_t* self);
/// Get the serialized URI representation.
bc_string_t* bc_bitcoin_uri_encoded(const bc_bitcoin_uri_t* self);
/// Property getters.
uint64_t bc_bitcoin_uri_amount(const bc_bitcoin_uri_t* self);
bc_string_t* bc_bitcoin_uri_label(const bc_bitcoin_uri_t* self);
bc_string_t* bc_bitcoin_uri_message(const bc_bitcoin_uri_t* self);
bc_string_t* bc_bitcoin_uri_r(const bc_bitcoin_uri_t* self);
bc_string_t* bc_bitcoin_uri_address(const bc_bitcoin_uri_t* self);
bc_payment_address_t* bc_bitcoin_uri_payment(const bc_bitcoin_uri_t* self);
// TODO: stealth address
bc_string_t* bc_bitcoin_uri_parameter(
    const bc_bitcoin_uri_t* self, const char* key);
/// Property setters.
void bc_bitcoin_uri_set_amount(bc_bitcoin_uri_t* self, uint64_t satoshis);
void bc_bitcoin_uri_set_label(bc_bitcoin_uri_t* self, const char* label);
void bc_bitcoin_uri_set_message(bc_bitcoin_uri_t* self, const char* message);
void bc_bitcoin_uri_set_r(bc_bitcoin_uri_t* self, const char* r);
void bc_bitcoin_uri_set_address(bc_bitcoin_uri_t* self, const char* address);
void bc_bitcoin_uri_set_payment(bc_bitcoin_uri_t* self,
    const bc_payment_address_t* payment);
// TODO: stealth address
/// uri_reader implementation.
void bc_bitcoin_uri_set_strict(bc_bitcoin_uri_t* self, bool strict);
bool bc_bitcoin_uri_set_scheme(bc_bitcoin_uri_t* self, const char* scheme);
bool bc_bitcoin_uri_set_authority(
    bc_bitcoin_uri_t* self, const char* authority);
bool bc_bitcoin_uri_set_path(bc_bitcoin_uri_t* self, const char* path);
bool bc_bitcoin_uri_set_fragment(bc_bitcoin_uri_t* self, const char* fragment);
bool bc_bitcoin_uri_set_parameter(bc_bitcoin_uri_t* self,
    const char* key, const char* value);

#ifdef __cplusplus
}
#endif

#endif

