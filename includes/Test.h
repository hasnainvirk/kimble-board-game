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
    int8_t Test_kill_opponent_peg(KimbleBase *game);
};



#endif /* INCLUDES_TEST_H_ */
