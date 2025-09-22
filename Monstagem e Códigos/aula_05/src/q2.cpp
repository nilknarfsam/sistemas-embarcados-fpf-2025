// Atividade 2
// Programe o LED Built-in da placa para piscar a com base em um tempo armazenado em uma variável.
// ESP32 DEVKIT: LED está no GPIO2
// ARDUINO UNO: LED Está no GPIO13

// #define COMPILE
#ifdef COMPILE
#include <Arduino.h>

uint32_t t = 1000;

void setup() {
  pinMode(2, OUTPUT);
}
void loop() {
  digitalWrite(2, HIGH);
  delay(t);
  digitalWrite(2, LOW);
  delay(t);
}
#endif