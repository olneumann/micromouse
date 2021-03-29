/*
 * File:   primitives.h
 * Author: lucia
 *
 * Created on 19. März 2021, 18:49
 */

#ifndef PRIMITIVES_H
#define	PRIMITIVES_H

float get_desired_val(int ctrl);
float get_input_val(int ctrl);
void stop(void);
void turn_left(void);
void turn_right(void);
void turn_around(void);
void move_forward(void);
void move_backward(void);
void move_distance(int distance);

#endif /* PRIMITIVES_H */