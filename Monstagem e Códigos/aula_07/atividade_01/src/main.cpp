#include <Arduino.h>
#include "buzzer.h"
#include "pir.h"

#define SERIAL_DEBUG

void setup() {
  pinMode(buzzer_pin, OUTPUT);
  #ifdef SERIAL_DEBUG
    Serial.begin(96000);
  #endif

}

void loop() {
  if (Serial.available() > 0){
    String message = Serial.readStringUntil('\n');
    int value = message.toInt();
    switch (value){
      case 0:
        controlBuzzer(false);
        break;
      case 1:
        controlBuzzer(true);
        break;
      default:
        #ifdef SERIAL_DEBUG
          Serial.println("Entendi foi nada");
        #endif
        break;
    }
  }

  Serial.print("O valor do PIR é: ");
  Serial.println(getPirValue());

}