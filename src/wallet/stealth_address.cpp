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
#include <bitcoin/bitcoin/c/wallet/stealth_address.h>
#include <bitcoin/bitcoin/c/internal/wallet/stealth_address.hpp>

#include <bitcoin/bitcoin/c/internal/math/elliptic_curve.hpp>
#include <bitcoin/bitcoin/c/internal/utility/binary.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>

extern "C" {

/// Static values
uint8_t bc_stealth_address__mainnet_p2kh()
{
    return libbitcoin::wallet::stealth_address::mainnet_p2kh;
}
uint8_t bc_stealth_address__reuse_key_flag()
{
    return libbitcoin::wallet::stealth_address::reuse_key_flag;
}
uint8_t bc_stealth_address__max_filter_bits()
{
    return libbitcoin::wallet::stealth_address::max_filter_bits;
}

/// Constructors.
bc_stealth_address_t* bc_create_stealth_address()
{
    return new bc_stealth_address_t{ new libbitcoin::wallet::stealth_address };
}
bc_stealth_address_t* bc_create_stealth_address_Data(
    const bc_data_chunk_t* decoded)
{
    return new bc_stealth_address_t{ new libbitcoin::wallet::stealth_address(
        *decoded->obj) };
}
bc_stealth_address_t* bc_create_stealth_address_String(const char* encoded)
{
    return new bc_stealth_address_t{ new libbitcoin::wallet::stealth_address(
        encoded) };
}
bc_stealth_address_t* bc_create_stealth_address_copy(
    const bc_stealth_address_t* other)
{
    return new bc_stealth_address_t{ new libbitcoin::wallet::stealth_address(
        *other->obj) };
}
bc_stealth_address_t* bc_create_stealth_address_Options(
    const bc_binary_t* filter, const bc_ec_compressed_t* scan_key,
    const bc_point_list_t* spend_keys, uint8_t signatures, uint8_t version)
{
    return new bc_stealth_address_t{ new libbitcoin::wallet::stealth_address(
        *filter->obj, *scan_key->obj, *spend_keys->obj,
        signatures, version) };
}

/// Destructor
void bc_destroy_stealth_address(bc_stealth_address_t* self)
{
    delete self->obj;
    delete self;
}

/// Operators.
bool bc_stealth_address__less_than(const bc_stealth_address_t* self,
    const bc_stealth_address_t* other)
{
    return *self->obj < *other->obj;
}
bool bc_stealth_address__equals(const bc_stealth_address_t* self,
    const bc_stealth_address_t* other)
{
    return *self->obj == *other->obj;
}
bool bc_stealth_address__not_equals(const bc_stealth_address_t* self,
    const bc_stealth_address_t* other)
{
    return *self->obj != *other->obj;
}
bc_stealth_address_t* bc_stealth_address__copy(
    bc_stealth_address_t* self, const bc_stealth_address_t* other)
{
    *self->obj = *other->obj;
    return self;
}

/// Cast operators.
bool bc_stealth_address__is_valid(const bc_stealth_address_t* self)
{
    return static_cast<bool>(*self->obj);
}

/// Serializer.
bc_string_t* bc_stealth_address__encoded(const bc_stealth_address_t* self)
{
    return bc_create_string_StdString(self->obj->encoded());
}

/// Accessors.
uint8_t bc_stealth_address__version(const bc_stealth_address_t* self)
{
    return self->obj->version();
}
bc_ec_compressed_t* bc_stealth_address__scan_key(
    const bc_stealth_address_t* self)
{
    return new bc_ec_compressed_t{ new libbitcoin::ec_compressed(
        self->obj->scan_key()) };
}
bc_point_list_t* bc_stealth_address__spend_keys(
    const bc_stealth_address_t* self)
{
    return new bc_point_list_t{ new libbitcoin::point_list(
        self->obj->spend_keys()), true };
}
uint8_t bc_stealth_address__signatures(const bc_stealth_address_t* self)
{
    return self->obj->signatures();
}
bc_binary_t* bc_stealth_address__filter(const bc_stealth_address_t* self)
{
    return new bc_binary_t{ new libbitcoin::binary(self->obj->filter()) };
}

/// Methods.
bc_data_chunk_t* bc_stealth_address__to_chunk(
    const bc_stealth_address_t* self)
{
    return bc_create_data_chunk_Internal(self->obj->to_chunk());
}

}

