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
#include <bitcoin/bitcoin/c/wallet/ek_token.h>
#include <bitcoin/bitcoin/c/internal/wallet/ek_token.hpp>

#include <bitcoin/bitcoin/c/internal/utility/string.hpp>
#include <bitcoin/bitcoin/c/internal/wallet/encrypted_keys.hpp>

extern "C" {

bc_ek_token_t* bc_create_ek_token_default()
{
    return new bc_ek_token_t{ new libbitcoin::wallet::ek_token };
}
bc_ek_token_t* bc_create_ek_token(const char* encoded)
{
    return new bc_ek_token_t{ new libbitcoin::wallet::ek_token(
        encoded) };
}
bc_ek_token_t* bc_create_ek_token_Token(const bc_encrypted_token_t* key)
{
    return new bc_ek_token_t{ new libbitcoin::wallet::ek_token(
        *key->obj) };
}
bc_ek_token_t* bc_create_ek_token_copy(const bc_ek_token_t* other)
{
    return new bc_ek_token_t{ new libbitcoin::wallet::ek_token(
        *other->obj) };
}
void bc_destroy_ek_token(bc_ek_token_t* self)
{
    delete self->obj;
    delete self;
}

bool bc_ek_token__less_than(
    const bc_ek_token_t* self, const bc_ek_token_t* other)
{
    return *self->obj < *other->obj;
}
bool bc_ek_token__equals(
    const bc_ek_token_t* self, const bc_ek_token_t* other)
{
    return *self->obj == *other->obj;
}
bool bc_ek_token__not_equals(
    const bc_ek_token_t* self, const bc_ek_token_t* other)
{
    return *self->obj != *other->obj;
}
void bc_ek_token__copy(bc_ek_token_t* self, const bc_ek_token_t* other)
{
    *self->obj = *other->obj;
}

bool bc_ek_token__is_valid(const bc_ek_token_t* self)
{
    return static_cast<bool>(*self->obj);
}

bc_string_t* bc_ek_token__encoded(const bc_ek_token_t* self)
{
    return bc_create_string_StdString(self->obj->encoded());
}

bc_encrypted_token_t* bc_ek_token__token(const bc_ek_token_t* self)
{
    return new bc_encrypted_token_t{ new libbitcoin::wallet::encrypted_token(
        self->obj->token()) };
}

}

