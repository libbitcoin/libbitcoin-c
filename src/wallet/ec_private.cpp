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
#include <bitcoin/bitcoin/c/wallet/ec_private.h>
#include <bitcoin/bitcoin/c/internal/wallet/ec_private.hpp>

#include <bitcoin/bitcoin/c/internal/math/elliptic_curve.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>
#include <bitcoin/bitcoin/c/internal/wallet/payment_address.hpp>

extern "C" {

BC_IMPLEMENT_BYTE_ARRAY__CUSTOM_NAMESPACE(
    wif_uncompressed, libbitcoin::wallet);

BC_IMPLEMENT_BYTE_ARRAY__CUSTOM_NAMESPACE(
    wif_compressed, libbitcoin::wallet);

uint8_t bc_ec_private_wif()
{
    return libbitcoin::wallet::ec_private::wif;
}
uint8_t bc_ec_private_mainnet_p2kh()
{
    return libbitcoin::wallet::ec_private::mainnet_p2kh;
}
uint16_t bc_ec_private_mainnet()
{
    return libbitcoin::wallet::ec_private::mainnet;
}
uint8_t bc_ec_private_compressed_sentinel()
{
    return libbitcoin::wallet::ec_private::compressed_sentinel;
}

uint8_t bc_ec_private_to_address_prefix(uint16_t version)
{
    return libbitcoin::wallet::ec_private::to_address_prefix(version);
}
uint8_t bc_ec_private_to_wif_prefix(uint16_t version)
{
    return libbitcoin::wallet::ec_private::to_wif_prefix(version);
}
uint8_t bc_ec_private_to_version(uint8_t address, uint8_t wif)
{
    return libbitcoin::wallet::ec_private::to_version(address, wif);
}

bc_ec_private_t* bc_create_ec_private()
{
    return new bc_ec_private_t{ new libbitcoin::wallet::ec_private };
}
bc_ec_private_t* bc_create_ec_private_copy(const bc_ec_private_t* other)
{
    return new bc_ec_private_t{ new libbitcoin::wallet::ec_private(
        *other->obj) };
}
bc_ec_private_t* bc_create_ec_private_String(
    const char* wif)
{
    return new bc_ec_private_t{ new libbitcoin::wallet::ec_private(
        wif) };
}
bc_ec_private_t* bc_create_ec_private_String_Version(
    const char* wif, uint8_t version)
{
    return new bc_ec_private_t{ new libbitcoin::wallet::ec_private(
        wif, version) };
}
bc_ec_private_t* bc_create_ec_private_WifComp(
    const bc_wif_compressed_t* wif)
{
    return new bc_ec_private_t{ new libbitcoin::wallet::ec_private(
        *wif->obj) };
}
bc_ec_private_t* bc_create_ec_private_WifComp_Version(
    const bc_wif_compressed_t* wif, uint8_t version)
{
    return new bc_ec_private_t{ new libbitcoin::wallet::ec_private(
        *wif->obj, version) };
}
bc_ec_private_t* bc_create_ec_private_WifUncomp(
    const bc_wif_uncompressed_t* wif)
{
    return new bc_ec_private_t{ new libbitcoin::wallet::ec_private(
        *wif->obj) };
}
bc_ec_private_t* bc_create_ec_private_WifUncomp_Version(
    const bc_wif_uncompressed_t* wif, uint8_t version)
{
    return new bc_ec_private_t{ new libbitcoin::wallet::ec_private(
        *wif->obj, version) };
}
bc_ec_private_t* bc_create_ec_private_Secret(
    const bc_ec_secret_t* secret)
{
    return new bc_ec_private_t{ new libbitcoin::wallet::ec_private(
        *secret->obj) };
}
bc_ec_private_t* bc_create_ec_private_Secret_Version(
    const bc_ec_secret_t* secret, uint16_t version)
{
    return new bc_ec_private_t{ new libbitcoin::wallet::ec_private(
        *secret->obj, version) };
}
bc_ec_private_t* bc_create_ec_private_Secret_Version_nocompress(
    const bc_ec_secret_t* secret, uint16_t version)
{
    return new bc_ec_private_t{ new libbitcoin::wallet::ec_private(
        *secret->obj, version, false) };
}

void bc_destroy_ec_private(bc_ec_private_t* self)
{
    delete self->obj;
    delete self;
}

bool bc_ec_private_less_than(const bc_ec_private_t* self,
    const bc_ec_private_t* other)
{
    return *self->obj < *other->obj;
}
bool bc_ec_private_equals(const bc_ec_private_t* self,
    const bc_ec_private_t* other)
{
    return *self->obj == *other->obj;
}
bool bc_ec_private_not_equals(const bc_ec_private_t* self,
    const bc_ec_private_t* other)
{
    return *self->obj != *other->obj;
}
void bc_ec_private_copy(bc_ec_private_t* self, const bc_ec_private_t* other)
{
    *self->obj = *other->obj;
}
bool bc_ec_private_is_valid(const bc_ec_private_t* self)
{
    return static_cast<bool>(*self->obj);
}

bc_string_t* bc_ec_private_encoded(const bc_ec_private_t* self)
{
    return bc_create_string_StdString(self->obj->encoded());
}

bc_ec_secret_t* bc_ec_private_secret(const bc_ec_private_t* self)
{
    return new bc_ec_secret_t{ new libbitcoin::ec_secret(
        self->obj->secret()) };
}
uint16_t bc_ec_private_version(const bc_ec_private_t* self)
{
    return self->obj->version();
}
uint8_t bc_ec_private_payment_version(const bc_ec_private_t* self)
{
    return self->obj->payment_version();
}
uint8_t bc_ec_private_wif_version(const bc_ec_private_t* self)
{
    return self->obj->wif_version();
}
bool bc_ec_private_compressed(const bc_ec_private_t* self)
{
    return self->obj->compressed();
}

bc_payment_address_t* bc_ec_private_to_payment_address(
    const bc_ec_private_t* self)
{
    return new bc_payment_address_t{ new libbitcoin::wallet::payment_address(
        self->obj->to_payment_address()) };
}

}

