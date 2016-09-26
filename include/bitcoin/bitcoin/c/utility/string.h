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
#ifndef LIBBITCOIN_C_STRING_H
#define LIBBITCOIN_C_STRING_H

#include <stdbool.h>
#include <stddef.h>
#include <bitcoin/bitcoin/c/utility/vector.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_string_t bc_string_t;
BC_DECLARE_VECTOR(string_list, bc_string_t);

/// Constructors
bc_string_t* bc_create_string_default();
bc_string_t* bc_create_string(const char* data);
bc_string_t* bc_create_string_Length(const char* data, size_t length);
/// Destructor
void bc_destroy_string(bc_string_t* self);
/// Methods
const char* bc_string__data(const bc_string_t* self);
bool bc_string__empty(const bc_string_t* self);
size_t bc_string__length(const bc_string_t* self);
int bc_string__compare(const bc_string_t* self, const bc_string_t* other);
bool bc_string__equals(const bc_string_t* self, const bc_string_t* other);
// Convenience function
bool bc_string__equals_cstr(const bc_string_t* self, const char* other);

/**
 * Join a list of strings into a single string, in order.
 * @param[in]  words      The list of strings to join.
 * @param[in]  delimiter  The delimiter, defaults to " ".
 * @return                The resulting string.
 */
bc_string_t* bc_join(const bc_string_list_t* words);
bc_string_t* bc_join_Delim(const bc_string_list_t* words,
    const char* delimiter);

/**
 * Split a list of strings into a string vector string, in order, white space
 * delimited.
 * @param[in]  sentence   The string to split.
 * @param[in]  delimiter  The delimeter, defaults to " ".
 * @param[in]  trim       Trim the sentence for whitespace, defaults to true.
 * @return                The list of resulting strings.
 */
bc_string_list_t* bc_split(const char* sentence);
bc_string_list_t* bc_split_Delim(const char* sentence,
    const char* delimiter);
bc_string_list_t* bc_split_Delim_notrim(const char* sentence,
    const char* delimiter);

#ifdef __cplusplus
}
#endif

#endif

