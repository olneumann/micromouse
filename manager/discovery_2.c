//
// Created by root on 3/2/21.
//


#include "discovery_2.h"

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

    set_a_wall_along_x(2, 3, 1, 5, 9);
    set_a_wall_along_x(3, 6, 2, 4, 6, 8, 10, 12);
    //set_a_wall(2, 13);
    set_a_wall_along_x(4, 1, 7);
    set_a_wall_along_x(5, 4, 2, 4, 10, 12);
    set_a_wall_along_x(6, 4, 3, 5, 7, 11);
    set_a_wall_along_x(7, 3, 4, 8, 12);
    set_a_wall_along_x(8, 1, 9);
    set_a_wall_along_x(9, 4, 2, 4, 10, 12);
    set_a_wall_along_x(10, 4, 3, 5, 7, 11);
    set_a_wall_along_x(11, 1, 8);
    set_a_wall_along_x(12, 5, 3, 5, 7, 9, 11);

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
    m->number_of_fork_missions = 0;
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

void process_mission(mission *current_mission) {
    state mouse_state = get_mouse_state();
    mission *found_mission_fork;
    position next_cell;
    u_int8_t step;
    print_missions(current_mission);
    printf("\nmission to (%d,%d) from (%d, %d) in %d steps in dir %d \n\n",
           current_mission->target.x,
           current_mission->target.y,
           current_mission->start.x, current_mission->start.y, current_mission->number_of_steps, current_mission->d);
    printf("mouse state (%d %d) dir : %d\n", mouse_state.p.x, mouse_state.p.y, mouse_state.d);
    for (step = 0; step < current_mission->number_of_steps; step++) {
        printf(" -----------------------\n");
        printf("move to (%d, %d )\n", next_cell.x, next_cell.y);
        move_to_one_cell_in_direction(current_mission->d);
        set_visited(get_mouse_state().p);
        found_mission_fork = search_a_mission(current_mission, False);
        if (found_mission_fork) {
            printf("mission %d to (%d,%d) from (%d,%d)  is added to mission : to (%d,%d)  from (%d,%d) \n",
                   current_mission->number_of_fork_missions + 1,
                   found_mission_fork->target.x, found_mission_fork->target.y,
                   found_mission_fork->start.x, found_mission_fork->start.y,
                   current_mission->target.x, current_mission->target.y,
                   current_mission->start.x, current_mission->start.y
            );
            current_mission->fork_missions[current_mission->number_of_fork_missions] = found_mission_fork;
            current_mission->number_of_fork_missions++;
        }
        printf(" --------------end of a step -----------------------\n");
        print_visited_cells();

    }
    printf(" --------------end of a mission -----------------------\n");
    printf(" --------------start of fork missions -----------------------\n");
    process_fork_missions(current_mission);
    printf(" --------------end of fork missions -----------------------\n");
    free(current_mission);
}

void convert_to_an_undo_mission(mission *mission_to_undo) {
    printf("\nundo a mission to (%d,%d) from (%d, %d) in %d steps in dir %d \n\n",
           mission_to_undo->target.x,
           mission_to_undo->target.y,
           mission_to_undo->start.x, mission_to_undo->start.y, mission_to_undo->number_of_steps, mission_to_undo->d);
    position start_cell = mission_to_undo->start;
    mission_to_undo->d = get_opposite_direction(mission_to_undo->d);
    mission_to_undo->start = mission_to_undo->target;
    mission_to_undo->target = start_cell;

}

void process_fork_mission(mission *fork_mission) {

    process_mission(fork_mission);

}

