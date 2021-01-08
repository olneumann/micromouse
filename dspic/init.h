/*
 * File:   init.h
 * Author: oliver
 *
 * Created on 8. Januar 2021, 09:59
 */
 
#ifndef INIT_H
#define	INIT_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    SYSTEM_STATE_INITIALISING   = 0,
    SYSTEM_STATE_CONFIG_LOADED  = (1 << 0),
    SYSTEM_STATE_SENSORS_READY  = (1 << 1),
    SYSTEM_STATE_MOTORS_READY   = (1 << 2),
    SYSTEM_STATE_TRANSPONDER_ENABLED = (1 << 3),
    SYSTEM_STATE_READY          = (1 << 7)
} systemState_e;

extern uint8_t systemState;

void init(void);
void processLoopback(void);

#endif	/* INIT_H */

