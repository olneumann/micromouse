#include "PIDcontrol.h"





void PID_Init(param_pid *pid) {

	/* Clear controller variables */
	pid->integrator_l = 0.0f;
	pid->preverror_l  = 0.0f;

	pid->differentiator_l  = 0.0f;
	pid->prev_m_l = 0.0f;
	pid->out_l = 0.0f;
    
    /*right*/
    	pid->integrator_r = 0.0f;
	pid->preverror_r  = 0.0f;

	pid->differentiator_r  = 0.0f;
	pid->prev_m_r = 0.0f;

	pid->out_r = 0.0f;

}
    /*setting desired velocities in m/s*/
    void set_d_vel_left (float desired_l){
        d_vel_left = desired_l;
    }    
    
    void set_d_vel_right (float desired_r){
        d_vel_right = desired_r;
    }    
    
    
    void get_d_vel_left(void){
        return d_vel_left;
    }
    
    void get_d_vel_right (void){
        return d_vel_right;
    }



float PID_update(param_pid *pid) { //d_vel is desired velocity of the motor
    float m_vel_l = getVelocityLeft();
    float m_vel_r = getVelocityRight();
    float max_vel=21.0487;     
    float out_vel_left;
    float out_vel_right;
    float pwm_left;
    float pwm_right;
    
    /*lane control parameters*/
    float lane;
    float r_left = getRangeLeft(void);
    float r_right = getRangeRight(void);
    float vel_lane_left;
    float vel_lane_right;
    
    
    
    /*desired velocities readings*/
    float d_vel_l = get_d_vel_left();
    float d_vel_r = get_d_vel_right();
    
    /*error left and right*/
    float error_l = d_vel_l - m_vel_l;
    float error_r = d_vel_r - m_vel_r;
    
    /*PID ALGORITHM*/
	
    /*
	Proportional
	*/
    float proportional_l = pid->kp * error_l;
    float proportional_r = pid->kp * error_r;
    
    /*
	* Integral
	*/
    pid->integrator_l += 0.5f * pid->ki * pid->T * (error_l + pid->preverror_l);

	/* Anti-wind-up via integrator clamping */
    if (pid->integrator_l > pid->MaxInt) {

        pid->integrator_l = pid->MaxInt;

    } else if (pid->integrator_l < pid->MinInt) {

        pid->integrator_l = pid->MinInt;

    }
    /*right*/
    pid->integrator_r += 0.5f * pid->ki * pid->T * (error_l + pid->preverror_r);

	/* Anti-wind-up via integrator clamping */
    if (pid->integrator_r > pid->MaxInt) {

        pid->integrator_r = pid->MaxInt;

    } else if (pid->integrator_r < pid->MinInt) {

        pid->integrator_r = pid->MinInt;

    }
    
	/*
	* Derivative (band-limited differentiator)
	*/		
    pid->differentiator_l = -(2.0f * pid->kd * (m_vel_l - pid->prev_m_l)	//derivative on measurement -
                        + (2.0f * pid->tau - pid->T) * pid->differentiator_l)
                        / (2.0f * pid->tau + pid->T);

    /*right*/
    pid->differentiator_r = -(2.0f * pid->kd * (m_vel_r - pid->prev_m_r)	//derivative on measurement -
                        + (2.0f * pid->tau - pid->T) * pid->differentiator_r)
                        / (2.0f * pid->tau + pid->T);


	/*
	* Compute output and apply limits
	*/
    pid->out_l = proportional_l + pid->integrator_l + pid->differentiator_l;

    if (pid->out_l > pid->outmax) {

        pid->out_l = pid->outmax;

    } else if (pid->out_l < pid->outmin) {

        pid->out_l = pid->outmax;

    }
    /*right*/
    pid->out_r = proportional_r + pid->integrator_r + pid->differentiator_r;

    if (pid->out_r > pid->outmax) {

        pid->out_r = pid->outmax;

    } else if (pid->out_r < pid->outmin) {

        pid->out_r = pid->outmax;

    }
    

	/* Store error and measurement for later use */
    pid->preverror_l       = error_l;
    pid->prev_m_l = m_vel_l;
    /*right*/
    pid->preverror_r       = error_r;
    pid->prev_m_r = m_vel_r;
    

	/* Return controller output */
    return pid->out_l;
    return pid->out_r;
    out_vel_left=pid->out_l;
    out_vel_right=pid->out_l;
    
    /*PID ALGORITHM END*/
    
    /*lane keeping (needs tuning)*/
    /*lane keepng best in desired */
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
        
        
        if (pwm_left > 1 ) {
           pwm_left=1;
        }
        if (pwm_right > 1){
            pwm_right=1;
        }
        
        
        driveLeft(pwm_left);
        driveRight(pwm_right);
}

