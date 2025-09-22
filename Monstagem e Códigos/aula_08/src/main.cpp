#include <Arduino.h>
#include<pwmWrite.h>
Pwm pwm = Pwm();
float calc_voltage(int leitura){
  return 3.3 * leitura / 4095.0;
}
void setup() {
  pinMode(4, INPUT);
  pinMode(26, OUTPUT);
  Serial.begin(115200);
}
void loop() {
  int leitura = analogRead(4);
  int brightness = map(leitura, 0, 4095, 0, 255);
  float tensao = calc_voltage(leitura);
  Serial.print("A tensao e: ");
  Serial.print(tensao);
  Serial.println("V");
  pwm.write(26, brightness);
  delay(100);
}
