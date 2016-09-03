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
#ifndef LIBBITCOIN_C_CHAIN_SPEND_H
#define LIBBITCOIN_C_CHAIN_SPEND_H

#include <bitcoin/bitcoin/c/chain/point.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_spend_t bc_spend_t;

// Constructor
bc_spend_t* bc_create_spend();
// Destructor
void bc_destroy_spend(bc_spend_t* self);
// Member variables
bool bc_spend_valid(const bc_spend_t* self);
void bc_spend_set_valid(bc_spend_t* self, bool valid);
uint32_t bc_spend_index(const bc_spend_t* self);
void bc_spend_set_index(bc_spend_t* self, uint32_t index);
bc_hash_digest_t* bc_spend_hash(const bc_spend_t* self);
void bc_spend_set_hash(bc_spend_t* self, const bc_hash_digest_t* hash);

typedef struct bc_spend_info_t bc_spend_info_t;
BC_DECLARE_VECTOR(spend_info_list, bc_spend_info_t);

// Constructor
bc_spend_info_t* bc_create_spend_info();
// Destructor
void bc_destroy_spend_info(bc_spend_info_t* self);
// Member variables
bc_input_point_t* bc_spend_info_point(const bc_spend_info_t* self);
void bc_spend_info_set_point(bc_spend_info_t* self,
    const bc_input_point_t* point);
bc_output_point_t* bc_spend_info_previous_output(const bc_spend_info_t* self);
void bc_spend_info_set_previous_output(bc_spend_info_t* self,
    const bc_output_point_t* previous_output);

#ifdef __cplusplus
}
#endif

#endif

