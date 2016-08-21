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

#include <string>

extern "C" {

struct bc_string_t
{
    std::string* obj;
};

bc_string_t* bc_create_string(const char* data)
{
    bc_string_t* self = new bc_string_t;
    self->obj = new std::string(data);
    return self;
}
bc_string_t* bc_create_string_Length(const char* data, size_t length)
{
    bc_string_t* self = new bc_string_t;
    self->obj = new std::string(data, length);
    return self;
}
void bc_destroy_string(bc_string_t* self)
{
    delete self->obj;
    delete self;
}
const char* bc_string_data(bc_string_t* self)
{
    return self->obj->data();
}
size_t bc_string_length(bc_string_t* self)
{
    return self->obj->length();
}
int bc_string_compare(bc_string_t* self, bc_string_t* other)
{
    return self->obj->compare(*other->obj);
}
bool bc_string_equals(bc_string_t* self, bc_string_t* other)
{
    return *self->obj == *other->obj;
}
bool bc_string_equals_cstr(bc_string_t* self, const char* other)
{
    return *self->obj == other;
}

}

