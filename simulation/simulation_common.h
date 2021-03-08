//
// Created by root on 3/3/21.
//

#ifndef MM_SIMULATION_COMMON_H
#define MM_SIMULATION_COMMON_H

#include "../common/general_parameters.h"
#include "../common/general_definitions.h"

#if DISCOVERY_SIMULATION
distance get_front_sensor_range_data(void);
distance get_right_sensor_range_data(void);
distance get_left_sensor_range_data(void);
#endif

#include "../manager/manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "time.h"

distance SIMULATION_get_distance_to_the_wall(position, ranging_sensor);
distance get_gaussian_noise(distance);


#endif //MM_SIMULATION_COMMON_H
