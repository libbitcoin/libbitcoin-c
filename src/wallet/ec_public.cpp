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
#include <bitcoin/bitcoin/c/wallet/ec_public.h>
#include <bitcoin/bitcoin/c/internal/wallet/ec_public.hpp>

#include <bitcoin/bitcoin/c/internal/math/elliptic_curve.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>
#include <bitcoin/bitcoin/c/internal/wallet/ec_private.hpp>
#include <bitcoin/bitcoin/c/internal/wallet/payment_address.hpp>

extern "C" {

/// Static values
uint8_t bc_ec_public__compressed_even()
{
    return libbitcoin::wallet::ec_public::compressed_even;
}
uint8_t bc_ec_public__compressed_odd()
{
    return libbitcoin::wallet::ec_public::compressed_odd;
}
uint8_t bc_ec_public__uncompressed()
{
    return libbitcoin::wallet::ec_public::uncompressed;
}
uint8_t bc_ec_public__mainnet_p2kh()
{
    return libbitcoin::wallet::ec_public::mainnet_p2kh;
}
/// Constructors.
bc_ec_public_t* bc_create_ec_public()
{
    return new bc_ec_public_t{ new libbitcoin::wallet::ec_public };
}
bc_ec_public_t* bc_create_ec_public_copy(const bc_ec_public_t* other)
{
    return new bc_ec_public_t{ new libbitcoin::wallet::ec_public(
        *other->obj) };
}
bc_ec_public_t* bc_create_ec_public_Private(const bc_ec_private_t* secret)
{
    return new bc_ec_public_t{ new libbitcoin::wallet::ec_public(
        *secret->obj) };
}
bc_ec_public_t* bc_create_ec_public_Data(const bc_data_chunk_t* decoded)
{
    return new bc_ec_public_t{ new libbitcoin::wallet::ec_public(
        *decoded->obj) };
}
bc_ec_public_t* bc_create_ec_public_String(const char* base16)
{
    return new bc_ec_public_t{ new libbitcoin::wallet::ec_public(
        base16) };
}
bc_ec_public_t* bc_create_ec_public_CompPoint(
    const bc_ec_compressed_t* point)
{
    return new bc_ec_public_t{ new libbitcoin::wallet::ec_public(
        *point->obj) };
}
bc_ec_public_t* bc_create_ec_public_CompPoint_nocompress(
    const bc_ec_compressed_t* point)
{
    return new bc_ec_public_t{ new libbitcoin::wallet::ec_public(
        *point->obj, false) };
}
bc_ec_public_t* bc_create_ec_public_UncompPoint(
    const bc_ec_uncompressed_t* point)
{
    return new bc_ec_public_t{ new libbitcoin::wallet::ec_public(
        *point->obj) };
}
bc_ec_public_t* bc_create_ec_public_UncompPoint_compress(
    const bc_ec_uncompressed_t* point)
{
    return new bc_ec_public_t{ new libbitcoin::wallet::ec_public(
        *point->obj, true) };
}
/// Destructor
void bc_destroy_ec_public(bc_ec_public_t* self)
{
    delete self->obj;
    delete self;
}
/// Operators
bool bc_ec_public__less_than(const bc_ec_public_t* self,
    const bc_ec_public_t* other)
{
    return *self->obj < *other->obj;
}
bool bc_ec_public__equals(const bc_ec_public_t* self,
    const bc_ec_public_t* other)
{
    return *self->obj == *other->obj;
}
bool bc_ec_public__not_equals(const bc_ec_public_t* self,
    const bc_ec_public_t* other)
{
    return *self->obj != *other->obj;
}
void bc_ec_public__copy(bc_ec_public_t* self, const bc_ec_public_t* other)
{
    *self->obj = *other->obj;
}
// Skipping stream operators.
bool bc_ec_public__is_valid(const bc_ec_public_t* self)
{
    return static_cast<bool>(*self->obj);
}
/// Serializer.
bc_string_t* bc_ec_public__encoded(const bc_ec_public_t* self)
{
    return bc_create_string_StdString(self->obj->encoded());
}
/// Accessors.
bc_ec_compressed_t* bc_ec_public__point(const bc_ec_public_t* self)
{
    return new bc_ec_compressed_t{ new libbitcoin::ec_compressed(
        self->obj->point()) };
}
/*
uint16_t bc_ec_public_version(const bc_ec_public_t* self)
{
    return self->obj->version();
}
uint8_t bc_ec_public_payment_version(const bc_ec_public_t* self)
{
    return self->obj->payment_version();
}
uint8_t bc_ec_public_wif_version(const bc_ec_public_t* self)
{
    return self->obj->wif_version();
}
*/
bool bc_ec_public__compressed(const bc_ec_public_t* self)
{
    return self->obj->compressed();
}
/// Methods.
bool bc_ec_public__to_data(const bc_ec_public_t* self, bc_data_chunk_t* out)
{
    return self->obj->to_data(*out->obj);
}
bool bc_ec_public__to_uncompressed(
    const bc_ec_public_t* self, bc_ec_uncompressed_t* out)
{
    return self->obj->to_uncompressed(*out->obj);
}
bc_payment_address_t* bc_ec_public__to_payment_address(
    const bc_ec_public_t* self)
{
    return new bc_payment_address_t{ new libbitcoin::wallet::payment_address(
        self->obj->to_payment_address()) };
}
bc_payment_address_t* bc_ec_public__to_payment_address_Version(
    const bc_ec_public_t* self, uint8_t version)
{
    return new bc_payment_address_t{ new libbitcoin::wallet::payment_address(
        self->obj->to_payment_address(version)) };
}

}

