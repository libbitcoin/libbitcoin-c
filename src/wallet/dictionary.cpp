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
#include <bitcoin/bitcoin/c/wallet/dictionary.h>

#include <bitcoin/bitcoin/wallet/dictionary.hpp>

extern "C" {

size_t bc_dictionary_size()
{
    return libbitcoin::wallet::dictionary_size;
}

const char* bc_dictionary_en_get(size_t i)
{
    return libbitcoin::wallet::language::en[i];
}
const char* bc_dictionary_es_get(size_t i)
{
    return libbitcoin::wallet::language::es[i];
}
const char* bc_dictionary_ja_get(size_t i)
{
    return libbitcoin::wallet::language::ja[i];
}
const char* bc_dictionary_zh_Hans_get(size_t i)
{
    return libbitcoin::wallet::language::zh_Hans[i];
}
const char* bc_dictionary_zh_Hant_get(size_t i)
{
    return libbitcoin::wallet::language::zh_Hant[i];
}

size_t bc_all_dictionaries_size()
{
    return libbitcoin::wallet::language::all.size();
}
const char* bc_all_dictionaries_get(size_t dict_i, size_t i)
{
    return (*libbitcoin::wallet::language::all[dict_i])[i];
}

}

