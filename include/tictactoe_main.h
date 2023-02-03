#ifndef TICTACTOE_MAIN_H
#define TICTACTOE_MAIN_H

#include "webserver.h"

#define GPIO_PIN_SWITCH         14  // GPIO 14 bzw. D5
#define DEMO_COLOR_PLAYER_X     0x0000ff
#define DEMO_COLOR_PLAYER_O     0x00ff00
#define DEMO_COLOR_GRID         0xff0000    // Red
#define DEMO_COLOR_TEXT         0xff0000    // Red

void tictactoe_main();

#endif