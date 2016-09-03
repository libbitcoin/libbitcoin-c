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
#ifndef LIBBITCOIN_C_CHAIN_STEALTH_H
#define LIBBITCOIN_C_CHAIN_STEALTH_H

#include <bitcoin/bitcoin/c/math/elliptic_curve.h>
#include <bitcoin/bitcoin/c/math/hash.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Differentiate subscription to payment address or stealth address.
/// v2 (deprecated) requires an explicit subscription type.
/// v3 eliminates the subscription type, which we map to 'unspecified'.
typedef enum bc_subscribe_type_t
{
    bc_subscribe_type_payment = 0,
    bc_subscribe_type_stealth = 1,
    bc_subscribe_type_unspecified = 2,
    bc_subscribe_type_unsubscribe = 3

} bc_subscribe_type_t;

/// This structure is used in the client-server protocol in v2/v3.
/// The stealth row excludes the sign byte (0x02) of the ephemeral public key.
typedef struct bc_stealth_compact_t bc_stealth_compact_t;
BC_DECLARE_VECTOR(stealth_compact_list, bc_stealth_compact_t);
// Constructor
bc_stealth_compact_t* bc_create_stealth_compact();
// Destructor
void bc_destroy_stealth_compact(bc_stealth_compact_t* self);
// Member variables
bc_hash_digest_t* bc_stealth_compact_ephemeral_public_key_hash(
    const bc_stealth_compact_t* self);
void bc_stealth_compact_set_ephemeral_public_key_hash(
    bc_stealth_compact_t* self, const bc_hash_digest_t* hash);
bc_short_hash_t* bc_stealth_compact_public_key_hash(
    const bc_stealth_compact_t* self);
void bc_stealth_compact_set_public_key_hash(
    bc_stealth_compact_t* self, const bc_short_hash_t* hash);
bc_hash_digest_t* bc_stealth_compact_transaction_hash(
    const bc_stealth_compact_t* self);
void bc_stealth_compact_set_transaction_hash(
    bc_stealth_compact_t* self, const bc_hash_digest_t* hash);

/// This structure is used between client and API callers in v2/v3.
/// The normal stealth row includes the sign byte of the ephemeral public key.
typedef struct bc_stealth_t bc_stealth_t;
BC_DECLARE_VECTOR(stealth_list, bc_stealth_t);
// Constructor
bc_stealth_t* bc_create_stealth();
// Destructor
void bc_destroy_stealth(bc_stealth_t* self);
// Member variables
bc_ec_compressed_t* bc_stealth_ephemeral_public_key(
    const bc_stealth_t* self);
void bc_stealth_set_ephemeral_public_key(
    bc_stealth_t* self, const bc_ec_compressed_t* key);
bc_short_hash_t* bc_stealth_public_key_hash(
    const bc_stealth_t* self);
void bc_stealth_set_public_key_hash(
    bc_stealth_t* self, const bc_short_hash_t* hash);
bc_hash_digest_t* bc_stealth_transaction_hash(
    const bc_stealth_t* self);
void bc_stealth_set_transaction_hash(
    bc_stealth_t* self, const bc_hash_digest_t* hash);

#ifdef __cplusplus
}
#endif

#endif

