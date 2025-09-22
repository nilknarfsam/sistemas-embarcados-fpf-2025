
#ifdef COMPILE
#include <Arduino.h>

unsigned long t_inicial = millis();
bool state = false;

void setup(){
  pinMode(2, OUTPUT);
}
void loop(){
  if (abs(int(millis()) - int(t_inicial)) >= 1000){
    state = !state;
    digitalWrite(2, state);
    t_inicial = millis();
  }
}
// pesquisar sobre _abs()
#endif