#include "buzzer.h"
#include <Arduino.h>

void controlBuzzer(bool state){
  digitalWrite(buzzer_pin, state);
}