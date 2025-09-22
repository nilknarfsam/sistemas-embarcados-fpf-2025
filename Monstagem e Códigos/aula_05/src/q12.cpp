// Atividade 12
// Crie um script que leia N números inteiros e armazene em um vector. 
// Ao receber -1 deve-se escrever a média dos números na serial.

// #define COMPILE
#ifdef COMPILE
#include <Arduino.h>
#include <StandardCplusplus.h>
#include<vector>
#include<iostream>

std::vector<int> numbers; 

void setup() {
    Serial.begin(9600); 
    Serial.println("Digite números inteiros. Digite -1 para calcular a média.");
}

void loop() {
    if (Serial.available() > 0) { 
        String input = Serial.readStringUntil('\n');
        input.trim(); 
        int number = input.toInt(); 
        if (number == -1) {
            if (!numbers.empty()) { 
                int sum = 0;
                for (int n : numbers) {
                    sum += n;
                }
                float average = (float)sum / numbers.size(); 
                Serial.print("Média dos números: ");
                Serial.println(average);
            } else {
                Serial.println("Nenhum número foi inserido.");
            }
            numbers.clear(); 
        } else {
            numbers.push_back(number); 
            Serial.print("Número adicionado: ");
            Serial.println(number);
        }
    }
}
#endif