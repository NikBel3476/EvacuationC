#include <assert.h>

#include <bim_json_object.h>
#include <bim_polygon_tools.h>

#include <bim_evac.c>

bim_zone_t receiving_zone_default() {
    uuid_t uuid = {.x = "00000000-0000-0000-0000-000000000000"};
    uuid_t *outputs = (uuid_t *) calloc(1, sizeof(uuid_t));
    strcpy((char *) outputs[0].x, uuid.x);
    point_t points[] = {};
    polygon_t polygon = {
            .numofpoints = 0,
            .points = points
    };
    bim_zone_t zone = {
            .id = 1,
            .name = "Receiving zone",
            .uuid = {.x = "00000000-0000-0000-0000-000000000000"},
            .outputs = outputs,
            .area = 10.0,
            .z_level = 1.0,
            .numofpeople = 10.0,
            .hazard_level = 0,
            .is_blocked = false,
            .is_visited = false,
            .is_safe = true,
            .sign = ROOM,
            .size_z = 2.0,
            .polygon = &polygon,
            .potential = 1.0
    };
    return zone;
}

bim_zone_t transmitting_zone_default() {
    uuid_t uuid = {.x = "00000000-0000-0000-0000-000000000000"};
    uuid_t *outputs = (uuid_t *) calloc(1, sizeof(uuid_t));
    strcpy((char *) outputs[0].x, uuid.x);
    point_t points[] = {};
    polygon_t polygon = {
            .numofpoints = 0,
            .points = points
    };
    bim_zone_t zone = {
            .id = 2,
            .name = "Transmitting zone",
            .uuid = uuid,
            .outputs = outputs,
            .area = 10.0,
            .z_level = 1.0,
            .numofpeople = 10.0,
            .hazard_level = 0,
            .is_blocked = false,
            .is_visited = false,
            .is_safe = true,
            .sign = ROOM,
            .size_z = 2.0,
            .polygon = &polygon,
            .potential = 1.0,
    };
    return zone;
}

bim_transit_t transit_default() {
    uuid_t uuid = {.x = "00000000-0000-0000-0000-000000000000"};
    uuid_t *outputs = (uuid_t *) calloc(1, sizeof(uuid_t));
    strcpy((char *) outputs[0].x, uuid.x);
    point_t points[] = {};
    polygon_t polygon = {
            .numofpoints = 0,
            .points = points
    };
    bim_transit_t transition = {
            .uuid = uuid,
            .id = 1,
            .name = "Transit",
            .outputs = outputs,
            .polygon = &polygon,
            .size_z = 2.0,
            .z_level = 1.0,
            .width = 1.0,
            .nop_proceeding = 0.0,
            .sign = DOOR_WAY,
            .is_visited = false,
            .is_blocked = false,
    };
    return transition;
}

void test_speed_in_element() {
    bim_zone_t receiving_zone = receiving_zone_default();
    bim_zone_t transmitting_zone = transmitting_zone_default();
    evac_speed_max = 100.0;

    assert(speed_in_element(&receiving_zone, &transmitting_zone) == 80.13633567871892);
}

void test_speed_at_exit() {
    bim_zone_t receiving_zone = receiving_zone_default();
    bim_zone_t transmitting_zone = transmitting_zone_default();
    double transit_width = 1.0;
    evac_speed_max = 100.0;

    assert(speed_at_exit(&receiving_zone, &transmitting_zone, transit_width) == 80.13633567871892);
}

void test_change_num_of_people() {
    bim_zone_t transmitting_zone = transmitting_zone_default();
    double transit_width = 1.0;
    evac_modeling_step = 0.01;
    double speed_at_exit_test = 50.0;

    assert(change_numofpeople(&transmitting_zone, transit_width, speed_at_exit_test) == 0.5);
}

void test_potential_element() {
    bim_zone_t receiving_zone = receiving_zone_default();
    bim_zone_t transmitting_zone = transmitting_zone_default();
    bim_transit_t transit = transit_default();

    assert(potential_element(&receiving_zone, &transmitting_zone, &transit) == 1.039461221097587);
}

void test_part_people_flow() {
    bim_zone_t receiving_zone = receiving_zone_default();
    bim_zone_t transmitting_zone = transmitting_zone_default();
    bim_transit_t transit = transit_default();
    evac_density_min = 0.1;
    evac_density_max = 5.0;

    assert(part_people_flow(&receiving_zone, &transmitting_zone, &transit) == 0.8013633567871893);
}

