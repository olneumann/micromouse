#ifndef ACTIONS_H
#define	ACTIONS_H


typedef enum {
    MOVE_NONE = -1,
    MOVE_FRONT = 0, // desired parameters should be given
    TURN_LEFT_INPLACE_90 = 1,
    TURN_RIGHT_INPLACE_90 = 2,
    TURN_LEFT = 3, //desired params should be given
    TURN_RIGHT = 4, //desired params should be given
    TURN_LEFT_INPLACE_180 = 5,
    TURN_RIGHT_INPLACE_180 = 6,
    MOVE_LEFT_DIAGONAL_45 = 7,
    MOVE_RIGHT_DIAGONAL_45 = 8
} Action;

void turn_left_n_radians(Radians); // radians
void turn_right_n_radians(Radians); // radians

void turn_left_inplace_90(void);
void turn_right_inplace_90(void);

void turn_left_inplace_180(void);
void turn_right_inplace_180(void);

void move_straight_n_cells(int8_t); // cell number
void move_straight_until_front_wall(void);

void move_straight_diagonal(void);
void move_until_front_wall(void);
void move_straight_one_cell(void);

void get_chain_of_actions(void);
void go_back_to_start_position(void);

#endif