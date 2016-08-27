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
    bc_opcode_zero = 0,
    bc_opcode_special = 1,
    bc_opcode_pushdata1 = 76,
    bc_opcode_pushdata2 = 77,
    bc_opcode_pushdata4 = 78,
    bc_opcode_negative_1 = 79,
    // reserved does nothing
    bc_opcode_reserved = 80,
    bc_opcode_1 = 81,
    bc_opcode_2 = 82,
    bc_opcode_3 = 83,
    bc_opcode_4 = 84,
    bc_opcode_5 = 85,
    bc_opcode_6 = 86,
    bc_opcode_7 = 87,
    bc_opcode_8 = 88,
    bc_opcode_9 = 89,
    bc_opcode_10 = 90,
    bc_opcode_11 = 91,
    bc_opcode_12 = 92,
    bc_opcode_13 = 93,
    bc_opcode_14 = 94,
    bc_opcode_15 = 95,
    bc_opcode_16 = 96,
    bc_opcode_nop = 97,
    bc_opcode_ver = 98,
    bc_opcode_if_ = 99,
    bc_opcode_notif = 100,
    bc_opcode_verif = 101,
    bc_opcode_vernotif = 102,
    bc_opcode_else = 103,
    bc_opcode_endif = 104,
    bc_opcode_verify = 105,
    bc_opcode_return_ = 106,
    bc_opcode_toaltstack = 107,
    bc_opcode_fromaltstack = 108,
    bc_opcode_2drop = 109,
    bc_opcode_2dup = 110,
    bc_opcode_3dup = 111,
    bc_opcode_2over = 112,
    bc_opcode_2rot = 113,
    bc_opcode_2swap = 114,
    bc_opcode_ifdup = 115,
    bc_opcode_depth = 116,
    bc_opcode_drop = 117,
    bc_opcode_dup = 118,
    bc_opcode_nip = 119,
    bc_opcode_over = 120,
    bc_opcode_pick = 121,
    bc_opcode_roll = 122,
    bc_opcode_rot = 123,
    bc_opcode_swap = 124,
    bc_opcode_tuck = 125,
    bc_opcode_cat = 126,          // disabled
    bc_opcode_substr = 127,       // disabled
    bc_opcode_left = 128,         // disabled
    bc_opcode_right = 129,        // disabled
    bc_opcode_size = 130,
    bc_opcode_invert = 131,       // disabled
    bc_opcode_and = 132,         // disabled
    bc_opcode_or = 133,          // disabled
    bc_opcode_xor = 134,         // disabled
    bc_opcode_equal = 135,
    bc_opcode_equalverify = 136,
    bc_opcode_reserved1 = 137,
    bc_opcode_reserved2 = 138,
    bc_opcode_1add = 139,
    bc_opcode_1sub = 140,
    bc_opcode_2mul = 141,      // disabled
    bc_opcode_2div = 142,      // disabled
    bc_opcode_negate = 143,
    bc_opcode_abs = 144,
    bc_opcode_not = 145,
    bc_opcode_0notequal = 146,
    bc_opcode_add = 147,
    bc_opcode_sub = 148,
    bc_opcode_mul = 149,          // disabled
    bc_opcode_div = 150,          // disabled
    bc_opcode_mod = 151,          // disabled
    bc_opcode_lshift = 152,       // disabled
    bc_opcode_rshift = 153,       // disabled
    bc_opcode_booland = 154,
    bc_opcode_boolor = 155,
    bc_opcode_numequal = 156,
    bc_opcode_numequalverify = 157,
    bc_opcode_numnotequal = 158,
    bc_opcode_lessthan = 159,
    bc_opcode_greaterthan = 160,
    bc_opcode_lessthanorequal = 161,
    bc_opcode_greaterthanorequal = 162,
    bc_opcode_min = 163,
    bc_opcode_max = 164,
    bc_opcode_within = 165,
    bc_opcode_ripemd160 = 166,
    bc_opcode_sha1 = 167,
    bc_opcode_sha256 = 168,
    bc_opcode_hash160 = 169,
    bc_opcode_hash256 = 170,
    bc_opcode_codeseparator = 171,
    bc_opcode_checksig = 172,
    bc_opcode_checksigverify = 173,
    bc_opcode_checkmultisig = 174,
    bc_opcode_checkmultisigverify = 175,
    bc_opcode_nop1 = 176,
    bc_opcode_nop2 = 177,
    bc_opcode_checklocktimeverify = bc_opcode_nop2,
    bc_opcode_nop3 = 178,
    bc_opcode_nop4 = 179,
    bc_opcode_nop5 = 180,
    bc_opcode_nop6 = 181,
    bc_opcode_nop7 = 182,
    bc_opcode_nop8 = 183,
    bc_opcode_nop9 = 184,
    bc_opcode_nop10 = 185,
    bc_opcode_bad_operation,
    bc_opcode_raw_data

} bc_opcode_t;

typedef enum bc_script_context_t
{
    bc_script_context_none_enabled = 0,

    /// pay-to-script-hash enabled
    bc_script_context_bip16_enabled = 1 << 0,

    /// no duplicated unspent transaction ids
    bc_script_context_bip30_enabled = 1 << 1,

    /// coinbase must include height
    bc_script_context_bip34_enabled = 1 << 2,

    /// strict DER signatures required
    bc_script_context_bip66_enabled = 1 << 3,

    /// nop2 becomes check locktime verify
    bc_script_context_bip65_enabled = 1 << 4,

    bc_script_context_all_enabled = 0xffffffff

} bc_script_context_t;

bc_string_t* opcode_to_string(bc_opcode_t value, uint32_t flags);
bc_opcode_t string_to_opcode(const char* value);
bc_opcode_t data_to_opcode(const bc_data_chunk_t* value);

#ifdef __cplusplus
}
#endif

#endif

