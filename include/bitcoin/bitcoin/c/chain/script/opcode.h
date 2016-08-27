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
#ifndef LIBBITCOIN_C_CHAIN_SCRIPT_OPCODE_H
#define LIBBITCOIN_C_CHAIN_SCRIPT_OPCODE_H

#include <stdint.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum bc_opcode_t
{
    opcode_zero = 0,
    opcode_special = 1,
    opcode_pushdata1 = 76,
    opcode_pushdata2 = 77,
    opcode_pushdata4 = 78,
    opcode_negative_1 = 79,
    // reserved does nothing
    opcode_reserved = 80,
    opcode_1 = 81,
    opcode_2 = 82,
    opcode_3 = 83,
    opcode_4 = 84,
    opcode_5 = 85,
    opcode_6 = 86,
    opcode_7 = 87,
    opcode_8 = 88,
    opcode_9 = 89,
    opcode_10 = 90,
    opcode_11 = 91,
    opcode_12 = 92,
    opcode_13 = 93,
    opcode_14 = 94,
    opcode_15 = 95,
    opcode_16 = 96,
    opcode_nop = 97,
    opcode_ver = 98,
    opcode_if_ = 99,
    opcode_notif = 100,
    opcode_verif = 101,
    opcode_vernotif = 102,
    opcode_else = 103,
    opcode_endif = 104,
    opcode_verify = 105,
    opcode_return_ = 106,
    opcode_toaltstack = 107,
    opcode_fromaltstack = 108,
    opcode_2drop = 109,
    opcode_2dup = 110,
    opcode_3dup = 111,
    opcode_2over = 112,
    opcode_2rot = 113,
    opcode_2swap = 114,
    opcode_ifdup = 115,
    opcode_depth = 116,
    opcode_drop = 117,
    opcode_dup = 118,
    opcode_nip = 119,
    opcode_over = 120,
    opcode_pick = 121,
    opcode_roll = 122,
    opcode_rot = 123,
    opcode_swap = 124,
    opcode_tuck = 125,
    opcode_cat = 126,          // disabled
    opcode_substr = 127,       // disabled
    opcode_left = 128,         // disabled
    opcode_right = 129,        // disabled
    opcode_size = 130,
    opcode_invert = 131,       // disabled
    opcode_and = 132,         // disabled
    opcode_or = 133,          // disabled
    opcode_xor = 134,         // disabled
    opcode_equal = 135,
    opcode_equalverify = 136,
    opcode_reserved1 = 137,
    opcode_reserved2 = 138,
    opcode_1add = 139,
    opcode_1sub = 140,
    opcode_2mul = 141,      // disabled
    opcode_2div = 142,      // disabled
    opcode_negate = 143,
    opcode_abs = 144,
    opcode_not = 145,
    opcode_0notequal = 146,
    opcode_add = 147,
    opcode_sub = 148,
    opcode_mul = 149,          // disabled
    opcode_div = 150,          // disabled
    opcode_mod = 151,          // disabled
    opcode_lshift = 152,       // disabled
    opcode_rshift = 153,       // disabled
    opcode_booland = 154,
    opcode_boolor = 155,
    opcode_numequal = 156,
    opcode_numequalverify = 157,
    opcode_numnotequal = 158,
    opcode_lessthan = 159,
    opcode_greaterthan = 160,
    opcode_lessthanorequal = 161,
    opcode_greaterthanorequal = 162,
    opcode_min = 163,
    opcode_max = 164,
    opcode_within = 165,
    opcode_ripemd160 = 166,
    opcode_sha1 = 167,
    opcode_sha256 = 168,
    opcode_hash160 = 169,
    opcode_hash256 = 170,
    opcode_codeseparator = 171,
    opcode_checksig = 172,
    opcode_checksigverify = 173,
    opcode_checkmultisig = 174,
    opcode_checkmultisigverify = 175,
    opcode_nop1 = 176,
    opcode_nop2 = 177,
    opcode_checklocktimeverify = opcode_nop2,
    opcode_nop3 = 178,
    opcode_nop4 = 179,
    opcode_nop5 = 180,
    opcode_nop6 = 181,
    opcode_nop7 = 182,
    opcode_nop8 = 183,
    opcode_nop9 = 184,
    opcode_nop10 = 185,
    opcode_bad_operation,
    opcode_raw_data

} bc_opcode_t;

typedef enum bc_script_context_t
{
    script_context_none_enabled = 0,

    /// pay-to-script-hash enabled
    script_context_bip16_enabled = 1 << 0,

    /// no duplicated unspent transaction ids
    script_context_bip30_enabled = 1 << 1,

    /// coinbase must include height
    script_context_bip34_enabled = 1 << 2,

    /// strict DER signatures required
    script_context_bip66_enabled = 1 << 3,

    /// nop2 becomes check locktime verify
    script_context_bip65_enabled = 1 << 4,

    script_context_all_enabled = 0xffffffff

} bc_script_context_t;

bc_string_t* opcode_to_string(bc_opcode_t value, uint32_t flags);
bc_opcode_t string_to_opcode(const char* value);
bc_opcode_t data_to_opcode(const bc_data_chunk_t* value);

#ifdef __cplusplus
}
#endif

#endif

