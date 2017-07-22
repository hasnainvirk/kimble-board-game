/*
 * KimbleBase.cpp
 *
 *  Created on: Jul 18, 2017
 *      Author: hasnain
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "KimbleBase.h"
#include "Utilities.h"

#define DIE_FACES               6 //faces 1-6
#define FINISH_POST_DISTANCE    32 //steps
#define CIRCLE_WRAP_AROUND      27 //

#define BLUE_ZONE_ORIGIN        0
#define GREEN_ZONE_ORIGIN       7
#define RED_ZONE_ORIGIN         14
#define YELLOW_ZONE_ORIGIN      21

#define BLUE_ZONE_START        BLUE_ZONE_ORIGIN+1
#define GREEN_ZONE_START       GREEN_ZONE_ORIGIN+1
#define RED_ZONE_START         RED_ZONE_ORIGIN+1
#define YELLOW_ZONE_START      YELLOW_ZONE_ORIGIN+1


typedef struct {
    uint8_t origin;   //origin position in regard to colour
    int8_t pos;       //position on the circle with respect to origin
    int8_t player_id; //id of the player who occupied the spot, -1 if unoccupied
    int8_t peg_id;    //id of the peg who occupied the spot, -1 if unoccupied
    bool occupied;    //boolean to mark if the position is occupied by a peg
    bool in_finish_lane;    //boolean to mark if the position is occupied by a peg
} Ground_t;

typedef struct {
    // From home, ground starts at 1, 0 is the slot from where you enter FinishLane
    // after a full circle around the board
    Ground_t blue_ground[7];
    Ground_t green_ground[7];
    Ground_t red_ground[7];
    Ground_t yellow_ground[7];


    Ground_t blue_finish_lane[4];
    Ground_t green_finish_lane[4];
    Ground_t red_finish_lane[4];
    Ground_t yellow_finish_lane[4];

} Board_ground_t;

static Board_ground_t board;

typedef struct {
    uint8_t player_id;
    uint8_t die_outcome;
} Turn_sequence_t;

Turn_sequence_t *turn_seq;

// Seed the random generator
void seed_srand()
{
    srand((unsigned)time(NULL));
}

int roll_die()
{
    return (rand() %  DIE_FACES) + 1;
}

void setup_board()
{
    uint8_t j = 0;
    uint8_t colours[MAX_NUMBER_OF_PLAYERS] = {BLUE, GREEN, RED, YELLOW};

    while (j < MAX_NUMBER_OF_PLAYERS) {
        if (colours[j] == BLUE) {
            for (uint8_t i = 0; i < 7; i++) {
                board.blue_ground[i].occupied = false;
                board.blue_ground[i].peg_id = -1;
                board.blue_ground[i].player_id = -1;
                board.blue_ground[i].origin = BLUE_ZONE_ORIGIN;
                board.blue_ground[i].pos = i+BLUE_ZONE_ORIGIN;
            }
            for (uint8_t i = 0; i < 4; i++) {
                board.blue_finish_lane[i].occupied = false;
                board.blue_finish_lane[i].peg_id = -1;
                board.blue_finish_lane[i].player_id = -1;
                board.blue_finish_lane[i].origin = BLUE_ZONE_ORIGIN;
                board.blue_finish_lane[i].pos = i+CIRCLE_WRAP_AROUND+1;
            }
        } else if (colours[j] == GREEN) {
            for (uint8_t i = 0; i < 7; i++) {
                board.green_ground[i].occupied = false;
                board.green_ground[i].peg_id = -1;
                board.green_ground[i].player_id = -1;
                board.green_ground[i].origin = GREEN_ZONE_ORIGIN;
                board.green_ground[i].pos = i+GREEN_ZONE_ORIGIN;
            }
            for (uint8_t i = 0; i < 4; i++) {
                board.green_finish_lane[i].occupied = false;
                board.green_finish_lane[i].peg_id = -1;
                board.green_finish_lane[i].player_id = -1;
                board.green_finish_lane[i].origin = GREEN_ZONE_ORIGIN;
                board.green_finish_lane[i].pos = i+CIRCLE_WRAP_AROUND+1;
            }
        } else if (colours[j] == RED) {
            for (uint8_t i = 0; i < 7; i++) {
                board.red_ground[i].occupied = false;
                board.red_ground[i].peg_id = -1;
                board.red_ground[i].player_id = -1;
                board.red_ground[i].origin = RED_ZONE_ORIGIN;
                board.red_ground[i].pos = i+RED_ZONE_ORIGIN;
            }
            for (uint8_t i = 0; i < 4; i++) {
                board.red_finish_lane[i].occupied = false;
                board.red_finish_lane[i].peg_id = -1;
                board.red_finish_lane[i].player_id = -1;
                board.red_finish_lane[i].origin = RED_ZONE_ORIGIN;
                board.red_finish_lane[i].pos = i+CIRCLE_WRAP_AROUND+1;
            }
        } else if (colours[j] == YELLOW) {
            for (uint8_t i = 0; i < 7; i++) {
                board.yellow_ground[i].occupied = false;
                board.yellow_ground[i].peg_id = -1;
                board.yellow_ground[i].player_id = -1;
                board.yellow_ground[i].origin = YELLOW_ZONE_ORIGIN;
                board.yellow_ground[i].pos = i+YELLOW_ZONE_ORIGIN;
            }
            for (uint8_t i = 0; i < 4; i++) {
                board.yellow_finish_lane[i].occupied = false;
                board.yellow_finish_lane[i].peg_id = -1;
                board.yellow_finish_lane[i].player_id = -1;
                board.yellow_finish_lane[i].origin = YELLOW_ZONE_ORIGIN;
                board.yellow_finish_lane[i].pos = i+CIRCLE_WRAP_AROUND+1;
            }
        }
        j++;
    } //while loop
}

KimbleBase::KimbleBase(uint8_t num_players)
{
    number_of_players = num_players;
    turn_seq = new Turn_sequence_t[4];
    seed_srand();
    setup_board();
}

KimbleBase::~KimbleBase()
{
    delete turn_seq;
}

void KimbleBase::game_engine_log(Player_config_t config, const char *msg)
{
    switch (config.peg_colour) {
        case BLUE:
            LOG(ANSI_COLOR_CYAN "[%s]: %s\n" ANSI_COLOR_RESET, config.player_name, msg);
            break;
        case GREEN:
            LOG(ANSI_COLOR_GREEN "[%s]: %s\n" ANSI_COLOR_RESET, config.player_name, msg);
            break;
        case RED:
            LOG(ANSI_COLOR_RED "[%s]: %s\n" ANSI_COLOR_RESET, config.player_name, msg);
            break;
        case YELLOW:
            LOG(ANSI_COLOR_YELLOW "[%s]: %s\n" ANSI_COLOR_RESET, config.player_name, msg);
            break;
        default:
            break;
    }
}



int8_t turn_toss(uint8_t *player_ids, uint8_t length)
{
    int die_outcome[length];
    Turn_sequence_t turns[length];

    //roll die for each player and record the result
    for (uint8_t i=0; i < length; i++) {
        die_outcome[i] = roll_die();
        turns[i].player_id = *player_ids++;
        turns[i].die_outcome = die_outcome[i];
    }

    //sort in descending order

}

int8_t generate_next_turn()
{

}

int8_t KimbleBase::game_engine(uint8_t num_players)
{
    int die_outcome;
    int8_t retcode;
    char buf[40];
    // round-robin pop-o-matic push
    for (uint8_t i=0; i < num_players; i++) {
        //current user data before rolling the die
        Player_t *player;

        Player_data_t data;

        retcode = players.access_player_data(i, player);
        if (retcode == SUCCESS && (player->meta_data.player_status == AWAITING_TURN)) {
            die_outcome = roll_die();
            sprintf(buf, "Rolled dice ... %d", die_outcome);
            game_engine_log(player->config, buf);

            switch (die_outcome) {
                case 6:
                    //when you rolled a 6 but your own peg is on the START position
                    if (board.blue_ground[BLUE_ZONE_START].occupied && (board.blue_ground[BLUE_ZONE_START].player_id == player->player_id)) {
                        //check if you can move any other peg which is IN_PLAY
                    }
                    break;
                case 5:
                    break;
                case 4:
                    break;
                case 3:
                    break;
                case 2:
                    break;
                case 1:
                    break;
                default:
                    fprintf(stderr, "This should never happen\n");
            }

        }


    }
}

int8_t KimbleBase::simulate_game(Player_config_t *config)
{
    int8_t retcode;
    if (number_of_players > 4 || number_of_players < 1) {
        return INVALID_PARAMETER;
    }

    retcode = players.create_players(number_of_players, config);
    assert(retcode == SUCCESS);

    return retcode;
}



