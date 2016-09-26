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
bc_string_t* bc_error_code__message(const bc_error_code_t* self)
{
    return bc_create_string_StdString(self->obj->message());
}
bool bc_error_code__is_valid(const bc_error_code_t* self)
{
    return static_cast<bool>(*self->obj);
}
bool bc_error_code__equals(const bc_error_code_t* self, bc_error_t ec)
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
            return bc_error__success;
        case libbitcoin::error::service_stopped:
            return bc_error__service_stopped;
        case libbitcoin::error::operation_failed:
            return bc_error__operation_failed;
        case libbitcoin::error::not_found:
            return bc_error__not_found;
        case libbitcoin::error::duplicate:
            return bc_error__duplicate;
        case libbitcoin::error::orphan:
            return bc_error__orphan;
        case libbitcoin::error::unsupported_script_pattern:
            return bc_error__unsupported_script_pattern;
        case libbitcoin::error::resolve_failed:
            return bc_error__resolve_failed;
        case libbitcoin::error::network_unreachable:
            return bc_error__network_unreachable;
        case libbitcoin::error::address_in_use:
            return bc_error__address_in_use;
        case libbitcoin::error::listen_failed:
            return bc_error__listen_failed;
        case libbitcoin::error::accept_failed:
            return bc_error__accept_failed;
        case libbitcoin::error::bad_stream:
            return bc_error__bad_stream;
        case libbitcoin::error::channel_timeout:
            return bc_error__channel_timeout;
        case libbitcoin::error::blockchain_reorganized:
            return bc_error__blockchain_reorganized;
        case libbitcoin::error::pool_filled:
            return bc_error__pool_filled;
        case libbitcoin::error::coinbase_transaction:
            return bc_error__coinbase_transaction;
        case libbitcoin::error::is_not_standard:
            return bc_error__is_not_standard;
        case libbitcoin::error::double_spend:
            return bc_error__double_spend;
        case libbitcoin::error::input_not_found:
            return bc_error__input_not_found;
        case libbitcoin::error::empty_transaction:
            return bc_error__empty_transaction;
        case libbitcoin::error::spend_overflow:
            return bc_error__spend_overflow;
        case libbitcoin::error::invalid_coinbase_script_size:
            return bc_error__invalid_coinbase_script_size;
        case libbitcoin::error::previous_output_null:
            return bc_error__previous_output_null;
        case libbitcoin::error::previous_block_invalid:
            return bc_error__previous_block_invalid;
        case libbitcoin::error::size_limits:
            return bc_error__size_limits;
        case libbitcoin::error::invalid_proof_of_work:
            return bc_error__invalid_proof_of_work;
        case libbitcoin::error::futuristic_timestamp:
            return bc_error__futuristic_timestamp;
        case libbitcoin::error::first_not_coinbase:
            return bc_error__first_not_coinbase;
        case libbitcoin::error::extra_coinbases:
            return bc_error__extra_coinbases;
        case libbitcoin::error::too_many_sigs:
            return bc_error__too_many_sigs;
        case libbitcoin::error::merkle_mismatch:
            return bc_error__merkle_mismatch;
        case libbitcoin::error::incorrect_proof_of_work:
            return bc_error__incorrect_proof_of_work;
        case libbitcoin::error::timestamp_too_early:
            return bc_error__timestamp_too_early;
        case libbitcoin::error::non_final_transaction:
            return bc_error__non_final_transaction;
        case libbitcoin::error::checkpoints_failed:
            return bc_error__checkpoints_failed;
        case libbitcoin::error::old_version_block:
            return bc_error__old_version_block;
        case libbitcoin::error::coinbase_height_mismatch:
            return bc_error__coinbase_height_mismatch;
        case libbitcoin::error::unspent_duplicate:
            return bc_error__unspent_duplicate;
        case libbitcoin::error::validate_inputs_failed:
            return bc_error__validate_inputs_failed;
        case libbitcoin::error::spend_exceeds_value:
            return bc_error__spend_exceeds_value;
        case libbitcoin::error::coinbase_too_large:
            return bc_error__coinbase_too_large;
        case libbitcoin::error::file_system:
            return bc_error__file_system;
        case libbitcoin::error::unknown:
            return bc_error__unknown;
        case libbitcoin::error::address_blocked:
            return bc_error__address_blocked;
        case libbitcoin::error::channel_stopped:
            return bc_error__channel_stopped;
        case libbitcoin::error::coinbase_maturity:
            return bc_error__coinbase_maturity;
        case libbitcoin::error::empty_block:
            return bc_error__empty_block;
        case libbitcoin::error::insufficient_work:
            return bc_error__insufficient_work;
    }
}
libbitcoin::error::error_code_t bc_error_code_from_ctype(bc_error_t value)
{
    switch (value)
    {
        case bc_error__success:
            return libbitcoin::error::success;
        case bc_error__service_stopped:
            return libbitcoin::error::service_stopped;
        case bc_error__operation_failed:
            return libbitcoin::error::operation_failed;
        case bc_error__not_found:
            return libbitcoin::error::not_found;
        case bc_error__duplicate:
            return libbitcoin::error::duplicate;
        case bc_error__orphan:
            return libbitcoin::error::orphan;
        case bc_error__unsupported_script_pattern:
            return libbitcoin::error::unsupported_script_pattern;
        case bc_error__resolve_failed:
            return libbitcoin::error::resolve_failed;
        case bc_error__network_unreachable:
            return libbitcoin::error::network_unreachable;
        case bc_error__address_in_use:
            return libbitcoin::error::address_in_use;
        case bc_error__listen_failed:
            return libbitcoin::error::listen_failed;
        case bc_error__accept_failed:
            return libbitcoin::error::accept_failed;
        case bc_error__bad_stream:
            return libbitcoin::error::bad_stream;
        case bc_error__channel_timeout:
            return libbitcoin::error::channel_timeout;
        case bc_error__blockchain_reorganized:
            return libbitcoin::error::blockchain_reorganized;
        case bc_error__pool_filled:
            return libbitcoin::error::pool_filled;
        case bc_error__coinbase_transaction:
            return libbitcoin::error::coinbase_transaction;
        case bc_error__is_not_standard:
            return libbitcoin::error::is_not_standard;
        case bc_error__double_spend:
            return libbitcoin::error::double_spend;
        case bc_error__input_not_found:
            return libbitcoin::error::input_not_found;
        case bc_error__empty_transaction:
            return libbitcoin::error::empty_transaction;
        case bc_error__spend_overflow:
            return libbitcoin::error::spend_overflow;
        case bc_error__invalid_coinbase_script_size:
            return libbitcoin::error::invalid_coinbase_script_size;
        case bc_error__previous_output_null:
            return libbitcoin::error::previous_output_null;
        case bc_error__previous_block_invalid:
            return libbitcoin::error::previous_block_invalid;
        case bc_error__size_limits:
            return libbitcoin::error::size_limits;
        case bc_error__invalid_proof_of_work:
            return libbitcoin::error::invalid_proof_of_work;
        case bc_error__futuristic_timestamp:
            return libbitcoin::error::futuristic_timestamp;
        case bc_error__first_not_coinbase:
            return libbitcoin::error::first_not_coinbase;
        case bc_error__extra_coinbases:
            return libbitcoin::error::extra_coinbases;
        case bc_error__too_many_sigs:
            return libbitcoin::error::too_many_sigs;
        case bc_error__merkle_mismatch:
            return libbitcoin::error::merkle_mismatch;
        case bc_error__incorrect_proof_of_work:
            return libbitcoin::error::incorrect_proof_of_work;
        case bc_error__timestamp_too_early:
            return libbitcoin::error::timestamp_too_early;
        case bc_error__non_final_transaction:
            return libbitcoin::error::non_final_transaction;
        case bc_error__checkpoints_failed:
            return libbitcoin::error::checkpoints_failed;
        case bc_error__old_version_block:
            return libbitcoin::error::old_version_block;
        case bc_error__coinbase_height_mismatch:
            return libbitcoin::error::coinbase_height_mismatch;
        case bc_error__unspent_duplicate:
            return libbitcoin::error::unspent_duplicate;
        case bc_error__validate_inputs_failed:
            return libbitcoin::error::validate_inputs_failed;
        case bc_error__spend_exceeds_value:
            return libbitcoin::error::spend_exceeds_value;
        case bc_error__coinbase_too_large:
            return libbitcoin::error::coinbase_too_large;
        case bc_error__file_system:
            return libbitcoin::error::file_system;
        case bc_error__unknown:
            return libbitcoin::error::unknown;
        case bc_error__address_blocked:
            return libbitcoin::error::address_blocked;
        case bc_error__channel_stopped:
            return libbitcoin::error::channel_stopped;
        case bc_error__coinbase_maturity:
            return libbitcoin::error::coinbase_maturity;
        case bc_error__empty_block:
            return libbitcoin::error::empty_block;
        case bc_error__insufficient_work:
            return libbitcoin::error::insufficient_work;
    }
}

