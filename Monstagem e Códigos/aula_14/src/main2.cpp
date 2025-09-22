#define COMPILE
#ifdef COMPILE

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "FPF-2Ghz";
const char* password = "10203040";

const char* mqtt_server = "10.31.3.1"; 
const int mqtt_port = 1883;
const char* mqtt_user = ""; 
const char* mqtt_password = ""; 
const char* mqtt_client_id = "ESP32_123456";

WiFiClient espClient;
PubSubClient client(espClient);

const char* topico_sub = "/esp32/test";
const char* topico_pub = "/esp32/test/out";


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida no tópico: ");
  Serial.println(topic);
  Serial.print("Conteúdo: ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {

  while (!client.connected()) {
    Serial.print("Tentando conectar ao MQTT...");
    if (client.connect(mqtt_client_id, mqtt_user, mqtt_password)) {
      Serial.println("conectado!");
      client.subscribe(topico_sub);
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);
  delay(10);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi conectado");
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  static unsigned long lastMsg = 0;
  if (millis() - lastMsg > 10000) {
    lastMsg = millis();
    String mensagem = "Olá do ESP!";
    client.publish(topico_pub, mensagem.c_str());
    Serial.println("Mensagem publicada!");
  }
}
#endif