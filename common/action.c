#include "action.h"


#define one_cell 20; // once cell distance (16cm) 
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

    int32_t target_distance;    
    target_distance = getDistanceRight() + one_cell;  
    /*target distance is starting point + the distance that needs to be traveled from starting point*/
    
    /*while traveled distance is smaller than the wanted target distance i.e. robot hasnt reached the end*/
    while (getDistanceRight() < target_distance){ 
		set_d_vel_left(0.05f * MAX_SPEED_MS);
        set_d_vel_right(0.05f * MAX_SPEED_MS);
    }
    
	} 
       
    
    
    move = forward;
    
    
}

void action_backward(void){
    control_on(void);
        
    /*setting desired values to a percentage of the maximum velocity of motor defined in motor.h*/
    control_on(void);

    int32_t target_distance;    
    target_distance = getDistanceRight() + one_cell;  
    /*target distance is starting point + the distance that needs to be traveled from starting point*/
    
    
    
            /*while traveled distance is bigger than the wanted target distance * i.e. robot hasnt reached the beginning*/
    while (getDistanceRight() > target_distance){ 
		set_d_vel_left(-0.05f * MAX_SPEED_MS);
        set_d_vel_right(-0.05f * MAX_SPEED_MS);
    }
    
	} 
       
    
    
    move=backward;
    
}


/*turn right*/
void action_turn_right(void){
    control_on(void);
    
    LED_IND2 = LEDON;
    while (getAngleLeft()-getAngleRight() < 90 ){
    set_d_vel_left(0.03f * MAX_SPEED_MS);
    set_d_vel_right(-0.03f * MAX_SPEED_MS);
    }
    
    move = turn_right;
    LED_IND2 = LEDOFF;
}


/*turn left 90 degrees*/
void action_turn_left(void){
    control_on(void);
    LED_IND1 = LEDON;

    while (getAngleLeft()-getAngleRight() > 90 ){
    set_d_vel_left(-0.03f * MAX_SPEED_MS);
    set_d_vel_right(0.03f * MAX_SPEED_MS);
    }
    move = turn_left;
    

    LED_IND1 = LEDOFF;
    
    
                   }

void action_turn_around (void){
control_on(void);
    LED_IND1 = LEDON;

    while (getAngleLeft()-getAngleRight() > 180 ){
    set_d_vel_left(-0.03f * MAX_SPEED_MS);
    set_d_vel_right(0.03f * MAX_SPEED_MS);
    }
    move = turn_left;
    

    LED_IND1 = LEDOFF;
    
    

}



void action_stop(void){
    control_on(void);
    set_d_vel_left(0);
    set_d_vel_right(0);
    d_distance=0;
    
    move = stop;
    
    
                   }


