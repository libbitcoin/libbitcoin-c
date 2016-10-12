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
#include <bitcoin/bitcoin/c/chain/script/operation.h>
#include <bitcoin/bitcoin/c/internal/chain/script/operation.hpp>

#include <bitcoin/bitcoin/c/internal/chain/script/opcode.hpp>
#include <bitcoin/bitcoin/c/internal/math/elliptic_curve.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>
#include <bitcoin/bitcoin/c/internal/utility/vector.hpp>

BC_IMPLEMENT_VECTOR(operation_stack, bc_operation_t, bc_destroy_operation,
    libbitcoin::chain::operation::stack);

extern "C" {

size_t bc_operation__max_null_data_size()
{
    return libbitcoin::chain::operation::max_null_data_size;
}
bc_operation_t* bc_operation__factory_from_data(const bc_data_chunk_t* data)
{
    return new bc_operation_t{ new libbitcoin::chain::operation(
        libbitcoin::chain::operation::factory_from_data(*data->obj)), true };
}
bool bc_operation__is_push_only(const bc_operation_stack_t* operations)
{
    return libbitcoin::chain::operation::is_push_only(*operations->obj);
}
/// unspendable pattern (standard)
bool bc_operation__is_null_data_pattern(const bc_operation_stack_t* ops)
{
    return libbitcoin::chain::operation::is_null_data_pattern(*ops->obj);
}
/// payment script patterns (standard)
bool bc_operation__is_pay_multisig_pattern(const bc_operation_stack_t* ops)
{
    return libbitcoin::chain::operation::is_pay_multisig_pattern(*ops->obj);
}
bool bc_operation__is_pay_public_key_pattern(const bc_operation_stack_t* ops)
{
    return libbitcoin::chain::operation::is_pay_public_key_pattern(*ops->obj);
}
bool bc_operation__is_pay_key_hash_pattern(const bc_operation_stack_t* ops)
{
    return libbitcoin::chain::operation::is_pay_key_hash_pattern(*ops->obj);
}
bool bc_operation__is_pay_script_hash_pattern(const bc_operation_stack_t* ops)
{
    return libbitcoin::chain::operation::is_pay_script_hash_pattern(*ops->obj);
}
/// signature script patterns (standard)
bool bc_operation__is_sign_multisig_pattern(const bc_operation_stack_t* ops)
{
    return libbitcoin::chain::operation::is_sign_multisig_pattern(*ops->obj);
}
bool bc_operation__is_sign_public_key_pattern(const bc_operation_stack_t* ops)
{
    return libbitcoin::chain::operation::is_sign_public_key_pattern(*ops->obj);
}
bool bc_operation__is_sign_key_hash_pattern(const bc_operation_stack_t* ops)
{
    return libbitcoin::chain::operation::is_sign_key_hash_pattern(*ops->obj);
}
bool bc_operation__is_sign_script_hash_pattern(const bc_operation_stack_t* ops)
{
    return libbitcoin::chain::operation::is_sign_script_hash_pattern(
        *ops->obj);
}
/// stack factories
bc_operation_stack_t* bc_operation__to_null_data_pattern(
    const bc_data_chunk_t* data)
{
    return bc_create_operation_stack_Internal(
        libbitcoin::chain::operation::to_null_data_pattern(*data->obj));
}
bc_operation_stack_t* bc_operation__to_pay_multisig_pattern_PointList(
    uint8_t signatures,
    const bc_point_list_t* points)
{
    const auto result = libbitcoin::chain::operation::to_pay_multisig_pattern(
        signatures, *points->obj);
    return bc_create_operation_stack_Internal(result);
}
bc_operation_stack_t* bc_operation__to_pay_multisig_pattern(
    uint8_t signatures,
    const bc_data_stack_t* points)
{
    const auto result = libbitcoin::chain::operation::to_pay_multisig_pattern(
        signatures, *points->obj);
    return bc_create_operation_stack_Internal(result);
}
bc_operation_stack_t* bc_operation__to_pay_public_key_pattern(
    const bc_data_chunk_t* point)
{
    return bc_create_operation_stack_Internal(
        libbitcoin::chain::operation::to_pay_public_key_pattern(*point->obj));
}
bc_operation_stack_t* bc_operation__to_pay_key_hash_pattern(
    const bc_short_hash_t* hash)
{
    return bc_create_operation_stack_Internal(
        libbitcoin::chain::operation::to_pay_key_hash_pattern(*hash->obj));
}
bc_operation_stack_t* bc_operation__to_pay_script_hash_pattern(
    const bc_short_hash_t* hash)
{
    return bc_create_operation_stack_Internal(
        libbitcoin::chain::operation::to_pay_script_hash_pattern(*hash->obj));
}

bc_operation_t* bc_create_operation()
{
    return new bc_operation_t{ new libbitcoin::chain::operation, true };
}
void bc_destroy_operation(bc_operation_t* self)
{
    if (self->delete_obj)
        delete self->obj;
    delete self;
}

// Class members
bool bc_operation__from_data(bc_operation_t* self, const bc_data_chunk_t* data)
{
    return self->obj->from_data(*data->obj);
}
bc_data_chunk_t* bc_operation__to_data(const bc_operation_t* self)
{
    return bc_create_data_chunk_Internal(self->obj->to_data());
}
bc_string_t* bc_operation__to_string(
    const bc_operation_t* self, uint32_t flags)
{
    return bc_create_string_StdString(self->obj->to_string(flags));
}
bool bc_operation__is_valid(const bc_operation_t* self)
{
    return self->obj->is_valid();
}
void bc_operation__reset(bc_operation_t* self)
{
    self->obj->reset();
}
uint64_t bc_operation__serialized_size(const bc_operation_t* self)
{
    return self->obj->serialized_size();
}

bc_opcode_t bc_operation__code(const bc_operation_t* self)
{
    return bc_opcode_to_ctype(self->obj->code);
}
void bc_operation__set_code(bc_operation_t* self, bc_opcode_t code)
{
    self->obj->code = bc_opcode_from_ctype(code);
}
bc_data_chunk_t* bc_operation__data(const bc_operation_t* self)
{
    return bc_create_data_chunk_Internal(self->obj->data);
}
void bc_operation__set_data(bc_operation_t* self, bc_data_chunk_t* data)
{
    self->obj->data = *data->obj;
}

} // extern C

