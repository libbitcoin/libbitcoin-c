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
#ifndef LIBBITCOIN_C_CHAIN_MACHINE_SIGHASH_ALGORITHM_H
#define LIBBITCOIN_C_CHAIN_MACHINE_SIGHASH_ALGORITHM_H

#include <bitcoin/bitcoin/c/machine/opcode.h>
#include <bitcoin/bitcoin/c/machine/operation.h>
#include <bitcoin/bitcoin/c/machine/rule_fork.h>
#include <bitcoin/bitcoin/c/error.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Signature hash types.
/// Comments from: bitcoin.org/en/developer-guide#standard-transactions
typedef enum bc_sighash_algorithm_t
{
    /// The default, signs all the inputs and outputs, protecting everything
    /// except the signature scripts against modification.
    bc_sighash_algorithm__all = 0x01,

    /// Signs all of the inputs but none of the outputs, allowing anyone to
    /// change where the satoshis are going unless other signatures using 
    /// other signature hash flags protect the outputs.
    bc_sighash_algorithm__none = 0x02,

    /// The only output signed is the one corresponding to this input (the
    /// output with the same output index number as this input), ensuring
    /// nobody can change your part of the transaction but allowing other 
    /// signers to change their part of the transaction. The corresponding 
    /// output must exist or the value '1' will be signed, breaking the
    /// security scheme. This input, as well as other inputs, are included
    /// in the signature. The sequence numbers of other inputs are not
    /// included in the signature, and can be updated.
    bc_sighash_algorithm__single = 0x03,

    /// The above types can be modified with this flag, creating three new
    /// combined types.
    bc_sighash_algorithm__anyone_can_pay = 0x80,

    /// Signs all of the outputs but only this one input, and it also allows
    /// anyone to add or remove other inputs, so anyone can contribute
    /// additional satoshis but they cannot change how many satoshis are
    /// sent nor where they go.
    bc_sighash_algorithm__all_anyone_can_pay =
        bc_sighash_algorithm__all |
        bc_sighash_algorithm__anyone_can_pay,

    /// Signs only this one input and allows anyone to add or remove other
    /// inputs or outputs, so anyone who gets a copy of this input can spend
    /// it however they'd like.
    bc_sighash_algorithm__none_anyone_can_pay =
        bc_sighash_algorithm__none |
        bc_sighash_algorithm__anyone_can_pay,

    /// Signs this one input and its corresponding output. Allows anyone to
    /// add or remove other inputs.
    bc_sighash_algorithm__single_anyone_can_pay =
        bc_sighash_algorithm__single |
        bc_sighash_algorithm__anyone_can_pay,

    /// Used to mask off the anyone_can_pay flag to access the enumeration.
    bc_sighash_algorithm__mask =
        ~bc_sighash_algorithm__anyone_can_pay

} bc_sighash_algorithm_t;

#ifdef __cplusplus
}
#endif

#endif

