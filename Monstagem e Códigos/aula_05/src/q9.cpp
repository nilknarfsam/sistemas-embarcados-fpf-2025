// Atividade 9

// Faça um script que receba uma mensagem na serial e escreva a mesma de volta na 
// serial pela metade;

// #define COMPILE
#ifdef COMPILE
#include <Arduino.h>

void setup(){
  Serial.begin(115200);
}

void loop(){
  if(Serial.available() > 0){
    String msg = Serial.readStringUntil('\n');
    String new_msg = msg.substring(0, msg.length() / 2);
    Serial.println(new_msg);
  }
  delay(10);
}
#endif