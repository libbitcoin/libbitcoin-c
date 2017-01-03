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
#ifndef LIBBITCOIN_C_CHAIN_INPUT_H
#define LIBBITCOIN_C_CHAIN_INPUT_H

#include <bitcoin/bitcoin/c/chain/output_point.h>
#include <bitcoin/bitcoin/c/chain/script.h>
#include <bitcoin/bitcoin/c/math/hash.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>
#include <bitcoin/bitcoin/c/utility/vector.h>
#include <bitcoin/bitcoin/c/wallet/payment_address.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_input_t bc_input_t;
BC_DECLARE_VECTOR(input_list, bc_input_t);
// Constructor
bc_input_t* bc_create_input();
bc_input_t* bc_create_input_copy(const bc_input_t* other);
bc_input_t* bc_create_input_Values(
    const bc_output_point_t* previous_output, const bc_script_t* script,
    uint32_t sequence);
// Destructor
void bc_destroy_input(bc_input_t* self);
// Operators
void bc_input__copy(bc_input_t* self, const bc_input_t* other);
bool bc_input__equals(bc_input_t* self, const bc_input_t* other);
bool bc_input__not_equals(bc_input_t* self, const bc_input_t* other);

// Deserialization.
bc_input_t* bc_input__factory_from_data(const bc_data_chunk_t* data);
bc_input_t* bc_input__factory_from_data_nowire(const bc_data_chunk_t* data);

bool bc_input__from_data(bc_input_t* self, const bc_data_chunk_t* data);
bool bc_input__from_data_nowire(bc_input_t* self, const bc_data_chunk_t* data);

bool bc_input__is_valid(const bc_input_t* self);

// Serialization.
bc_data_chunk_t* bc_input__to_data(const bc_input_t* self);
bc_data_chunk_t* bc_input__to_data_nowire(const bc_input_t* self);

// Properties
uint64_t bc_input__serialized_size(const bc_input_t* self);
uint64_t bc_input__serialized_size_nowire(const bc_input_t* self);

bc_output_point_t* bc_input__previous_output(const bc_input_t* self);
void bc_input__set_previous_output(bc_input_t* self,
    bc_output_point_t* previous_output);

bc_script_t* bc_input__script(const bc_input_t* self);
void bc_input__set_script(bc_input_t* self, const bc_script_t* script);

uint32_t bc_input__sequence(const bc_input_t* self);
void bc_input__set_sequence(bc_input_t* self, uint32_t sequence);

/// The payment address extracted from this input as a standard script.
bc_payment_address_t* bc_input__address(const bc_input_t* self);

bool bc_input__is_final(const bc_input_t* self);
size_t bc_input__signature_operations(
    const bc_input_t* self, bool bip16_active);

#ifdef __cplusplus
}
#endif

#endif

