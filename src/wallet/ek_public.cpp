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
#include <bitcoin/bitcoin/c/wallet/ek_public.h>
#include <bitcoin/bitcoin/c/internal/wallet/ek_public.hpp>

#include <bitcoin/bitcoin/c/internal/utility/string.hpp>
#include <bitcoin/bitcoin/c/internal/wallet/encrypted_keys.hpp>

extern "C" {

bc_ek_public_t* bc_create_ek_public_default()
{
    return new bc_ek_public_t{ new libbitcoin::wallet::ek_public };
}
bc_ek_public_t* bc_create_ek_public(const char* encoded)
{
    return new bc_ek_public_t{ new libbitcoin::wallet::ek_public(
        encoded) };
}
bc_ek_public_t* bc_create_ek_public_Key(const bc_encrypted_public_t* key)
{
    return new bc_ek_public_t{ new libbitcoin::wallet::ek_public(
        *key->obj) };
}
bc_ek_public_t* bc_create_ek_public_copy(const bc_ek_public_t* other)
{
    return new bc_ek_public_t{ new libbitcoin::wallet::ek_public(
        *other->obj) };
}
void bc_destroy_ek_public(bc_ek_public_t* self)
{
    delete self->obj;
    delete self;
}

bool bc_ek_public__less_than(
    const bc_ek_public_t* self, const bc_ek_public_t* other)
{
    return *self->obj < *other->obj;
}
bool bc_ek_public__equals(
    const bc_ek_public_t* self, const bc_ek_public_t* other)
{
    return *self->obj == *other->obj;
}
bool bc_ek_public__not_equals(
    const bc_ek_public_t* self, const bc_ek_public_t* other)
{
    return *self->obj != *other->obj;
}
void bc_ek_public__copy(bc_ek_public_t* self, const bc_ek_public_t* other)
{
    *self->obj = *other->obj;
}

bool bc_ek_public__is_valid(const bc_ek_public_t* self)
{
    return static_cast<bool>(*self->obj);
}

bc_string_t* bc_ek_public__encoded(const bc_ek_public_t* self)
{
    return bc_create_string_StdString(self->obj->encoded());
}

bc_encrypted_public_t* bc_ek_public__public(const bc_ek_public_t* self)
{
    return new bc_encrypted_public_t{
        new libbitcoin::wallet::encrypted_public(
            self->obj->public_key()) };
}

}

