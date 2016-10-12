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
#include <bitcoin/bitcoin/c/math/elliptic_curve.h>

#include <bitcoin/bitcoin/c/internal/math/elliptic_curve.hpp>
#include <bitcoin/bitcoin/c/internal/math/hash.hpp>
#include <bitcoin/bitcoin/c/internal/utility/data.hpp>

extern "C" {

BC_IMPLEMENT_VECTOR(point_list, bc_ec_compressed_t, bc_destroy_ec_compressed,
    libbitcoin::point_list);

BC_IMPLEMENT_BYTE_ARRAY(ec_secret);

BC_IMPLEMENT_BYTE_ARRAY(ec_compressed);

BC_IMPLEMENT_BYTE_ARRAY(ec_uncompressed);

BC_IMPLEMENT_BYTE_ARRAY(ec_signature);

size_t bc_max_der_signature_size()
{
    return libbitcoin::max_der_signature_size;
}

size_t bc_max_endorsement_size()
{
    return libbitcoin::max_endorsement_size;
}

bc_recoverable_signature_t* bc_create_recoverable_signature()
{
    return new bc_recoverable_signature_t{
        new libbitcoin::recoverable_signature, true };
}
void bc_destroy_recoverable_signature(bc_recoverable_signature_t* self)
{
    if (self->delete_obj)
        delete self->obj;
    delete self;
}
bc_ec_signature_t* bc_recoverable_signature__signature(
    const bc_recoverable_signature_t* self)
{
    return new bc_ec_signature_t{ &self->obj->signature, false };
}
void bc_recoverable_signature__set_signature(
    bc_recoverable_signature_t* self, const bc_ec_signature_t* signature)
{
    self->obj->signature = *signature->obj;
}
uint8_t bc_recoverable_signature__recovery_id(
    const bc_recoverable_signature_t* self)
{
    return self->obj->recovery_id;
}
void bc_recoverable_signature__set_recovery_id(
    const bc_recoverable_signature_t* self, uint8_t recovery_id)
{
    self->obj->recovery_id = recovery_id;
}

bc_ec_compressed_t* null_compressed_point()
{
    return new bc_ec_compressed_t{ new libbitcoin::ec_compressed(
        libbitcoin::null_compressed_point), false };
}
bc_ec_uncompressed_t* null_uncompressed_point()
{
    return new bc_ec_uncompressed_t{ new libbitcoin::ec_uncompressed(
        libbitcoin::null_uncompressed_point), false };
}

// Add and multiply EC values
// ----------------------------------------------------------------------------

bool bc_ec_add_compressed(
    bc_ec_compressed_t* point, const bc_ec_secret_t* secret)
{
    return libbitcoin::ec_add(*point->obj, *secret->obj);
}

bool bc_ec_add_uncompressed(
    bc_ec_uncompressed_t* point, const bc_ec_secret_t* secret)
{
    return libbitcoin::ec_add(*point->obj, *secret->obj);
}

bool bc_ec_add(bc_ec_secret_t* left, const bc_ec_secret_t* right)
{
    return libbitcoin::ec_add(*left->obj, *right->obj);
}

bool bc_ec_multiply_compressed(
    bc_ec_compressed_t* point, const bc_ec_secret_t* secret)
{
    return libbitcoin::ec_multiply(*point->obj, *secret->obj);
}

bool bc_ec_multiply_uncompressed(
    bc_ec_uncompressed_t* point, const bc_ec_secret_t* secret)
{
    return libbitcoin::ec_multiply(*point->obj, *secret->obj);
}

bool bc_ec_multiply(bc_ec_secret_t* left, const bc_ec_secret_t* right)
{
    return libbitcoin::ec_multiply(*left->obj, *right->obj);
}

// Convert keys
// ----------------------------------------------------------------------------

bool bc_compress(bc_ec_compressed_t* out, const bc_ec_uncompressed_t* point)
{
    return libbitcoin::compress(*out->obj, *point->obj);
}

bool bc_decompress(bc_ec_uncompressed_t* out, const bc_ec_compressed_t* point)
{
    return libbitcoin::decompress(*out->obj, *point->obj);
}

bool bc_secret_to_public_compressed(
    bc_ec_compressed_t* out, const bc_ec_secret_t* secret)
{
    return libbitcoin::secret_to_public(*out->obj, *secret->obj);
}

bool bc_secret_to_public_uncompressed(
    bc_ec_uncompressed_t* out, const bc_ec_secret_t* secret)
{
    return libbitcoin::secret_to_public(*out->obj, *secret->obj);
}

// Verify keys
// ----------------------------------------------------------------------------

bool bc_verify_secret(const bc_ec_secret_t* secret)
{
    return libbitcoin::verify(*secret->obj);
}

bool bc_verify_compressed(const bc_ec_compressed_t* point)
{
    return libbitcoin::verify(*point->obj);
}

bool bc_verify_uncompressed(const bc_ec_uncompressed_t* point)
{
    return libbitcoin::verify(*point->obj);
}

// Detect public keys
// ----------------------------------------------------------------------------

bool bc_is_compressed_key(const bc_data_chunk_t* point)
{
    return libbitcoin::is_compressed_key(*point->obj);
}

bool bc_is_uncompressed_key(const bc_data_chunk_t* point)
{
    return libbitcoin::is_uncompressed_key(*point->obj);
}

bool bc_is_public_key(const bc_data_chunk_t* point)
{
    return libbitcoin::is_public_key(*point->obj);
}

// DER parse/encode
// ----------------------------------------------------------------------------

bool bc_parse_signature(bc_ec_signature_t* out,
    const bc_der_signature_t* der_signature, bool strict)
{
    return libbitcoin::parse_signature(*out->obj, *der_signature->obj, strict);
}

bool bc_encode_signature(bc_der_signature_t* out,
    const bc_ec_signature_t* signature)
{
    return libbitcoin::encode_signature(*out->obj, *signature->obj);
}

// EC sign/verify
// ----------------------------------------------------------------------------

bool bc_sign(bc_ec_signature_t* out, const bc_ec_secret_t* secret,
    const bc_hash_digest_t* hash)
{
    return libbitcoin::sign(*out->obj, *secret->obj, *hash->obj);
}

bool bc_verify_signature_compressed(const bc_ec_compressed_t* point,
    const bc_hash_digest_t* hash, const bc_ec_signature_t* signature)
{
    return libbitcoin::verify_signature(
        *point->obj, *hash->obj, *signature->obj);
}

bool bc_verify_signature_uncompressed(const bc_ec_uncompressed_t* point,
    const bc_hash_digest_t* hash, const bc_ec_signature_t* signature)
{
    return libbitcoin::verify_signature(
        *point->obj, *hash->obj, *signature->obj);
}

bool bc_verify_signature_point(const bc_data_chunk_t* point,
    const bc_hash_digest_t* hash, const bc_ec_signature_t* signature)
{
    return libbitcoin::verify_signature(
        *point->obj, *hash->obj, *signature->obj);
}

// Recoverable sign/recover
// ----------------------------------------------------------------------------

bool sign_recoverable(bc_recoverable_signature_t* out,
    const bc_ec_secret_t* secret, const bc_hash_digest_t* hash)
{
    return libbitcoin::sign_recoverable(*out->obj, *secret->obj, *hash->obj);
}

bool recover_public_compressed(bc_ec_compressed_t* out,
    const bc_recoverable_signature_t* recoverable,
    const bc_hash_digest_t* hash)
{
    return libbitcoin::recover_public(
        *out->obj, *recoverable->obj, *hash->obj);
}

bool recover_public_uncompressed(bc_ec_uncompressed_t* out,
    const bc_recoverable_signature_t* recoverable,
    const bc_hash_digest_t* hash)
{
    return libbitcoin::recover_public(
        *out->obj, *recoverable->obj, *hash->obj);
}

} // extern C

