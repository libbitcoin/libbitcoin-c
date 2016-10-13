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
#include <bitcoin/bitcoin/c/wallet/hd_public.h>
#include <bitcoin/bitcoin/c/internal/wallet/hd_public.hpp>

#include <bitcoin/bitcoin/c/internal/math/elliptic_curve.hpp>

extern "C" {

uint32_t bc_hd_first_hardened_key()
{
    return libbitcoin::wallet::hd_first_hardened_key;
}

/// An hd key chain code.
size_t bc_hd_chain_code_size()
{
    return libbitcoin::wallet::hd_chain_code_size;
}
void bc_destroy_hd_chain_code(bc_hd_chain_code_t* self)
{
    delete self->obj;
    delete self;
}

/// A decoded hd public or private key.
size_t bc_hd_key_size()
{
    return libbitcoin::wallet::hd_key_size;
}
void bc_destroy_hd_key(bc_hd_key_t* self)
{
    delete self->obj;
    delete self;
}

// prefixes
uint64_t bc_hd_lineage__get_prefixes(bc_hd_lineage_t* self)
{
    return self->obj->prefixes;
}
void bc_hd_lineage__set_prefixes(
    bc_hd_lineage_t* self, uint64_t prefixes)
{
    self->obj->prefixes = prefixes;
}
// depth
uint8_t bc_hd_lineage__get_depth(bc_hd_lineage_t* self)
{
    return self->obj->depth;
}
void bc_hd_lineage__set_depth(
    bc_hd_lineage_t* self, uint8_t depth)
{
    self->obj->depth = depth;
}
// parent_fingerprint
uint32_t bc_hd_lineage__get_parent_fingerprint(bc_hd_lineage_t* self)
{
    return self->obj->parent_fingerprint;
}
void bc_hd_lineage__set_parent_fingerprint(
    bc_hd_lineage_t* self,uint32_t parent_fingerprint)
{
    self->obj->parent_fingerprint = parent_fingerprint;
}
// child_number
uint32_t bc_hd_lineage__get_child_number(bc_hd_lineage_t* self)
{
    return self->obj->child_number;
}
void bc_hd_lineage__set_child_number(
    bc_hd_lineage_t* self, uint32_t child_number)
{
    self->obj->child_number = child_number;
}
// Comparison operators
bool bc_hd_lineage__equals(bc_hd_lineage_t* a, bc_hd_lineage_t* b)
{
    return *a->obj == *b->obj;
}
bool bc_hd_lineage__not_equals(bc_hd_lineage_t* a, bc_hd_lineage_t* b)
{
    return *a->obj != *b->obj;
}

uint32_t bc_hd_public__mainnet()
{
    return libbitcoin::wallet::hd_public::mainnet;
}
uint32_t bc_hd_public__to_prefix(uint64_t prefixes)
{
    return libbitcoin::wallet::hd_public::to_prefix(prefixes);
}
bc_hd_public_t* bc_create_hd_public()
{
    return new bc_hd_public_t{
        new libbitcoin::wallet::hd_public, true };
}
bc_hd_public_t* bc_create_hd_public_copy(const bc_hd_public_t* other)
{
    return new bc_hd_public_t{
        new libbitcoin::wallet::hd_public(*other->obj), true };
}
bc_hd_public_t* bc_create_hd_public_Key(bc_hd_key_t* public_key)
{
    return new bc_hd_public_t{
        new libbitcoin::wallet::hd_public(*public_key->obj), true };
}
bc_hd_public_t* bc_create_hd_public_Key_Prefix(
    bc_hd_key_t* public_key, uint32_t prefix)
{
    return new bc_hd_public_t{
        new libbitcoin::wallet::hd_public(*public_key->obj, prefix), true };
}
bc_hd_public_t* bc_create_hd_public_String(const char* encoded)
{
    return new bc_hd_public_t{
        new libbitcoin::wallet::hd_public(encoded), true };
}
bc_hd_public_t* bc_create_hd_public_String_Prefix(
    const char* encoded, uint32_t prefix)
{
    return new bc_hd_public_t{
        new libbitcoin::wallet::hd_public(encoded, prefix), true };
}
void bc_destroy_hd_public(bc_hd_public_t* self)
{
    if (self->delete_obj)
        delete self->obj;
    delete self;
}
bool bc_hd_public__less_than(
    const bc_hd_public_t* self, const bc_hd_public_t* other)
{
    return *self->obj < *other->obj;
}
bool bc_hd_public__equals(
    const bc_hd_public_t* self, const bc_hd_public_t* other)
{
    return *self->obj == *other->obj;
}
bool bc_hd_public__not_equals(
    const bc_hd_public_t* self, const bc_hd_public_t* other)
{
    return *self->obj != *other->obj;
}
bc_hd_public_t* bc_hd_public__copy(
    bc_hd_public_t* self, const bc_hd_public_t* other)
{
    *self->obj = *other->obj;
}
bool bc_hd_public__is_valid(const bc_hd_public_t* self)
{
    return static_cast<bool>(*self->obj);
}
bc_string_t* bc_hd_public__encoded(const bc_hd_public_t* self)
{
    std::string encoded = self->obj->encoded();
    return bc_create_string_Length(encoded.data(), encoded.length());
}
bc_hd_chain_code_t* bc_hd_public__chain_code(const bc_hd_public_t* self)
{
    auto &chain_code = self->obj->chain_code();
    bc_hd_chain_code_t* result = new bc_hd_chain_code_t;
    result->obj = new libbitcoin::wallet::hd_chain_code(chain_code);
    return result;
}
bc_hd_lineage_t* bc_hd_public__lineage(const bc_hd_public_t* self)
{
    auto &lineage = self->obj->lineage();
    bc_hd_lineage_t* result = new bc_hd_lineage_t;
    result->obj = new libbitcoin::wallet::hd_lineage(lineage);
    return result;
}
bc_ec_compressed_t* bc_hd_public__point(const bc_hd_public_t* self)
{
    return new bc_ec_compressed_t{ new libbitcoin::ec_compressed(
        self->obj->point()), true };
}
bc_hd_key_t* bc_hd_public__to_hd_key(const bc_hd_public_t* self)
{
    return new bc_hd_key_t{ new libbitcoin::wallet::hd_key(
        self->obj->to_hd_key()) };
}
bc_hd_public_t* bc_hd_public__derive_public(
    const bc_hd_public_t* self, uint32_t index)
{
    return new bc_hd_public_t{ new libbitcoin::wallet::hd_public(
        self->obj->derive_public(index)), true };
}

}

