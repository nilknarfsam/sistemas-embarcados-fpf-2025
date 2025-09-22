// Atividade 10

// Crie um script o qual receba um número na serial. Se o número for 1 o LED Built-in deve ser ligado.
// Se o número for 0 o LED Built-in deve ser desligado. Para os demais números nada deve ser feito. Utilize switch case.

// #define COMPILE
#ifdef COMPILE
#include <Arduino.h>

void setup(){
    Serial.begin(115200);
    pinMode(2, OUTPUT);
}

void loop(){
    if (Serial.available() > 0){
        uint8_t msg = Serial.read();
        switch (msg) {
            case 0: {
                digitalWrite(2, LOW);
                break;
            }
            case 1: {
                digitalWrite(2, HIGH);
                break;
            }
            default: {
                break;
            }
        }
    }
     delay(10);
}
#endif