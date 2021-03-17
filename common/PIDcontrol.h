/* 
 * File:   PIDcontrol.h
 * Author: s-hha
 *
 * Created on 17. März 2021, 14:46
 */

#ifndef PIDCONTROL_H
#define	PIDCONTROL_H


typedef struct {

    /* controller gains */
    float kp;
    float ki;
    float kd;

    /* derivative low pass filter timer constant*/
    float tau;
    
    /*output limits - maximum and minimum values PWM*/
    float PWMmin;
    float PWMmax;
    
    /*integratorlimits*/
    float LimitMinInt;
    float LimitMaxInt;    
    
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