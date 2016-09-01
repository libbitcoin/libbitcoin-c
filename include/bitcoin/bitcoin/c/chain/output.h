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
#ifndef LIBBITCOIN_C_CHAIN_OUTPUT_H
#define LIBBITCOIN_C_CHAIN_OUTPUT_H

#include <bitcoin/bitcoin/c/chain/script/script.h>
#include <bitcoin/bitcoin/c/math/hash.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>
#include <bitcoin/bitcoin/c/utility/vector.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_output_t bc_output_t;
BC_DECLARE_VECTOR(output_list, bc_output_t);
// Static functions
bc_output_t* bc_output_factory_from_data(const bc_data_chunk_t* data);
// Constructor
bc_output_t* bc_create_output();
// Destructor
void bc_destroy_output(bc_output_t* self);
// Member functions
bool bc_output_from_data(bc_output_t* self, const bc_data_chunk_t* data);
bc_data_chunk_t* bc_output_to_data(const bc_output_t* self);
bc_string_t* bc_output_to_string(const bc_output_t* self, uint32_t flags);
bool bc_output_is_valid(const bc_output_t* self);
void bc_output_reset(bc_output_t* self);
uint64_t bc_output_serialized_size(const bc_output_t* self);
// Member variables
uint64_t bc_output_value(const bc_output_t* self);
void bc_output_set_value(const bc_output_t* self, uint64_t value);
bc_script_t* bc_output_script(const bc_output_t* self);
void bc_output_set_script(const bc_output_t* self, const bc_script_t* script);

#ifdef __cplusplus
}
#endif

#endif

