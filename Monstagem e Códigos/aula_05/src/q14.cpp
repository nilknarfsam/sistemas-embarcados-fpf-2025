#include <Arduino.h>
#include <ArduinoJson.h>
JsonDocument doc;
void setup(){
  Serial.begin(115200);
  pinMode(2, OUTPUT);
}
void loop(){
  if(Serial.available() > 0){
    String msg = Serial.readStringUntil('\n');
    deserializeJson(doc, msg);
    bool led_state = doc["led_state"];
    digitalWrite(2, led_state);

    doc.clear();
    doc["led_state"] = led_state;
    String response;
    serializeJson(doc, response);
    Serial.println(response);
  }
}

