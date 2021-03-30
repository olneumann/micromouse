/* 
 * File:   action.h
 * Author: s-hha
 *
 * Created on 17. März 2021, 21:38
 */

#ifndef ACTION_H
#define	ACTION_H

#include <stdio.h>


#include "../drivers/motor.h"
#include "../mana" /*manager*/
#include "../drivers/encoder.h"
#include "PIDcontrol.h"
#include "../drivers/ranging.h"
#include "../drivers/encoder.h"


 enum move_type {
    turn_left,
    turn_right,
    forward,
    backward,
    stop
};



void action_init(void);

void action_forward(void);

void action_backward(void);

void action_turn_left(void);

void action_turn_right(void);

void action_turn_around(void);





#endif	/* ACTION_H */

