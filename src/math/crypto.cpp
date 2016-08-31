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
#include <bitcoin/bitcoin/c/math/crypto.h>
#include <bitcoin/bitcoin/c/internal/math/crypto.hpp>

#include <bitcoin/bitcoin/c/internal/utility/data.hpp>

// Define these aliases so the macros for implementing byte array will work
namespace libbitcoin {
    BC_CONSTEXPR uint8_t aes_secret_size = aes256_key_size;
    BC_CONSTEXPR uint8_t aes_block_size = aes256_block_size;
} // namespace libbitcoin

extern "C" {

uint8_t bc_aes256_key_size()
{
    return libbitcoin::aes256_key_size;
}
BC_IMPLEMENT_BYTE_ARRAY(aes_secret);

uint8_t bc_aes256_block_size()
{
    return libbitcoin::aes256_block_size;
}
BC_IMPLEMENT_BYTE_ARRAY(aes_block);

void bc_aes256_encrypt(const bc_aes_secret_t* key, bc_aes_block_t* block)
{
    libbitcoin::aes256_encrypt(*key->obj, *block->obj);
}

void bc_aes256_decrypt(const bc_aes_secret_t* key, bc_aes_block_t* block)
{
    libbitcoin::aes256_decrypt(*key->obj, *block->obj);
}

} // extern C

