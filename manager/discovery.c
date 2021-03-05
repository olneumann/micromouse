//
// Created by root on 3/2/21.
//


#include "discovery.h"

static volatile uint8_t visited_cells[MAZE_SIZE][MAZE_SIZE];

void init_visited_cells(void) {
    int i, j;
    for (i = 0; i < MAZE_SIZE; i++) {
        for (j = 0; j < MAZE_SIZE; j++) {
            visited_cells[i][j];
        }
    }
}

void print_visited_cells(void) {
    int i, j;
    for (j = MAZE_SIZE - 1; j >= 0; j--) {
        printf("\n");
        for (i = 0; i < MAZE_SIZE; i++) {
            printf("%d ", visited_cells[i][j]);
        }
    }
    printf("\n");

}

void set_the_map(void) { // 5v5

    set_a_wall(2, 1);
    set_a_wall(5, 2);
    set_a_wall(7, 2);
    set_a_wall(2, 3);
    set_a_wall(8, 3);
    set_a_wall(3, 4);
    set_a_wall(7, 4);
    set_a_wall(4, 5);
    set_a_wall(6, 5);
    set_a_wall(8, 5);
    set_a_wall(3, 6);
    set_a_wall(5, 6);
    set_a_wall(2, 7);
    set_a_wall(6, 7);
    set_a_wall(8, 7);
    set_a_wall(3, 8);
    set_a_wall(5, 8);

}
void set_the_map_2(void) { //7v7

    set_a_wall_along_x(2,3, 1, 5,9);
    set_a_wall_along_x(3,6, 2,4,6,8,10,12);
    set_a_wall(2,13);
    set_a_wall_along_x(4,1, 7);
    set_a_wall_along_x(5,4, 2,4,10,12);
    set_a_wall_along_x(6,4, 3,5,7,11);
    set_a_wall_along_x(7,3, 4,8,12);
    set_a_wall_along_x(8,1, 9);
    set_a_wall_along_x(9,4, 2,4,10,12);
    set_a_wall_along_x(10,4, 3,5,7,11);
    set_a_wall_along_x(11,1, 8);
    set_a_wall_along_x(12,5, 3,5,7,9,11);

}

uint8_t manhattan_distance(position a, position b) {
    printf(" manhattan ==> (%d, %d,) vs ( %d %d) \n", a.x, a.y, b.x, b.y);
    return (u_int8_t) abs(a.x - b.x) + abs(a.y - b.y);
}

position get_the_cell_by_the_wall_related_to_mouse_orientation(position wall) {
    state mouse_state = get_mouse_state();
    uint8_t mouse_x = mouse_state.p.x * 2 + 1, mouse_y = mouse_state.p.y * 2 + 1, wall_x = wall.x, wall_y = wall.y;
    position cell;
    printf(" mouse  in maze coordinate space ==> (%d, %d)\n", mouse_x, mouse_y);

    if (mouse_x > wall_x) {
        cell.y = (wall_y - 1) / 2;
        cell.x = (wall_x) / 2;
    } else if (mouse_x < wall_x) {

        cell.x = (wall_x / 2) - 1;
        cell.y = (wall_y - 1) / 2;

    } else if (mouse_y > wall_y) {

        cell.x = (wall_x - 1) / 2;
        cell.y = (wall_y) / 2;
    } else if (mouse_y < wall_y) {

        cell.y = (wall_y / 2) - 1;
        cell.x = (wall_x - 1) / 2;
    } else {
        cell.x = 255;
        cell.y = 255;
    }
    printf(" get cell by wall ==> (%d, %d)\n", cell.x, cell.y);

    return cell;
}

direction get_direction_btw_start_and_end_cells(position start, position end) {
    printf(" get_direction ==> (%d, %d,) ( %d %d) \n", start.x, start.y, end.x, end.y);

    if (start.x > end.x && start.y == end.y) {
        return West;
    } else if (start.x < end.x && start.y == end.y) {
        return East;
    } else if (start.x == end.x && start.y < end.y) {
        return North;
    } else if (start.x == end.x && start.y > end.y) {
        return South;
    } else if (start.x == end.x && start.y == end.y) {
        return get_mouse_state().d;
    } else return -1;
}

