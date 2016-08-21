#include <bitcoin/bitcoin.h>

int main()
{
    bc_hd_public_t* w = bc_create_hd_public();
    bc_destroy_hd_public(w);
    return 0;
}

