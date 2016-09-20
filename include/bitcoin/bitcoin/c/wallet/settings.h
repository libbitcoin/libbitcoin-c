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
#ifndef LIBBITCOIN_C_WALLET_SETTINGS_H
#define LIBBITCOIN_C_WALLET_SETTINGS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_settings_t bc_settings_t;
bc_settings_t* bc_create_settings();
void bc_destroy_settings(bc_settings_t* self);
uint8_t bc_settings_address_public_key(const bc_settings_t* self);
void bc_settings_set_address_public_key(bc_settings_t* self,
    uint8_t address_public_key);
uint8_t bc_settings_address_script(const bc_settings_t* self);
void bc_settings_set_address_script(bc_settings_t* self,
    uint8_t address_script);
uint8_t bc_settings_address_stealth(const bc_settings_t* self);
void bc_settings_set_address_stealth(bc_settings_t* self,
    uint8_t address_stealth);
uint8_t bc_settings_private_key(const bc_settings_t* self);
void bc_settings_set_private_key(bc_settings_t* self,
    uint8_t private_key);
uint64_t bc_settings_private_key_hd(const bc_settings_t* self);
void bc_settings_set_private_key_hd(bc_settings_t* self,
    uint64_t private_key_hd);
uint64_t bc_settings_public_key_hd(const bc_settings_t* self);
void bc_settings_set_public_key_hd(bc_settings_t* self,
    uint64_t public_key_hd);

#ifdef __cplusplus
}
#endif

#endif

