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
#include <bitcoin/bitcoin/c/formats/base_16.h>

#include <bitcoin/bitcoin/formats/base_16.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>

extern "C" {

bool bc_is_base16(const char c)
{
    return libbitcoin::is_base16(c);
}

bc_string_t* bc_encode_base16(const bc_data_chunk_t* data)
{
    auto encoded = libbitcoin::encode_base16(*data->obj);
    return bc_create_string_Length(encoded.data(), encoded.length());
}

bool bc_decode_base16(bc_data_chunk_t* out, const char* in)
{
    return libbitcoin::decode_base16(*out->obj, in);
}

bc_string_t* bc_encode_hash(const bc_hash_digest_t* hash)
{
    auto encoded = libbitcoin::encode_hash(*hash->obj);
}

bool bc_decode_hash(bc_hash_digest_t* out, const char* in)
{
    return libbitcoin::decode_hash(*out->obj, in);
}

bc_hash_digest_t* bc_hash_literal(const char (*string)[65])
{
    return new bc_hash_digest_t{ new libbitcoin::hash_digest(
        libbitcoin::hash_literal(*string)) };
}

}

