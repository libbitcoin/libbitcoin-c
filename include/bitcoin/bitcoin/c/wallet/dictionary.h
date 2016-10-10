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
#ifndef LIBBITCOIN_C_WALLET_DICTIONARY_H
#define LIBBITCOIN_C_WALLET_DICTIONARY_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A valid mnemonic dictionary has exactly this many words.
 */
size_t bc_dictionary_size();

/**
 * A dictionary for creating mnemonics.
 * The bip39 spec calls this a "wordlist".
 * This is a POD type, which means the compiler can write it directly
 * to static memory with no run-time overhead.
 */
typedef struct bc_dictionary_t bc_dictionary_t;
void bc_destroy_dictionary(bc_dictionary_t* self);

const char* bc_dictionary__const_at(const bc_dictionary_t* self, size_t pos);

// Individual built-in languages:
bc_dictionary_t* bc_dictionary_en();
bc_dictionary_t* bc_dictionary_es();
bc_dictionary_t* bc_dictionary_ja();
bc_dictionary_t* bc_dictionary_zh_Hans();
bc_dictionary_t* bc_dictionary_zh_Hant();

// All built-in languages:
size_t bc_all_dictionaries_size();
bc_dictionary_t* bc_all_dictionaries_get(size_t i);

#ifdef __cplusplus
}
#endif

#endif

