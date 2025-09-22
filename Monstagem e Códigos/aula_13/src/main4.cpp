// #define COMPILE
#ifdef COMPILE

#include<Arduino.h>
#include <FS.h>
#include <SPIFFS.h>

void setup() {
  Serial.begin(115200);
  delay(200);

  if (!SPIFFS.begin(true)) {
    Serial.println("Falha ao montar SPIFFS");
    return;
  }
  Serial.println("SPIFFS montado.");

  const char* path = "/dados.txt";
  
  File f = SPIFFS.open(path, FILE_WRITE);
  if (!f) {
    Serial.println("Falha ao abrir arquivo para escrita");
  } else {
    String conteudo = "Linha 1: Olá SPIFFS!\nLinha 2: Persistência no ESP32.\n";
    size_t n = f.print(conteudo);
    f.close();
    Serial.printf("Escrito %u bytes em %s\n", (unsigned)n, path);
  }
  
  f = SPIFFS.open(path, FILE_READ);
  if (!f) {
    Serial.println("Falha ao abrir arquivo para leitura");
  } else {
    Serial.printf("Lendo %s (%u bytes):\n", path, (unsigned)f.size());
    while (f.available()) {
      Serial.write(f.read());
    }
    f.close();
    Serial.println();
  
  }
  
  Serial.println("Arquivos na raiz (/):");
  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  while (file) {
    Serial.printf("  %s  (%u bytes)\n", file.name(), (unsigned)file.size());
    file = root.openNextFile();
  }
  
}

void loop() {
}
#endif