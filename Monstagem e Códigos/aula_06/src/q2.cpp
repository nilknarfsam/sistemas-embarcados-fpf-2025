// Atividade 2

// Utilizando o ESP32 crie um script o qual pisque o LED Built-In 5 vezes em 
// um intervalo de 1 segundo,  e o coloque para dormir por 10 segundos. 
// Se o ESP32 acordar pelo timer deve repetir o processo, caso acorde pelo pino 
// externo deve apenas escrever uma mensagem na serial.

// #define COMPILE
#ifdef COMPILE
#include <Arduino.h>

void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  esp_sleep_wakeup_cause_t reason = esp_sleep_get_wakeup_cause();
  int total;
  if (reason == ESP_SLEEP_WAKEUP_TIMER){
    int i = 0;
    do{
      digitalWrite(2, HIGH);
      delay(1000);
      digitalWrite(2, LOW);
      delay(1000);
      i++;
    }while(i < 5);
  }
  else if(reason == ESP_SLEEP_WAKEUP_EXT0){
    Serial.println("Acordou pelo pino exteno");
  }
  else{
    Serial.println("Acordou por outro motivo...");
  }
  esp_deep_sleep(10 * 1000000);
}
void loop() {
  
}
#endif