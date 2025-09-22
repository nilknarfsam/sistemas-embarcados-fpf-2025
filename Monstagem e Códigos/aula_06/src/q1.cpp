// Atividade 1
// Utilizando o ESP32 crie um script o qual pisque o LED 
// Built-In 5 vezes em um intervalo de 1 segundo,  e o coloque para dormir por 10 segundos. 
// Esse processo deve ser executado em loop.


// #define COMPILE
#ifdef COMPILE
#include <Arduino.h>

void setup() {
  int i = 0;
  do{
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);
    delay(1000);
    i++;
  }while(i < 5);
  
  esp_deep_sleep(10 * 1000000);
}
void loop() {
  
}
#endif