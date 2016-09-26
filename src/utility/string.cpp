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
#include <bitcoin/bitcoin/c/utility/string.h>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>

BC_IMPLEMENT_VECTOR(string_list, bc_string_t, bc_destroy_string,
    libbitcoin::string_list);

extern "C" {

bc_string_t* bc_create_string_default()
{
    return new bc_string_t{ new std::string };
}
bc_string_t* bc_create_string(const char* data)
{
    return new bc_string_t{ new std::string(data) };
}
bc_string_t* bc_create_string_Length(const char* data, size_t length)
{
    return new bc_string_t{ new std::string(data, length) };
}
void bc_destroy_string(bc_string_t* self)
{
    delete self->obj;
    delete self;
}
const char* bc_string__data(const bc_string_t* self)
{
    return self->obj->data();
}
bool bc_string__empty(const bc_string_t* self)
{
    return self->obj->empty();
}
size_t bc_string__length(const bc_string_t* self)
{
    return self->obj->length();
}
int bc_string__compare(const bc_string_t* self, const bc_string_t* other)
{
    return self->obj->compare(*other->obj);
}
bool bc_string__equals(const bc_string_t* self, const bc_string_t* other)
{
    return *self->obj == *other->obj;
}
bool bc_string__equals_cstr(const bc_string_t* self, const char* other)
{
    return *self->obj == other;
}

bc_string_t* bc_join(const bc_string_list_t* words)
{
    return bc_create_string_StdString(
        libbitcoin::join(bc_string_list_from_ctype(words)));
}
bc_string_t* bc_join_Delim(const bc_string_list_t* words,
    const char* delimiter)
{
    return bc_create_string_StdString(
        libbitcoin::join(bc_string_list_from_ctype(words), delimiter));
}

bc_string_list_t* bc_split(const char* sentence)
{
    return bc_string_list_to_ctype(
        libbitcoin::split(sentence));
}
bc_string_list_t* bc_split_Delim(const char* sentence,
    const char* delimiter)
{
    return bc_string_list_to_ctype(
        libbitcoin::split(sentence, delimiter));
}
bc_string_list_t* bc_split_Delim_notrim(const char* sentence,
    const char* delimiter)
{
    return bc_string_list_to_ctype(
        libbitcoin::split(sentence, delimiter, false));
}

} // extern C

bc_string_t* bc_create_string_StdString(const std::string& string)
{
    return bc_create_string_Length(string.data(), string.length());
}

