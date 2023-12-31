#include <assert.h>
#include <memory.h>
#include <bim_polygon_tools.h>

polygon_t triangle_polygon_with_area_1() {
    size_t number_of_points = 4;
    point_t *points = (point_t *) calloc(number_of_points, sizeof(point_t));
    point_t points_arr[] = {
            {0.0, -1.0},
            {1.0, 0.0},
            {0.0, 1.0},
            {0.0, -1.0}
    };
    memcpy(points, points_arr, sizeof(point_t) * number_of_points);
    polygon_t polygon = {
            .points = points,
            .numofpoints = number_of_points
    };
    return polygon;
}

polygon_t triangle_polygon_with_area_0_5() {
    size_t number_of_points = 4;
    point_t *points = (point_t *) calloc(number_of_points, sizeof(point_t));
    point_t points_arr[] = {
            {0.0, 0.0},
            {1.0, 0.0},
            {0.0, 1.0},
            {0.0, 0.0}
    };
    memcpy(points, points_arr, sizeof(point_t) * number_of_points);
    polygon_t polygon = {
            .points = points,
            .numofpoints = number_of_points
    };
    return polygon;
}

polygon_t parallelogram_polygon() {
    size_t number_of_points = 5;
    point_t *points = (point_t *) calloc(number_of_points, sizeof(point_t));
    point_t points_arr[] = {
            {-2.0, -1.0},
            {2.0,  -1.0},
            {3.0,  1.0},
            {-1.0, 1.0},
            {-2.0, -1.0}
    };
    memcpy(points, points_arr, sizeof(point_t) * number_of_points);
    polygon_t polygon = {
            .points = points,
            .numofpoints = number_of_points
    };
    return polygon;
}

polygon_t complex_figure_with_right_angles_polygon() {
    size_t number_of_points = 21;
    point_t *points = (point_t *) calloc(number_of_points, sizeof(point_t));
    point_t points_arr[] = {
            {35.97872543334961,  -34.659114837646484},
            {35.97872543334961,  -37.01911163330078},
            {33.9708251953125,   -37.01911163330078},
            {33.9708251953125,   -37.219112396240234},
            {34.07872772216797,  -37.219112396240234},
            {34.0787277221679,   -38.4352912902832},
            {33.15372467041016,  -38.4352912902832},
            {33.153724670410156, -37.219112396240234},
            {33.25210189819336,  -37.219112396240234},
            {33.25210189819336,  -37.01911163330078},
            {32.90689468383789,  -37.01911163330078},
            {32.90689468383789,  -37.219112396240234},
            {33.003726959228516, -37.219112396240234},
            {33.00372695922856,  -38.4352912902832},
            {32.0787277221679,   -38.4352912902832},
            {32.07872772216797,  -37.219112396240234},
            {32.193763732910156, -37.219112396240234},
            {32.19376373291015,  -37.01911163330078},
            {30.50872802734375,  -37.01911163330078},
            {30.50872802734375,  -34.659114837646484},
            {35.97872543334961,  -34.659114837646484}
    };
    memcpy(points, points_arr, sizeof(point_t) * number_of_points);
    polygon_t polygon = {
            .points = points,
            .numofpoints = number_of_points
    };
    return polygon;
}

polygon_t square_polygon() {
    size_t number_of_points = 5;
    point_t *points = (point_t *) calloc(number_of_points, sizeof(point_t));
    point_t points_arr[] = {
            {0.0, 0.0},
            {1.0, 0.0},
            {1.0, 1.0},
            {0.0, 1.0},
            {0.0, 0.0}
    };
    memcpy(points, points_arr, sizeof(point_t) * number_of_points);
    polygon_t polygon = {
            .points = points,
            .numofpoints = number_of_points
    };
    return polygon;
}

void test_triangle_area() {
    polygon_t polygon = triangle_polygon_with_area_1();
    assert(geom_tools_area_polygon(&polygon) == 1.0);
}

void test_parallelogram_polygon_area() {
    polygon_t polygon = parallelogram_polygon();
    assert(geom_tools_area_polygon(&polygon) == 8.0);
}

void test_complex_figure_with_right_angles_polygon_area() {
    polygon_t polygon = complex_figure_with_right_angles_polygon();
    assert(geom_tools_area_polygon(&polygon) == 15.445482030030689202249050140380859375);
}

void test_point_inside_triangle() {
    polygon_t triangle_polygon = triangle_polygon_with_area_0_5();
    point_t points[] = {
        { 0.0, 0.0 },
        { 0.5, 0.0 },
        { 1.0, 0.0 },
        { 0.5, 0.5 },
        { 0.0, 1.0 },
        { 0.0, 0.5 },
        { 0.0, 0.0 }
    };
    size_t number_of_points = 7;

    for (size_t i = 0; i < number_of_points; i++) {
        assert(geom_tools_is_point_in_polygon(&points[i], &triangle_polygon));
    }
}

void test_point_outside_triangle() {
    polygon_t triangle_polygon = triangle_polygon_with_area_0_5();
    point_t points[] = {
        {-1.0, -1.0},
        {0.5, -1.0},
        {1.5, -0.5},
        {1.0, 1.0},
        {-0.5, 1.5},
        {-0.5, 0.5}
    };
    size_t number_of_points = 6;

    for (size_t i = 0; i < number_of_points; i++) {
        assert(!geom_tools_is_point_in_polygon(&points[i], &triangle_polygon));
    }
}

void test_point_inside_square() {
    polygon_t polygon = square_polygon();
    point_t points[] = {
        {0.0, 0.0},
        {0.5, 0.0},
        {1.0, 0.0},
        {1.0, 0.5},
        {1.0, 1.0},
        {0.5, 1.0},
        {0.0, 1.0},
        {0.0, 0.5},
        {0.5, 0.5}
    };
    size_t number_of_points = 9;

    for (size_t i = 0; i < number_of_points; i++) {
        assert(geom_tools_is_point_in_polygon(&points[i], &polygon));
    }
}

void test_point_outside_square() {
    polygon_t polygon = square_polygon();
    point_t points[] = {
        {-0.5, -0.5},
        {0.5, -0.5},
        {1.5, -0.5},
        {1.5, 0.5},
        {1.5, 1.5},
        {0.5, 1.5},
        {-0.5, 1.5},
        {-0.5, 0.5}
    };
    size_t number_of_points = 8;

    for (size_t i = 0; i < number_of_points; i++) {
        assert(!geom_tools_is_point_in_polygon(&points[i], &polygon));
    }
}

void test_polygon_intersection() {
    polygon_t polygon = complex_figure_with_right_angles_polygon();
    point_t points_outside[] = {
        {31.87872886657715, -38.24702072143555},
        {31.87872886657715, -37.34701919555664}
    };
    size_t number_of_points_inside = 2;
    point_t points_inside[] = {
        {32.07872772216797, -38.24702072143555},
        {32.07872772216797, -37.34701919555664}
    };
    size_t number_of_points_outside = 2;

    for (size_t i = 0; i < number_of_points_inside; i++) {
        assert(geom_tools_is_point_in_polygon(&points_inside[i], &polygon));
    }
    for (size_t i = 0; i < number_of_points_outside; i++) {
        assert(!geom_tools_is_point_in_polygon(&points_outside[i], &polygon));
    }
}

int main() {
    test_triangle_area();
    test_parallelogram_polygon_area();
    test_complex_figure_with_right_angles_polygon_area();
    test_point_inside_triangle();
    test_point_outside_triangle();
    test_point_inside_square();
    test_point_outside_square();
    test_polygon_intersection();
    return 0;
}
