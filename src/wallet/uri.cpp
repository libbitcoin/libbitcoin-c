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
#include <bitcoin/bitcoin/c/wallet/uri.h>
#include <bitcoin/bitcoin/c/internal/wallet/uri.hpp>

#include <bitcoin/bitcoin/c/internal/utility/string.hpp>

extern "C" {

bc_uri_t* bc_create_uri()
{
    return new bc_uri_t{ new libbitcoin::wallet::uri };
}
void bc_destroy_uri(bc_uri_t* self)
{
    delete self->obj;
    delete self;
}

bool bc_uri_decode(bc_uri_t* self, const char* encoded)
{
    self->obj->decode(encoded);
}
bool bc_uri_decode_nostrict(bc_uri_t* self, const char* encoded)
{
    self->obj->decode(encoded, false);
}
bc_string_t* bc_uri_encoded(const bc_uri_t* self)
{
    return bc_create_string_StdString(self->obj->encoded());
}

bc_string_t* bc_uri_scheme(const bc_uri_t* self)
{
    return bc_create_string_StdString(self->obj->scheme());
}
void bc_uri_set_scheme(bc_uri_t* self, const char* scheme)
{
    self->obj->set_scheme(scheme);
}

bc_string_t* bc_uri_authority(const bc_uri_t* self)
{
    return bc_create_string_StdString(self->obj->authority());
}
bool bc_uri_has_authority(const bc_uri_t* self)
{
    return self->obj->has_authority();
}
void bc_uri_set_authority(bc_uri_t* self, const char* authority)
{
    self->obj->set_authority(authority);
}
void bc_uri_remove_authority(bc_uri_t* self)
{
    self->obj->remove_authority();
}

bc_string_t* bc_uri_path(const bc_uri_t* self)
{
    return bc_create_string_StdString(self->obj->path());
}
void bc_uri_set_path(bc_uri_t* self, const char* path)
{
    self->obj->set_path(path);
}

bc_string_t* bc_uri_query(const bc_uri_t* self)
{
    return bc_create_string_StdString(self->obj->query());
}
bool bc_uri_has_query(const bc_uri_t* self)
{
    return self->obj->has_query();
}
void bc_uri_set_query(bc_uri_t* self, const char* query)
{
    self->obj->set_query(query);
}
void bc_uri_remove_query(bc_uri_t* self)
{
    self->obj->remove_query();
}

bc_string_t* bc_uri_fragment(const bc_uri_t* self)
{
    return bc_create_string_StdString(self->obj->fragment());
}
bool bc_uri_has_fragment(const bc_uri_t* self)
{
    return self->obj->has_fragment();
}
void bc_uri_set_fragment(bc_uri_t* self, const char* fragment)
{
    self->obj->set_fragment(fragment);
}
void bc_uri_remove_fragment(bc_uri_t* self)
{
    self->obj->remove_fragment();
}

}

