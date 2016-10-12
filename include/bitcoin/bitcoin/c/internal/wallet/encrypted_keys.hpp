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
#ifndef LIBBITCOIN_C_INTERNAL_WALLET_ENCRYPTED_KEYS_HPP
#define LIBBITCOIN_C_INTERNAL_WALLET_ENCRYPTED_KEYS_HPP

#include <bitcoin/bitcoin/wallet/encrypted_keys.hpp>

extern "C" {

struct bc_ek_salt_t
{
    libbitcoin::wallet::ek_salt* obj;
    const bool delete_obj;
};

struct bc_ek_entropy_t
{
    libbitcoin::wallet::ek_entropy* obj;
    const bool delete_obj;
};

struct bc_ek_seed_t
{
    libbitcoin::wallet::ek_seed* obj;
    const bool delete_obj;
};

struct bc_encrypted_token_t
{
    libbitcoin::wallet::encrypted_token* obj;
    const bool delete_obj;
};

struct bc_encrypted_private_t
{
    libbitcoin::wallet::encrypted_private* obj;
    const bool delete_obj;
};

struct bc_encrypted_public_t
{
    libbitcoin::wallet::encrypted_public* obj;
    const bool delete_obj;
};

}

#endif

