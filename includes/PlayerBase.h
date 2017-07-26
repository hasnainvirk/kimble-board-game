/*
 * PlayerBase.h
 *
 *  Created on: Jul 18, 2017
 *      Author: hasnain
 */

#ifndef INCLUDES_PLAYERBASE_H_
#define INCLUDES_PLAYERBASE_H_

#define MAX_NUMBER_OF_PEGS      4
#define MAX_NUMBER_OF_PLAYERS   4

#include <stdint.h>

typedef enum {
    SUCCESS=0,
    INVALID_PARAMETER=-1,
    PLAYER_DOES_NOT_EXIST=-2,
    PLAYER_ALREADY_EXIST=-3,
    OPERATION_NOT_ALLOWED=-4,
    PEG_ALREADY_POPPED_OUT=-5,
    NO_MORE_PEGS_AT_HOME=-6,
    NO_PEGS_IN_PLAY=-7
} error_codes;

typedef enum {
    RED = 0,
    GREEN,
    YELLOW,
    BLUE
} Player_colour_e;

typedef struct {
    const char *player_name;
    uint8_t peg_colour;
} Player_config_t;

typedef enum {
    IN_HOME = -1,
    IN_CIRCULATION = 0,
    IN_FINISH_LANE = 1,
    POPPED_OUT = 2
} Peg_state_e;

typedef enum {
    ROLLING,
    AWAITING_TURN,
    LOST,
    WON
} Player_status;

typedef struct {
    uint8_t peg_number;
    int8_t peg_state;
    int8_t peg_position;
    int8_t distance_covered;
    int8_t distance_to_origin_marker;
} Peg_t;

typedef struct {
    Peg_t pegs[MAX_NUMBER_OF_PEGS];
    uint8_t player_status;
    uint8_t player_standing;
    uint8_t pegs_in_play;
    uint8_t pegs_at_home;
    uint8_t pegs_in_normal_lane;
    uint8_t pegs_in_finish_lane;
    uint8_t pegs_popped_out;
} Player_data_t;

typedef struct {
    uint8_t player_id;
    Player_config_t config;
    Player_data_t meta_data;
} Player_t;

class PlayerBase {

public:

    PlayerBase();
    virtual ~PlayerBase();

    /**
     * Create players.
     *
     * Number of player corresponds to the colour defined in the colour array, i.e., Player 1 will get
     * the colour defined in the first index of colour array.
     *
     * @param   num_players     An integer representing number of players, MAX 4
     * @param   colour          An array of colours corresponding to the player
     */
    int8_t create_players(uint8_t num_players, Player_config_t *config);

    /**
     * Updates player status after every move.
     *
     * @params   data   Player meta data
     */
    int8_t update_player_status(Player_t *player_data);

    int8_t access_player_data(uint8_t player_id, Player_t *&player_data);

private:

    // A linked list to hold 4 players data
    typedef struct Player_entry_s{
        Player_t *player_data;
        Player_entry_s *next;
    } Player_entry_t;

    Player_entry_t *player_list_head;

    // Enter a player to the players list
    int8_t add_entry_to_list(Player_entry_t *&list, Player_t *data);

    // Update entry in list
    int8_t update_entry_in_list(Player_entry_t *&list, Player_data_t *data, uint8_t player_id);

    // Drop the whole list
    int8_t drop_list(Player_entry_t *&list);
};



#endif /* INCLUDES_PLAYERBASE_H_ */
