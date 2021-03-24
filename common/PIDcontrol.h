/* 
 * File:   PIDcontrol.h
 * Author: s-hha
 *
 * Created on 17. März 2021, 14:46
 */


//PID control for motors

#ifndef PIDCONTROL_H
#define	PIDCONTROL_H

#include "../drivers/ranging.h"
#include "../drivers/encoder.h"
#include "../drivers/motor.h"



typedef struct {

    /* controller gains */
    float kp=0.0199;
    float ki=0.0223;
    float kd=0.0042;

    /* derivative low pass filter timer constant*/
    float tau=0.0040;
    
    /*output limits - maximum and minimum values PWM*/
    float outmin;
    float outmax;
    
    /*integratorlimits*/
    float MinInt;
    float MaxInt;    
    
    /*sample time in seconds*/
    float T;
    /*controller memory*/
    float integrator;
    float preverror; //previous error
    float differentiator;
    float prev_m; //previous measurement
    
    /*controller output*/
    float out;
} param_pid;

void PID_Init(param_pid *pid); /*resets function*/
float PID_Update (param_pid *pid, float d_vel, float m_vel); /*output function*/

#endif