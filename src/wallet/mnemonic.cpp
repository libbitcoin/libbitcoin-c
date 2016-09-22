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
#include <bitcoin/bitcoin/c/wallet/mnemonic.h>
#include <bitcoin/bitcoin/c/internal/wallet/mnemonic.hpp>

#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>
#include <bitcoin/bitcoin/c/internal/wallet/dictionary.hpp>

BC_IMPLEMENT_VECTOR(word_list, bc_string_t, bc_destroy_string,
    libbitcoin::wallet::word_list);

extern "C" {

size_t bc_mnemonic_word_multiple()
{
    return libbitcoin::wallet::mnemonic_word_multiple;
}

size_t bc_mnemonic_seed_multiple()
{
    return libbitcoin::wallet::mnemonic_seed_multiple;
}

bc_word_list_t* bc_create_mnemonic(const bc_data_chunk_t* entropy)
{
    return bc_word_list_to_ctype(
        libbitcoin::wallet::create_mnemonic(*entropy->obj));
}
bc_word_list_t* bc_create_mnemonic_Dict(const bc_data_chunk_t* entropy,
    const bc_dictionary_t* lexicon)
{
    return bc_word_list_to_ctype(
        libbitcoin::wallet::create_mnemonic(*entropy->obj, *lexicon->obj));
}

bool bc_validate_mnemonic(const bc_word_list_t* mnemonic,
    const bc_dictionary_t* lexicon)
{
    return libbitcoin::wallet::validate_mnemonic(
        bc_word_list_from_ctype(mnemonic), *lexicon->obj);
}

bool bc_validate_mnemonic_all_languages(const bc_word_list_t* mnemonic)
{
    return libbitcoin::wallet::validate_mnemonic(
        bc_word_list_from_ctype(mnemonic));
}

bc_long_hash_t* bc_decode_mnemonic(const bc_word_list_t* mnemonic)
{
    return bc_create_long_hash_Internal(
        libbitcoin::wallet::decode_mnemonic(
            bc_word_list_from_ctype(mnemonic)));
}

}

