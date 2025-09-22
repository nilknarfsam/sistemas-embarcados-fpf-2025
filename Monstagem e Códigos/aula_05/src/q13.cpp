// Atividade 13

// Crie um script utilizando a função map o qual receba cinco números inteiros separados por vírgula e faça de um mapeamento simples com eles:
// O primeiro número é o menor da primeira escala;
// O segundo número é o maior da primeira escala;
// O terceiro número é o  menor da segunda escala;
// O quarto número é o maior da segunda escala;
// O quinto número é o valor a ser mapeado;

// #define COMPILE
#ifdef COMPILE
#include <Arduino.h>
const int paraMenor = 0;
const int paraMaior = 500;
void setup() {
  Serial.begin(9600);
  Serial.println(" ");
}
void loop() {
  if(Serial.available() > 0){
    String msg = Serial.readStringUntil('\n');
    int inicial = msg.indexOf(',');
    String deMenor = msg.substring(0, inicial);
    String deMaior = msg.substring(deMenor.length() + 1, msg.length());
    int deMaiorInt = deMaior.toInt();
    int deMenorInt = deMenor.toInt();
    int result = map(500, deMenorInt, deMaiorInt, paraMenor, paraMaior);
    Serial.println(result);
  }
}
#endif