
#if DEBUG
  #include <Arduino.h>
#endif
#include "tictactoe_main.h"

void setup() {

  #if DEBUG
  Serial.begin(115200);
  while (!Serial); // wait for serial attach
  
  Serial.println();
  Serial.println("Initializing...");
  Serial.flush();
  #endif

  tictactoe_main();
  
  
}

void loop() {}

