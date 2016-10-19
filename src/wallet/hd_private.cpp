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
#include <bitcoin/bitcoin/c/wallet/hd_private.h>

#include <bitcoin/bitcoin/wallet/hd_private.hpp>
#include <bitcoin/bitcoin/c/internal/math/elliptic_curve.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/wallet/hd_public.hpp>
#include <bitcoin/bitcoin/c/internal/wallet/hd_private.hpp>

extern "C" {

uint64_t bc_hd_private__mainnet()
{
    return libbitcoin::wallet::hd_private::mainnet;
}
uint64_t bc_hd_private__testnet()
{
    return libbitcoin::wallet::hd_private::testnet;
}
uint32_t bc_hd_private__to_prefix(uint64_t prefixes)
{
    return libbitcoin::wallet::hd_private::to_prefix(prefixes);
}
uint64_t bc_hd_private__to_prefixes(
    uint32_t private_prefix, uint32_t public_prefix)
{
    return libbitcoin::wallet::hd_private::to_prefixes(
        private_prefix, public_prefix);
}
/// Constructors.
bc_hd_private_t* bc_create_hd_private()
{
    return new bc_hd_private_t{ new libbitcoin::wallet::hd_private() };
}
bc_hd_private_t* bc_create_hd_private_copy(const bc_hd_private_t* other)
{
    return new bc_hd_private_t{ new libbitcoin::wallet::hd_private(
        *other->obj) };
}
bc_hd_private_t* bc_create_hd_private_Seed(
    const bc_data_chunk_t* seed, uint64_t prefixes)
{
    return new bc_hd_private_t{ new libbitcoin::wallet::hd_private(
        *seed->obj, prefixes) };
}
bc_hd_private_t* bc_create_hd_private_Key(
    const bc_hd_key_t* key)
{
    return new bc_hd_private_t{ new libbitcoin::wallet::hd_private(
        *key->obj) };
}
bc_hd_private_t* bc_create_hd_private_Key_Prefixes(
    const bc_hd_key_t* key, uint64_t prefixes)
{
    return new bc_hd_private_t{ new libbitcoin::wallet::hd_private(
        *key->obj, prefixes) };
}
bc_hd_private_t* bc_create_hd_private_Key_Prefix(
    const bc_hd_key_t* key, uint32_t public_prefix)
{
    return new bc_hd_private_t{ new libbitcoin::wallet::hd_private(
        *key->obj, public_prefix) };
}
bc_hd_private_t* bc_create_hd_private_String(
    const char* encoded)
{
    return new bc_hd_private_t{ new libbitcoin::wallet::hd_private(
        encoded) };
}
bc_hd_private_t* bc_create_hd_private_String_Prefixes(
    const char* encoded, uint64_t prefixes)
{
    return new bc_hd_private_t{ new libbitcoin::wallet::hd_private(
        encoded, prefixes) };
}
bc_hd_private_t* bc_create_hd_private_String_Prefix(
    const char* encoded, uint32_t public_prefix)
{
    return new bc_hd_private_t{ new libbitcoin::wallet::hd_private(
        encoded, public_prefix) };
}
void bc_destroy_hd_private(bc_hd_private_t* self)
{
    delete self->obj;
    delete self;
}
/// Operators.
bool bc_hd_private__less_than(
    bc_hd_private_t* self, const bc_hd_private_t* other)
{
    return *self->obj < *other->obj;
}
bool bc_hd_private__equals(
    bc_hd_private_t* self, const bc_hd_private_t* other)
{
    return *self->obj == *other->obj;
}
bool bc_hd_private__not_equals(
    bc_hd_private_t* self, const bc_hd_private_t* other)
{
    return *self->obj != *other->obj;
}

bc_hd_public_t* bc_hd_private__hd_public_Base(bc_hd_private_t* self)
{
    return new bc_hd_public_t{
        static_cast<libbitcoin::wallet::hd_public*>(self->obj), false };
}
// Simply returns itself again
bc_hd_private_t* bc_hd_private__copy(
    bc_hd_private_t* self, const bc_hd_private_t* other)
{
    *self->obj = *other->obj;
    return self;
}
// istream and ostream operators ignored.
/// Serializer.
bc_string_t* bc_hd_private__encoded(const bc_hd_private_t* self)
{
    std::string encoded = self->obj->encoded();
    return bc_create_string_Length(encoded.data(), encoded.length());
}
/// Accessors.
bc_ec_secret_t* bc_hd_private__secret(const bc_hd_private_t* self)
{
    return new bc_ec_secret_t{ new libbitcoin::ec_secret(
        self->obj->secret()), true };
}
/// Methods.
bc_hd_key_t* bc_hd_private__to_hd_key(const bc_hd_private_t* self)
{
    return new bc_hd_key_t{ new libbitcoin::wallet::hd_key(
        self->obj->to_hd_key()) };
}
bc_hd_public_t* bc_hd_private__to_public(const bc_hd_private_t* self)
{
    return new bc_hd_public_t{ new libbitcoin::wallet::hd_public(
        self->obj->to_public()), true };
}
bc_hd_private_t* bc_hd_private__derive_private(
    const bc_hd_private_t* self, uint32_t index)
{
    return new bc_hd_private_t{ new libbitcoin::wallet::hd_private(
        self->obj->derive_private(index)) };
}
bc_hd_public_t* bc_hd_private__derive_public(
    const bc_hd_private_t* self, uint32_t index)
{
    return new bc_hd_public_t{ new libbitcoin::wallet::hd_public(
        self->obj->derive_public(index)), true };
}

}

