#include <Arduino.h>
#include "pir.h"

#define SERIAL_DEBUG

void setup() {
  #ifdef SERIAL_DEBUG
    Serial.begin(96000);
  #endif
  pinMode(PIR_PIN, INPUT);

}

void loop() {
  Serial.print("O valor do PIR é: ");
  Serial.println(getPirValue());
  delay(100);
}