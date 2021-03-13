#ifndef MANAGER_H
#define MANAGER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "../common/general_parameters.h"
#include "../common/general_definitions.h"
#include "../common/logger.h"

#include "map_updater.h"
#include "discovery.h"
#include "mouse_state.h"

#if DISCOVERY_SIMULATION
#include "../simulation/simulation_main.h"
#endif

void init_manager(void);

void init_inference(void);

void start_inference(inference_mode mode);

void start_discovery();

#include "actions.h"

Action *decide_next_action(void);

void start_action(Action*);

#endif //MANAGER_H
