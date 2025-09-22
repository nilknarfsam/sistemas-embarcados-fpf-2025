// #define COMPILE
#ifdef COMPILE
#include<Arduino.h>
#include<WiFi.h>
#include<HTTPClient.h>

String url = "https://api.adviceslip.com/advice";

const String ssid = "FPF-2Ghz";
const String password = "10203040";
const unsigned long timeout = 30 * 1000;
 HTTPClient http;

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

void setup(){
  Serial.begin(115200);
  connectWifi(ssid, password, 30 * 1000);
}

void loop(){

  handleWiFiConnection();
  
  // http.setInsecure();
  http.begin(url);

  int code = http.GET();
  Serial.println(code);
  if (code == 200){
     Serial.println(http.getString());
  }  
  delay(10 * 1000);
}

#endif