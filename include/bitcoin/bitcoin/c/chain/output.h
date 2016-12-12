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

#include <bitcoin/bitcoin/c/chain/point.h>
#include <bitcoin/bitcoin/c/chain/script.h>
#include <bitcoin/bitcoin/c/math/hash.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>
#include <bitcoin/bitcoin/c/utility/vector.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_output_t bc_output_t;
BC_DECLARE_VECTOR(output_list, bc_output_t);
// Static values
/// This is a sentinel used in .value to indicate not found in store.
/// This is a sentinel used in cache.value to indicate not populated.
/// This is a consensus value used in script::generate_signature_hash.
uint64_t bc_output__not_found();
// Constructor
bc_output_t* bc_create_output();
bc_output_t* bc_create_output_copy(const bc_output_t* other);
bc_output_t* bc_create_output_Value(uint64_t value, const bc_script_t* script);
// Destructor
void bc_destroy_output(bc_output_t* self);

// Operators
void bc_output__copy(bc_output_t* self, const bc_output_t* other);
bool bc_output__equals(const bc_output_t* self, const bc_output_t* other);
bool bc_output__not_equals(const bc_output_t* self, const bc_output_t* other);

// Member functions
bc_output_t* bc_output__factory_from_data(const bc_data_chunk_t* data);
bc_output_t* bc_output__factory_from_data_nowire(const bc_data_chunk_t* data);
bool bc_output__from_data(bc_output_t* self, const bc_data_chunk_t* data);
bool bc_output__from_data_nowire(bc_output_t* self, const bc_data_chunk_t* data);

bool bc_output__is_valid(const bc_output_t* self);

bc_data_chunk_t* bc_output__to_data(const bc_output_t* self);
bc_data_chunk_t* bc_output__to_data_nowire(const bc_output_t* self);

size_t bc_output__serialized_size(const bc_output_t* self);
size_t bc_output__serialized_size_nowire(const bc_output_t* self);

uint64_t bc_output__value(const bc_output_t* self);
void bc_output__set_value(bc_output_t* self, uint64_t value);

bc_script_t* bc_output__script(const bc_output_t* self);
void bc_output__set_script(bc_output_t* self, const bc_script_t* script);

size_t bc_output__signature_operations(const bc_output_t* self);

#ifdef __cplusplus
}
#endif

#endif

