#include <assert.h>
#include <bitcoin/bitcoin.h>

int main()
{
    bc_data_chunk_t* rawdata = bc_create_data_chunk();
    bc_decode_base16(rawdata,
        "46682488f0a721124a3905a1bb72445bf13493e2cd46c5c0c8db1c15afa0d58e00000000");

    const uint8_t rawbytes[] = {
        0x46, 0x68, 0x24, 0x88, 0xf0, 0xa7, 0x21, 0x12, 0x4a, 0x39, 0x05, 0xa1,
        0xbb, 0x72, 0x44, 0x5b, 0xf1, 0x34, 0x93, 0xe2, 0xcd, 0x46, 0xc5, 0xc0,
        0xc8, 0xdb, 0x1c, 0x15, 0xaf, 0xa0, 0xd5, 0x8e, 0x00, 0x00, 0x00, 0x00
    };
    bc_data_chunk_t* rawdata_cmp = bc_create_data_chunk_Array(
        rawbytes, sizeof(rawbytes));
    assert(bc_data_chunk_equals(rawdata_cmp, rawdata));
    bc_destroy_data_chunk(rawdata_cmp);

    bc_point_t* point = bc_point_factory_from_data(rawdata);

    assert(bc_point_is_valid(point));

    bc_hash_digest_t* point_hash = bc_point_hash(point);
    bc_string_t* hash_str = bc_encode_hash(point_hash);
    assert(bc_string_equals_cstr(hash_str,
        "8ed5a0af151cdbc8c0c546cde29334f15b4472bba105394a1221a7f088246846"));
    bc_destroy_string(hash_str);
    bc_destroy_hash_digest(point_hash);

    assert(bc_point_index(point) == 0);

    bc_data_chunk_t* output = bc_point_to_data(point);
    assert(bc_data_chunk_equals(output, rawdata));
    bc_destroy_data_chunk(output);

    bc_destroy_point(point);
    bc_destroy_data_chunk(rawdata);
    return 0;
}

