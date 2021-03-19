#include "action.h"

#include "motor.h"
#include "encoder.h"


int d_vel_left;
int d_vel_right;

//use encoder counter?



void action_init(){
    
    void motorInit(uint16_t kfpwm);
    d_vel_left=0;
    d_vel_right=0;
 
    
    
}



void action_forward();

void action_backward();

void action_right();

void action_left();

void action_stop();

