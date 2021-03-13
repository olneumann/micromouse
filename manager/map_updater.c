#include "map_updater.h"

position goal_cells[] = {{GOAL_CELL_1_X,GOAL_CELL_1_Y}
#ifdef GOAL_CELL_2_X
        ,{GOAL_CELL_2_X,GOAL_CELL_2_Y}
#endif
#ifdef GOAL_CELL_3_X
        ,{GOAL_CELL_3_X,GOAL_CELL_3_Y}
#endif
#ifdef GOAL_CELL_4_X
        ,{GOAL_CELL_4_X,GOAL_CELL_4_Y}
#endif
};

position get_first_seen_wall(direction sensor_sight_direction, distance d){
    return (position){0,1};
}
void print_walls_around() {
    logger.info(" f:%d r:%d l:%d\n", walls_around.front, walls_around.right, walls_around.left);
}
walls_around_t reset_around_walls() {
    double f_distance = get_front_sensor_range_data();
    double r_distance = get_right_sensor_range_data();
    double l_distance = get_left_sensor_range_data();
    logger.info("f dist : %f ,r dist : %f ,l dist : %f \n", f_distance, r_distance, l_distance);
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

bool is_cells_the_same(position a, position b) {
    if (a.x == b.x && a.y == b.y) return True;
    return False;
}
#if !DISCOVERY_SIMULATION
distance get_front_sensor_range_data() {
    logger.info("sensor data front\n");
    return 0;
}

distance get_right_sensor_range_data() {
    logger.info("sensor data right\n");
    return 0;
}

distance get_left_sensor_range_data() {
    logger.info("sensor data left\n");

    return 0;
}
#endif
