// #define COMPILE
#ifdef COMPILE
#include<Arduino.h>
#include<WiFi.h>
#include<WebServer.h>

WebServer server(80);

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

void setup(){
  Serial.begin(115200);
  connectWifi(ssid, password, 30 * 1000);
  server.on("/", handleRoot);
  server.on("/teste", handleTest);
  server.begin();
}
void loop(){
  server.handleClient();
  handleWiFiConnection();
}

#endif