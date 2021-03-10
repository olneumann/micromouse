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
void print_walls_around() {
    printf(" f:%d r:%d l:%d\n", walls_around.front, walls_around.right, walls_around.left);
}
walls_around_t reset_around_walls() {
    double f_distance = get_front_sensor_range_data();
    double r_distance = get_right_sensor_range_data();
    double l_distance = get_left_sensor_range_data();
    printf("f dist : %f ,r dist : %f ,l dist : %f \n", f_distance, r_distance, l_distance);
    walls_around.front = f_distance > IS_THAT_A_WALL_THRESHOLD ? False : True;
    walls_around.right = r_distance > IS_THAT_A_WALL_THRESHOLD ? False : True;
    walls_around.left = l_distance > IS_THAT_A_WALL_THRESHOLD ? False : True;
    return walls_around;
}

void update_map(void){
    state mouse_state = get_mouse_state();
    switch (mouse_state.d) {
        case East:
            get_first_seen_wall(East, get_front_sensor_range_data()); // front sensor
            get_first_seen_wall(South, get_right_sensor_range_data()); // right sensor
            get_first_seen_wall(North, get_left_sensor_range_data()); // left sensor

            break;
        case West:
            get_first_seen_wall(West,get_front_sensor_range_data()); // front sensor
            get_first_seen_wall(North,get_right_sensor_range_data()); // right sensor
            get_first_seen_wall(South,get_left_sensor_range_data()); // left sensor

            break;
        case North:
            get_first_seen_wall(North,get_front_sensor_range_data()); // front sensor
            get_first_seen_wall(East,get_right_sensor_range_data()); // right sensor
            get_first_seen_wall(West,get_left_sensor_range_data()); // left sensor
            break;
        case South:
            get_first_seen_wall(South,get_front_sensor_range_data()); // front sensor
            get_first_seen_wall(West,get_right_sensor_range_data()); // right sensor
            get_first_seen_wall(East,get_left_sensor_range_data()); // left sensor
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
bool is_cells_the_same(position a, position b) {
    if (a.x == b.x && a.y == b.y) return True;
    return False;
}
#if !DISCOVERY_SIMULATION
distance get_front_sensor_range_data() {
    printf("aaaaaaaaaa");
    return 0;
}

distance get_right_sensor_range_data() {
    printf("aaaaaaaaaa");
    return 0;
}

distance get_left_sensor_range_data() {
    printf("aaaaaaaaaa");

    return 0;
}
#endif
