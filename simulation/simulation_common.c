//
// Created by root on 3/3/21.
//

#include "simulation_common.h"
distance SIMULATION_get_distance_to_the_wall(position the_wall, ranging_sensor sensor){
    state mouse_state = get_mouse_state();
    uint8_t x = mouse_state.p.x * 2 + 1;
    uint8_t y = mouse_state.p.y * 2 + 1;
    distance sensor_distance = 0;
    uint16_t distance_in_wall_space= manhattan_distance_uint16_t((position) {x, y}, the_wall);

    double half_distance = (distance_in_wall_space-1.)/2.;

    sensor_distance = sensor_distance + (half_distance * A_WALL_PLUS_A_CELL_SIZE);

    if (sensor==Front) {
        sensor_distance += FRONT_MARGIN_BTW_MOUSE_AND_WALL;
    }
    else{
        sensor_distance += SIDE_MARGIN_BTW_MOUSE_AND_WALL;
    }
    printf("distance in wall space %f\n",sensor_distance);
    return sensor_distance + get_gaussian_noise(sensor_distance);
}
distance SIMULATION_get_front_sensor_range_data() {
    state mouse_state = get_mouse_state();

    uint8_t y = mouse_state.p.y * 2 + 1;
    uint8_t x = mouse_state.p.x * 2 + 1;

    int i;
    position wall = {-1, -1};

    printf("(%d %d) f",x,y);

    switch (mouse_state.d) {
        case West:
            for (i = x - 1; i >= 0; i -= 2) {
                printf("w(%d,%d)", i, y);
                if (is_wall(i,y)) {
                    wall.x = i;
                    wall.y = y;
                    break;
                }
            }
            break;
        case East:
            for (i = x + 1; i <= MAZE_WALL_SIZE; i += 2) {
                printf("e(%d,%d)", i, y);
                if (is_wall(i,y)) {
                    wall.x = i;
                    wall.y = y;
                    break;
                }
            }
            break;
        case South:
            for (i = y - 1; i >= 0; i -= 2) {
                printf("s(%d,%d)", x, i);
                if (is_wall(x,i)) {
                    wall.x = x;
                    wall.y = i;
                    break;
                }
            }
            break;
        case North:
            for (i = y + 1; i <= MAZE_WALL_SIZE; i += 2) {
                printf("n(%d,%d)", x, i);
                if (is_wall(x,i)) {
                    wall.x = x;
                    wall.y = i;
                    break;
                }
            }
            break;
        default:
            break;
    }
    return SIMULATION_get_distance_to_the_wall(wall,Front);

}

distance SIMULATION_get_right_sensor_range_data() {
    state mouse_state = get_mouse_state();
    uint8_t y = mouse_state.p.y * 2 + 1;
    uint8_t x = mouse_state.p.x * 2 + 1;
    int i;
    position wall = {-1, -1};
    printf("(%d %d) r",x,y);
    switch (mouse_state.d) {
        case West:
            for (i = y + 1; i <= MAZE_WALL_SIZE; i += 2) {
                printf("w(%d,%d)", x, i);
                if (is_wall(x,i)) {
                    wall.x = x;
                    wall.y = i;
                    break;
                }
            }

            break;
        case East:
            for (i = y - 1; i >= 0; i -= 2) {
                printf("e(%d,%d)", x, i);
                if (is_wall(x,i)) {
                    wall.x = x;
                    wall.y = i;
                    break;
                }
            }

            break;
        case South:
            for (i = x - 1; i >= 0; i -= 2) {
                printf("s(%d,%d)", i, y);
                if (is_wall(i,y)) {
                    wall.x = i;
                    wall.y = y;
                    break;
                }
            }
            break;
        case North:
            for (i = x + 1; i <= MAZE_WALL_SIZE; i += 2) {
                printf("n(%d,%d)", i, y);
                if (is_wall(i,y)) {
                    wall.x = i;
                    wall.y = y;
                    break;
                }
            }
            break;
        default:
            break;
    }
    return SIMULATION_get_distance_to_the_wall(wall,Right);

}

distance SIMULATION_get_left_sensor_range_data() {
    state mouse_state = get_mouse_state();
    uint8_t y = mouse_state.p.y * 2 + 1;
    uint8_t x = mouse_state.p.x * 2 + 1;
    int i;
    position wall = {-1, -1};
    printf("(%d %d) l",x,y);
    switch (mouse_state.d) {
        case West:
            for (i = y - 1; i >= 0; i -= 2) {
                printf("w(%d,%d)", x, i);
                if (is_wall(x,i)) {
                    wall.x = x;
                    wall.y = i;
                    break;
                }
            }


            break;
        case East:

            for (i = y + 1; i <= MAZE_WALL_SIZE; i+=2) {
                printf("e(%d,%d)", x, i);
                if (is_wall(x,i)) {
                    wall.x = x;
                    wall.y = i;
                    break;
                }
            }
            break;
        case South:
            for (i = x + 1; i <= MAZE_WALL_SIZE; i+=2) {
                printf("s(%d,%d)", i, y);
                if (is_wall(i,y)) {
                    wall.x = i;
                    wall.y = y;
                    break;
                }
            }
            break;
        case North:
            for (i = x - 1; i >= 0; i -= 2) {
                printf("n(%d,%d)", i, y);
                if (is_wall(i,y)) {
                    wall.x = i;
                    wall.y = y;
                    break;
                }
            }
            break;
        default:
            break;
    }
    return SIMULATION_get_distance_to_the_wall(wall,Left);
}
distance get_gaussian_noise(distance d){
    static double mean = 0;
    double stdd = ((double) d) * (4.0 / (100.*3.)), noise;
    double u, v, s1;
    do{
        u = (rand() / ((double ) RAND_MAX) * 2.0 - 1.0);
        v = (rand() / ((double ) RAND_MAX) * 2.0 - 1.0);

        s1 = u*u + v*v;

    }while(s1>= 1.0 || s1== 0.0);
    s1 = sqrt(-2.0 * log(s1) / s1);
    noise = mean + stdd * u * s1;

    return noise;

}