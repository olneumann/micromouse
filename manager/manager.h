#ifndef MANAGER_H
#define MANAGER_H

#include "map_updater.h"
#include "solver.h"
#include "actions.h"
#include "../control/pid.h"
#include "general_parameters.h"



typedef enum {
    Normal = 0, Fast = 1, BlindlyFast = 2
} Inference_Mode;

void init_manager(void);

void start_inference(void);

void do_inference(Inference_Mode);

void do_discovery(void);

void start_discovery(void);

Action *decide_next_action(void);

void start_action(Action *);

#endif //MANAGER_H
