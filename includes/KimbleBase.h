/*
 * KimbleBase.h
 *
 *  Created on: Jul 20, 2017
 *      Author: hasnain
 */

#ifndef INCLUDES_KIMBLEBASE_H_
#define INCLUDES_KIMBLEBASE_H_

#include "PlayerBase.h"

class KimbleBase
{
public:
    KimbleBase(uint8_t num_players);
    virtual ~KimbleBase();

    int8_t simulate_game(Player_config_t *config);


    PlayerBase players; //KimbleBase has PlayerBase

private:
    uint8_t number_of_players
    int8_t game_engine(uint8_t num_players);
    void game_engine_log(Player_config_t config, const char *msg);


};


#endif /* INCLUDES_KIMBLEBASE_H_ */
