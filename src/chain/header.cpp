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
#include <bitcoin/bitcoin/c/chain/header.h>
#include <bitcoin/bitcoin/c/internal/chain/header.hpp>

#include <bitcoin/bitcoin/c/internal/error.hpp>
#include <bitcoin/bitcoin/c/internal/chain/chain_state.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>
#include <bitcoin/bitcoin/c/internal/utility/vector.hpp>

extern "C" {

BC_IMPLEMENT_VECTOR(header_list, bc_header_t, bc_destroy_header,
    libbitcoin::chain::header::list);

// Constructor
bc_header_t* bc_create_header()
{
    return new bc_header_t{ new libbitcoin::chain::header, true };
}
bc_header_t* bc_create_header_copy(const bc_header_t* other)
{
    return new bc_header_t{ new libbitcoin::chain::header(*other->obj), true };
}
bc_header_t* bc_create_header_copy_with_Hash(const bc_header_t* other,
    const bc_hash_digest_t* hash)
{
    return new bc_header_t{ new libbitcoin::chain::header(
        *other->obj, *hash->obj), true };
}
bc_header_t* bc_create_header_Options(
    uint32_t version, const bc_hash_digest_t* previous_block_hash,
    const bc_hash_digest_t* merkle, uint32_t timestamp, uint32_t bits,
    uint32_t nonce)
{
    return new bc_header_t{ new libbitcoin::chain::header(
        version, *previous_block_hash->obj, *merkle->obj, timestamp,
        bits, nonce), true };
}

// Destructor
void bc_destroy_header(const bc_header_t* self)
{
    if (self->delete_obj)
        delete self->obj;
    delete self;
}

// Operators
void bc_header__copy(bc_header_t* self, const bc_header_t* other)
{
    *self->obj = *other->obj;
}

bool bc_header__equals(const bc_header_t* self, const bc_header_t* other)
{
    return *self->obj == *other->obj;
}
bool bc_header__not_equals(const bc_header_t* self, const bc_header_t* other)
{
    return *self->obj != *other->obj;
}

// Member functions
bc_header_t* bc_header__factory_from_data(
    const bc_data_chunk_t* data)
{
    return new bc_header_t{ new libbitcoin::chain::header(
        libbitcoin::chain::header::factory_from_data(*data->obj)), true };
}

bool bc_header__from_data(
    bc_header_t* self, const bc_data_chunk_t* data)
{
    return self->obj->from_data(*data->obj);
}

bool bc_header__is_valid(const bc_header_t* self)
{
    return self->obj->is_valid();
}

bc_data_chunk_t* bc_header__to_data(const bc_header_t* self)
{
    return bc_create_data_chunk_Internal(self->obj->to_data());
}

uint64_t bc_header__satoshi_fixed_size()
{
    return libbitcoin::chain::header::satoshi_fixed_size();
}
uint64_t bc_header__serialized_size(const bc_header_t* self)
{
    return self->obj->serialized_size();
}

// Member variables
uint32_t bc_header__version(const bc_header_t* self)
{
    return self->obj->version();
}
void bc_header__set_version(bc_header_t* self, uint32_t version)
{
    self->obj->set_version(version);
}

bc_hash_digest_t* bc_header__previous_block_hash(const bc_header_t* self)
{
    return new bc_hash_digest_t{ new libbitcoin::hash_digest(
        self->obj->previous_block_hash()), true };
}
void bc_header__set_previous_block_hash(bc_header_t* self,
    const bc_hash_digest_t* previous_block_hash)
{
    self->obj->set_previous_block_hash(*previous_block_hash->obj);
}

bc_hash_digest_t* bc_header__merkle(const bc_header_t* self)
{
    return new bc_hash_digest_t{ new libbitcoin::hash_digest(
        self->obj->merkle()), true };
}
void bc_header__set_merkle(bc_header_t* self,
    const bc_hash_digest_t* merkle)
{
    self->obj->set_merkle(*merkle->obj);
}

uint32_t bc_header__timestamp(const bc_header_t* self)
{
    return self->obj->timestamp();
}
void bc_header__set_timestamp(bc_header_t* self, uint32_t timestamp)
{
    self->obj->set_timestamp(timestamp);
}

uint32_t bc_header__bits(const bc_header_t* self)
{
    return self->obj->bits();
}
void bc_header__set_bits(bc_header_t* self, uint32_t bits)
{
    self->obj->set_bits(bits);
}

uint32_t bc_header__nonce(const bc_header_t* self)
{
    return self->obj->nonce();
}
void bc_header__set_nonce(bc_header_t* self, uint32_t nonce)
{
    self->obj->set_nonce(nonce);
}

bc_hash_digest_t* bc_header__hash(const bc_header_t* self)
{
    return bc_create_hash_digest_Internal(self->obj->hash());
}

bool bc_header__is_valid_timestamp(const bc_header_t* self)
{
    return self->obj->is_valid_timestamp();
}
bool bc_header__is_valid_proof_of_work(const bc_header_t* self)
{
    return self->obj->is_valid_proof_of_work();
}

bc_error_code_t* bc_header__check(const bc_header_t* self)
{
    return new bc_error_code_t{ new std::error_code(self->obj->check()) };
}
bc_error_code_t* bc_header__accept(const bc_header_t* self,
    const bc_chain_state_t* state)
{
    return new bc_error_code_t{ new std::error_code(self->obj->accept(
        *state->obj)) };
}

} // extern C

