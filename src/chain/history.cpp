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
#include <bitcoin/bitcoin/c/chain/history.h>
#include <bitcoin/bitcoin/c/internal/chain/history.hpp>

#include <bitcoin/bitcoin/c/internal/chain/output_point.hpp>
#include <bitcoin/bitcoin/c/internal/chain/point.hpp>

extern "C" {

BC_IMPLEMENT_VECTOR(history_compact_list, bc_history_compact_t,
    bc_destroy_history_compact, libbitcoin::chain::history_compact::list);

BC_IMPLEMENT_VECTOR(history_list, bc_history_t,
    bc_destroy_history, libbitcoin::chain::history::list);

// Constructor
bc_history_compact_t* bc_create_history_compact()
{
    return new bc_history_compact_t{
        new libbitcoin::chain::history_compact, true };
}
// Destructor
void bc_destroy_history_compact(bc_history_compact_t* self)
{
    if (self->delete_obj)
        delete self->obj;
    delete self;
}
// Member variables
// The type of point (output or spend).
bc_point_kind_t bc_history_compact__kind(const bc_history_compact_t* self)
{
    return static_cast<bc_point_kind_t>(self->obj->kind);
}
void bc_history_compact__set_kind(bc_history_compact_t* self,
    bc_point_kind_t kind)
{
    self->obj->kind = static_cast<libbitcoin::chain::point_kind>(kind);
}
/// The point that identifies the record.
bc_point_t* bc_history_compact__point(const bc_history_compact_t* self)
{
    return new bc_point_t{ &self->obj->point, false };
}
void bc_history_compact__set_point(bc_history_compact_t* self,
    const bc_point_t* point)
{
    self->obj->point = *point->obj;
}
/// The height of the point.
uint64_t bc_history_compact__height(const bc_history_compact_t* self)
{
    return self->obj->height;
}
void bc_history_compact__set_height(bc_history_compact_t* self,
    uint64_t height)
{
    self->obj->height = height;
}
/// If output, then satoshi value of output.
uint64_t bc_history_compact__value(const bc_history_compact_t* self)
{
    return self->obj->value;
}
void bc_history_compact__set_value(bc_history_compact_t* self,
    uint64_t value)
{
    self->obj->value = value;
}
/// If spend, then checksum hash of previous output point
/// To match up this row with the output, recompute the
/// checksum from the output row with spend_checksum(row.point)
uint64_t bc_history_compact__previous_checksum(
    const bc_history_compact_t* self)
{
    return self->obj->previous_checksum;
}
void bc_history_compact__set_previous_checksum(bc_history_compact_t* self,
    uint64_t previous_checksum)
{
    self->obj->previous_checksum = previous_checksum;
}

// Constructor
bc_history_t* bc_create_history()
{
    return new bc_history_t{ new libbitcoin::chain::history, true };
}
// Destructor
void bc_destroy_history(bc_history_t* self)
{
    if (self->delete_obj)
        delete self->obj;
    delete self;
}
// Member variables
/// If there is no output this is null_hash:max.
bc_output_point_t* bc_history__output(const bc_history_t* self)
{
    return new bc_output_point_t{ &self->obj->output, false };
}
void bc_history__set_output(bc_history_t* self,
    const bc_output_point_t* output)
{
    self->obj->output = *output->obj;
}
uint64_t bc_history__output_height(const bc_history_t* self)
{
    return self->obj->output_height;
}
void bc_history__set_output_height(bc_history_t* self, uint64_t output_height)
{
    self->obj->output_height = output_height;
}
/// The satoshi value of the output.
uint64_t bc_history__value(const bc_history_t* self)
{
    return self->obj->value;
}
void bc_history__set_value(bc_history_t* self, uint64_t value)
{
    self->obj->value = value;
}
/// If there is no spend this is null_hash:max.
bc_input_point_t* bc_history__spend(const bc_history_t* self)
{
    return new bc_input_point_t{ &self->obj->spend, false };
}
void bc_history__set_spend(bc_history_t* self, const bc_input_point_t* spend)
{
    self->obj->spend = *spend->obj;
}
/// The height of the spend or max if no spend.
uint64_t bc_history__spend_height(const bc_history_t* self)
{
    return self->obj->spend_height;
}
void bc_history__set_spend_height(bc_history_t* self, uint64_t spend_height)
{
    self->obj->spend_height = spend_height;
}
/// During expansion this value temporarily doubles as a checksum.
uint64_t bc_history__temporary_checksum(const bc_history_t* self)
{
    return self->obj->temporary_checksum;
}
void bc_history__set_temporary_checksum(bc_history_t* self,
    uint64_t temporary_checksum)
{
    self->obj->temporary_checksum = temporary_checksum;
}

} // extern C

