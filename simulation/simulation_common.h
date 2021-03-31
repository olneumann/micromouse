/*
 * File:   simulation_common.h
 * Author: yigit
 *
 * Created on 2. March 2021, 17:00
 */

#ifndef MM_SIMULATION_COMMON_H
#define MM_SIMULATION_COMMON_H

#include "../manager/manager_parameters.h"
#include "../manager/manager_definitions.h"
#include "../manager/mouse_state.h"
#include "../manager/map_updater.h"
#include "simulation_maps.h"

#if DISCOVERY_SIMULATION
distance get_front_sensor_range_data(void);
distance get_right_sensor_range_data(void);
distance get_left_sensor_range_data(void);
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "time.h"

distance SIMULATION_get_distance_to_the_wall(position, ranging_sensor);
distance get_gaussian_noise(distance);

#endif //MM_SIMULATION_COMMON_H
