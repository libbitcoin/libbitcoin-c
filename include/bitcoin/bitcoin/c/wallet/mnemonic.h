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
#ifndef LIBBITCOIN_C_WALLET_MNEMONIC_H
#define LIBBITCOIN_C_WALLET_MNEMONIC_H

#include <stdbool.h>
#include <stddef.h>
#include <bitcoin/bitcoin/c/math/hash.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>
#include <bitcoin/bitcoin/c/wallet/dictionary.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A valid mnemonic word count is evenly divisible by this number.
 */
size_t bc_mnemonic_word_multiple();

/**
 * A valid seed byte count is evenly divisible by this number.
 */
size_t bc_mnemonic_seed_multiple();

/**
 * Represents a mnemonic word list.
 */
typedef struct bc_string_list_t bc_word_list_t;

/**
 * Create a new mnenomic (list of words) from provided entropy and a dictionary
 * selection. The mnemonic can later be converted to a seed for use in wallet
 * creation. Entropy byte count must be evenly divisible by 4.
 */
bc_word_list_t* bc_create_mnemonic(const bc_data_chunk_t* entropy);
bc_word_list_t* bc_create_mnemonic_Dict(const bc_data_chunk_t* entropy,
    const bc_dictionary_t* lexicon);

/**
 * Checks a mnemonic against a dictionary to determine if the
 * words are spelled correctly and the checksum matches.
 * The words must have been created using mnemonic encoding.
 */
bool bc_validate_mnemonic(const bc_word_list_t* mnemonic,
    const bc_dictionary_t* lexicon);

/**
 * Checks that a mnemonic is valid in at least one of the provided languages.
 */
bool bc_validate_mnemonic_all_languages(const bc_word_list_t* mnemonic);

/**
 * Convert a mnemonic with no passphrase to a wallet-generation seed.
 */
bc_long_hash_t* bc_decode_mnemonic(const bc_word_list_t* mnemonic);

/**
 * Convert a mnemonic with passphrase to a wallet-generation seed.
 */
bc_long_hash_t* bc_decode_mnemonic_Passphrase(const bc_word_list_t* mnemonic,
					      const bc_string_t* passphrase);

#ifdef __cplusplus
}
#endif

#endif

