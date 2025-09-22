#ifdef COMPILE
#include <Arduino.h>
void setup(){
  pinMode(2, OUTPUT);
  Serial.begin(115200);
}
void loop(){
  if (Serial.available() > 0){
    String msg = Serial.readStringUntil('\n');
    Serial.println(msg);
    msg.trim();
    msg.toUpperCase();
    if (msg == "ON"){
      digitalWrite(2, HIGH);
    }
    else if(msg == "OFF"){
      digitalWrite(2, LOW);
    }
  }
}
#endif