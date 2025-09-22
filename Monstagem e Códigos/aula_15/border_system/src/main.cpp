#include <Arduino.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// Pinos
const int LDR_PIN = A0;
const int DHT_PIN = 12;
const int SOFT_RX = 10;
const int SOFT_TX = 11;

DHT dht(DHT_PIN, DHT22);
LiquidCrystal_I2C lcd(0x27, 16, 2); // Endereço comum: 0x27 ou 0x3F
SoftwareSerial softSerial(SOFT_RX, SOFT_TX);

unsigned long lastRead = 0; 
const unsigned long interval = 1000; // 1 segundo

String ultimaMensagem = ""; // Guarda a última mensagem recebida

void setup() {
  Serial.begin(9600);
  softSerial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");
  delay(1000);
  lcd.clear();
}

void loop() {
  // Leitura e envio dos sensores a cada 1 segundo
  if (millis() - lastRead >= interval) {
    lastRead = millis();

    int ldrValue = analogRead(LDR_PIN);
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    // Checa se leitura falhou
    if (isnan(temp) || isnan(hum)) {
      lcd.setCursor(0, 0);
      lcd.print("Erro DHT22      ");
      Serial.println("Erro DHT22");
    } else {
      // Monta string de dados
      String data = String("LDR:") + ldrValue + ",T:" + temp + ",H:" + hum;

      // Serial padrão
      Serial.println(data);

      // SoftwareSerial
      softSerial.println(data);

      // Monta string para o display (linha 1)
      char linha1[17];
      snprintf(linha1, sizeof(linha1), "L%dH%.1fT%.1f", ldrValue, hum, temp);

      lcd.setCursor(0, 0);
      lcd.print(linha1);
      int len = strlen(linha1);
      // Limpa o resto da linha se sobrar espaço
      for (int i = len; i < 16; i++) lcd.print(" ");
    }

    // Atualiza a segunda linha com a última mensagem recebida (se houver)
    lcd.setCursor(0, 1);
    if (ultimaMensagem.length() > 0) {
      lcd.print(ultimaMensagem.substring(0, 16));
      int len = ultimaMensagem.length();
      for (int i = len; i < 16; i++) lcd.print(" ");
    } else {
      lcd.print("                "); // Limpa a linha se não houver mensagem
    }
  }

  // Verifica se recebeu mensagem na SoftwareSerial
  if (softSerial.available()) {
    String msg = softSerial.readStringUntil('\n');
    msg.trim();

    // Mostra na Serial padrão
    Serial.print("Recebido SoftSerial: ");
    Serial.println(msg);

    // Atualiza a última mensagem recebida
    ultimaMensagem = msg;

    // Limpa e mostra a nova mensagem na segunda linha
    lcd.setCursor(0, 1);
    lcd.print("                "); // Limpa a linha
    lcd.setCursor(0, 1);
    lcd.print(ultimaMensagem.substring(0, 16));
  }
}