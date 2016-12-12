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
#include <bitcoin/bitcoin/c/utility/color.h>
#include <bitcoin/bitcoin/c/internal/utility/color.hpp>

extern "C" {

bc_color_t* bc_create_color()
{
    return new bc_color_t{ new libbitcoin::color };
}
void bc_destroy_color(bc_color_t* self)
{
    delete self->obj;
    delete self;
}

uint8_t bc_color__red(const bc_color_t* self)
{
    return self->obj->red;
}
void bc_color__set_red(bc_color_t* self, uint8_t red)
{
    self->obj->red = red;
}

uint8_t bc_color__green(const bc_color_t* self)
{
    return self->obj->green;
}
void bc_color__set_green(bc_color_t* self, uint8_t green)
{
    self->obj->green = green;
}

uint8_t bc_color__blue(const bc_color_t* self)
{
    return self->obj->blue;
}
void bc_color__set_blue(bc_color_t* self, uint8_t blue)
{
    self->obj->blue = blue;
}

uint8_t bc_color__alpha(const bc_color_t* self)
{
    return self->obj->alpha;
}
void bc_color__set_alpha(bc_color_t* self, uint8_t alpha)
{
    self->obj->alpha = alpha;
}

}

