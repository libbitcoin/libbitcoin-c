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
#ifndef LIBBITCOIN_C_WALLET_HD_PUBLIC_KEY_H
#define LIBBITCOIN_C_WALLET_HD_PUBLIC_KEY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <bitcoin/bitcoin/c/string.h>

#ifdef __cplusplus
extern "C" {
#endif

/// A constant used in key derivation.
uint32_t bc_hd_first_hardened_key();

/// An hd key chain code.
size_t bc_hd_chain_code_size();
typedef struct bc_hd_chain_code_t bc_hd_chain_code_t;
void bc_destroy_hd_chain_code(bc_hd_chain_code_t* self);

/// A decoded hd public or private key.
size_t bc_hd_key_size();
typedef struct bc_hd_key_t bc_hd_key_t;
void bc_destroy_hd_key(bc_hd_key_t* self);

/// Key derivation information used in the serialization format.
typedef struct bc_hd_lineage_t bc_hd_lineage_t;
// prefixes
uint64_t bc_hd_lineage_get_prefixes(bc_hd_lineage_t* self);
void bc_hd_lineage_set_prefixes(
    bc_hd_lineage_t* self, uint64_t prefixes);
// depth
uint8_t bc_hd_lineage_get_depth(bc_hd_lineage_t* self);
void bc_hd_lineage_set_depth(
    bc_hd_lineage_t* self, uint8_t depth);
// parent_fingerprint
uint32_t bc_hd_lineage_get_parent_fingerprint(bc_hd_lineage_t* self);
void bc_hd_lineage_set_parent_fingerprint(
    bc_hd_lineage_t* self,uint32_t parent_fingerprint);
// child_number
uint32_t bc_hd_lineage_get_child_number(bc_hd_lineage_t* self);
void bc_hd_lineage_set_child_number(
    bc_hd_lineage_t* self, uint32_t child_number);
// Comparison operators
bool bc_hd_lineage_equals(bc_hd_lineage_t* a, bc_hd_lineage_t* b);
bool bc_hd_lineage_not_equals(bc_hd_lineage_t* a, bc_hd_lineage_t* b);

/// An extended public key, as defined by BIP 32.
typedef struct bc_hd_public_t bc_hd_public_t;
uint32_t bc_hd_public_mainnet();
uint32_t bc_hd_public_to_prefix(uint64_t prefixes);
/// Constructors.
// hd_public();
bc_hd_public_t* bc_create_hd_public();
// hd_public(const hd_public& other);
bc_hd_public_t* bc_create_hd_public_copy(bc_hd_public_t* other);
// hd_public(const hd_key& public_key);
bc_hd_public_t* bc_create_hd_public_Key(bc_hd_key_t* public_key);
// hd_public(const hd_key& public_key, uint32_t prefix);
bc_hd_public_t* bc_create_hd_public_Key_Prefix(
    bc_hd_key_t* public_key, uint32_t prefix);
// hd_public(const std::string& encoded);
bc_hd_public_t* bc_create_hd_public_String(const char* encoded);
// hd_public(const std::string& encoded, uint32_t prefix);
bc_hd_public_t* bc_create_hd_public_String_Prefix(
    const char* encoded, uint32_t prefix);
/// Destructor
void bc_destroy_hd_public(bc_hd_public_t* self);
/// Operators.
bool bc_hd_public_less_than(bc_hd_public_t* self, bc_hd_public_t* other);
bool bc_hd_public_equals(bc_hd_public_t* self, bc_hd_public_t* other);
bool bc_hd_public_not_equals(bc_hd_public_t* self, bc_hd_public_t* other);
bc_hd_public_t* bc_hd_public_copy(bc_hd_public_t* self, bc_hd_public_t* other);
// Ignored:
//  friend std::istream& operator>>(std::istream& in, hd_public& to);
//  friend std::ostream& operator<<(std::ostream& out, const hd_public& of);
bool bc_hd_public_to_bool(bc_hd_public_t* self);
// TODO:
//   operator const ec_compressed&() const;
/// Serializer.
bc_string_t* bc_hd_public_encoded(bc_hd_public_t* self);
/// Accessors.
bc_hd_chain_code_t* bc_hd_public_chain_code(bc_hd_public_t* self);
bc_hd_lineage_t* bc_hd_public_lineage(bc_hd_public_t* self);
// TODO:
//   const ec_compressed& point() const;
/// Methods.
bc_hd_key_t* bc_hd_public_to_hd_key(bc_hd_public_t* self);
bc_hd_public_t* bc_hd_public_derive_public(
    bc_hd_public_t* self, uint32_t index);

#ifdef __cplusplus
}
#endif

#endif

