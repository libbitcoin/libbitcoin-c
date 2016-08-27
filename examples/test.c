#include <assert.h>
#include <bitcoin/bitcoin.h>

#define SECRET1 "8010b1bb119ad37d4b65a1022a314897b1b3614b345974332cb1b9582cf03536"

void test()
{
    bc_ec_compressed_t* point = bc_create_ec_compressed();
    bc_ec_signature_t* signature = bc_create_ec_signature();

    uint8_t data_bytes[] = { 'd', 'a', 't', 'a' };
    bc_data_chunk_t* data = bc_create_data_chunk_Array(data_bytes, 4);
    bc_hash_digest_t* hash = bc_bitcoin_hash(data);
    bc_destroy_data_chunk(data);

    bc_hash_digest_t* secret_literal = bc_hash_literal(&SECRET1);
    bc_ec_secret_t* secret = bc_create_ec_secret_Data(
        bc_hash_digest_cdata(secret_literal));
    bc_destroy_hash_digest(secret_literal);

    assert(bc_secret_to_public_compressed(point, secret));
    assert(bc_sign(signature, secret, hash));
    assert(bc_verify_signature_compressed(point, hash, signature));

    bc_hash_digest_data(hash)[0] = 110;
    assert(!bc_verify_signature_compressed(point, hash, signature));

    bc_destroy_ec_secret(secret);
    bc_destroy_hash_digest(hash);
    bc_destroy_ec_signature(signature);
    bc_destroy_ec_compressed(point);
}

int main()
{
    bc_hd_public_t* w = bc_create_hd_public();
    bc_destroy_hd_public(w);

    bc_hash_digest_t* h = bc_null_hash();
    bc_destroy_hash_digest(h);

    test();
    return 0;
}

