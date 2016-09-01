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
#include <bitcoin/bitcoin/c/math/checksum.h>

#include <bitcoin/bitcoin/math/checksum.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>

extern "C" {

size_t bc_checksum_size()
{
    return libbitcoin::checksum_size;
}

void bc_append_checksum(bc_data_chunk_t* data)
{
    libbitcoin::append_checksum(*data->obj);
}

uint32_t bc_bitcoin_checksum(const bc_data_chunk_t* data)
{
    return libbitcoin::bitcoin_checksum(*data->obj);
}

bool bc_verify_checksum(const bc_data_chunk_t* data)
{
    return libbitcoin::verify_checksum(*data->obj);
}

} // extern C


