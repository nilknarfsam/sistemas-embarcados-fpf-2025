#include <Arduino.h>
const int LED_PIN = 35;
void setup(){
  pinMode(LED_PIN, OUTPUT);
  for(;;){
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    delay(1000);
  }
}
void loop(){}