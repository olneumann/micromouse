#include "PIDcontrol.h"

void PID_Init(param_pid *pid) {

	/* Clear controller variables */
	pid->integrator = 0.0f;
	pid->preverror  = 0.0f;

	pid->differentiator  = 0.0f;
	pid->prev_m = 0.0f;

	pid->out = 0.0f;

}

float PID_update(param_pid *pid, float d_vel, float m_vel) { //d_vel is desired velocity of the motor

	/*
	* Error signal
	*/
    float error = d_vel - m_vel;
    

	/*
	* Proportional
	*/
    float proportional = pid->kp * error;


	/*
	* Integral
	*/
    pid->integrator += 0.5f * pid->ki * pid->T * (error + pid->preverror);

	/* Anti-wind-up via integrator clamping */
    if (pid->integrator > pid->LimitMaxInt) {

        pid->integrator = pid->LimitMaxInt;

    } else if (pid->integrator < pid->LimitMinInt) {

        pid->integrator = pid->LimitMinInt;

    }


	/*
	* Derivative (band-limited differentiator)
	*/
		
    pid->differentiator = -(2.0f * pid->kd * (m_vel - pid->prev_m)	//derivative on measurement -
                        + (2.0f * pid->tau - pid->T) * pid->differentiator)
                        / (2.0f * pid->tau + pid->T);


	/*
	* Compute output and apply limits
	*/
    pid->out = proportional + pid->integrator + pid->differentiator;

    if (pid->out > pid->PWMmax) {

        pid->out = pid->PWMmax;

    } else if (pid->out < pid->PWMmin) {

        pid->out = pid->PWMmax;

    }

	/* Store error and measurement for later use */
    pid->preverror       = error;
    pid->prev_m = m_vel;

	/* Return controller output */
    return pid->out;

}