void process_fork_missions(mission *mission_to_fork) {
    convert_to_an_undo_mission(mission_to_fork);
    mission *fork_mission;
    int8_t fork_mission_index;
    int8_t step, number_of_steps, a;
    state mouse_state;
    printf("%d fork missions \n", mission_to_fork->number_of_fork_missions);
    if(mission_to_fork->number_of_fork_missions){
        for (fork_mission_index = mission_to_fork->number_of_fork_missions - 1;
             fork_mission_index >=0; fork_mission_index--) {
            printf("qweee\n");
            for (a = mission_to_fork->number_of_fork_missions - 1;
                 a >=0; a--) {
                printf("qweeeee11 %d %d\n",a, mission_to_fork->number_of_fork_missions);

            }
            printf("qweeeee11 %d\n",fork_mission_index);
            fork_mission = mission_to_fork->fork_missions[fork_mission_index];
            printf("qweeeee125 %d\n",fork_mission_index);

            number_of_steps = manhattan_distance(get_mouse_state().p, fork_mission->start);
            printf("qweeeee12\n");

            printf(" -----------preparation of a fork mission------------\n");

            for (step = 0; step < number_of_steps; step++) { // move to the start position of the fork mission
                move_to_one_cell_in_direction(mission_to_fork->d);
                mouse_state = get_mouse_state();
                printf("move to (%d, %d )\n", mouse_state.p.x, mouse_state.p.y);
                set_visited(mouse_state.p);
            }
            printf(" -----------start of a fork mission------------\n");
            printf("\nfork mission to (%d,%d) from (%d, %d) in %d steps in dir %d \n",
                   fork_mission->target.x,
                   fork_mission->target.y,
                   fork_mission->start.x, fork_mission->start.y, fork_mission->number_of_steps, fork_mission->d);
            process_fork_mission(fork_mission);

            printf(" --------------end of a fork mission -----------------------\n");
            printf("qweeeeee\n");

        }
    }    printf("qweeeeee222\n");

    mouse_state = get_mouse_state();
    printf("qweeeeee22233\n");

    number_of_steps = manhattan_distance(mouse_state.p, mission_to_fork->target);

    printf(" -----------complete the undo mission after fork missions %d------------\n", number_of_steps);

    for (step = 0; step < number_of_steps; step++) { // move to the start position of the fork mission
        move_to_one_cell_in_direction(mission_to_fork->d);
        mouse_state = get_mouse_state();
        printf("move to (%d, %d )\n", mouse_state.p.x, mouse_state.p.y);
        set_visited(mouse_state.p);
    }
    printf(" -----------completed undo mission------------\n");

}

mission *search_a_mission(mission *parent, bool init_search) {//search for undo missions
    position f_wall, r_wall, l_wall;
    mission *mission = NULL;
    position possible_next_cell;
    u_int8_t distance_to_the_possible_next_cell;
    state mouse_state = get_mouse_state();
    r_wall = SIMULATION_get_right_sensor_range_data();
    printf("right sensor first wall ==> (%d, %d) \n", r_wall.x, r_wall.y);
    l_wall = SIMULATION_get_left_sensor_range_data();
    printf("left sensor first wall ==> (%d, %d) \n", l_wall.x, l_wall.y);

    if (init_search) {
        f_wall = SIMULATION_get_front_sensor_range_data();
        printf("front sensor first wall ==> (%d, %d) \n", f_wall.x, f_wall.y);
        possible_next_cell = get_the_most_distant_cell_for_3_walls(f_wall, r_wall, l_wall);
    } else {
        possible_next_cell = get_the_most_distant_cell_for_2_walls(r_wall, l_wall);
    }
    printf(" possible_next_cell ==> (%d, %d) \n", possible_next_cell.x, possible_next_cell.y);

    distance_to_the_possible_next_cell = manhattan_distance(mouse_state.p, possible_next_cell);
    if (distance_to_the_possible_next_cell > 0 && !get_visits(possible_next_cell)) {
        mission = init_mission(parent, possible_next_cell, mouse_state.p);
        printf(" found possible_next_cell ==> (%d, %d, distance: %d) \n", possible_next_cell.x,
               possible_next_cell.y, distance_to_the_possible_next_cell);
    }
    return mission;
}

void run_algo(void) {
    mission *init_mission = search_a_mission(NULL, True);
    set_visited(get_mouse_state().p);
    process_mission(init_mission);
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