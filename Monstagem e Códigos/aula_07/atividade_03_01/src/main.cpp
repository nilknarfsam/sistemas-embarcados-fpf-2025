#include <Arduino.h>

void setup() {
  Serial.begin(4800);
  pinMode(LED_BUILTIN, OUTPUT); 
}

void loop() {
  if (Serial.available() > 0) {
    byte receivedByte = Serial.read();
    while (Serial.available() > 0)
    {
     Serial.read();
    }
    if (receivedByte == 41) {
      digitalWrite(LED_BUILTIN, HIGH);
    }else if (receivedByte == 40){
       digitalWrite(LED_BUILTIN, LOW);
    }
    
       
  }
  delay(50);
}
