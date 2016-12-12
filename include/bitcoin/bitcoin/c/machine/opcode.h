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
#ifndef LIBBITCOIN_C_MACHINE_OPCODE_H
#define LIBBITCOIN_C_MACHINE_OPCODE_H

#include <stdint.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum bc_opcode_t
{
    //-------------------------------------------------------------------------
    // is_push (excluding reserved_80)

    bc_opcode__push_size_0 = 0,
    bc_opcode__push_size_1 = 1,
    bc_opcode__push_size_2 = 2,
    bc_opcode__push_size_3 = 3,
    bc_opcode__push_size_4 = 4,
    bc_opcode__push_size_5 = 5,
    bc_opcode__push_size_6 = 6,
    bc_opcode__push_size_7 = 7,
    bc_opcode__push_size_8 = 8,
    bc_opcode__push_size_9 = 9,
    bc_opcode__push_size_10 = 10,
    bc_opcode__push_size_11 = 11,
    bc_opcode__push_size_12 = 12,
    bc_opcode__push_size_13 = 13,
    bc_opcode__push_size_14 = 14,
    bc_opcode__push_size_15 = 15,
    bc_opcode__push_size_16 = 16,
    bc_opcode__push_size_17 = 17,
    bc_opcode__push_size_18 = 18,
    bc_opcode__push_size_19 = 19,
    bc_opcode__push_size_20 = 20,
    bc_opcode__push_size_21 = 21,
    bc_opcode__push_size_22 = 22,
    bc_opcode__push_size_23 = 23,
    bc_opcode__push_size_24 = 24,
    bc_opcode__push_size_25 = 25,
    bc_opcode__push_size_26 = 26,
    bc_opcode__push_size_27 = 27,
    bc_opcode__push_size_28 = 28,
    bc_opcode__push_size_29 = 29,
    bc_opcode__push_size_30 = 30,
    bc_opcode__push_size_31 = 31,
    bc_opcode__push_size_32 = 32,
    bc_opcode__push_size_33 = 33,
    bc_opcode__push_size_34 = 34,
    bc_opcode__push_size_35 = 35,
    bc_opcode__push_size_36 = 36,
    bc_opcode__push_size_37 = 37,
    bc_opcode__push_size_38 = 38,
    bc_opcode__push_size_39 = 39,
    bc_opcode__push_size_40 = 40,
    bc_opcode__push_size_41 = 41,
    bc_opcode__push_size_42 = 42,
    bc_opcode__push_size_43 = 43,
    bc_opcode__push_size_44 = 44,
    bc_opcode__push_size_45 = 45,
    bc_opcode__push_size_46 = 46,
    bc_opcode__push_size_47 = 47,
    bc_opcode__push_size_48 = 48,
    bc_opcode__push_size_49 = 49,
    bc_opcode__push_size_50 = 50,
    bc_opcode__push_size_51 = 51,
    bc_opcode__push_size_52 = 52,
    bc_opcode__push_size_53 = 53,
    bc_opcode__push_size_54 = 54,
    bc_opcode__push_size_55 = 55,
    bc_opcode__push_size_56 = 56,
    bc_opcode__push_size_57 = 57,
    bc_opcode__push_size_58 = 58,
    bc_opcode__push_size_59 = 59,
    bc_opcode__push_size_60 = 60,
    bc_opcode__push_size_61 = 61,
    bc_opcode__push_size_62 = 62,
    bc_opcode__push_size_63 = 63,
    bc_opcode__push_size_64 = 64,
    bc_opcode__push_size_65 = 65,
    bc_opcode__push_size_66 = 66,
    bc_opcode__push_size_67 = 67,
    bc_opcode__push_size_68 = 68,
    bc_opcode__push_size_69 = 69,
    bc_opcode__push_size_70 = 70,
    bc_opcode__push_size_71 = 71,
    bc_opcode__push_size_72 = 72,
    bc_opcode__push_size_73 = 73,
    bc_opcode__push_size_74 = 74,
    bc_opcode__push_size_75 = 75,
    bc_opcode__push_one_size = 76,
    bc_opcode__push_two_size = 77,
    bc_opcode__push_four_size = 78,
    bc_opcode__push_negative_1 = 79,   // is_numeric
    bc_opcode__reserved_80 = 80,       // [reserved]
    bc_opcode__push_positive_1 = 81,   // is_numeric, is_positive
    bc_opcode__push_positive_2 = 82,   // is_numeric, is_positive
    bc_opcode__push_positive_3 = 83,   // is_numeric, is_positive
    bc_opcode__push_positive_4 = 84,   // is_numeric, is_positive
    bc_opcode__push_positive_5 = 85,   // is_numeric, is_positive
    bc_opcode__push_positive_6 = 86,   // is_numeric, is_positive
    bc_opcode__push_positive_7 = 87,   // is_numeric, is_positive
    bc_opcode__push_positive_8 = 88,   // is_numeric, is_positive
    bc_opcode__push_positive_9 = 89,   // is_numeric, is_positive
    bc_opcode__push_positive_10 = 90,  // is_numeric, is_positive
    bc_opcode__push_positive_11 = 91,  // is_numeric, is_positive
    bc_opcode__push_positive_12 = 92,  // is_numeric, is_positive
    bc_opcode__push_positive_13 = 93,  // is_numeric, is_positive
    bc_opcode__push_positive_14 = 94,  // is_numeric, is_positive
    bc_opcode__push_positive_15 = 95,  // is_numeric, is_positive
    bc_opcode__push_positive_16 = 96,  // is_numeric, is_positive

    //-------------------------------------------------------------------------
    // is_counted

    bc_opcode__nop = 97,
    bc_opcode__reserved_98 = 98,       // [ver]
    bc_opcode__if_ = 99,               // is_conditional
    bc_opcode__notif = 100,            // is_conditional
    bc_opcode__disabled_verif = 101,   // is_disabled
    bc_opcode__disabled_vernotif = 102,// is_disabled
    bc_opcode__else_ = 103,            // is_conditional
    bc_opcode__endif = 104,            // is_conditional
    bc_opcode__verify = 105,
    bc_opcode__return_ = 106,
    bc_opcode__toaltstack = 107,
    bc_opcode__fromaltstack = 108,
    bc_opcode__drop2 = 109,
    bc_opcode__dup2 = 110,
    bc_opcode__dup3 = 111,
    bc_opcode__over2 = 112,
    bc_opcode__rot2 = 113,
    bc_opcode__swap2 = 114,
    bc_opcode__ifdup = 115,
    bc_opcode__depth = 116,
    bc_opcode__drop = 117,
    bc_opcode__dup = 118,
    bc_opcode__nip = 119,
    bc_opcode__over = 120,
    bc_opcode__pick = 121,
    bc_opcode__roll = 122,
    bc_opcode__rot = 123,
    bc_opcode__swap = 124,
    bc_opcode__tuck = 125,
    bc_opcode__disabled_cat = 126,     // is_disabled
    bc_opcode__disabled_substr = 127,  // is_disabled
    bc_opcode__disabled_left = 128,    // is_disabled
    bc_opcode__disabled_right = 129,   // is_disabled
    bc_opcode__size = 130,
    bc_opcode__disabled_invert = 131,  // is_disabled
    bc_opcode__disabled_and = 132,     // is_disabled
    bc_opcode__disabled_or = 133,      // is_disabled
    bc_opcode__disabled_xor = 134,     // is_disabled
    bc_opcode__equal = 135,
    bc_opcode__equalverify = 136,
    bc_opcode__reserved_137 = 137,     // [reserved1]
    bc_opcode__reserved_138 = 138,     // [reserved2]
    bc_opcode__add1 = 139,
    bc_opcode__sub1 = 140,
    bc_opcode__disabled_mul2 = 141,    // is_disabled
    bc_opcode__disabled_div2 = 142,    // is_disabled
    bc_opcode__negate = 143,
    bc_opcode__abs = 144,
    bc_opcode__not_ = 145,
    bc_opcode__nonzero = 146,
    bc_opcode__add = 147,
    bc_opcode__sub = 148,
    bc_opcode__disabled_mul = 149,     // is_disabled
    bc_opcode__disabled_div = 150,     // is_disabled
    bc_opcode__disabled_mod = 151,     // is_disabled
    bc_opcode__disabled_lshift = 152,  // is_disabled
    bc_opcode__disabled_rshift = 153,  // is_disabled
    bc_opcode__booland = 154,
    bc_opcode__boolor = 155,
    bc_opcode__numequal = 156,
    bc_opcode__numequalverify = 157,
    bc_opcode__numnotequal = 158,
    bc_opcode__lessthan = 159,
    bc_opcode__greaterthan = 160,
    bc_opcode__lessthanorequal = 161,
    bc_opcode__greaterthanorequal = 162,
    bc_opcode__min = 163,
    bc_opcode__max = 164,
    bc_opcode__within = 165,
    bc_opcode__ripemd160 = 166,
    bc_opcode__sha1 = 167,
    bc_opcode__sha256 = 168,
    bc_opcode__hash160 = 169,
    bc_opcode__hash256 = 170,
    bc_opcode__codeseparator = 171,
    bc_opcode__checksig = 172,
    bc_opcode__checksigverify = 173,
    bc_opcode__checkmultisig = 174,
    bc_opcode__checkmultisigverify = 175,
    bc_opcode__nop1 = 176,
    bc_opcode__nop2 = 177,
    bc_opcode__checklocktimeverify = bc_opcode__nop2,
    bc_opcode__nop3 = 178,
    bc_opcode__nop4 = 179,
    bc_opcode__nop5 = 180,
    bc_opcode__nop6 = 181,
    bc_opcode__nop7 = 182,
    bc_opcode__nop8 = 183,
    bc_opcode__nop9 = 184,
    bc_opcode__nop10 = 185,
    bc_opcode__reserved_186 = 186,
    bc_opcode__reserved_187 = 187,
    bc_opcode__reserved_188 = 188,
    bc_opcode__reserved_189 = 189,
    bc_opcode__reserved_190 = 190,
    bc_opcode__reserved_191 = 191,
    bc_opcode__reserved_192 = 192,
    bc_opcode__reserved_193 = 193,
    bc_opcode__reserved_194 = 194,
    bc_opcode__reserved_195 = 195,
    bc_opcode__reserved_196 = 196,
    bc_opcode__reserved_197 = 197,
    bc_opcode__reserved_198 = 198,
    bc_opcode__reserved_199 = 199,
    bc_opcode__reserved_200 = 200,
    bc_opcode__reserved_201 = 201,
    bc_opcode__reserved_202 = 202,
    bc_opcode__reserved_203 = 203,
    bc_opcode__reserved_204 = 204,
    bc_opcode__reserved_205 = 205,
    bc_opcode__reserved_206 = 206,
    bc_opcode__reserved_207 = 207,
    bc_opcode__reserved_208 = 208,
    bc_opcode__reserved_209 = 209,
    bc_opcode__reserved_210 = 210,
    bc_opcode__reserved_211 = 211,
    bc_opcode__reserved_212 = 212,
    bc_opcode__reserved_213 = 213,
    bc_opcode__reserved_214 = 214,
    bc_opcode__reserved_215 = 215,
    bc_opcode__reserved_216 = 216,
    bc_opcode__reserved_217 = 217,
    bc_opcode__reserved_218 = 218,
    bc_opcode__reserved_219 = 219,
    bc_opcode__reserved_220 = 220,
    bc_opcode__reserved_221 = 221,
    bc_opcode__reserved_222 = 222,
    bc_opcode__reserved_223 = 223,
    bc_opcode__reserved_224 = 224,
    bc_opcode__reserved_225 = 225,
    bc_opcode__reserved_226 = 226,
    bc_opcode__reserved_227 = 227,
    bc_opcode__reserved_228 = 228,
    bc_opcode__reserved_229 = 229,
    bc_opcode__reserved_230 = 230,
    bc_opcode__reserved_231 = 231,
    bc_opcode__reserved_232 = 232,
    bc_opcode__reserved_233 = 233,
    bc_opcode__reserved_234 = 234,
    bc_opcode__reserved_235 = 235,
    bc_opcode__reserved_236 = 236,
    bc_opcode__reserved_237 = 237,
    bc_opcode__reserved_238 = 238,
    bc_opcode__reserved_239 = 239,
    bc_opcode__reserved_240 = 240,
    bc_opcode__reserved_241 = 241,
    bc_opcode__reserved_242 = 242,
    bc_opcode__reserved_243 = 243,
    bc_opcode__reserved_244 = 244,
    bc_opcode__reserved_245 = 245,
    bc_opcode__reserved_246 = 246,
    bc_opcode__reserved_247 = 247,
    bc_opcode__reserved_248 = 248,
    bc_opcode__reserved_249 = 249,
    bc_opcode__reserved_250 = 250,
    bc_opcode__reserved_251 = 251,
    bc_opcode__reserved_252 = 252,
    bc_opcode__reserved_253 = 253,
    bc_opcode__reserved_254 = 254,
    bc_opcode__reserved_255 = 255

} bc_opcode_t;

/// Convert the opcode to a mnemonic string.
bc_string_t* bc_opcode_to_string(bc_opcode_t value, uint32_t active_forks);

/// Convert a string to an opcode.
bool bc_opcode_from_string(bc_opcode_t* out_code, const char* value);

/// Convert any opcode to a string hexadecimal representation.
bc_string_t* bc_opcode_to_hexadecimal(bc_opcode_t code);

/// Convert any hexadecimal byte to an opcode.
bool bc_opcode_from_hexadecimal(bc_opcode_t* out_code, const char* value);

#ifdef __cplusplus
}
#endif

#endif

