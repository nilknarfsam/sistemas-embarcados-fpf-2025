// #define COMPILE
#ifdef COMPILE
#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  esp_sleep_wakeup_cause_t reason = esp_sleep_get_wakeup_cause();
  int total;
  if (reason == ESP_SLEEP_WAKEUP_TIMER){
    Serial.println("Acordou pelo timer");
    total = 10;
  }
  else{
     Serial.println("Acordou por outro motivo...");
    total = 5;
  }
  int i = 0;
  do{
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);
    delay(1000);
    i++;
  }while(i < total);
  esp_deep_sleep(10 * 1000000);
}
void loop() {
  
}
#endif