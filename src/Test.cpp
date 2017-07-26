/*
 * Test.cpp
 *
 *  Created on: Jul 26, 2017
 *      Author: hasnain
 */

#include <stdio.h>
#include "Test.h"
#include "KimbleBase.h"

int8_t Test::Test_kill_opponent_peg(KimbleBase *game)
{
    game->setup_board(game->board);
    Player_t *player_1, *player_2;
    game->players.access_player_data(0, player_1);
    game->players.access_player_data(1, player_2);

    player_1->meta_data.pegs[0].peg_position = 10;
    player_1->meta_data.pegs_at_home-=1;
    player_1->meta_data.pegs_in_normal_lane+=1;
    player_1->meta_data.pegs[0].peg_state = IN_CIRCULATION;

    game->board->pos_normal_lane[10].occupied = true;
    game->board->pos_normal_lane[10].occupant[0].peg_id = 0;
    game->board->pos_normal_lane[10].occupant[0].player_id = 0;
    game->board->pos_normal_lane[10].pos = 10;

    player_2->meta_data.pegs[1].peg_position = 8;
    player_2->meta_data.pegs_at_home-=1;
    player_2->meta_data.pegs_in_normal_lane+=1;
    player_2->meta_data.pegs[1].peg_state = IN_CIRCULATION;

    game->board->pos_normal_lane[8].occupied = true;
    game->board->pos_normal_lane[8].occupant[0].peg_id  = 1;
    game->board->pos_normal_lane[8].occupant[0].player_id = 1;
    game->board->pos_normal_lane[8].pos = 8;


    int8_t retcode = game->move_peg_to_position(player_2, 1, 2, IN_CIRCULATION);

    printf("TEST - Retcode %d\n", retcode);


}
