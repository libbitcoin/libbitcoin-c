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

// Individual built-in languages:
const char* bc_dictionary_en_get(size_t i);
const char* bc_dictionary_es_get(size_t i);
const char* bc_dictionary_ja_get(size_t i);
const char* bc_dictionary_zh_Hans_get(size_t i);
const char* bc_dictionary_zh_Hant_get(size_t i);

// All built-in languages:
size_t bc_all_dictionaries_size();
const char* bc_all_dictionaries_get(size_t dict_i, size_t i);

#ifdef __cplusplus
}
#endif

#endif

