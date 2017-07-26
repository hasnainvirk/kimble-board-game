/*
 * Utilities.h
 *
 *  Created on: Jul 19, 2017
 *      Author: hasnain
 */

#ifndef INCLUDES_UTILITIES_H_
#define INCLUDES_UTILITIES_H_

/* --- Various Macros defined. Setting the colour of Traces etc. --- */
#define     ANSI_COLOR_YELLOW   "\x1b[33m"
#define     ANSI_COLOR_RED      "\x1b[31m"
#define     ANSI_COLOR_GREEN    "\x1b[32m"
#define     ANSI_COLOR_RESET    "\x1b[0m"
#define     ANSI_COLOR_CYAN     "\x1b[36m"
#define     ANSI_COLOR_GRAY     "\x1b[1;30m"
#define     BPurple             "\033[1;35m"
#define     Color_Off           "\033[0m"


#define     LOG(...)                 printf(__VA_ARGS__);


#endif /* INCLUDES_UTILITIES_H_ */
