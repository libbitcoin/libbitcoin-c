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
#ifndef LIBBITCOIN_C_MATH_CRYPTO_H
#define LIBBITCOIN_C_MATH_CRYPTO_H

#include <stdint.h>
#include <bitcoin/bitcoin/c/utility/data.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The secret for aes256 block cypher.
 */
uint8_t bc_aes256_key_size();
BC_DECLARE_BYTE_ARRAY(aes_secret);

/**
 * The data block for use with aes256 block cypher.
 */
uint8_t bc_aes256_block_size();
BC_DECLARE_BYTE_ARRAY(aes_block);

/**
 * Perform aes256 encryption on the specified data block.
 */
void bc_aes256_encrypt(const bc_aes_secret_t* key, bc_aes_block_t* block);

/**
 * Perform aes256 decryption on the specified data block.
 */
void bc_aes256_decrypt(const bc_aes_secret_t* key, bc_aes_block_t* block);

#ifdef __cplusplus
}
#endif

#endif