position get_the_most_distant_cell_for_2_walls(position r_wall, position l_wall) {
    u_int8_t ultimate_visits = 255;
    position the_cell, r_cell, l_cell;
    u_int8_t visits;

    r_cell = get_the_cell_by_the_wall_related_to_mouse_orientation(r_wall);
    printf(" l_cell ==> (%d, %d) \n", r_cell.x, r_cell.y);
    visits = get_visits(r_cell);
    if (visits < ultimate_visits) {
        ultimate_visits = visits;
        the_cell = r_cell;
    }

    l_cell = get_the_cell_by_the_wall_related_to_mouse_orientation(l_wall);
    printf(" l_cell ==> (%d, %d) \n", l_cell.x, l_cell.y);
    visits = get_visits(l_cell);
    if (visits < ultimate_visits) {
        ultimate_visits = visits;
        the_cell = l_cell;
    }
    printf(" a cell to go ==> (%d, %d) \n", the_cell.x, the_cell.y);
    return the_cell;
}

position get_the_most_distant_cell_for_3_walls(position f_wall, position r_wall, position l_wall) {

    u_int8_t ultimate_visits = 255;
    position the_cell, f_cell, r_cell, l_cell;
    u_int8_t visits;

    f_cell = get_the_cell_by_the_wall_related_to_mouse_orientation(f_wall);
    visits = get_visits(f_cell);

    printf(" f_cell ==> (%d, %d) visits : %d\n", f_cell.x, f_cell.y, visits);

    if (visits < ultimate_visits) {

        ultimate_visits = visits;
        the_cell = f_cell;
    }

    r_cell = get_the_cell_by_the_wall_related_to_mouse_orientation(r_wall);
    visits = get_visits(r_cell);

    printf(" r_cell ==> (%d, %d) visits : %d\n", r_cell.x, r_cell.y, visits);
    if (visits < ultimate_visits) {
        ultimate_visits = visits;
        the_cell = r_cell;
    }

    l_cell = get_the_cell_by_the_wall_related_to_mouse_orientation(l_wall);
    visits = get_visits(l_cell);

    printf(" l_cell ==> (%d, %d) visits : %d\n", l_cell.x, l_cell.y, visits);
    if (visits < ultimate_visits) {
        ultimate_visits = visits;
        the_cell = l_cell;
    }
    printf(" a cell to go ==> (%d, %d) \n", the_cell.x, the_cell.y);

    return the_cell;
}

direction get_opposite_direction(direction d) {
    switch (d) {
        case East:
            return West;
        case West:
            return East;
        case North:
            return South;
        case South:
            return North;
        default:
            return -1;
    }
}


mission *init_mission(mission *parent, position target, position start) {
    mission *m = malloc(sizeof(mission));
    m->parent = parent;
    m->target = target;
    m->start = start;
    m->d = get_direction_btw_start_and_end_cells(start, target);
    m->number_of_steps = manhattan_distance(start, target);
    m->distance_to_last_seen_cell_to_visit = 0;
    return m;
}


uint8_t get_visits(position cell) {
    printf("is visited (%d, %d )\n", cell.x, cell.y);

    return visited_cells[cell.x][cell.y];
}

void set_visited(position cell) {
    visited_cells[cell.x][cell.y] += 1;

}

bool is_cells_the_same(position a, position b) {
    if (a.x == b.x && a.y == b.y) return True;
    return False;
}

void print_missions(mission *mission_tail) {
    mission *parent;

    printf("missions : ");

    while (mission_tail) {
        printf(" to (%d,%d) from (%d, %d) <<=", mission_tail->target.x, mission_tail->target.y, mission_tail->start.x,
               mission_tail->start.y);
        mission_tail = mission_tail->parent;
    }
    printf("\n");
}

