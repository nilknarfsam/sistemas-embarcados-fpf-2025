// Atividade 3

// Utilizando o Arduino UNO, crie um script que 
// pisque o LED Built-in a cada 1 segundos. 
// Quando um botão, conectado no pino 3, for 
// clicado (fazendo o nível lógico ir para baixo) um segundo LED, no pino 5, 
// deve mudar de estado.

#ifdef COMPILE
#include<Arduino.h>

volatile bool ledState = false;
void interruptFunction(){
  ledState = !ledState;
  digitalWrite(5, ledState);
}

void setup(){
  Serial.begin(9600);
  pinMode(3, INPUT_PULLUP);
  pinMode(5, OUTPUT);
  pinMode(13, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(3), interruptFunction, CHANGE);
}
void loop(){
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}

// Ideia para medição de velocidade
// volatile bool ledState = false;
// volatile unsigned long t_inicial;
// volatile bool first_measure = true;
// void interruptFunction(){
//   if (first_measure){
//      t_inicial = millis();
//      first_measure = false;
//   }
//   else{
//     unsigned long delta = millis() - t_inicial;
//   }
// }

#endif