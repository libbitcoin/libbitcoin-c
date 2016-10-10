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
#include <bitcoin/bitcoin/c/internal/wallet/dictionary.hpp>

extern "C" {

size_t bc_dictionary_size()
{
    return libbitcoin::wallet::dictionary_size;
}

void bc_destroy_dictionary(bc_dictionary_t* self)
{
    delete self;
}

const char* bc_dictionary__const_at(const bc_dictionary_t* self, size_t pos)
{
    return self->obj->at(pos);
}

bc_dictionary_t* bc_dictionary_en()
{
    return new bc_dictionary_t{ &libbitcoin::wallet::language::en };
}
bc_dictionary_t* bc_dictionary_es()
{
    return new bc_dictionary_t{ &libbitcoin::wallet::language::es };
}
bc_dictionary_t* bc_dictionary_ja()
{
    return new bc_dictionary_t{ &libbitcoin::wallet::language::ja };
}
bc_dictionary_t* bc_dictionary_zh_Hans()
{
    return new bc_dictionary_t{ &libbitcoin::wallet::language::zh_Hans };
}
bc_dictionary_t* bc_dictionary_zh_Hant()
{
    return new bc_dictionary_t{ &libbitcoin::wallet::language::zh_Hant };
}

size_t bc_all_dictionaries_size()
{
    return libbitcoin::wallet::language::all.size();
}
bc_dictionary_t* bc_all_dictionaries_get(size_t i)
{
    return new bc_dictionary_t{ libbitcoin::wallet::language::all[i] };
}

}

