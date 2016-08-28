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
#include <bitcoin/bitcoin/c/chain/script/script.h>
#include <bitcoin/bitcoin/c/internal/chain/script/script.hpp>

#include <bitcoin/bitcoin/c/internal/chain/script/opcode.hpp>
#include <bitcoin/bitcoin/c/internal/chain/script/operation.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>

extern "C" {

// Static functions
bc_script_t* bc_script_factory_from_data(const bc_data_chunk_t* data,
    bool prefix, bc_script_parse_mode_t mode)
{
    const auto script = libbitcoin::chain::script::factory_from_data(
        *data->obj, prefix, bc_script_parse_mode_from_ctype(mode));
    return new bc_script_t{ new libbitcoin::chain::script(script) };
}
bool bc_script_is_active(uint32_t flags, bc_script_context_t flag)
{
    return libbitcoin::chain::script::is_active(
        flags, bc_script_context_from_ctype(flag));
}
// Constructor
bc_script_t* bc_create_script()
{
    return new bc_script_t{ new libbitcoin::chain::script };
}
// Destructor
void bc_destroy_script(bc_script_t* self)
{
    delete self->obj;
    delete self;
}
// Member functions
bc_script_pattern_t bc_script_pattern(const bc_script_t* self)
{
    return bc_script_pattern_to_ctype(self->obj->pattern());
}
bool bc_script_is_raw_data(const bc_script_t* self)
{
    return self->obj->is_raw_data();
}
bool bc_script_from_data(bc_script_t* self, const bc_data_chunk_t* data,
    bool prefix, bc_script_parse_mode_t mode)
{
    return self->obj->from_data(*data->obj, prefix,
        bc_script_parse_mode_from_ctype(mode));
}
bc_data_chunk_t* bc_script_to_data(const bc_script_t* self, bool prefix)
{
    return bc_create_data_chunk_Internal(self->obj->to_data(prefix));
}
bool bc_script_from_string(bc_script_t* self, const char* human_readable)
{
    return self->obj->from_string(human_readable);
}
bc_string_t* bc_script_to_string(const bc_script_t* self, uint32_t flags)
{
    return bc_create_string_StdString(self->obj->to_string(flags));
}
bool bc_script_is_valid(const bc_script_t* self)
{
    return self->obj->is_valid();
}
void bc_script_reset(bc_script_t* self)
{
    self->obj->reset();
}
uint64_t bc_script_satoshi_content_size(const bc_script_t* self)
{
    return self->obj->satoshi_content_size();
}
uint64_t bc_script_serialized_size(const bc_script_t* self, bool prefix)
{
    return self->obj->serialized_size(prefix);
}
// Member variables
bc_operation_stack_t* bc_script_operations(const bc_script_t* self)
{
    return bc_operation_stack_to_ctype(self->obj->operations);
}
void bc_script_set_operations(const bc_script_t* self,
    const bc_operation_stack_t* operations)
{
    self->obj->operations = bc_operation_stack_from_ctype(operations);
}

} // extern C

bc_signature_hash_algorithm_t bc_signature_hash_algorithm_to_ctype(
    libbitcoin::chain::signature_hash_algorithm alg)
{
    return static_cast<bc_signature_hash_algorithm_t>(alg);
}

libbitcoin::chain::signature_hash_algorithm
    bc_signature_hash_algorithm_from_ctype(bc_signature_hash_algorithm_t alg)
{
    return static_cast<libbitcoin::chain::signature_hash_algorithm>(alg);
}

bc_script_parse_mode_t bc_script_parse_mode_to_ctype(
    libbitcoin::chain::script::parse_mode mode)
{
    switch (mode)
    {
        case libbitcoin::chain::script::parse_mode::strict:
            return bc_script_parse_mode_strict;

        case libbitcoin::chain::script::parse_mode::raw_data:
            return bc_script_parse_mode_raw_data;

        case libbitcoin::chain::script::parse_mode::raw_data_fallback:
            return bc_script_parse_mode_raw_data_fallback;
    }
}

libbitcoin::chain::script::parse_mode bc_script_parse_mode_from_ctype(
    bc_script_parse_mode_t mode)
{
    switch (mode)
    {
        case bc_script_parse_mode_strict:
            return libbitcoin::chain::script::parse_mode::strict;

        case bc_script_parse_mode_raw_data:
            return libbitcoin::chain::script::parse_mode::raw_data;

        case bc_script_parse_mode_raw_data_fallback:
            return libbitcoin::chain::script::parse_mode::raw_data_fallback;
    }
}

