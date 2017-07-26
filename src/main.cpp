/*
 * main.cpp
 *
 *  Created on: Jul 19, 2017
 *      Author: hasnain
 */

#include <stdio.h>
#include <string.h>

#include "KimbleBase.h"
#include "Test.h"

static const char *determine_user_colour(uint8_t colour)
{
    const char *ret_val;
    switch (colour) {
        case RED:
            ret_val = "RED";
            break;
        case GREEN:
            ret_val = "GREEN";
            break;
        case YELLOW:
            ret_val = "YELLOW";
            break;
        case BLUE:
            ret_val =  "BLUE";
            break;
        default:
            return NULL;
    }

    return ret_val;
}

static const char *determine_user_status(uint8_t status)
{
    const char *ret_val;

    switch (status) {
        case ROLLING:
            ret_val = "ROLLING";
            break;
        case AWAITING_TURN:
            ret_val = "AWAITING_TURN";
            break;
        case LOST:
            ret_val = "LOST";
            break;
        case WON:
            ret_val =  "WON";
            break;
        default:
            return NULL;
    }

    return ret_val;
}

static const char *determine_peg_state(int8_t state)
{
    const char *ret_val;

    switch (state) {
        case IN_CIRCULATION:
            ret_val = "IN_CIRCULATION";
            break;
        case IN_HOME:
            ret_val =  "IN_HOME";
            break;
        case IN_FINISH_LANE:
            ret_val =  "IN_FINISH_LANE";
            break;
        case POPPED_OUT:
            ret_val =  "POPPED_OUT";
            break;
        default:
            return NULL;
    }

    return ret_val;
}

static void TEST_add_entry_to_list();
static void TEST_simulate_game();
static void print_meta_data(Player_t *data);
static void TEST_kill_opponent_peg();

int main()
{

    TEST_kill_opponent_peg();
    //TEST_simulate_game();
    return 0;
    //TEST_add_entry_to_list();
}

static void print_meta_data(Player_t *data)
{
    printf("Player Name: %s\n", data->config.player_name);
    printf("Player Colour: %s\n", determine_user_colour(data->config.peg_colour));
    printf("Player status: %s\n", determine_user_status(data->meta_data.player_status));
    printf("Pegs - In Play: %d\n", data->meta_data.pegs_in_play);
    printf("Pegs - Popped out: %d\n", data->meta_data.pegs_popped_out);
    printf("PEG Status:\n");
    for (uint8_t j=0; j < MAX_NUMBER_OF_PEGS; j++) {
        printf("\t Peg-%d:\n", data->meta_data.pegs[j].peg_number);
        printf("\t Peg position: %d\n", data->meta_data.pegs[j].peg_position);
        printf("\t Peg state: %s\n", determine_peg_state(data->meta_data.pegs[j].peg_state));
    }
}

static void TEST_simulate_game()
{
    KimbleBase game(MAX_NUMBER_OF_PLAYERS);
    Player_config_t config[4];
    config[0].player_name = "Hasnain";
    config[0].peg_colour = RED;
    config[1].player_name = "Noriko";
    config[1].peg_colour = GREEN;
    config[2].player_name = "Akif";
    config[2].peg_colour = BLUE;
    config[3].player_name = "Ahad";
    config[3].peg_colour = YELLOW;
    game.simulate_game(config);

    for (uint8_t i=0; i < MAX_NUMBER_OF_PLAYERS; i++) {
        Player_t *data = NULL;
        int8_t retcode = game.players.access_player_data(i, data);
        if (retcode != SUCCESS) {
            fprintf(stderr, "Test failed.\n");
            return;
        }

        print_meta_data(data);
    }
}

static void TEST_kill_opponent_peg()
{
    Test test_env;
    Player_config_t config[MAX_NUMBER_OF_PLAYERS];
    config[0].player_name = "Hasnain";
    config[0].peg_colour = RED;
    config[1].player_name = "Noriko";
    config[1].peg_colour = GREEN;
    config[2].player_name = "Akif";
    config[2].peg_colour = BLUE;
    config[3].player_name = "Ahad";
    config[3].peg_colour = YELLOW;

    KimbleBase game(MAX_NUMBER_OF_PLAYERS);
    game.players.create_players(MAX_NUMBER_OF_PLAYERS, config);

    test_env.Test_kill_opponent_peg(&game);


}

static void TEST_add_entry_to_list()
{
    //Variables
    static PlayerBase players;
    Player_config_t config[4];
    config[0].player_name = "Hasnain";
    config[0].peg_colour = RED;
    config[1].player_name = "Noriko";
    config[1].peg_colour = GREEN;
    config[2].player_name = "Akif";
    config[2].peg_colour = BLUE;
    config[3].player_name = "Ahad";
    config[3].peg_colour = YELLOW;

    players.create_players(4, config);

    for (uint8_t i=0; i < MAX_NUMBER_OF_PLAYERS; i++) {
        Player_t *data = NULL;
        int8_t retcode = players.access_player_data(i, data);
        if (retcode != SUCCESS) {
            fprintf(stderr, "Test failed.\n");
            return;
        }

        print_meta_data(data);
    }
}

