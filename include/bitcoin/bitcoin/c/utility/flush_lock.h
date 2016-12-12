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
#ifndef LIBBITCOIN_C_UTILITY_FLUSH_LOCK_H
#define LIBBITCOIN_C_UTILITY_FLUSH_LOCK_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/// This class is not thread safe.
/// Guard a resource that may be corrupted due to an interrupted write.
typedef struct bc_flush_lock_t bc_flush_lock_t;

bc_flush_lock_t* bc_create_flush_lock(const char* lock_path);
void bc_destroy_flush_lock(bc_flush_lock_t* self);

bool bc_flush_lock__try_lock(const bc_flush_lock_t* self);
bool bc_flush_lock__lock_shared(const bc_flush_lock_t* self);
bool bc_flush_lock__unlock_shared(const bc_flush_lock_t* self);

#ifdef __cplusplus
}
#endif

#endif

