// #define COMPILE
#ifdef COMPILE

#include<Arduino.h>
#include<WiFi.h>
#include<WiFiClient.h>

const String ssid = "FPF-2Ghz";
const String password = "10203040";
const unsigned long timeout = 30 * 1000;
WiFiClient cl;
WiFiServer sv(3000);

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

void tcp(){
  if (cl.connected()){
    if(cl.available() > 0){
      String received_msg = "";
      while(cl.available() > 0){
        received_msg += cl.readString();
      }
      Serial.println("\nUm cliente enviou uma mensagem");
      Serial.print("IP do cliente: ");
      Serial.print(cl.remoteIP());
      Serial.print("\nIP do servidor: ");
      Serial.print(WiFi.localIP());
      Serial.print("\nMensagem do cliente: " + received_msg + "\n");

      cl.println("\nO servidor recebeu sua mensagem");
      cl.print("Seu IP: ");
      cl.print(cl.remoteIP());
      cl.print("\nIP do Servidor: ");
      cl.println(WiFi.localIP());
      cl.print("Sua mensagem: " + received_msg + "\n");
    }
  }
  else{
      cl = sv.available();
      delay(1);
    }
}

void setup(){
  Serial.begin(115200);
  connectWifi(ssid, password, timeout);
  sv.begin();
}
void loop(){
  tcp();
  handleWiFiConnection();
}
#endif