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
#ifndef LIBBITCOIN_C_UTILITY_RESOURCE_LOCK_H
#define LIBBITCOIN_C_UTILITY_RESOURCE_LOCK_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A resource lock device that ensures exclusive access to a resource.
 * It takes a path for creating a lock file object that can be used
 * for telling the usage of some resource between processes.
 * Example: opening/closing blockchain database.
 */
typedef struct bc_resource_lock_t bc_resource_lock_t;

bc_resource_lock_t* bc_create_resource_lock(const char* lock_path);
void bc_destroy_resource_lock(bc_resource_lock_t* self);

bool bc_resource_lock__lock(const bc_resource_lock_t* self);
bool bc_resource_lock__unlock(const bc_resource_lock_t* self);

#ifdef __cplusplus
}
#endif

#endif

