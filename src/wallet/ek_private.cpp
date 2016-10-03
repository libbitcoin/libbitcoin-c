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
#include <bitcoin/bitcoin/c/wallet/ek_private.h>
#include <bitcoin/bitcoin/c/internal/wallet/ek_private.hpp>

#include <bitcoin/bitcoin/c/internal/utility/string.hpp>
#include <bitcoin/bitcoin/c/internal/wallet/encrypted_keys.hpp>

extern "C" {

bc_ek_private_t* bc_create_ek_private_default()
{
    return new bc_ek_private_t{ new libbitcoin::wallet::ek_private };
}
bc_ek_private_t* bc_create_ek_private(const char* encoded)
{
    return new bc_ek_private_t{ new libbitcoin::wallet::ek_private(
        encoded) };
}
bc_ek_private_t* bc_create_ek_private_Key(const bc_encrypted_private_t* key)
{
    return new bc_ek_private_t{ new libbitcoin::wallet::ek_private(
        *key->obj) };
}
bc_ek_private_t* bc_create_ek_private_copy(const bc_ek_private_t* other)
{
    return new bc_ek_private_t{ new libbitcoin::wallet::ek_private(
        *other->obj) };
}
void bc_destroy_ek_private(bc_ek_private_t* self)
{
    delete self->obj;
    delete self;
}

bool bc_ek_private__less_than(
    const bc_ek_private_t* self, const bc_ek_private_t* other)
{
    return *self->obj < *other->obj;
}
bool bc_ek_private__equals(
    const bc_ek_private_t* self, const bc_ek_private_t* other)
{
    return *self->obj == *other->obj;
}
bool bc_ek_private__not_equals(
    const bc_ek_private_t* self, const bc_ek_private_t* other)
{
    return *self->obj != *other->obj;
}
void bc_ek_private__copy(bc_ek_private_t* self, const bc_ek_private_t* other)
{
    *self->obj = *other->obj;
}

bool bc_ek_private__is_valid(const bc_ek_private_t* self)
{
    return static_cast<bool>(*self->obj);
}

bc_string_t* bc_ek_private__encoded(const bc_ek_private_t* self)
{
    return bc_create_string_StdString(self->obj->encoded());
}

bc_encrypted_private_t* bc_ek_private__private_key(const bc_ek_private_t* self)
{
    return new bc_encrypted_private_t{
        new libbitcoin::wallet::encrypted_private(
            self->obj->private_key()) };
}

}

