#include "action.h"
#include "motor.h"
#include "encoder.h"




int d_vel_left;
int d_vel_right;
float percent_left;     //desired percentage to drive left motor
float percent_right;    //desired percentage to drive right motor
//use encoder counter


//change placeholders to pid input

void action_init(){
    
    motorInit();
    d_vel_left=0;
    d_vel_right=0;
    
    
    
}



void action_forward(){
    
    percent_right=0.5;
    percent_left=0.5;
    
    driveRight(percent_right);
    driveLeft(percent_left);
    
}

void action_backward(){
    
    percent_right=-0.5;
    percent_left=-0.5;
    driveRight(percent_right);
    driveLeft(percent_left);
    
    
}

void action_right(){
    
    percent_right=-0.5;
    percent_left=0.5;
    driveRight(percent_right);
    driveLeft(percent_left);
    
    
}

void action_left(){
    
    percent_right=0.5;
    percent_left=-0.5;
    driveRight(percent_right);
    driveLeft(percent_left);
    
    
                   }
void action_stop(){
    
    percent_right=0;
    percent_left=0;
    driveRight(percent_right);
    driveLeft(percent_left);
    
    
                   }
