#include "action.h"


#define cell_distance 20; // once cell distance (16cm) 
#define turn_distance 20; // distance when mouse turns


int d_vel_left;
int d_vel_right;
//use encoder counter
float d_distance;
enum move_type move;


void action_init(void){
    
    control_off(void);
    motorInit();
    d_vel_left=0;
    d_vel_right=0;
    PID_Init();
    
    
}



void action_forward(void){
    
    
    /*setting desired values to a percentage of the maximum velocity of motor defined in motor.h*/
    control_on(void);
    set_d_vel_left(0.05f * MAX_SPEED_MS);
    set_d_vel_right(0.05f * MAX_SPEED_MS);
    
    
    
    move = forward;
    
    
}

void action_backward(void){
    control_on(void);
    set_d_vel_left(-10);
    set_d_vel_right(-10);
    
    
    
    move=backward;
    
}

void action_right(void){
    control_on(void);
    set_d_vel_left(-10);
    set_d_vel_right(10);
    
    move = turn_right;
    
}

void action_left(void){
    control_on(void);
    set_d_vel_left(10);
    set_d_vel_right(-10);
    
    move = turn_left;
    
    
                   }
void action_stop(void){
    control_on(void);
    set_d_vel_left(0);
    set_d_vel_right(0);
    d_distance=0;
    
    move = stop;
    
    
                   }



void move_distance_front(int32_t start, float distance, float speed){
    int32_t target_distance;
    
    
    target_distance = start + (int32_t)(distance*1e6);
    if (distance > 0) {
		set_d_vel_left(speed);
		while (getDistanceRight() < target_distance);
	} 
    
    else {
		set_d_vel_left(-speed);
		while (getDistanceRight() > target_distance);
	}
    set_d_vel_left(speed);
	   
}

