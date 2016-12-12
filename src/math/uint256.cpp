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
#include <bitcoin/bitcoin/c/math/uint256.h>
#include <bitcoin/bitcoin/c/internal/math/uint256.hpp>

#include <bitcoin/bitcoin/math/uint256.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>

extern "C" {

// Constructors
bc_uint256_t* bc_create_uint256()
{
    return new bc_uint256_t{ new libbitcoin::uint256_t };
}
/*bc_uint256_t* bc_create_uint256_copy(const bc_uint256_t* other)
{
    return new bc_uint256_t{ new libbitcoin::uint256_t(*other->obj) };
}
bc_uint256_t* bc_create_uint256_Uint64(uint64_t b)
{
    return new bc_uint256_t{ new libbitcoin::uint256_t(b) };
}
bc_uint256_t* bc_create_uint256_Data(const bc_data_chunk_t* data)
{
    return new bc_uint256_t{ new libbitcoin::uint256_t(*data->obj) };
}*/
// Destructor
void bc_destroy_uint256(bc_uint256_t* self)
{
    delete self->obj;
    delete self;
}
#if 0

// Operators
void bc_uint256_copy(bc_uint256_t* self, const bc_uint256_t* other)
{
    *self->obj = *other->obj;
}
bool bc_uint256_not(const bc_uint256_t* self)
{
    return !(*self->obj);
}
bc_uint256_t* bc_uint256_negate(const bc_uint256_t* self)
{
    return new bc_uint256_t{ new libbitcoin::uint256_t(
        ~(*self->obj)) };
}
bc_uint256_t* bc_uint256_negative(const bc_uint256_t* self)
{
    return new bc_uint256_t{ new libbitcoin::uint256_t(
        -(*self->obj)) };
}
void bc_uint256_copy_Uint64(bc_uint256_t* self, uint64_t b)
{
    *self->obj = b;
}
void bc_uint256_xor(bc_uint256_t* self, const bc_uint256_t* other)
{
    *self->obj ^= *other->obj;
}
void bc_uint256_and(bc_uint256_t* self, const bc_uint256_t* other)
{
    *self->obj &= *other->obj;
}
void bc_uint256_or(bc_uint256_t* self, const bc_uint256_t* other)
{
    *self->obj |= *other->obj;
}
void bc_uint256_xor_Uint64(bc_uint256_t* self, uint64_t b)
{
    *self->obj ^= b;
}
void bc_uint256_or_Uint64(bc_uint256_t* self, uint64_t b)
{
    *self->obj |= b;
}
void bc_uint256_shift_left(bc_uint256_t* self, unsigned int shift)
{
    *self->obj <<= shift;
}
void bc_uint256_shift_right(bc_uint256_t* self, unsigned int shift)
{
    *self->obj >>= shift;
}
void bc_uint256_add(bc_uint256_t* self, const bc_uint256_t* other)
{
    *self->obj += *other->obj;
}
void bc_uint256_subtract(bc_uint256_t* self, const bc_uint256_t* other)
{
    *self->obj -= *other->obj;
}
void bc_uint256_add_Uint64(bc_uint256_t* self, uint64_t b64)
{
    *self->obj += b64;
}
void bc_uint256_subtract_Uint64(bc_uint256_t* self, uint64_t b64)
{
    *self->obj -= b64;
}
void bc_uint256_multiply_Uint32(bc_uint256_t* self, uint32_t b32)
{
    *self->obj *= b32;
}
void bc_uint256_multiply(bc_uint256_t* self, const bc_uint256_t* other)
{
    *self->obj *= *other->obj;
}
void bc_uint256_divide(bc_uint256_t* self, const bc_uint256_t* other)
{
    *self->obj /= *other->obj;
}
void bc_uint256_increment(bc_uint256_t* self)
{
    ++(*self->obj);
}
void bc_uint256_decrement(bc_uint256_t* self)
{
    --(*self->obj);
}

// Methods
int bc_uint256_compare_to(bc_uint256_t* self, const bc_uint256_t* other)
{
    return self->obj->CompareTo(*other->obj);
}
bool bc_uint256_equal_to(bc_uint256_t* self, uint64_t b)
{
    return self->obj->EqualTo(b);
}

bool bc_uint256_equals(const bc_uint256_t* self, const bc_uint256_t* other)
{
    return *self->obj == *other->obj;
}
bool bc_uint256_not_equals(const bc_uint256_t* self,
    const bc_uint256_t* other)
{
    return *self->obj != *other->obj;
}
bool bc_uint256_greater_than(const bc_uint256_t* self,
    const bc_uint256_t* other)
{
    return *self->obj > *other->obj;
}
bool bc_uint256_less_than(const bc_uint256_t* self,
    const bc_uint256_t* other)
{
    return *self->obj < *other->obj;
}
bool bc_uint256_greater_than_or_equals(const bc_uint256_t* self,
    const bc_uint256_t* other)
{
    return *self->obj >= *other->obj;
}
bool bc_uint256_less_than_or_equals(const bc_uint256_t* self,
    const bc_uint256_t* other)
{
    return *self->obj <= *other->obj;
}
bool bc_uint256_equals_Uint64(const bc_uint256_t* self, uint64_t b)
{
    return *self->obj == b;
}
bool bc_uint256_not_equals_Uint64(const bc_uint256_t* self, uint64_t b)
{
    return *self->obj != b;
}

unsigned char* bc_uint256_begin(bc_uint256_t* self)
{
    return self->obj->begin();
}
unsigned char* bc_uint256_end(bc_uint256_t* self)
{
    return self->obj->end();
}
const unsigned char* bc_uint256_cbegin(const bc_uint256_t* self)
{
    return self->obj->begin();
}
const unsigned char* bc_uint256_cend(const bc_uint256_t* self)
{
    return self->obj->end();
}
unsigned int bc_uint256_size(const bc_uint256_t* self)
{
    return self->obj->size();
}
/**
 * Returns the position of the highest bit set plus one, or zero if the
 * value is zero.
 */
unsigned int bc_uint256_bits(const bc_uint256_t* self)
{
    return self->obj->bits();
}
uint64_t bc_uint256_get_low_64(const bc_uint256_t* self)
{
    return self->obj->GetLow64();
}

/**
 * The "compact" format is a representation of a whole
 * number N using an unsigned 32bit number similar to a
 * floating point format.
 * The most significant 8 bits are the unsigned exponent of base 256.
 * This exponent can be thought of as "number of bytes of N".
 * The lower 23 bits are the mantissa.
 * Bit number 24 (0x800000) represents the sign of N.
 * N = (-1^sign) * mantissa * 256^(exponent-3)
 *
 * Satoshi's original implementation used BN_bn2mpi() and BN_mpi2bn().
 * MPI uses the most significant bit of the first byte as sign.
 * Thus 0x1234560000 is compact (0x05123456)
 * and  0xc0de000000 is compact (0x0600c0de)
 *
 * Bitcoin only uses this "compact" format for encoding difficulty
 * targets, which are unsigned 256bit quantities.  Thus, all the
 * complexities of the sign bit and using base 256 are probably an
 * implementation accident.
 */
uint32_t bc_uint256_get_compact(const bc_uint256_t* self)
{
    return self->obj->GetCompact();
}
uint32_t bc_uint256_get_compact_fNegative(const bc_uint256_t* self)
{
    return self->obj->GetCompact(true);
}
void bc_uint256_set_compact(bc_uint256_t* self,
    uint32_t ncompact, bool* negative, bool* overflow)
{
    self->obj->SetCompact(ncompact, negative, overflow);
}
#endif

} // extern C

