#include <Arduino.h>
#include <math.h>
void setup() {
  Serial.begin(9600);
}
void loop() {
  if(Serial.available() > 0){
    int dado = Serial.read();
    Serial.println(dado + 5);
    Serial.println(dado * 200);
    if (dado > 5){
      Serial.println("Maior que 5!");
    }
    for(int i; i < 4; i++){
      Serial.println(i);
    }
  }
}
