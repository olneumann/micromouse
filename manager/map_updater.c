#include "map_updater.h"

void init_walls(void) {
    int i, j;
    for (i = 0; i < MAZE_WALL_SIZE; i++) {
        for (j = 0; j < MAZE_WALL_SIZE; j++) {
            if (i == 0 || i == MAZE_WALL_SIZE - 1 || j == 0 || j == MAZE_WALL_SIZE - 1) {
                walls[i][j] = 1;
            } else {
                walls[i][j] = 0;
            }
        }
    }
}
bool is_wall(uint8_t x, uint8_t y){
    return walls[x][y];
}
void set_a_wall(uint8_t x, uint8_t y){
    walls[x][y] = 1;
}
void set_walls_along_x(uint8_t x, int wall_count, ...){
    va_list ap;
    int i, y;
    va_start (ap, wall_count);         /* Initialize the argument list. */

    for (i = 0; i < wall_count; i++){
        y = (uint8_t) va_arg (ap, int);
        set_a_wall(x, y);
    }
    va_end (ap);
}
void set_walls_along_y(uint8_t y, int wall_count, ...){
    va_list ap;
    int i, x;
    va_start (ap, wall_count);         /* Initialize the argument list. */

    for (i = 0; i < wall_count; i++){
        x = (uint8_t) va_arg (ap, int);
        set_a_wall(x, y);
    }
    va_end (ap);
}
position get_first_seen_wall(direction sensor_sight_direction, distance d){
    state mouse_state = get_mouse_state();
    return (position){0,1};
}

void update_map(void){
    state mouse_state = get_mouse_state();
    switch (mouse_state.d) {
        case East:
            get_first_seen_wall(East, get_front_sensor_range_distance() ); // front sensor
            get_first_seen_wall(South, get_right_sensor_range_distance()); // right sensor
            get_first_seen_wall(North, get_left_sensor_range_distance()); // left sensor

            break;
        case West:
            get_first_seen_wall(West,get_front_sensor_range_distance()); // front sensor
            get_first_seen_wall(North,get_right_sensor_range_distance()); // right sensor
            get_first_seen_wall(South,get_left_sensor_range_distance()); // left sensor

            break;
        case North:
            get_first_seen_wall(North,get_front_sensor_range_distance()); // front sensor
            get_first_seen_wall(East,get_right_sensor_range_distance()); // right sensor
            get_first_seen_wall(West,get_left_sensor_range_distance()); // left sensor
            break;
        case South:
            get_first_seen_wall(South,get_front_sensor_range_distance()); // front sensor
            get_first_seen_wall(West,get_right_sensor_range_distance()); // right sensor
            get_first_seen_wall(East,get_left_sensor_range_distance()); // left sensor
            break;
        default:
            break;
    }
}
void print_walls(void){
    int i, j;
    for (j = MAZE_WALL_SIZE-1; j >=0; j--) {
        printf("\n");
        for (i = 0; i < MAZE_WALL_SIZE; i++) {
            printf("%d ",walls[i][j]);
        }
    }
    printf("\n");

}
