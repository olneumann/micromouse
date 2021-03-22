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

direction get_direction_btw_start_and_end_cell(position start, position end) {
    logger.info(" get_direction ==> (%d, %d,) ( %d %d) \n", start.x, start.y, end.x, end.y);

    if (start.x > end.x && start.y == end.y) {
        return West;
    } else if (start.x < end.x && start.y == end.y) {
        return East;
    } else if (start.x == end.x && start.y < end.y) {
        return North;
    } else if (start.x == end.x && start.y > end.y) {
        return South;
    } else if (start.x == end.x && start.y == end.y) {
        return get_mouse_state().d;
    } else return -1;
}
position what_is_the_position_after_moving_one_step_in_the_direction(position pos, direction d) {
    switch (d) {
        case West:
            pos.x -= 1;
            return pos;
        case East:
            pos.x += 1;
            return pos;
        case North:
            pos.y += 1;
            return pos;
        case South:
            pos.y -= 1;
            return pos;
        default:
            return pos;
    }

}

direction get_sight_direction_of_sensor(ranging_sensor sensor) {
    state mouse_state = get_mouse_state();
    switch (sensor) {
        case Front_Sensor:
            return mouse_state.d;
        case Right_Sensor:
            switch (mouse_state.d) {
                case West:
                    return North;
                case East:
                    return South;
                case North:
                    return East;
                case South:
                    return West;
                default:
                    return -1;
            }
            break;
        case Left_Sensor:
            switch (mouse_state.d) {
                case West:
                    return South;
                case East:
                    return North;
                case North:
                    return West;
                case South:
                    return East;
                default:
                    return -1;

            }
        default:
            return -1;
    }
}
bool is_cells_the_same(position a, position b) {
    if (a.x == b.x && a.y == b.y) return True;
    return False;
}

uint8_t manhattan_distance_uint16_t(position a, position b) {
    logger.info(" manhattan ==> (%d, %d,) vs ( %d %d) \n", a.x, a.y, b.x, b.y);
    return (uint8_t) abs(a.x - b.x) + abs(a.y - b.y);
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
