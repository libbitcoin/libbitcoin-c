#include <bitcoin/bitcoin.h>
#include <stdio.h>

int main()
{
    bc_output_info_list_t* unspent = bc_create_output_info_list();

    bc_output_info_t* oi = NULL;
    bc_output_point_t* out_point = NULL;
    bc_point_t* point = NULL;
    bc_hash_digest_t* hash = NULL;

    oi = bc_create_output_info();
    out_point = bc_output_info__point(oi);
    point = bc_output_point__point_Base(out_point);
    hash = bc_point__hash(point);
    bc_decode_hash(hash,
        "c7ade88fc7a21498a6a5e5c385e1f68bed822b72aa63c4a9a48a02c2466ee29e");
    bc_point__set_index(point, 110);
    bc_output_info__set_value(oi, 2);
    bc_destroy_hash_digest(hash);
    bc_destroy_point(point);
    bc_destroy_output_point(out_point);
    bc_output_info_list__push_back_consume(unspent, &oi);

    oi = bc_create_output_info();
    out_point = bc_output_info__point(oi);
    point = bc_output_point__point_Base(out_point);
    hash = bc_point__hash(point);
    bc_decode_hash(hash,
        "9595c9df90075148eb06860365df33584b75bff782a510c6cd4883a419833d50");
    bc_point__set_index(point, 4);
    bc_output_info__set_value(oi, 9);
    bc_destroy_hash_digest(hash);
    bc_destroy_point(point);
    bc_destroy_output_point(out_point);
    bc_output_info_list__push_back_consume(unspent, &oi);

    oi = bc_create_output_info();
    out_point = bc_output_info__point(oi);
    point = bc_output_point__point_Base(out_point);
    hash = bc_point__hash(point);
    bc_decode_hash(hash,
        "89bd03eb43519deb91838f413da7d2f131a625eab653d4486104bfd1d7fa3121");
    bc_point__set_index(point, 99);
    bc_output_info__set_value(oi, 1);
    bc_destroy_hash_digest(hash);
    bc_destroy_point(point);
    bc_destroy_output_point(out_point);
    bc_output_info_list__push_back_consume(unspent, &oi);

    oi = bc_create_output_info();
    out_point = bc_output_info__point(oi);
    point = bc_output_point__point_Base(out_point);
    hash = bc_point__hash(point);
    bc_decode_hash(hash,
        "42177a97f21819d54a8ad2f478c11ec1e19b29aa7bd3ddf0a49164854c95a5f7");
    bc_point__set_index(point, 8);
    bc_output_info__set_value(oi, 88);
    bc_destroy_hash_digest(hash);
    bc_destroy_point(point);
    bc_destroy_output_point(out_point);
    bc_output_info_list__push_back_consume(unspent, &oi);

    const uint64_t minimum_value = 10;

    bc_points_info_t* out = bc_create_points_info();

    bc_select_outputs__select(out, unspent, minimum_value);

    bc_chain_point_list_t* points = bc_points_info__points(out);
    for (size_t i = 0; i < bc_chain_point_list__size(points); ++i)
    {
        point = bc_chain_point_list__at(points, i);
        bc_string_t* desc = bc_point__to_string(point);
        printf("%s\n", bc_string__data(desc));
        bc_destroy_string(desc);
    }
    bc_destroy_chain_point_list(points);

    printf("%lu\n", bc_points_info__change(out));

    bc_destroy_points_info(out);
    bc_destroy_output_info_list(unspent);
    return 0;
}

