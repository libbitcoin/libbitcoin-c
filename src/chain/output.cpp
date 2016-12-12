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
#include <bitcoin/bitcoin/c/chain/output.h>
#include <bitcoin/bitcoin/c/internal/chain/output.hpp>

#include <bitcoin/bitcoin/c/internal/chain/point.hpp>
#include <bitcoin/bitcoin/c/internal/chain/script.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>
#include <bitcoin/bitcoin/c/internal/utility/string.hpp>
#include <bitcoin/bitcoin/c/internal/utility/vector.hpp>

extern "C" {

BC_IMPLEMENT_VECTOR(output_list, bc_output_t,
    bc_destroy_output, libbitcoin::chain::output::list);

// Static values
uint64_t bc_output__not_found()
{
    return libbitcoin::chain::output::not_found;
}
// Constructor
bc_output_t* bc_create_output()
{
    return new bc_output_t{ new libbitcoin::chain::output, true };
}
bc_output_t* bc_create_output_copy(const bc_output_t* other)
{
    return new bc_output_t{ new libbitcoin::chain::output(*other->obj), true };
}
bc_output_t* bc_create_output_Value(uint64_t value, const bc_script_t* script)
{
    return new bc_output_t{ new libbitcoin::chain::output(
        value, *script->obj), true };
}
// Destructor
void bc_destroy_output(bc_output_t* self)
{
    if (self->delete_obj)
        delete self->obj;
    delete self;
}
// Member functions
bc_output_t* bc_output__factory_from_data(const bc_data_chunk_t* data)
{
    return new bc_output_t{ new libbitcoin::chain::output(
        libbitcoin::chain::output::factory_from_data(*data->obj)), true };
}
bc_output_t* bc_output__factory_from_data_nowire(const bc_data_chunk_t* data)
{
    return new bc_output_t{ new libbitcoin::chain::output(
        libbitcoin::chain::output::factory_from_data(
            *data->obj, false)), true };
}
bool bc_output__from_data(bc_output_t* self, const bc_data_chunk_t* data)
{
    return self->obj->from_data(*data->obj);
}
bool bc_output__from_data_nowire(
    bc_output_t* self, const bc_data_chunk_t* data)
{
    return self->obj->from_data(*data->obj, false);
}
bc_data_chunk_t* bc_output__to_data(const bc_output_t* self)
{
    return bc_create_data_chunk_Internal(self->obj->to_data());
}
bc_data_chunk_t* bc_output__to_data_nowire(const bc_output_t* self)
{
    return bc_create_data_chunk_Internal(self->obj->to_data(false));
}
bool bc_output__is_valid(const bc_output_t* self)
{
    return self->obj->is_valid();
}
uint64_t bc_output__serialized_size(const bc_output_t* self)
{
    return self->obj->serialized_size();
}
uint64_t bc_output__serialized_size_nowire(const bc_output_t* self)
{
    return self->obj->serialized_size(false);
}
// Member variables
uint64_t bc_output__value(const bc_output_t* self)
{
    return self->obj->value();
}
void bc_output__set_value(bc_output_t* self, uint64_t value)
{
    self->obj->set_value(value);
}
bc_script_t* bc_output__script(const bc_output_t* self)
{
    return new bc_script_t{ new libbitcoin::chain::script(
        self->obj->script()), false };
}
void bc_output__set_script(bc_output_t* self, const bc_script_t* script)
{
    self->obj->set_script(*script->obj);
}

size_t bc_output__signature_operations(const bc_output_t* self)
{
    return self->obj->signature_operations();
}

} // extern C

