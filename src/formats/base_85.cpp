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
#include <bitcoin/bitcoin/c/formats/base_85.h>

#include <bitcoin/bitcoin/formats/base_85.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>

extern "C" {

bool bc_encode_base85(bc_string_t* out, const bc_data_chunk_t* in)
{
    return libbitcoin::encode_base85(*out->obj, *in->obj);
}

bool bc_decode_base85(bc_data_chunk_t* out, const char* in)
{
    return libbitcoin::decode_base85(*out->obj, in);
}

} // extern C

