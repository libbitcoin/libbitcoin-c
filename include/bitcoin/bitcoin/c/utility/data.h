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
#ifndef LIBBITCOIN_C_DATA_H
#define LIBBITCOIN_C_DATA_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_data_chunk_t bc_data_chunk_t;
// Empty chunk
bc_data_chunk_t* bc_create_data_chunk();
// Copy constructor
bc_data_chunk_t* bc_create_data_chunk_copy(bc_data_chunk_t* other);
// Initialize data chunk from uint8_t array
bc_data_chunk_t* bc_create_data_chunk_Array(uint8_t* data, size_t size);
// Destructor
void bc_destroy_data_chunk(bc_data_chunk_t* self);
// .size()
size_t bc_data_chunk_size(bc_data_chunk_t* self);
// .empty()
bool bc_data_chunk_empty(bc_data_chunk_t* self);
// .data()
uint8_t* bc_data_chunk_data(bc_data_chunk_t* self);
// extend_data()
void bc_data_chunk_extend_data(bc_data_chunk_t* self, bc_data_chunk_t* other);

#ifdef __cplusplus
}
#endif

#endif

