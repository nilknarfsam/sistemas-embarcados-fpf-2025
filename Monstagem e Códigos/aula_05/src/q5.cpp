// Atividade 1
//Crie um script que escreva uma frase na serial apenas 10 vezes;
// Utilize for;
// Utilize while;


// #define COMPILE
#ifdef COMPILE

#include <Arduino.h>

void setup(){
  Serial.begin(115200);

  for (int i = 0; i < 10; i++){
    Serial.print("Esta é uma frase!");
    delay(1000);
  }
  int i = 0;
  while(i < 10){
    Serial.print("Esta é uma frase!");
    i = i + 1;
  }
}
void loop(){}
#endif