/* 
 * File:   PIDcontrol.h
 * Author: s-hha
 *
 * Created on 17. März 2021, 14:46
 */


//PID control for motors

#ifndef PIDCONTROL_H
#define	PIDCONTROL_H


#include <stdbool.h>
#include "../drivers/ranging.h"
#include "../drivers/encoder.h"
#include "../drivers/motor.h"
#include "action.h"


typedef struct {

    /* controller gains */
    float kp=0.0199;
    float ki=0.0223;
    float kd=0.0042;

    /* derivative low pass filter timer constant*/
    float tau=0.0040;
    
    /*output limits - maximum and minimum values PWM*/
    float outmin=-1;
    float outmax=1;
    
    /*integratorlimits*/
    float MinInt;
    float MaxInt;    
    
    /*sample time in seconds*/
    float T;
   
    /*controller memory*/
    
    float integrator_l;
    float integrator_r;
    float preverror_l;
    float preverror_r;
    //previous error
    float differentiator_l;
    float differentiator_r;
    float prev_m_l;
    float prev_m_r;//previous measurement
    
    /*controller output*/
    float out_l;
    float out_r;
} param_pid;

void PID_Init(param_pid *pid); /*resets function*/
float PID_Update (param_pid *pid); /*output function*/


void control_on(void);
void control_off(void);

void get_d_vel_right (void);
void get_d_vel_left (void);
void set_d_vel_left (float desired_l);
void set_d_vel_right (float desired_r);


#endif