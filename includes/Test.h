/*
 * Test.h
 *
 *  Created on: Jul 26, 2017
 *      Author: hasnain
 */

#ifndef INCLUDES_TEST_H_
#define INCLUDES_TEST_H_

#include <stdint.h>
#include "KimbleBase.h"

//Forward Declaration of KimbleBase
class KimbleBase;

class Test {
public:
    int8_t kill_opponent_peg(KimbleBase *game);
    int8_t occupy_block_on_board(KimbleBase *game);
    int8_t free_block_on_board(KimbleBase *game);
    int8_t enter_finish_lane(KimbleBase *game);
    int8_t pop_a_peg(KimbleBase *game);
};



#endif /* INCLUDES_TEST_H_ */
