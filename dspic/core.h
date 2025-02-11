/*
 * File:   core.h
 * Author: oliver
 *
 * Created on 8. Januar 2021, 09:59
 */

#ifndef CORE_H
#define CORE_H

#include <stdint.h>

#define CONTROL_LOOP_PERIODE_MS         (uint16_t)20 
#define CONTROL_LOOP_FREQ_HZ            (uint16_t)1/(CONTROL_LOOP_PERIODE_MS * 1e-3)
#define SETPOINT_UPDATE_RATE            (uint8_t)2
#define ENCODER_UPDATE_PERIODE_MS       (uint16_t)10
#define ENCODER_UPDATE_FREQ_HZ          (uint16_t)1/(ENCODER_UPDATE_PERIODE_MS * 1e-3) 
#define RANGING_UPDATE_PERIODE_MS       (uint16_t)200 // debug; normal double sensing?
#define RANGING_UPDATE_FREQ_HZ          (uint16_t)1/(RANGING_UPDATE_PERIODE_MS * 1e-3) 

void debug(void);

void control_loop(uint16_t freq);
void encoder_loop(uint16_t freq);
void ranging_loop(uint16_t freq);

void explore(void);
void inference(void);

#endif	/* CORE_H */

