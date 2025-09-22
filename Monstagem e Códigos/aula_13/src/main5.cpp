#define COMPILE
#ifdef COMPILE
#include<Arduino.h>
#include<WiFi.h>
#include<WebServer.h>
#include <FS.h>
#include <SPIFFS.h>

WebServer server(80);
File f;
const String ssid = "FPF-2Ghz";
const String password = "10203040";
const unsigned long timeout = 30 * 1000;

bool connectWifi(String ssid, String password, unsigned long timeout){
  WiFi.mode(WIFI_OFF);
  delay(10);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.println("Tentando se conectar ao Wi-Fi...");
  unsigned long current_time = millis();
  while(WiFi.status() != WL_CONNECTED ){
    Serial.print('.');
    delay(100);
    if (millis() - current_time >= timeout){
      return false;
    }
  }
  Serial.println("\nConectado ao Wi-Fi!");
  Serial.println(WiFi.localIP());
  return true;
}

void handleWiFiConnection(){
  if (WiFi.status() != WL_CONNECTED){
    if(!connectWifi(ssid, password, timeout)){
      ESP.restart();
    }
  }
}
void handleRoot() {
  server.send(200, "text/plain", "Ola, tudo bem?");
}
void handleTest(){
  server.send(200, "text/html", "<html><p>OLA<p></html>");
}
void handleHtml(){
  f = SPIFFS.open("/index.html", FILE_READ);
  if (!f) {
    Serial.println("Falha ao abrir arquivo para leitura");
    server.send(200, "text/html", "<html><p>ERROR<p></html>");
  } else {
    server.send(200, "text/html", f.readString());
  }
}
void handleON(){

  f = SPIFFS.open("/index.html", FILE_READ);
  if (!f) {
    Serial.println("Falha ao abrir arquivo para leitura");
    server.send(200, "text/html", "<html><p>ERROR<p></html>");
  } else {
    server.send(200, "text/html", f.readString());
  }
  Serial.println("Led ligado!");
  digitalWrite(2, HIGH);
}

void handleOFF(){

  f = SPIFFS.open("/index.html", FILE_READ);
  if (!f) {
    Serial.println("Falha ao abrir arquivo para leitura");
    server.send(200, "text/html", "<html><p>ERROR<p></html>");
  } else {
    server.send(200, "text/html", f.readString());
  }
  Serial.println("Led desligado!");
  digitalWrite(2, LOW);
}


void setup(){
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  delay(200);
  if (!SPIFFS.begin(true)) {
    Serial.println("Falha ao montar SPIFFS");
    return;
  }
  connectWifi(ssid, password, 30 * 1000);
  server.on("/", handleHtml);
  // server.on("/teste", handleTest);
  server.on("/ligar", handleON);
  server.on("/desligar", handleOFF);
  server.begin();
}
void loop(){
  server.handleClient();
  handleWiFiConnection();
}

#endif