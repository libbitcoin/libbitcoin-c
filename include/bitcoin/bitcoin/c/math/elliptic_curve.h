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
#ifndef LIBBITCOIN_C_ELLIPTIC_CURVE_H
#define LIBBITCOIN_C_ELLIPTIC_CURVE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Private key:
size_t bc_ec_secret_size();
typedef struct bc_ec_secret_t bc_ec_secret_t;
void bc_destroy_ec_secret(bc_ec_secret_t* self);

/// Compressed public key:
size_t bc_ec_compressed_size();
typedef struct bc_ec_compressed_t bc_ec_compressed_t;
void bc_destroy_ec_compressed(bc_ec_compressed_t* self);

/// Uncompressed public key:
size_t bc_ec_uncompressed_size();
typedef struct bc_ec_uncompressed_t bc_ec_uncompressed_t;
void bc_destroy_ec_uncompressed(bc_ec_uncompressed_t* self);

// Parsed ECDSA signature:
size_t bc_ec_signature_size();
typedef struct bc_ec_signature_t bc_ec_signature_t;
void bc_destroy_ec_signature(bc_ec_signature_t* self);

// DER encoded signature:
size_t bc_max_der_signature_size();
typedef struct bc_der_signature_t bc_der_signature_t;
void bc_destroy_der_signature(bc_der_signature_t* self);

/// DER encoded signature with sighash byte for input endorsement:
size_t bc_max_endorsement_size();
typedef struct bc_endorsement_t bc_endorsement_t;
void bc_destroy_endorsement(bc_endorsement_t* self);

/// Recoverable ecdsa signature for message signing:
typedef struct bc_recoverable_signature_t bc_recoverable_signature_t;
void bc_destroy_recoverable_signature(bc_recoverable_signature_t* self);

bc_ec_compressed_t* null_compressed_point();
bc_ec_uncompressed_t* null_uncompressed_point();

// Add and multiply EC values
// ----------------------------------------------------------------------------

/// Compute the sum a += G*b, where G is the curve's generator point.
/// return false on failure (such as infinity or zero).
bool bc_ec_add_compressed(bc_ec_compressed_t* point, bc_ec_secret_t* secret);

/// Compute the sum a += G*b, where G is the curve's generator point.
/// return false on failure (such as infinity or zero).
bool bc_ec_add_uncompressed(
    bc_ec_uncompressed_t* point, bc_ec_secret_t* secret);

/// Compute the sum a = (a + b) % n, where n is the curve order.
/// return false on failure (such as a zero result).
bool bc_ec_add(bc_ec_secret_t* left, bc_ec_secret_t* right);

/// Compute the product point *= secret.
/// return false on failure (such as infinity or zero).
bool bc_ec_multiply_compressed(
    bc_ec_compressed_t* point, bc_ec_secret_t* secret);

/// Compute the product point *= secret.
/// return false on failure (such as infinity or zero).
bool bc_ec_multiply_uncompressed(
    bc_ec_uncompressed_t* point, bc_ec_secret_t* secret);

/// Compute the product a = (a * b) % n, where n is the curve order.
/// return false on failure (such as a zero result).
bool bc_ec_multiply(bc_ec_secret_t* left, bc_ec_secret_t* right);

// Convert keys
// ----------------------------------------------------------------------------

/// Convert an uncompressed public point to compressed.
bool bc_compress(bc_ec_compressed_t* out, bc_ec_uncompressed_t* point);

/// Convert a compressed public point to decompressed.
bool bc_decompress(bc_ec_uncompressed_t* out, bc_ec_compressed_t* point);

/// Convert a secret to a compressed public point.
bool bc_compressed_secret_to_public(
    bc_ec_compressed_t* out, bc_ec_secret_t* secret);

/// Convert a secret parameter to an uncompressed public point.
bool bc_uncompressed_secret_to_public(
    bc_ec_uncompressed_t* out, bc_ec_secret_t* secret);

// Verify keys
// ----------------------------------------------------------------------------

/// Verify a secret.
bool bc_verify_secret(bc_ec_secret_t* secret);

/// Verify a point.
bool bc_verify_compressed(bc_ec_compressed_t* point);

/// Verify a point.
bool bc_verify_uncompressed(bc_ec_uncompressed_t* point);

#ifdef __cplusplus
}
#endif

#endif

