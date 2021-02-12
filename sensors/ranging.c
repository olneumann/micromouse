/*
 * File:   ranging.c
 * Author: oliver
 *
 * Created on 2. Januar 2021, 17:00
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

//#include "../drivers/ranging/vl53l0x_api.h"
//#include "../drivers/ranging/vl53l0x_platform.h"

#include "ranging.h"

// TODO: Bootstrap - remapping of i2c addresses for multiple sensors

// TODO: Continuous Ranging - functions for PID loop