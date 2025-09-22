// Atividade 8

// Faça um script que pisque o LED Built-in a cada 1 segundo. Caso o microcontrolador receba um valor na serial (inteiro). 
// Esse valor deve ser aplicado ao intervalo de tempo em ms o qual o LED Built-in ficará ligado e desligado;

// #define COMPILE
#ifdef COMPILE
#include <Arduino.h>
int time_ms = 1000;
void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
}
void loop() {
  if(Serial.available() > 0){
    String msg = Serial.readStringUntil('\n');
    time_ms = msg.toInt();
  }
  digitalWrite(2, HIGH);
  delay(time_ms);
  digitalWrite(2, LOW);
  delay(time_ms);
}
#endif