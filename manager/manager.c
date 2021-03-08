#include "manager.h"

static volatile state mouse_state = {{START_POSITION_X, START_POSITION_Y}, START_DIRECTION};

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
void init_manager() {

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
    switch (sensor) {
        case Front:
            return mouse_state.d;
        case Right:
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
        case Left:
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

void move_to_one_cell_in_direction(direction d) {
    position cell = what_is_the_position_after_moving_one_step_in_the_direction(mouse_state.p, d);
    mouse_state.p.x = cell.x;
    mouse_state.p.y = cell.y;
    mouse_state.d = d;
}

state get_mouse_state() {
    return mouse_state;
}

void start_discovery() {

}

position get_start_cell() {
    return (position) {START_POSITION_X, START_POSITION_Y};
}

void do_discovery() {

}

void start_inference() {

}

void do_inference(inference_mode mode) {

}

Action *decide_next_action() {

}

void start_action(Action *action) {

}
void init_goal_cells(){

}
void turn_towards(direction d) {
    mouse_state.d = d;
    switch (mouse_state.d) {
        case West:
            switch (d) {
                case West:
                    break;
                case East:
                    break;
                case North:
                    break;
                case South:
                    break;
                default:
                    break;
            }
            break;
        case East:
            switch (mouse_state.d) {
                case West:
                    break;
                case East:
                    break;
                case North:
                    break;
                case South:
                    break;
                default:
                    break;
            }
            break;

        case North:
            switch (mouse_state.d) {
                case West:
                    break;
                case East:
                    break;
                case North:
                    break;
                case South:
                    break;
                default:
                    break;
            }
            break;

        case South:
            switch (mouse_state.d) {
                case West:
                    break;
                case East:
                    break;
                case North:
                    break;
                case South:
                    break;
                default:
                    break;
            }
            break;

        default:
            break;
    }
}

uint8_t manhattan_distance_uint16_t(position a, position b) {
    printf(" manhattan ==> (%d, %d,) vs ( %d %d) \n", a.x, a.y, b.x, b.y);
    return (uint8_t) abs(a.x - b.x) + abs(a.y - b.y);
}

distance get_front_sensor_range_distance() {
    return 0;
}

distance get_right_sensor_range_distance() {
    return 0;
}

distance get_left_sensor_range_distance() {
    return 0;
}