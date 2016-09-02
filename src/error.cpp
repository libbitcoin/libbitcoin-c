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
#include <bitcoin/bitcoin/c/error.h>

#include <bitcoin/bitcoin/c/internal/error.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>

extern "C" {

bc_error_code_t* bc_create_error_code(bc_error_t error)
{
    return new bc_error_code_t{ new std::error_code(
        bc_error_code_from_ctype(error)) };
}
bc_error_code_t* bc_create_error_code_default()
{
    return new bc_error_code_t{ new std::error_code };
}
void bc_destroy_error_code(bc_error_code_t* self)
{
    delete self->obj;
    delete self;
}
bc_string_t* bc_error_code_message(const bc_error_code_t* self)
{
    return bc_create_string_StdString(self->obj->message());
}
bool bc_error_code_is_error(const bc_error_code_t* self)
{
    return static_cast<bool>(*self->obj);
}
bool bc_error_code_equals(const bc_error_code_t* self, bc_error_t ec)
{
    return *self->obj == bc_error_code_from_ctype(ec);
}

} // extern C

// C++ convenience functions
bc_error_t bc_error_code_to_ctype(libbitcoin::error::error_code_t value)
{
    switch (value)
    {
        case libbitcoin::error::success:
            return bc_error_success;
        case libbitcoin::error::service_stopped:
            return bc_error_service_stopped;
        case libbitcoin::error::operation_failed:
            return bc_error_operation_failed;
        case libbitcoin::error::not_found:
            return bc_error_not_found;
        case libbitcoin::error::duplicate:
            return bc_error_duplicate;
        case libbitcoin::error::unspent_output:
            return bc_error_unspent_output;
        case libbitcoin::error::unsupported_script_pattern:
            return bc_error_unsupported_script_pattern;
        case libbitcoin::error::resolve_failed:
            return bc_error_resolve_failed;
        case libbitcoin::error::network_unreachable:
            return bc_error_network_unreachable;
        case libbitcoin::error::address_in_use:
            return bc_error_address_in_use;
        case libbitcoin::error::listen_failed:
            return bc_error_listen_failed;
        case libbitcoin::error::accept_failed:
            return bc_error_accept_failed;
        case libbitcoin::error::bad_stream:
            return bc_error_bad_stream;
        case libbitcoin::error::channel_timeout:
            return bc_error_channel_timeout;
        case libbitcoin::error::blockchain_reorganized:
            return bc_error_blockchain_reorganized;
        case libbitcoin::error::pool_filled:
            return bc_error_pool_filled;
        case libbitcoin::error::coinbase_transaction:
            return bc_error_coinbase_transaction;
        case libbitcoin::error::is_not_standard:
            return bc_error_is_not_standard;
        case libbitcoin::error::double_spend:
            return bc_error_double_spend;
        case libbitcoin::error::input_not_found:
            return bc_error_input_not_found;
        case libbitcoin::error::empty_transaction:
            return bc_error_empty_transaction;
        case libbitcoin::error::output_value_overflow:
            return bc_error_output_value_overflow;
        case libbitcoin::error::invalid_coinbase_script_size:
            return bc_error_invalid_coinbase_script_size;
        case libbitcoin::error::previous_output_null:
            return bc_error_previous_output_null;
        case libbitcoin::error::previous_block_invalid:
            return bc_error_previous_block_invalid;
        case libbitcoin::error::size_limits:
            return bc_error_size_limits;
        case libbitcoin::error::proof_of_work:
            return bc_error_proof_of_work;
        case libbitcoin::error::futuristic_timestamp:
            return bc_error_futuristic_timestamp;
        case libbitcoin::error::first_not_coinbase:
            return bc_error_first_not_coinbase;
        case libbitcoin::error::extra_coinbases:
            return bc_error_extra_coinbases;
        case libbitcoin::error::too_many_sigs:
            return bc_error_too_many_sigs;
        case libbitcoin::error::merkle_mismatch:
            return bc_error_merkle_mismatch;
        case libbitcoin::error::incorrect_proof_of_work:
            return bc_error_incorrect_proof_of_work;
        case libbitcoin::error::timestamp_too_early:
            return bc_error_timestamp_too_early;
        case libbitcoin::error::non_final_transaction:
            return bc_error_non_final_transaction;
        case libbitcoin::error::checkpoints_failed:
            return bc_error_checkpoints_failed;
        case libbitcoin::error::old_version_block:
            return bc_error_old_version_block;
        case libbitcoin::error::coinbase_height_mismatch:
            return bc_error_coinbase_height_mismatch;
        case libbitcoin::error::duplicate_or_spent:
            return bc_error_duplicate_or_spent;
        case libbitcoin::error::validate_inputs_failed:
            return bc_error_validate_inputs_failed;
        case libbitcoin::error::fees_out_of_range:
            return bc_error_fees_out_of_range;
        case libbitcoin::error::coinbase_too_large:
            return bc_error_coinbase_too_large;
        case libbitcoin::error::file_system:
            return bc_error_file_system;
        case libbitcoin::error::unknown:
            return bc_error_unknown;
        case libbitcoin::error::address_blocked:
            return bc_error_address_blocked;
        case libbitcoin::error::channel_stopped:
            return bc_error_channel_stopped;
    }
}
libbitcoin::error::error_code_t bc_error_code_from_ctype(bc_error_t value)
{
    switch (value)
    {
        case bc_error_success:
            return libbitcoin::error::success;
        case bc_error_service_stopped:
            return libbitcoin::error::service_stopped;
        case bc_error_operation_failed:
            return libbitcoin::error::operation_failed;
        case bc_error_not_found:
            return libbitcoin::error::not_found;
        case bc_error_duplicate:
            return libbitcoin::error::duplicate;
        case bc_error_unspent_output:
            return libbitcoin::error::unspent_output;
        case bc_error_unsupported_script_pattern:
            return libbitcoin::error::unsupported_script_pattern;
        case bc_error_resolve_failed:
            return libbitcoin::error::resolve_failed;
        case bc_error_network_unreachable:
            return libbitcoin::error::network_unreachable;
        case bc_error_address_in_use:
            return libbitcoin::error::address_in_use;
        case bc_error_listen_failed:
            return libbitcoin::error::listen_failed;
        case bc_error_accept_failed:
            return libbitcoin::error::accept_failed;
        case bc_error_bad_stream:
            return libbitcoin::error::bad_stream;
        case bc_error_channel_timeout:
            return libbitcoin::error::channel_timeout;
        case bc_error_blockchain_reorganized:
            return libbitcoin::error::blockchain_reorganized;
        case bc_error_pool_filled:
            return libbitcoin::error::pool_filled;
        case bc_error_coinbase_transaction:
            return libbitcoin::error::coinbase_transaction;
        case bc_error_is_not_standard:
            return libbitcoin::error::is_not_standard;
        case bc_error_double_spend:
            return libbitcoin::error::double_spend;
        case bc_error_input_not_found:
            return libbitcoin::error::input_not_found;
        case bc_error_empty_transaction:
            return libbitcoin::error::empty_transaction;
        case bc_error_output_value_overflow:
            return libbitcoin::error::output_value_overflow;
        case bc_error_invalid_coinbase_script_size:
            return libbitcoin::error::invalid_coinbase_script_size;
        case bc_error_previous_output_null:
            return libbitcoin::error::previous_output_null;
        case bc_error_previous_block_invalid:
            return libbitcoin::error::previous_block_invalid;
        case bc_error_size_limits:
            return libbitcoin::error::size_limits;
        case bc_error_proof_of_work:
            return libbitcoin::error::proof_of_work;
        case bc_error_futuristic_timestamp:
            return libbitcoin::error::futuristic_timestamp;
        case bc_error_first_not_coinbase:
            return libbitcoin::error::first_not_coinbase;
        case bc_error_extra_coinbases:
            return libbitcoin::error::extra_coinbases;
        case bc_error_too_many_sigs:
            return libbitcoin::error::too_many_sigs;
        case bc_error_merkle_mismatch:
            return libbitcoin::error::merkle_mismatch;
        case bc_error_incorrect_proof_of_work:
            return libbitcoin::error::incorrect_proof_of_work;
        case bc_error_timestamp_too_early:
            return libbitcoin::error::timestamp_too_early;
        case bc_error_non_final_transaction:
            return libbitcoin::error::non_final_transaction;
        case bc_error_checkpoints_failed:
            return libbitcoin::error::checkpoints_failed;
        case bc_error_old_version_block:
            return libbitcoin::error::old_version_block;
        case bc_error_coinbase_height_mismatch:
            return libbitcoin::error::coinbase_height_mismatch;
        case bc_error_duplicate_or_spent:
            return libbitcoin::error::duplicate_or_spent;
        case bc_error_validate_inputs_failed:
            return libbitcoin::error::validate_inputs_failed;
        case bc_error_fees_out_of_range:
            return libbitcoin::error::fees_out_of_range;
        case bc_error_coinbase_too_large:
            return libbitcoin::error::coinbase_too_large;
        case bc_error_file_system:
            return libbitcoin::error::file_system;
        case bc_error_unknown:
            return libbitcoin::error::unknown;
        case bc_error_address_blocked:
            return libbitcoin::error::address_blocked;
        case bc_error_channel_stopped:
            return libbitcoin::error::channel_stopped;
    }
}

