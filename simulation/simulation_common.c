//
// Created by root on 3/3/21.
//

#include "simulation_common.h"

position SIMULATION_get_front_sensor_range_data() {
    state mouse_state = get_mouse_state();
    uint8_t y = mouse_state.p.y * 2 + 1;
    uint8_t x = mouse_state.p.x * 2 + 1;
    uint8_t i;
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
                printf("n(%d,%d) %d", x, i, is_wall(x,i));
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
    return wall;

}

position SIMULATION_get_right_sensor_range_data() {
    state mouse_state = get_mouse_state();
    uint8_t y = mouse_state.p.y * 2 + 1;
    uint8_t x = mouse_state.p.x * 2 + 1;
    uint8_t i;
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
    return wall;

}

position SIMULATION_get_left_sensor_range_data() {
    state mouse_state = get_mouse_state();
    uint8_t y = mouse_state.p.y * 2 + 1;
    uint8_t x = mouse_state.p.x * 2 + 1;
    uint8_t i;
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

            for (i = y + 1; i <= MAZE_WALL_SIZE; ++i) {
                printf("e(%d,%d)", x, i);
                if (is_wall(x,i)) {
                    wall.x = x;
                    wall.y = i;
                    break;
                }
            }
            break;
        case South:
            for (i = x + 1; i <= MAZE_WALL_SIZE; ++i) {
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
    return wall;
}