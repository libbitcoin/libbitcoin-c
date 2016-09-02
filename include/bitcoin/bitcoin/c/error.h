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
#ifndef LIBBITCOIN_C_ERROR_H
#define LIBBITCOIN_C_ERROR_H

#include <stdbool.h>
#include <bitcoin/bitcoin/c/utility/string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum bc_console_result_t
{
    bc_console_result_failure = -1,
    bc_console_result_okay = 0,
    bc_console_result_invalid = 1
} bc_console_result_t;

// The numeric values of these codes may change without notice.
typedef enum bc_error_t
{
    bc_error_success = 0,

    // network errors
    bc_error_service_stopped,
    bc_error_operation_failed,

    // blockchain errors
    bc_error_not_found,
    bc_error_duplicate,
    bc_error_unspent_output,
    bc_error_unsupported_script_pattern,

    // network errors (more)
    bc_error_resolve_failed,
    bc_error_network_unreachable,
    bc_error_address_in_use,
    bc_error_listen_failed,
    bc_error_accept_failed,
    bc_error_bad_stream,
    bc_error_channel_timeout,

    // transaction pool
    bc_error_blockchain_reorganized,
    bc_error_pool_filled,

    // validate tx
    bc_error_coinbase_transaction,
    bc_error_is_not_standard,
    bc_error_double_spend,
    bc_error_input_not_found,

    // check_transaction()
    bc_error_empty_transaction,
    bc_error_output_value_overflow,
    bc_error_invalid_coinbase_script_size,
    bc_error_previous_output_null,

    // validate block
    bc_error_previous_block_invalid,

    // check_block()
    bc_error_size_limits,
    bc_error_proof_of_work,
    bc_error_futuristic_timestamp,
    bc_error_first_not_coinbase,
    bc_error_extra_coinbases,
    bc_error_too_many_sigs,
    bc_error_merkle_mismatch,

    // accept_block()
    bc_error_incorrect_proof_of_work,
    bc_error_timestamp_too_early,
    bc_error_non_final_transaction,
    bc_error_checkpoints_failed,
    bc_error_old_version_block,
    bc_error_coinbase_height_mismatch,

    // connect_block()
    bc_error_duplicate_or_spent,
    bc_error_validate_inputs_failed,
    bc_error_fees_out_of_range,
    bc_error_coinbase_too_large,

    // file system errors
    bc_error_file_system,

    // unknown errors
    bc_error_unknown,

    // network errors (more)
    bc_error_address_blocked,
    bc_error_channel_stopped
} bc_error_t;

typedef struct bc_error_code_t bc_error_code_t;
bc_error_code_t* bc_create_error_code(bc_error_t error);
bc_error_code_t* bc_create_error_code_default();
void bc_destroy_error_code(bc_error_code_t* self);
bc_string_t* bc_error_code_message(const bc_error_code_t* self);
bool bc_error_code_is_error(const bc_error_code_t* self);
bool bc_error_code_equals(const bc_error_code_t* self, bc_error_t ec);

#ifdef __cplusplus
}
#endif

#endif

