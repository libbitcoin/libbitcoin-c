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
#ifndef LIBBITCOIN_C_MACHINE_INTERPRETER_H
#define LIBBITCOIN_C_MACHINE_INTERPRETER_H

#include <bitcoin/bitcoin/c/error.h>
#include <bitcoin/bitcoin/c/machine/opcode.h>
#include <bitcoin/bitcoin/c/machine/operation.h>
#include <bitcoin/bitcoin/c/machine/program.h>
#include <bitcoin/bitcoin/c/utility/data.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_interpreter_t bc_interpreter_t;

// Operations (shared).
//-----------------------------------------------------------------------------

bc_error_t bc_interpreter__op_nop(bc_opcode_t);
bc_error_t bc_interpreter__op_disabled(bc_opcode_t);
bc_error_t bc_interpreter__op_reserved(bc_opcode_t);
bc_error_t bc_interpreter__op_push_number(bc_program_t* program, uint8_t value);
bc_error_t bc_interpreter__op_push_size(bc_program_t* program,
    const bc_operation_t* op);
bc_error_t bc_interpreter__op_push_data(bc_program_t* program,
    const bc_data_chunk_t* data, uint32_t size_limit);

// Operations (not shared).
//-----------------------------------------------------------------------------

bc_error_t bc_interpreter__op_if(bc_program_t* program);
bc_error_t bc_interpreter__op_notif(bc_program_t* program);
bc_error_t bc_interpreter__op_else(bc_program_t* program);
bc_error_t bc_interpreter__op_endif(bc_program_t* program);
bc_error_t bc_interpreter__op_verify(bc_program_t* program);
bc_error_t bc_interpreter__op_return(bc_program_t* program);
bc_error_t bc_interpreter__op_to_alt_stack(bc_program_t* program);
bc_error_t bc_interpreter__op_from_alt_stack(bc_program_t* program);
bc_error_t bc_interpreter__op_drop2(bc_program_t* program);
bc_error_t bc_interpreter__op_dup2(bc_program_t* program);
bc_error_t bc_interpreter__op_dup3(bc_program_t* program);
bc_error_t bc_interpreter__op_over2(bc_program_t* program);
bc_error_t bc_interpreter__op_rot2(bc_program_t* program);
bc_error_t bc_interpreter__op_swap2(bc_program_t* program);
bc_error_t bc_interpreter__op_if_dup(bc_program_t* program);
bc_error_t bc_interpreter__op_depth(bc_program_t* program);
bc_error_t bc_interpreter__op_drop(bc_program_t* program);
bc_error_t bc_interpreter__op_dup(bc_program_t* program);
bc_error_t bc_interpreter__op_nip(bc_program_t* program);
bc_error_t bc_interpreter__op_over(bc_program_t* program);
bc_error_t bc_interpreter__op_pick(bc_program_t* program);
bc_error_t bc_interpreter__op_roll(bc_program_t* program);
bc_error_t bc_interpreter__op_rot(bc_program_t* program);
bc_error_t bc_interpreter__op_swap(bc_program_t* program);
bc_error_t bc_interpreter__op_tuck(bc_program_t* program);
bc_error_t bc_interpreter__op_size(bc_program_t* program);
bc_error_t bc_interpreter__op_equal(bc_program_t* program);
bc_error_t bc_interpreter__op_equal_verify(bc_program_t* program);
bc_error_t bc_interpreter__op_add1(bc_program_t* program);
bc_error_t bc_interpreter__op_sub1(bc_program_t* program);
bc_error_t bc_interpreter__op_negate(bc_program_t* program);
bc_error_t bc_interpreter__op_abs(bc_program_t* program);
bc_error_t bc_interpreter__op_not(bc_program_t* program);
bc_error_t bc_interpreter__op_nonzero(bc_program_t* program);
bc_error_t bc_interpreter__op_add(bc_program_t* program);
bc_error_t bc_interpreter__op_sub(bc_program_t* program);
bc_error_t bc_interpreter__op_bool_and(bc_program_t* program);
bc_error_t bc_interpreter__op_bool_or(bc_program_t* program);
bc_error_t bc_interpreter__op_num_equal(bc_program_t* program);
bc_error_t bc_interpreter__op_num_equal_verify(bc_program_t* program);
bc_error_t bc_interpreter__op_num_not_equal(bc_program_t* program);
bc_error_t bc_interpreter__op_less_than(bc_program_t* program);
bc_error_t bc_interpreter__op_greater_than(bc_program_t* program);
bc_error_t bc_interpreter__op_less_than_or_equal(bc_program_t* program);
bc_error_t bc_interpreter__op_greater_than_or_equal(bc_program_t* program);
bc_error_t bc_interpreter__op_min(bc_program_t* program);
bc_error_t bc_interpreter__op_max(bc_program_t* program);
bc_error_t bc_interpreter__op_within(bc_program_t* program);
bc_error_t bc_interpreter__op_ripemd160(bc_program_t* program);
bc_error_t bc_interpreter__op_sha1(bc_program_t* program);
bc_error_t bc_interpreter__op_sha256(bc_program_t* program);
bc_error_t bc_interpreter__op_hash160(bc_program_t* program);
bc_error_t bc_interpreter__op_hash256(bc_program_t* program);
bc_error_t bc_interpreter__op_codeseparator(bc_program_t* program,
    const bc_operation_t* op);
bc_error_t bc_interpreter__op_check_sig_verify(bc_program_t* program);
bc_error_t bc_interpreter__op_check_sig(bc_program_t* program);
bc_error_t bc_interpreter__op_check_multisig_verify(bc_program_t* program);
bc_error_t bc_interpreter__op_check_multisig(bc_program_t* program);
bc_error_t bc_interpreter__op_check_locktime_verify(bc_program_t* program);

/// Run program script.
bc_error_code_t* bc_interpreter__run(bc_program_t* program);

/// Run individual operations (idependent of the script).
/// For best performance use script runner for a sequence of operations.
bc_error_code_t* bc_interpreter__run_Op(
    const bc_operation_t* op, bc_program_t* program);

#ifdef __cplusplus
}
#endif

#endif

