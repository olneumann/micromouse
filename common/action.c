#include "action.h"


int d_vel_left;
int d_vel_right;
float percent_left;     //desired percentage to drive left motor
float percent_right;    //desired percentage to drive right motor
//use encoder counter


void action_init(){
    
    motorInit();
    d_vel_left=0;
    d_vel_right=0;
    PID_Init();
    
    
}



void action_forward(){
    
    set_d_vel_left(10);
    set_d_vel_right(10);
    
 
    
    
    
}

void action_backward(){
    
    set_d_vel_left(-10);
    set_d_vel_right(-10);
    
    
    
}

void action_right(){
    
    set_d_vel_left(-10);
    set_d_vel_right(10);
    
    
}

void action_left(){
    
    set_d_vel_left(10);
    set_d_vel_right(-10);
    
    
    
                   }
void action_stop(){
    
    set_d_vel_left(0);
    set_d_vel_right(0);
   
    
    
                   }
