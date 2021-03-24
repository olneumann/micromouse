#include "PIDcontrol.h"





void PID_Init(param_pid *pid) {

	/* Clear controller variables */
	pid->integrator = 0.0f;
	pid->preverror  = 0.0f;

	pid->differentiator  = 0.0f;
	pid->prev_m = 0.0f;

	pid->out = 0.0f;

}



float PID_update(param_pid *pid, float d_vel) { //d_vel is desired velocity of the motor

    float m_vel_l = getVelocityLeft();
    float m_vel_r = getVelocityRight();
    float max_vel=21.0487;
    float m_vel= (m_vel_l+m_vel_l)/2;       //average velocity of both motors
    float out_vel_left;
    float out_vel_right;
    float pwm_left, pwm_right;
    
    float error = d_vel - m_vel;
    
    /*lane control parameters*/
    float lane;
    float r_left = getRangeLeft(void);
    float r_right = getRangeRight(void);
    float vel_lane_left;
    float vel_lane_right;
    
    
    /*PID ALGORITHM*/
	
    /*
	Proportional
	*/
    float proportional = pid->kp * error;
    
    /*
	* Integral
	*/
    pid->integrator += 0.5f * pid->ki * pid->T * (error + pid->preverror);

	/* Anti-wind-up via integrator clamping */
    if (pid->integrator > pid->MaxInt) {

        pid->integrator = pid->MaxInt;

    } else if (pid->integrator < pid->MinInt) {

        pid->integrator = pid->MinInt;

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

    if (pid->out > pid->outmax) {

        pid->out = pid->outmax;

    } else if (pid->out < pid->outmin) {

        pid->out = pid->outmax;

    }

	/* Store error and measurement for later use */
    pid->preverror       = error;
    pid->prev_m = m_vel;

	/* Return controller output */
    return pid->out;
    
    out_vel_left=pid->out;
    out_vel_right=pid->out;
    
    /*PID ALGORITHM END*/
    
    /*lane keeping (needs tuning)*/
    
    if (( r_left > 10 ) && (r_right < 10 ) ){ 
			out_vel_left = 0;
			out_vel_right = 0.01;

		}

	if (( r_left < 10 ) && (r_right > 10 ) ){ 
			out_vel_left = 0.01;
			out_vel_right = 0;

		}
    else {
        out_vel_left=0;
        out_vel_right=0;
    }

    
    /*output of velocity for the motor as PWM (percent)*/
   
        pwm_left    =   out_vel_left/max_vel + out_vel_left;
        pwm_right   =   out_vel_right/max_vel + out_vel_right;

        
        
        driveLeft(pwm_left);
        driveRight(pwm_right);
}

