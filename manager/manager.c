#include "manager.h"

static volatile state mouse_state = {{START_POSITION_X,START_POSITION_Y},START_DIRECTION };

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
void move_to_one_cell_in_direction(direction d){
    position cell = what_is_the_position_after_moving_one_step_in_the_direction(mouse_state.p,d);
    mouse_state.p.x = cell.x;
    mouse_state.p.y = cell.y;
    mouse_state.d = d;
}

state get_mouse_state(){
    return mouse_state;
}
void start_discovery() {

}
position get_start_cell(){
    return (position) {START_POSITION_X,START_POSITION_Y};
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