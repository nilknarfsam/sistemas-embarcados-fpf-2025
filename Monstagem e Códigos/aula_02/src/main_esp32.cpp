#include<Arduino.h>

// #define COMPILE
#ifdef COMPILE
void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(115200);
}

void loop() {

  digitalWrite(2, HIGH);
  Serial.println("Led ligado!");
  delay(1000);
  digitalWrite(2, LOW);
  Serial.println("Led desligado!");
  delay(1000);
}
#endif