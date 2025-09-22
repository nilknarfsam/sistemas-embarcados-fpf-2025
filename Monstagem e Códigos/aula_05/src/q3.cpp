// Atividade 3
// Crie um programa que faça o LED Built-in piscar apenas 10 vezes;
// Utilize for;
// Utilize while;
// #define COMPILE
#ifdef COMPILE
#include <Arduino.h>

void setup(){
  pinMode(2, OUTPUT);
  for (int i = 0; i < 10; i++){
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);
    delay(1000);
  }
  int j = 0;
  while(j < 10){
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);
    delay(1000);
    j = j + 1;
  }
}
void loop(){}
#endif