void test_part_people_flow_outside() {
    polygon_t receiving_zone_polygon = {
            .numofpoints = 0,
            .points = {}
    };
    uuid_t *receiving_zone_outputs = (uuid_t *) calloc(2, sizeof(uuid_t));
    strcpy((char *) receiving_zone_outputs[0].x, "f2590703-5d39-43c7-8241-5e7dd246e3d4");
    strcpy((char *) receiving_zone_outputs[1].x, "003c0e9b-2671-4e4a-bc23-31456986725c");
    bim_zone_t receiving_zone = {
            .id = 6,
            .name = "Outside",
            .uuid = {.x = "00000000-0000-0000-0000-000000000000"},
            .outputs = receiving_zone_outputs,
            .area = 1.7976931348623157e+308,
            .z_level = 0.0,
            .numofpeople = 10.0,
            .hazard_level = 0,
            .is_blocked = false,
            .is_visited = false,
            .is_safe = true,
            .sign = OUTSIDE,
            .size_z = 1.7976931348623157e+308,
            .polygon = &receiving_zone_polygon,
            .potential = 0.05983352150182077,
    };

    uuid_t *transmitting_zone_outputs = (uuid_t *) calloc(3, sizeof(uuid_t));
    strcpy((char *) transmitting_zone_outputs[0].x, "b0611c37-febb-44ca-b8b4-f4ed4626d007");
    strcpy((char *) transmitting_zone_outputs[1].x, "ad4962eb-dfd5-4295-8693-18066f5e82e3");
    strcpy((char *) transmitting_zone_outputs[2].x, "003c0e9b-2671-4e4a-bc23-31456986725c");
    point_t transmitting_zone_polygon_points[] = {
            {8.049085116975721,  3.939957782245948},
            {13.925474407478942, 3.939957782245948},
            {13.925474407478942, 0.03282578402084191},
            {8.03339382381016,   0.03282578402084263},
            {8.049085116975721,  3.939957782245948},
    };
    polygon_t transmitting_zone_polygon = {
            .numofpoints = 5,
            .points = transmitting_zone_polygon_points
    };
    bim_zone_t transmitting_zone = {
            .id = 3,
            .name = "Comp 5 (00 : 6349c)",
            .uuid = {.x = "37a611a3-b0b4-491f-b3de-f0eb7a06349c"},
            .outputs = transmitting_zone_outputs,
            .area = 22.990482607762807,
            .z_level = 0.0,
            .numofpeople = 22.990482607762807,
            .hazard_level = 0,
            .is_blocked = false,
            .is_visited = false,
            .is_safe = false,
            .sign = ROOM,
            .size_z = 3.0,
            .polygon = &transmitting_zone_polygon,
            .potential = 1.7976931348623157e+308,
    };

    uuid_t *transition_outputs = (uuid_t *)calloc(1, sizeof(uuid_t));
    strcpy((char *) transition_outputs[0].x, "37a611a3-b0b4-491f-b3de-f0eb7a06349c");
    point_t transition_polygon_points[] = {
        {10.98923990097158,  -0.23217549927336378},
        {10.98923990097158, 0.3678245007266362},
        {12.98923990097158, 0.3678245007266362},
        {12.98923990097158,   -0.23217549927336378},
        {10.98923990097158,  -0.23217549927336378},
    };
    polygon_t transition_polygon = {
            .numofpoints = 5,
            .points = transition_polygon_points
    };
    bim_transit_t transition = {
            .uuid = { .x = "003c0e9b-2671-4e4a-bc23-31456986725c" },
            .id = 6,
            .name = "Выход (00 : 6725c) 6349c<->",
            .outputs = transition_outputs,
            .polygon = &transition_polygon,
            .size_z = 2.0,
            .z_level = 0.0,
            .width = 2.0,
            .nop_proceeding = 0.0,
            .sign = DOOR_WAY_OUT,
            .is_visited = false,
            .is_blocked = false,
    };

    evac_density_min = 0.1;
    evac_density_max = 5.0;

    assert(part_people_flow(&receiving_zone, &transmitting_zone, &transition) == 1.60272671357437856975991508079459890723228454589844);
}

int main() {
    test_speed_in_element();
    test_speed_at_exit();
    test_change_num_of_people();
    test_potential_element();
    test_part_people_flow();
    test_part_people_flow_outside();
    return 0;
}
