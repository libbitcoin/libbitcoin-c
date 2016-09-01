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

#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>
#include <bitcoin/bitcoin/c/internal/utility/vector.hpp>

BC_IMPLEMENT_VECTOR(header_list, bc_header_t, bc_destroy_header,
    libbitcoin::chain::header::list);

extern "C" {

// Static functions
bc_header_t* bc_header_factory_from_data(
    const bc_data_chunk_t* data)
{
    return new bc_header_t{ new libbitcoin::chain::header(
        libbitcoin::chain::header::factory_from_data(*data->obj)) };
}
bc_header_t* bc_header_factory_from_data_without_transaction_count(
    const bc_data_chunk_t* data)
{
    return new bc_header_t{ new libbitcoin::chain::header(
        libbitcoin::chain::header::factory_from_data(
            *data->obj, false)) };
}
uint64_t bc_header_satoshi_fixed_size_without_transaction_count()
{
    return libbitcoin::chain::header::satoshi_fixed_size_without_transaction_count();
}

// Constructor
bc_header_t* bc_create_header()
{
    return new bc_header_t{ new libbitcoin::chain::header };
}
bc_header_t* bc_create_header_copy(const bc_header_t* other)
{
    return new bc_header_t{ new libbitcoin::chain::header(*other->obj) };
}
bc_header_t* bc_create_header_Options(
    uint32_t version, const bc_hash_digest_t* previous_block_hash,
    const bc_hash_digest_t* merkle, uint32_t timestamp, uint32_t bits,
    uint32_t nonce, uint64_t transaction_count)
{
    return new bc_header_t{ new libbitcoin::chain::header(
        version, *previous_block_hash->obj, *merkle->obj, timestamp,
        bits, nonce, transaction_count) };
}

// Destructor
void bc_destroy_header(const bc_header_t* self)
{
    delete self->obj;
    delete self;
}

// Member functions
bool bc_header_from_data(
    bc_header_t* self, const bc_data_chunk_t* data)
{
    return self->obj->from_data(*data->obj);
}
bc_data_chunk_t* bc_header_to_data(const bc_header_t* self)
{
    return bc_create_data_chunk_Internal(self->obj->to_data());
}
bc_hash_digest_t* bc_header_hash(const bc_header_t* self)
{
    return bc_create_hash_digest_Internal(self->obj->hash());
}
bool bc_header_is_valid(const bc_header_t* self)
{
    return self->obj->is_valid();
}
void bc_header_reset(bc_header_t* self)
{
    self->obj->reset();
}
uint64_t bc_header_serialized_size(const bc_header_t* self)
{
    return self->obj->serialized_size();
}
uint64_t bc_header_serialized_size_without_transaction_count(
    const bc_header_t* self)
{
    return self->obj->serialized_size(false);
}

// Member variables
uint32_t bc_header_version(const bc_header_t* self)
{
    return self->obj->version;
}
void bc_header_set_version(const bc_header_t* self, uint32_t version)
{
    self->obj->version = version;
}
bc_hash_digest_t* bc_header_previous_block_hash(const bc_header_t* self)
{
    return bc_create_hash_digest_Internal(self->obj->previous_block_hash);
}
void bc_header_set_previous_block_hash(const bc_header_t* self,
    const bc_hash_digest_t* previous_block_hash)
{
    self->obj->previous_block_hash = *previous_block_hash->obj;
}
bc_hash_digest_t* bc_header_merkle(const bc_header_t* self)
{
    return bc_create_hash_digest_Internal(self->obj->merkle);
}
void bc_header_set_merkle(const bc_header_t* self,
    const bc_hash_digest_t* merkle)
{
    self->obj->merkle = *merkle->obj;
}
uint32_t bc_header_timestamp(const bc_header_t* self)
{
    return self->obj->timestamp;
}
void bc_header_set_timestamp(const bc_header_t* self, uint32_t timestamp)
{
    self->obj->timestamp = timestamp;
}
uint32_t bc_header_bits(const bc_header_t* self)
{
    return self->obj->bits;
}
void bc_header_set_bits(const bc_header_t* self, uint32_t bits)
{
    self->obj->bits = bits;
}
uint32_t bc_header_nonce(const bc_header_t* self)
{
    return self->obj->nonce;
}
void bc_header_set_nonce(const bc_header_t* self, uint32_t nonce)
{
    self->obj->nonce = nonce;
}

// The longest size (64) of a protocol variable int is deserialized here.
// WHen writing a block the size of the transaction collection is used.
uint32_t bc_header_transaction_count(const bc_header_t* self)
{
    return self->obj->transaction_count;
}
void bc_header_set_transaction_count(const bc_header_t* self,
    uint32_t transaction_count)
{
    self->obj->transaction_count = transaction_count;
}

} // extern C

