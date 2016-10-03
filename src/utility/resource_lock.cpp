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
#include <bitcoin/bitcoin/c/utility/resource_lock.h>
#include <bitcoin/bitcoin/c/internal/utility/resource_lock.hpp>

#include <bitcoin/bitcoin/utility/resource_lock.hpp>

extern "C" {

bc_resource_lock_t* bc_create_resource_lock(const char* lock_path)
{
    return new bc_resource_lock_t{ new libbitcoin::resource_lock(lock_path) };
}
void bc_destroy_resource_lock(bc_resource_lock_t* self)
{
    delete self->obj;
    delete self;
}

bool bc_resource_lock__lock(const bc_resource_lock_t* self)
{
    return self->obj->lock();
}
bool bc_resource_lock__unlock(const bc_resource_lock_t* self)
{
    return self->obj->unlock();
}

} // extern C

