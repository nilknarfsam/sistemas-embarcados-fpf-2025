// Atividade 11
// Crie um script que leia 5 números da serial e escreva a média desses números;

// #define COMPILE
#ifdef COMPILE
#include <Arduino.h>

int i = 1;
int acm = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {

  Serial.print("Digite o número ");
  Serial.print(i);
  Serial.println(": ");
  while(Serial.available() == 0);
  acm = acm + Serial.readStringUntil('\n').toInt();
  if (i == 5){
    i = 1;
    Serial.println(acm / 5);
    acm = 0;
  }
  i++;
   delay(10);
}
#endif