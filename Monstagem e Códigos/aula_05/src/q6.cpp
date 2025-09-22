// Atividade 6
// Faça um script que leia um valor da serial e o escreva de volta na serial (repetidor);
#ifdef COMPILE
#include <Arduino.h>

void setup(){
  Serial.begin(115200);
}

void loop(){
  if(Serial.available() > 0){
    Serial.println(Serial.readStringUntil('\n'));
  }
  delay(10);
}
#endif