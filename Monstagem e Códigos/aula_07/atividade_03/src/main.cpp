#include <Arduino.h>
void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}
void loop() {
  if(Serial.available() > 0){
    uint8_t message = Serial.read();
    if (message == 41){
      digitalWrite(LED_BUILTIN, HIGH);
    }else if(message == 40){
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
  delay(10);
}