void run_algo(void) {
    position f_wall, r_wall, l_wall;
    mission *mission_tail, *mission_parent;
    position possible_next_cell, next_mission_target_cell, next_mission_start_cell;
    direction d;
    bool volatile undo_mission = False, found_next_cell = False, coming_home_mission = False, end_of_discovery=False;
    u_int8_t step, distance_to_the_possible_next_cell;
    state mouse_state = get_mouse_state();
    set_visited(mouse_state.p);
    f_wall = SIMULATION_get_front_sensor_range_data();
    printf("front sensor first wall ==> (%d, %d) \n", f_wall.x, f_wall.y);
    r_wall = SIMULATION_get_right_sensor_range_data();
    printf("right sensor first wall ==> (%d, %d) \n", r_wall.x, r_wall.y);
    l_wall = SIMULATION_get_left_sensor_range_data();
    printf("left sensor first wall ==> (%d, %d) \n", l_wall.x, l_wall.y);

    possible_next_cell = get_the_most_distant_cell_for_3_walls(f_wall, r_wall, l_wall);
    printf(" possible_next_cell ==> (%d, %d) \n", possible_next_cell.x, possible_next_cell.y);
    found_next_cell = True;
    mission_tail = init_mission(NULL, possible_next_cell, mouse_state.p);
    int i = 0;
    while (!end_of_discovery) {
        found_next_cell = False;
        printf("%smission to (%d,%d) from (%d, %d) in %d steps in dir %d \n", undo_mission ? "undo " : "",
               mission_tail->target.x,
               mission_tail->target.y,
               mission_tail->start.x, mission_tail->start.y, mission_tail->number_of_steps, mission_tail->d);
        for (step = 0; step < mission_tail->number_of_steps; step++) {

            mouse_state = get_mouse_state();
            printf("mouse state (%d %d) dir : %d\n", mouse_state.p.x, mouse_state.p.y, mouse_state.d);
            printf(" -----------------------\n");
            position next_cell = what_is_the_position_after_moving_one_step_in_the_direction(mouse_state.p,
                                                                                             mission_tail->d);
            printf("moved to (%d, %d )\n", next_cell.x, next_cell.y);
            move_to_the_cell_in_direction(next_cell, mission_tail->d);
            mouse_state = get_mouse_state();
            set_visited(mouse_state.p);
            printf(" pos ==> (%d, %d) \n", mouse_state.p.x, mouse_state.p.y);

            r_wall = SIMULATION_get_right_sensor_range_data();
            printf(" ==> (%d, %d) \n", r_wall.x, r_wall.y);
            l_wall = SIMULATION_get_left_sensor_range_data();
            printf(" ==> (%d, %d) \n", l_wall.x, l_wall.y);
            if (step == mission_tail->number_of_steps - 1) {
                f_wall = SIMULATION_get_front_sensor_range_data();
                printf(" ==> (%d, %d) \n", f_wall.x, f_wall.y);
                possible_next_cell = get_the_most_distant_cell_for_3_walls(f_wall, r_wall, l_wall);
            } else {
                possible_next_cell = get_the_most_distant_cell_for_2_walls(r_wall, l_wall);
            }
            distance_to_the_possible_next_cell = manhattan_distance(mouse_state.p, possible_next_cell);
            if (distance_to_the_possible_next_cell > 0 && (!get_visits(possible_next_cell))) {
                mission_tail->distance_to_last_seen_cell_to_visit = distance_to_the_possible_next_cell;
                mission_tail->the_start_cell_for_the_last_seen_cell_to_visit = mouse_state.p;
                mission_tail->last_seen_to_visit_cell = possible_next_cell;
                found_next_cell = True;
                printf(" found possible_next_cell ==> (%d, %d, distance: %d) \n", possible_next_cell.x,
                       possible_next_cell.y, distance_to_the_possible_next_cell);
            }
            printf(" --------------end of a step -----------------------\n");
            print_visited_cells();

        } // END OF A MISSION
        printf(" --------------end of a mission -----------------------\n");

        mouse_state = get_mouse_state();
        if (found_next_cell && undo_mission) {// undo mission -> found
            printf(" desired mission  ==> (%d, %d,) to ( %d %d) \n", mouse_state.p.x, mouse_state.p.y,
                   mission_tail->last_seen_to_visit_cell.x, mission_tail->last_seen_to_visit_cell.y);
            if(!mission_tail->parent){
                mission_parent=NULL;
            }
            else{
                mission_parent = mission_tail->parent; // parent more
            }

            if (is_cells_the_same(mission_tail->the_start_cell_for_the_last_seen_cell_to_visit, mouse_state.p)) {
                next_mission_target_cell = mission_tail->last_seen_to_visit_cell;
                next_mission_start_cell = mouse_state.p;
            } else {
                printf(" sub mission  ==> (%d, %d,) to ( %d %d) \n", mouse_state.p.x, mouse_state.p.y,
                       mission_tail->the_start_cell_for_the_last_seen_cell_to_visit.x,
                       mission_tail->the_start_cell_for_the_last_seen_cell_to_visit.y);
                next_mission_target_cell = mission_tail->the_start_cell_for_the_last_seen_cell_to_visit;
                next_mission_start_cell = mouse_state.p;

            }
            //free(mission_tail->parent);
            free(mission_tail);
            mission_tail = init_mission(mission_parent, next_mission_target_cell, next_mission_start_cell);
            undo_mission = False;

        } else if (!found_next_cell && undo_mission) {// undo mission -> not found

            if(coming_home_mission){
                free(mission_tail);
                mission_tail = NULL;
                end_of_discovery = True;
            }
            else if(!mission_tail->parent && !coming_home_mission){ // coming home
                mission_parent=NULL;
                printf(" coming home mission style 1 ! \n");
                next_mission_target_cell = get_start_cell();
                next_mission_start_cell = mouse_state.p;
                mission_tail = init_mission(mission_parent, next_mission_target_cell, next_mission_start_cell);
                coming_home_mission = True;
            }
            else if(mission_tail->parent->parent){
                mission_parent = mission_tail->parent->parent;
                //if (mission_parent->parent){
                //    next_mission_target_cell = mission_parent->parent->start;
                //
                //}
                //else{
                // next_mission_target_cell = mission_parent->start;

                //}
                next_mission_target_cell = mission_parent->start;


                next_mission_start_cell = mouse_state.p;
                free(mission_tail->parent);
                free(mission_tail);
                printf(" undo mission  ==> (%d, %d,) to ( %d %d) \n", next_mission_start_cell.x, next_mission_start_cell.y,
                       next_mission_target_cell.x, next_mission_target_cell.y);
                mission_tail = init_mission(mission_parent, next_mission_target_cell, next_mission_start_cell);
            }
            else if(mission_tail->parent){ //coming home
                mission_parent=NULL;
                next_mission_target_cell = mission_tail->parent->start;
                next_mission_start_cell = mouse_state.p;
                printf(" coming home mission style 2! \n");
                free(mission_tail->parent);
                free(mission_tail);
                mission_tail = init_mission(mission_parent, next_mission_target_cell, next_mission_start_cell);
                coming_home_mission = True;
            }


            undo_mission = True;

        } else if (found_next_cell && !undo_mission) { //mission -> found

            printf(" desired mission  ==> (%d, %d) to ( %d %d) \n", mouse_state.p.x, mouse_state.p.y,
                   mission_tail->last_seen_to_visit_cell.x, mission_tail->last_seen_to_visit_cell.y);

            if (is_cells_the_same(mission_tail->the_start_cell_for_the_last_seen_cell_to_visit, mouse_state.p)) {
                next_mission_target_cell = mission_tail->last_seen_to_visit_cell;
                next_mission_start_cell = mouse_state.p;
            } else {
                printf(" sub mission  ==> (%d, %d,) to ( %d %d) \n", mouse_state.p.x, mouse_state.p.y,
                       mission_tail->the_start_cell_for_the_last_seen_cell_to_visit.x,
                       mission_tail->the_start_cell_for_the_last_seen_cell_to_visit.y);
                next_mission_target_cell = mission_tail->the_start_cell_for_the_last_seen_cell_to_visit;
                next_mission_start_cell = mouse_state.p;
            }
            mission_tail = init_mission(mission_tail, next_mission_target_cell, next_mission_start_cell);
            undo_mission = False;

        } else if (!found_next_cell && !undo_mission) { //mission -> not found
            next_mission_target_cell = mission_tail->start;
            next_mission_start_cell = mouse_state.p;
            printf(" undo mission  ==> (%d, %d,) to ( %d %d) \n", next_mission_start_cell.x, next_mission_start_cell.y,
                   next_mission_target_cell.x, next_mission_target_cell.y);
            mission_tail = init_mission(mission_tail, next_mission_target_cell, next_mission_start_cell);
            undo_mission = True;
        } else {
            printf("unknown ! \n");
        }
        print_missions(mission_tail);
        if(++i==12){
            break;
        }
    }
    printf("\n-----end of discovery----\n\n ");
    print_missions(mission_tail);
    print_visited_cells();
}

int main() {
    state mouse_state = get_mouse_state();
    printf("mouse state (%d %d) dir : %d\n", mouse_state.p.x, mouse_state.p.y, mouse_state.d);
    init_walls();
    init_visited_cells();
    print_visited_cells();
    set_the_map_2();
    run_algo();
    return 0;
}