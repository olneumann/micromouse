//
// Created by root on 3/22/21.
//
#include "inference.h"
action* chain_of_actions_of_the_shortest_path;
void print_actions(action *head_action) {
    action* temp = head_action;
    while (temp) {
        logger.info("%d (%d %d):(%d %d) ori = %d\n",
                    temp->action_primitive_id,
                    temp->starting_cell.x,
                    temp->starting_cell.y,
                    temp->resulting_cell.x,
                    temp->resulting_cell.y,
                    temp->resulting_direction);
        temp = temp->next;

    }

}

void init_finisher() {
    position the_goal_cell_with_the_shortest_path = get_the_goal_cell_with_the_shortest_path();
    logger.info("---finisher--- %d %d\n\n", the_goal_cell_with_the_shortest_path.x,
                the_goal_cell_with_the_shortest_path.y);
    action *head_action = get_chain_of_actions_to_reach_goal_cell(the_goal_cell_with_the_shortest_path);
    print_actions(head_action);
    chain_of_actions_of_the_shortest_path = head_action;
}

void start_finisher() {
    action* current_action = chain_of_actions_of_the_shortest_path;
    while (current_action) {

#ifndef DISCOVERY_SIMULATION
        move(current_action->action_primitive_id);
#endif
        logger.info("ACTION >>>> %d (%d %d):(%d %d) ori = %d\n",
                    current_action->action_primitive_id,
                    current_action->starting_cell.x,
                    current_action->starting_cell.y,
                    current_action->resulting_cell.x,
                    current_action->resulting_cell.y,
                    current_action->resulting_direction);
        current_action = current_action->next;
    }
}
