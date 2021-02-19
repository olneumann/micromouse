#ifndef ACTIONS_H
#define	ACTIONS_H

void static_left_turn_90_degrees(void);
void static_right_turn_90_degrees(void);
void static_left_turn_180_degrees(void);
void static_right_turn_180_degrees(void);

void move_straight(void);
void move_straight_diagonal(void);
void move_until_front_wall(void);
void move_straight_one_cell(void);

void get_chain_of_actions(void);
void go_back_to_start_position(void);