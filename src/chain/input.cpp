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
#include <bitcoin/bitcoin/c/chain/input.h>
#include <bitcoin/bitcoin/c/internal/chain/input.hpp>

#include <bitcoin/bitcoin/c/internal/chain/output_point.hpp>
#include <bitcoin/bitcoin/c/internal/chain/point.hpp>
#include <bitcoin/bitcoin/c/internal/chain/script.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>
#include <bitcoin/bitcoin/c/internal/utility/vector.hpp>

extern "C" {

BC_IMPLEMENT_VECTOR(input_list, bc_input_t, bc_destroy_input,
    libbitcoin::chain::input::list);

// Constructor
bc_input_t* bc_create_input()
{
    return new bc_input_t{ new libbitcoin::chain::input, true };
}
bc_input_t* bc_create_input_copy(const bc_input_t* other)
{
    return new bc_input_t{ new libbitcoin::chain::input(*other->obj), true };
}
bc_input_t* bc_create_input_Values(
    const bc_output_point_t* previous_output, const bc_script_t* script,
    uint32_t sequence)
{
    return new bc_input_t{ new libbitcoin::chain::input(
        *previous_output->obj, *script->obj, sequence), true };
}
// Destructor
void bc_destroy_input(bc_input_t* self)
{
    if (self->delete_obj)
        delete self->obj;
    delete self;
}
// Operators
void bc_input__copy(bc_input_t* self, const bc_input_t* other)
{
    *self->obj = *other->obj;
}
bool bc_input__equals(bc_input_t* self, const bc_input_t* other)
{
    return *self->obj == *other->obj;
}
bool bc_input__not_equals(bc_input_t* self, const bc_input_t* other)
{
    return *self->obj != *other->obj;
}
// Member functions
bc_input_t* bc_input__factory_from_data(const bc_data_chunk_t* data)
{
    return new bc_input_t{ new libbitcoin::chain::input(
        libbitcoin::chain::input::factory_from_data(*data->obj)), true };
}
bc_input_t* bc_input__factory_from_data_nowire(const bc_data_chunk_t* data)
{
    return new bc_input_t{ new libbitcoin::chain::input(
        libbitcoin::chain::input::factory_from_data(
            *data->obj, false)), true };
}
bool bc_input__from_data(bc_input_t* self, const bc_data_chunk_t* data)
{
    return self->obj->from_data(*data->obj);
}
bool bc_input__from_data_nowire(bc_input_t* self, const bc_data_chunk_t* data)
{
    return self->obj->from_data(*data->obj, false);
}
bool bc_input__is_valid(const bc_input_t* self)
{
    return self->obj->is_valid();
}
bc_data_chunk_t* bc_input__to_data(const bc_input_t* self)
{
    return bc_create_data_chunk_Internal(self->obj->to_data());
}
bc_data_chunk_t* bc_input__to_data_nowire(const bc_input_t* self)
{
    return bc_create_data_chunk_Internal(self->obj->to_data(false));
}
uint64_t bc_input__serialized_size(const bc_input_t* self)
{
    return self->obj->serialized_size();
}
uint64_t bc_input__serialized_size_nowire(const bc_input_t* self)
{
    return self->obj->serialized_size(false);
}
bc_output_point_t* bc_input__previous_output(const bc_input_t* self)
{
    return new bc_output_point_t{ new libbitcoin::chain::output_point(
        self->obj->previous_output()), false };
}
void bc_input__set_previous_output(bc_input_t* self,
    bc_output_point_t* previous_output)
{
    self->obj->set_previous_output(*previous_output->obj);
}
bc_script_t* bc_input__script(const bc_input_t* self)
{
    return new bc_script_t{ new libbitcoin::chain::script(
        self->obj->script()), false };
}
void bc_input__set_script(bc_input_t* self, const bc_script_t* script)
{
    self->obj->set_script(*script->obj);
}
uint32_t bc_input__sequence(const bc_input_t* self)
{
    return self->obj->sequence();
}
void bc_input__set_sequence(bc_input_t* self, uint32_t sequence)
{
    self->obj->set_sequence(sequence);
}

bool bc_input__is_final(const bc_input_t* self)
{
    return self->obj->is_final();
}
size_t bc_input__signature_operations(
    const bc_input_t* self, bool bip16_active)
{
    return self->obj->signature_operations(bip16_active);
}

} // extern C