bc_script_pattern_t bc_script_pattern_to_ctype(
    libbitcoin::chain::script_pattern value)
{
    switch (value)
    {
        case libbitcoin::chain::script_pattern::null_data:
            return bc_script_pattern__null_data;

        case libbitcoin::chain::script_pattern::pay_multisig:
            return bc_script_pattern__pay_multisig;

        case libbitcoin::chain::script_pattern::pay_public_key:
            return bc_script_pattern__pay_public_key;

        case libbitcoin::chain::script_pattern::pay_key_hash:
            return bc_script_pattern__pay_key_hash;

        case libbitcoin::chain::script_pattern::pay_script_hash:
            return bc_script_pattern__pay_script_hash;

        case libbitcoin::chain::script_pattern::sign_multisig:
            return bc_script_pattern__sign_multisig;

        case libbitcoin::chain::script_pattern::sign_public_key:
            return bc_script_pattern__sign_public_key;

        case libbitcoin::chain::script_pattern::sign_key_hash:
            return bc_script_pattern__sign_key_hash;

        case libbitcoin::chain::script_pattern::sign_script_hash:
            return bc_script_pattern__sign_script_hash;

        case libbitcoin::chain::script_pattern::non_standard:
            return bc_script_pattern__non_standard;
    }
}

libbitcoin::chain::script_pattern bc_script_pattern_from_ctype(
    bc_script_pattern_t value)
{
    switch (value)
    {
        case bc_script_pattern__null_data:
            return libbitcoin::chain::script_pattern::null_data;

        case bc_script_pattern__pay_multisig:
            return libbitcoin::chain::script_pattern::pay_multisig;

        case bc_script_pattern__pay_public_key:
            return libbitcoin::chain::script_pattern::pay_public_key;

        case bc_script_pattern__pay_key_hash:
            return libbitcoin::chain::script_pattern::pay_key_hash;

        case bc_script_pattern__pay_script_hash:
            return libbitcoin::chain::script_pattern::pay_script_hash;

        case bc_script_pattern__sign_multisig:
            return libbitcoin::chain::script_pattern::sign_multisig;

        case bc_script_pattern__sign_public_key:
            return libbitcoin::chain::script_pattern::sign_public_key;

        case bc_script_pattern__sign_key_hash:
            return libbitcoin::chain::script_pattern::sign_key_hash;

        case bc_script_pattern__sign_script_hash:
            return libbitcoin::chain::script_pattern::sign_script_hash;

        case bc_script_pattern__non_standard:
            return libbitcoin::chain::script_pattern::non_standard;
    }
}

