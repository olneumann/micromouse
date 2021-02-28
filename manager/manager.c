#include "manager.h"
#include "logger.h"


void init_manager() {
    logger.info("manager init started");
    init_map();
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
void do_inference(Inference_Mode mode) {

}

Action *decide_next_action() {

}

void start_action(Action *action) {

}