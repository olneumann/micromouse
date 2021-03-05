#ifndef ACTIONS_H
#define	ACTIONS_H
#include "../common/general_definitions.h"
typedef enum {
    MOVE_NONE = -1,
    MOVE_FRONT = 0, // desired parameters should be given
    MOVE_DIAGONAL = 1,
    TURN_LEFT_INPLACE_90 = 4,
    TURN_RIGHT_INPLACE_90 = 5,
    TURN_LEFT_INPLACE_135 = 6,
    TURN_RIGHT_INPLACE_135 = 7,
    TURN_LEFT_INPLACE_180 = 8,
    TURN_RIGHT_INPLACE_180 = 9,
    TURN_LEFT_90 = 10,
    TURN_RIGHT_90 = 12,
    TURN_LEFT_135 = 13,
    TURN_RIGHT_135 = 14,
    TURN_LEFT_180 = 15,
    TURN_RIGHT_180 = 16,
} Action;

void turn_left_n_radians(radians r); // radians
void turn_right_n_radians(radians r) ; // radians

void turn_left_45(void);
void turn_right_45(void);
void turn_left_inplace_45(void);
void turn_right_inplace_45(void);

void turn_left_135(void);
void turn_right_135(void);
void turn_left_inplace_135(void);
void turn_right_inplace_135(void);

void turn_left_90(void);
void turn_right_90(void);
void turn_left_inplace_90(void);
void turn_right_inplace_90(void);

void turn_left_180(void);
void turn_right_180(void);
void turn_left_inplace_180(void);
void turn_right_inplace_180(void);

void move_straight_n_cells(int8_t); // cell number
void move_straight_until_front_wall(void);

void move_straight_diagonal_one_cell(void);

void move_until_front_wall(void);

void move_straight_one_cell(void);

void get_chain_of_actions(void);
void go_back_to_start_position(void);

#endif