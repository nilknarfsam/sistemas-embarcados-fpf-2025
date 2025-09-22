#define COMPILE
#ifdef COMPILE

#include <Arduino.h>
#include <BleSerial.h>

BleSerial ble;

void bleConnectCallback(bool connected){
    if(connected){
        Serial.println("Connected!");
    }
    else{
        Serial.println("Disconnected!");
    }
}

void setup()
{
    Serial.begin(115200);
	ble.begin("BLE_RAPHAEL");
    ble.setConnectCallback(bleConnectCallback);
    pinMode(2, OUTPUT);
}

void loop(){
	if(ble.available() > 0){
    uint8_t msg_c = ble.read();
    Serial.println(msg_c);
    if (msg_c == 0x01){
        digitalWrite(2, HIGH);
        ble.print("Led ligado");
    }
    else if(msg_c == 0x00){
        digitalWrite(2, LOW);
        ble.print("Led desligado");
    }
  }
	delay(10);
}
#endif