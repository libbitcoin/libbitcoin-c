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
#include <bitcoin/bitcoin/c/wallet/bitcoin_uri.h>
#include <bitcoin/bitcoin/c/internal/wallet/bitcoin_uri.hpp>

#include <bitcoin/bitcoin/c/internal/utility/string.hpp>

extern "C" {

bc_bitcoin_uri_t* bc_create_bitcoin_uri_default()
{
    return new bc_bitcoin_uri_t{ new libbitcoin::wallet::bitcoin_uri };
}
bc_bitcoin_uri_t* bc_create_bitcoin_uri_copy(const bc_bitcoin_uri_t* other)
{
    return new bc_bitcoin_uri_t{ new libbitcoin::wallet::bitcoin_uri(
        *other->obj) };
}
bc_bitcoin_uri_t* bc_create_bitcoin_uri(const char* uri)
{
    return new bc_bitcoin_uri_t{ new libbitcoin::wallet::bitcoin_uri(uri) };
}
bc_bitcoin_uri_t* bc_create_bitcoin_uri_nonstrict(const char* uri)
{
    return new bc_bitcoin_uri_t{ new libbitcoin::wallet::bitcoin_uri(
        uri, false) };
}
void bc_destroy_bitcoin_uri(bc_bitcoin_uri_t* self)
{
    delete self->obj;
    delete self;
}
/// Operators.
bool bc_bitcoin_uri_less_than(
    const bc_bitcoin_uri_t* self, const bc_bitcoin_uri_t* other)
{
    return *self->obj < *other->obj;
}
bool bc_bitcoin_uri_equals(
    const bc_bitcoin_uri_t* self, const bc_bitcoin_uri_t* other)
{
    return *self->obj == *other->obj;
}
bool bc_bitcoin_uri_not_equals(
    const bc_bitcoin_uri_t* self, const bc_bitcoin_uri_t* other)
{
    return *self->obj != *other->obj;
}
bc_bitcoin_uri_t* bc_bitcoin_uri_copy(
    bc_bitcoin_uri_t* self, const bc_bitcoin_uri_t* other)
{
    *self->obj = *other->obj;
    return self;
}
// stream operators ignored
/// Test whether the URI has been initialized.
bool bc_bitcoin_uri_is_initialized(const bc_bitcoin_uri_t* self)
{
    return static_cast<bool>(*self->obj);
}
/// Get the serialized URI representation.
bc_string_t* bc_bitcoin_uri_encoded(const bc_bitcoin_uri_t* self)
{
    return bc_create_string_StdString(self->obj->encoded());
}
/// Property getters.
uint64_t bc_bitcoin_uri_amount(const bc_bitcoin_uri_t* self)
{
    return self->obj->amount();
}
bc_string_t* bc_bitcoin_uri_label(const bc_bitcoin_uri_t* self)
{
    return bc_create_string_StdString(self->obj->label());
}
bc_string_t* bc_bitcoin_uri_message(const bc_bitcoin_uri_t* self)
{
    return bc_create_string_StdString(self->obj->message());
}
bc_string_t* bc_bitcoin_uri_r(const bc_bitcoin_uri_t* self)
{
    return bc_create_string_StdString(self->obj->r());
}
bc_string_t* bc_bitcoin_uri_address(const bc_bitcoin_uri_t* self)
{
    return bc_create_string_StdString(self->obj->address());
}
bc_string_t* bc_bitcoin_uri_parameter(
    const bc_bitcoin_uri_t* self, const char* key)
{
    return bc_create_string_StdString(self->obj->parameter(key));
}
/// Property setters.
void bc_bitcoin_uri_set_amount(bc_bitcoin_uri_t* self, uint64_t satoshis)
{
    self->obj->set_amount(satoshis);
}
void bc_bitcoin_uri_set_label(bc_bitcoin_uri_t* self, const char* label)
{
    self->obj->set_label(label);
}
void bc_bitcoin_uri_set_message(bc_bitcoin_uri_t* self, const char* message)
{
    self->obj->set_message(message);
}
void bc_bitcoin_uri_set_r(bc_bitcoin_uri_t* self, const char* r)
{
    self->obj->set_r(r);
}
void bc_bitcoin_uri_set_address(bc_bitcoin_uri_t* self, const char* address)
{
    self->obj->set_address(address);
}
/// uri_reader implementation.
void bc_bitcoin_uri_set_strict(bc_bitcoin_uri_t* self, bool strict)
{
    self->obj->set_strict(strict);
}
bool bc_bitcoin_uri_set_scheme(bc_bitcoin_uri_t* self, const char* scheme)
{
    self->obj->set_scheme(scheme);
}
bool bc_bitcoin_uri_set_authority(
    bc_bitcoin_uri_t* self, const char* authority)
{
    self->obj->set_authority(authority);
}
bool bc_bitcoin_uri_set_path(bc_bitcoin_uri_t* self, const char* path)
{
    self->obj->set_path(path);
}
bool bc_bitcoin_uri_set_fragment(bc_bitcoin_uri_t* self, const char* fragment)
{
    self->obj->set_fragment(fragment);
}
bool bc_bitcoin_uri_set_parameter(bc_bitcoin_uri_t* self,
    const char* key, const char* value)
{
    self->obj->set_parameter(key, value);
}

}

