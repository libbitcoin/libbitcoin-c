#include <bitcoin/bitcoin.h>

int main()
{
    bc_hd_public_t* w = bc_create_hd_public();
    bc_destroy_hd_public(w);

    bc_hash_digest_t* h = bc_null_hash();
    bc_destroy_hash_digest(h);
    return 0;
}

