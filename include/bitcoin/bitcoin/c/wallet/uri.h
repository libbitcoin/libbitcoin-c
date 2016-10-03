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
#ifndef LIBBITCOIN_C_WALLET_URI_H
#define LIBBITCOIN_C_WALLET_URI_H

#include <stdbool.h>
#include <bitcoin/bitcoin/c/utility/string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A parsed URI according to RFC 3986.
 */
typedef struct bc_uri_t bc_uri_t;
/// Constructors.
bc_uri_t* bc_create_uri();
/// Destructor
void bc_destroy_uri(bc_uri_t* self);

/**
 * Decodes a URI from a string.
 * @param strict Set to false to tolerate unescaped special characters.
 */
bool bc_uri__decode(bc_uri_t* self, const char* encoded);
bool bc_uri__decode_nostrict(bc_uri_t* self, const char* encoded);
bc_string_t* bc_uri__encoded(const bc_uri_t* self);

/**
 * Returns the lowercased URI scheme.
 */
bc_string_t* bc_uri__scheme(const bc_uri_t* self);
void bc_uri__set_scheme(bc_uri_t* self, const char* scheme);

/**
 * Obtains the unescaped authority part, if any (user@server:port).
 */
bc_string_t* bc_uri__authority(const bc_uri_t* self);
bool bc_uri__has_authority(const bc_uri_t* self);
void bc_uri__set_authority(bc_uri_t* self, const char* authority);
void bc_uri__remove_authority(bc_uri_t* self);

/**
 * Obtains the unescaped path part.
 */
bc_string_t* bc_uri__path(const bc_uri_t* self);
void bc_uri__set_path(bc_uri_t* self, const char* path);

/**
 * Returns the unescaped query string, if any.
 */
bc_string_t* bc_uri__query(const bc_uri_t* self);
bool bc_uri__has_query(const bc_uri_t* self);
void bc_uri__set_query(bc_uri_t* self, const char* query);
void bc_uri__remove_query(bc_uri_t* self);

/**
 * Returns the unescaped fragment string, if any.
 */
bc_string_t* bc_uri__fragment(const bc_uri_t* self);
bool bc_uri__has_fragment(const bc_uri_t* self);
void bc_uri__set_fragment(bc_uri_t* self, const char* fragment);
void bc_uri__remove_fragment(bc_uri_t* self);

#ifdef __cplusplus
}
#endif

#endif

