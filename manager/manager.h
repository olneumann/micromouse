/*
 * File:   manager.h
 * Author: yigit
 *
 * Created on 2. March 2021, 17:00
 */

#ifndef MANAGER_H
#define MANAGER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "../manager/manager_parameters.h"
#include "../manager/manager_definitions.h"

#include "map_updater.h"
#include "discovery.h"
#include "inference.h"
#include "mouse_state.h"
#include "actions.h"

#if DISCOVERY_SIMULATION
#include "../simulation/simulation_main.h"
#endif

void initManager(void);
void start_discovery(void);
void start_inference(void);

#endif //MANAGER_H
