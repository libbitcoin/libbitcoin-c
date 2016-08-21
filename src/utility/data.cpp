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
#include <bitcoin/bitcoin/c/utility/data.h>

#include <bitcoin/bitcoin/utility/data.hpp>

extern "C" {

struct bc_data_chunk_t
{
    libbitcoin::data_chunk* obj;
};
bc_data_chunk_t* bc_create_data_chunk()
{
    bc_data_chunk_t* self = new bc_data_chunk_t;
    self->obj = new libbitcoin::data_chunk();
    return self;
}
// Copy constructor
bc_data_chunk_t* bc_create_data_chunk_copy(bc_data_chunk_t* other)
{
    bc_data_chunk_t* self = new bc_data_chunk_t;
    self->obj = new libbitcoin::data_chunk(*other->obj);
    return self;
}
// Initialize data chunk from uint8_t array
bc_data_chunk_t* bc_create_data_chunk_Array(uint8_t* data, size_t size)
{
    bc_data_chunk_t* self = new bc_data_chunk_t;
    self->obj = new libbitcoin::data_chunk(data, data + size);
    return self;
}
// Destructor
void bc_destroy_data_chunk(bc_data_chunk_t* self)
{
    delete self->obj;
    delete self;
}
// .size()
size_t bc_data_chunk_size(bc_data_chunk_t* self)
{
    return self->obj->size();
}
// .empty()
bool bc_data_chunk_empty(bc_data_chunk_t* self)
{
    return self->obj->empty();
}
// .data()
uint8_t* bc_data_chunk_data(bc_data_chunk_t* self)
{
    return self->obj->data();
}
// extend_data()
void bc_data_chunk_extend_data(bc_data_chunk_t* self, bc_data_chunk_t* other)
{
    libbitcoin::extend_data(*self->obj, *other->obj);
}

}

