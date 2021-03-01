#include "manager.h"

static volatile position_t current_position = {0,0, North};
static volatile walls_around_t  current_walls_around = {False, True, True, True};

void init_manager() {
    logger.info("manager init started");
    init_walls();
    logger.info("map init finished");
    init_solver();
    logger.info("solver init finished");
}

void start_discovery() {

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