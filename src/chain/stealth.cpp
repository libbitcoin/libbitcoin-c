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
#include <bitcoin/bitcoin/c/chain/stealth.h>
#include <bitcoin/bitcoin/c/internal/chain/stealth.hpp>

#include <bitcoin/bitcoin/c/internal/math/elliptic_curve.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>

BC_IMPLEMENT_VECTOR(stealth_compact_list, bc_stealth_compact_t,
    bc_destroy_stealth_compact, libbitcoin::chain::stealth_compact::list);

BC_IMPLEMENT_VECTOR(stealth_list, bc_stealth_t,
    bc_destroy_stealth, libbitcoin::chain::stealth::list);

extern "C" {

// Constructor
bc_stealth_compact_t* bc_create_stealth_compact()
{
    return new bc_stealth_compact_t{ new libbitcoin::chain::stealth_compact };
}
// Destructor
void bc_destroy_stealth_compact(bc_stealth_compact_t* self)
{
    delete self->obj;
    delete self;
}
// Member variables
bc_hash_digest_t* bc_stealth_compact_ephemeral_public_key_hash(
    const bc_stealth_compact_t* self)
{
    return bc_create_hash_digest_Internal(
        self->obj->ephemeral_public_key_hash);
}
void bc_stealth_compact_set_ephemeral_public_key_hash(
    bc_stealth_compact_t* self, const bc_hash_digest_t* hash)
{
    self->obj->ephemeral_public_key_hash = *hash->obj;
}
bc_short_hash_t* bc_stealth_compact_public_key_hash(
    const bc_stealth_compact_t* self)
{
    return bc_create_short_hash_Internal(
        self->obj->public_key_hash);
}
void bc_stealth_compact_set_public_key_hash(
    bc_stealth_compact_t* self, const bc_short_hash_t* hash)
{
    self->obj->public_key_hash = *hash->obj;
}
bc_hash_digest_t* bc_stealth_compact_transaction_hash(
    const bc_stealth_compact_t* self)
{
    return bc_create_hash_digest_Internal(
        self->obj->transaction_hash);
}
void bc_stealth_compact_set_transaction_hash(
    bc_stealth_compact_t* self, const bc_hash_digest_t* hash)
{
    self->obj->transaction_hash = *hash->obj;
}

// Constructor
bc_stealth_t* bc_create_stealth()
{
    return new bc_stealth_t{ new libbitcoin::chain::stealth };
}
// Destructor
void bc_destroy_stealth(bc_stealth_t* self)
{
    delete self->obj;
    delete self;
}
// Member variables
bc_ec_compressed_t* bc_stealth_ephemeral_public_key(
    const bc_stealth_t* self)
{
    return new bc_ec_compressed_t{ new libbitcoin::ec_compressed(
        self->obj->ephemeral_public_key) };
}
void bc_stealth_set_ephemeral_public_key(
    bc_stealth_t* self, const bc_ec_compressed_t* key)
{
    self->obj->ephemeral_public_key = *key->obj;
}
bc_short_hash_t* bc_stealth_public_key_hash(
    const bc_stealth_t* self)
{
    return bc_create_short_hash_Internal(self->obj->public_key_hash);
}
void bc_stealth_set_public_key_hash(
    bc_stealth_t* self, const bc_short_hash_t* hash)
{
    self->obj->public_key_hash = *hash->obj;
}
bc_hash_digest_t* bc_stealth_transaction_hash(
    const bc_stealth_t* self)
{
    return bc_create_hash_digest_Internal(self->obj->transaction_hash);
}
void bc_stealth_set_transaction_hash(
    bc_stealth_t* self, const bc_hash_digest_t* hash)
{
    self->obj->transaction_hash = *hash->obj;
}

} // extern C

