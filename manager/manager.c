#include "manager.h"

void init_manager() {
    state mouse_state = get_mouse_state();
    logger.info("mouse state (%d %d) dir : %d\n", mouse_state.p.x, mouse_state.p.y, mouse_state.d);
    init_shortest_path_utils();
    init_visited_cells();
    print_visited_cells();
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



void start_discovery() {
#if (DISCOVERY_SIMULATION==1)
    simulation_main();
#else
    run_discovery_algo();
#endif
}

void init_inference() {

}

void start_inference(inference_mode mode) {

}

Action *decide_next_action() {
    return 0;
}

void start_action(Action *action) {

}

uint8_t manhattan_distance_uint16_t(position a, position b) {
    logger.info(" manhattan ==> (%d, %d,) vs ( %d %d) \n", a.x, a.y, b.x, b.y);
    return (uint8_t) abs(a.x - b.x) + abs(a.y - b.y);
}