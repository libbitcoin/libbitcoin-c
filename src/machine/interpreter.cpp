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
#include <bitcoin/bitcoin/c/machine/interpreter.h>
#include <bitcoin/bitcoin/c/internal/machine/interpreter.hpp>

#include <bitcoin/bitcoin/c/internal/error.hpp>
#include <bitcoin/bitcoin/c/internal/machine/opcode.hpp>
#include <bitcoin/bitcoin/c/internal/machine/operation.hpp>
#include <bitcoin/bitcoin/c/internal/machine/program.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>

extern "C" {

bc_error_t bc_interpreter__op_nop(bc_opcode_t value)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_nop(
            bc_opcode_from_ctype(value)));
}
bc_error_t bc_interpreter__op_disabled(bc_opcode_t value)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_disabled(
            bc_opcode_from_ctype(value)));
}
bc_error_t bc_interpreter__op_reserved(bc_opcode_t value)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_reserved(
            bc_opcode_from_ctype(value)));
}
bc_error_t bc_interpreter__op_push_number(bc_program_t* program, uint8_t value)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_push_number(
            *program->obj, value));
}
bc_error_t bc_interpreter__op_push_size(bc_program_t* program,
    const bc_operation_t* op)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_push_size(
            *program->obj, *op->obj));
}
bc_error_t bc_interpreter__op_push_data(bc_program_t* program,
    const bc_data_chunk_t* data, uint32_t size_limit)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_push_data(
            *program->obj, *data->obj, size_limit));
}

// Operations (not shared).
//-----------------------------------------------------------------------------

