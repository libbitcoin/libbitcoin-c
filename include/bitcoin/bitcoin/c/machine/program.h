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
#ifndef LIBBITCOIN_C_MACHINE_PROGRAM_H
#define LIBBITCOIN_C_MACHINE_PROGRAM_H

#include <bitcoin/bitcoin/c/chain/script.h>
#include <bitcoin/bitcoin/c/chain/transaction.h>
#include <bitcoin/bitcoin/c/constants.h>
#include <bitcoin/bitcoin/c/machine/number.h>
#include <bitcoin/bitcoin/c/machine/opcode.h>
#include <bitcoin/bitcoin/c/machine/operation.h>
#include <bitcoin/bitcoin/c/utility/data.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_program_t bc_program_t;

/// Create an instance that does not expect to verify signatures.
/// This is useful for script utilities but not with input validation.
/// This can only run individual operations via run(op, program).
bc_program_t* bc_create_program();

/// Create an instance that does not expect to verify signatures.
/// This is useful for script utilities but not with input validation.
/// This can run ops via run(op, program) or the script via run(program).
bc_program_t* bc_create_program_Script(const bc_script_t* script);

/// Create an instance with empty stacks (input run).
bc_program_t* bc_create_program_Args(
    const bc_script_t* script, const bc_transaction_t* transaction,
    uint32_t input_index, uint32_t forks);

/// Create using copied forks and copied stack (prevout run).
bc_program_t* bc_create_program_Other(
    const bc_script_t* script, const bc_program_t* other);

/// Destructor
void bc_destroy_program(bc_program_t* self);

/// Constant registers.
bool bc_program__is_valid(const bc_program_t* self);
uint32_t bc_program__forks(const bc_program_t* self);
uint32_t bc_program__input_index(const bc_program_t* self);
bc_transaction_t* bc_program__transaction(const bc_program_t* self);

/// Program registers.
/*
inline op_iterator begin() const;
inline op_iterator jump() const;
inline op_iterator end() const;
inline size_t operation_count() const;
*/

/// Instructions.
bc_error_code_t* bc_program__evaluate(const bc_program_t* self);
bc_error_code_t* bc_program__evaluate_Op(
    const bc_program_t* self, const bc_operation_t* op);
bool bc_program__increment_operation_count(
    const bc_program_t* self, const bc_operation_t* op);
bool bc_program__increment_multisig_public_key_count(
    const bc_program_t* self, int32_t count);
bool bc_program__set_jump_register(
    const bc_program_t* self, const bc_operation_t* op, int32_t offset);

// Primary stack.
//-------------------------------------------------------------------------

/// Primary push.
void bc_program__push(const bc_program_t* self, bool value);
void bc_program__push_copy(
    const bc_program_t* self, const bc_data_chunk_t* item);

/// Primary pop.
bc_data_chunk_t* bc_program__pop(const bc_program_t* self);
bool bc_program__pop_Int(const bc_program_t* self, int32_t* out_value);
bool bc_program__pop_Number(const bc_program_t* self,
    bc_machine_number_t* out_number);
bool bc_program__pop_Number_MaxSize(const bc_program_t* self,
    bc_machine_number_t* out_number, size_t maxiumum_size);
bool bc_program__pop_binary(
    bc_machine_number_t* first, bc_machine_number_t* second);
bool bc_program__pop_ternary(
    bc_machine_number_t* first, bc_machine_number_t* second,
    bc_machine_number_t* third);
//bool pop_position(stack_iterator& out_position);
bool bc_program__pop_Section(const bc_data_stack_t* section, size_t count);

/// Primary push/pop optimizations (active).
void bc_program__duplicate(bc_program_t* self, size_t index);
void bc_program__swap(bc_program_t* self,
    size_t index_left, size_t index_right);
void bc_program__erase(bc_program_t* self, size_t position);
void bc_program__erase_2Iters(bc_program_t* self, size_t first, size_t last);

/// Primary push/pop optimizations (passive).
bool bc_program__empty(const bc_program_t* self);
bool bc_program__stack_true(const bc_program_t* self);
bool bc_program__stack_result(const bc_program_t* self);
bool bc_program__is_stack_overflow(const bc_program_t* self);
bool bc_program__if_(const bc_program_t* self, const bc_operation_t* op);
bc_data_chunk_t* bc_program__item(bc_program_t* self, size_t index);
bool bc_program__top(bc_machine_number_t* out_number);
bool bc_program__top_MaxSize(
    bc_machine_number_t* out_number, size_t maxiumum_size);
//stack_iterator position(size_t index) /*const*/;
bc_operation_list_t* bc_program__subscript(const bc_program_t* self);
size_t bc_program__size(const bc_program_t* self);

// Alternate stack.
//-------------------------------------------------------------------------

bool bc_program__empty_alternate(const bc_program_t* self);
void push_alternate(const bc_program_t* self, const bc_data_chunk_t* value);
bc_data_chunk_t* pop_alternate();

// Conditional stack.
//-------------------------------------------------------------------------

void bc_program__open(bc_program_t* self, bool value);
void bc_program__negate(bc_program_t* self);
void bc_program__close(bc_program_t* self);
bool bc_program__closed(const bc_program_t* self);
bool bc_program__succeeded(const bc_program_t* self);

#ifdef __cplusplus
}
#endif

#endif


