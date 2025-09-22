#include <Arduino.h>
void setup(){
  pinMode(14, OUTPUT);
  pinMode(2, OUTPUT);
}
void loop(){
  digitalWrite(14, LOW);
  digitalWrite(2, LOW);
  delay(2000);
  digitalWrite(14, HIGH);
  digitalWrite(2, HIGH);
  delay(2000);
}