bc_error_t bc_interpreter__op_if(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_if(
            *program->obj));
}
bc_error_t bc_interpreter__op_notif(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_notif(
            *program->obj));
}
bc_error_t bc_interpreter__op_else(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_else(
            *program->obj));
}
bc_error_t bc_interpreter__op_endif(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_endif(
            *program->obj));
}
bc_error_t bc_interpreter__op_verify(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_verify(
            *program->obj));
}
bc_error_t bc_interpreter__op_return(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_return(
            *program->obj));
}
bc_error_t bc_interpreter__op_to_alt_stack(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_to_alt_stack(
            *program->obj));
}
bc_error_t bc_interpreter__op_from_alt_stack(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_from_alt_stack(
            *program->obj));
}
bc_error_t bc_interpreter__op_drop2(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_drop2(
            *program->obj));
}
bc_error_t bc_interpreter__op_dup2(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_dup2(
            *program->obj));
}
bc_error_t bc_interpreter__op_dup3(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_dup3(
            *program->obj));
}
bc_error_t bc_interpreter__op_over2(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_over2(
            *program->obj));
}
bc_error_t bc_interpreter__op_rot2(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_rot2(
            *program->obj));
}
bc_error_t bc_interpreter__op_swap2(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_swap2(
            *program->obj));
}
bc_error_t bc_interpreter__op_if_dup(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_if_dup(
            *program->obj));
}
bc_error_t bc_interpreter__op_depth(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_depth(
            *program->obj));
}
bc_error_t bc_interpreter__op_drop(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_drop(
            *program->obj));
}
bc_error_t bc_interpreter__op_dup(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_dup(
            *program->obj));
}
bc_error_t bc_interpreter__op_nip(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_nip(
            *program->obj));
}
bc_error_t bc_interpreter__op_over(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_over(
            *program->obj));
}
bc_error_t bc_interpreter__op_pick(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_pick(
            *program->obj));
}
bc_error_t bc_interpreter__op_roll(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_roll(
            *program->obj));
}
bc_error_t bc_interpreter__op_rot(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_rot(
            *program->obj));
}
bc_error_t bc_interpreter__op_swap(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_swap(
            *program->obj));
}
bc_error_t bc_interpreter__op_tuck(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_tuck(
            *program->obj));
}
bc_error_t bc_interpreter__op_size(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_size(
            *program->obj));
}
bc_error_t bc_interpreter__op_equal(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_equal(
            *program->obj));
}
bc_error_t bc_interpreter__op_equal_verify(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_equal_verify(
            *program->obj));
}
bc_error_t bc_interpreter__op_add1(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_add1(
            *program->obj));
}
bc_error_t bc_interpreter__op_sub1(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_sub1(
            *program->obj));
}
bc_error_t bc_interpreter__op_negate(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_negate(
            *program->obj));
}
bc_error_t bc_interpreter__op_abs(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_abs(
            *program->obj));
}
bc_error_t bc_interpreter__op_not(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_not(
            *program->obj));
}
bc_error_t bc_interpreter__op_nonzero(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_nonzero(
            *program->obj));
}
bc_error_t bc_interpreter__op_add(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_add(
            *program->obj));
}
bc_error_t bc_interpreter__op_sub(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_sub(
            *program->obj));
}
bc_error_t bc_interpreter__op_bool_and(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_bool_and(
            *program->obj));
}
bc_error_t bc_interpreter__op_bool_or(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_bool_or(
            *program->obj));
}
bc_error_t bc_interpreter__op_num_equal(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_num_equal(
            *program->obj));
}
bc_error_t bc_interpreter__op_num_equal_verify(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_num_equal_verify(
            *program->obj));
}
bc_error_t bc_interpreter__op_num_not_equal(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_num_not_equal(
            *program->obj));
}
bc_error_t bc_interpreter__op_less_than(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_less_than(
            *program->obj));
}
bc_error_t bc_interpreter__op_greater_than(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_greater_than(
            *program->obj));
}
bc_error_t bc_interpreter__op_less_than_or_equal(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_less_than_or_equal(
            *program->obj));
}
bc_error_t bc_interpreter__op_greater_than_or_equal(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_greater_than_or_equal(
            *program->obj));
}
bc_error_t bc_interpreter__op_min(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_min(
            *program->obj));
}
bc_error_t bc_interpreter__op_max(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_max(
            *program->obj));
}
bc_error_t bc_interpreter__op_within(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_within(
            *program->obj));
}
bc_error_t bc_interpreter__op_ripemd160(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_ripemd160(
            *program->obj));
}
bc_error_t bc_interpreter__op_sha1(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_sha1(
            *program->obj));
}
bc_error_t bc_interpreter__op_sha256(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_sha256(
            *program->obj));
}
bc_error_t bc_interpreter__op_hash160(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_hash160(
            *program->obj));
}
bc_error_t bc_interpreter__op_hash256(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_hash256(
            *program->obj));
}
bc_error_t bc_interpreter__op_codeseparator(bc_program_t* program,
    const bc_operation_t* op)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_codeseparator(
            *program->obj, *op->obj));
}
bc_error_t bc_interpreter__op_check_sig_verify(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_check_sig_verify(
            *program->obj));
}
bc_error_t bc_interpreter__op_check_sig(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_check_sig(
            *program->obj));
}
bc_error_t bc_interpreter__op_check_multisig_verify(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_check_multisig_verify(
            *program->obj));
}
bc_error_t bc_interpreter__op_check_multisig(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_check_multisig(
            *program->obj));
}
bc_error_t bc_interpreter__op_check_locktime_verify(bc_program_t* program)
{
    return bc_error_code_to_ctype(
        libbitcoin::machine::interpreter::op_check_locktime_verify(
            *program->obj));
}

/// Run program script.
bc_error_code_t* bc_interpreter__run(bc_program_t* program)
{
    return new bc_error_code_t{ new std::error_code(
        libbitcoin::machine::interpreter::run(*program->obj)) };
}

/// Run individual operations (idependent of the script).
/// For best performance use script runner for a sequence of operations.
bc_error_code_t* bc_interpreter__run_Op(
    const bc_operation_t* op, bc_program_t* program)
{
    return new bc_error_code_t{ new std::error_code(
        libbitcoin::machine::interpreter::run(*op->obj, *program->obj)) };
}

} // extern C

