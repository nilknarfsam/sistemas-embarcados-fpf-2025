#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// Configurações WiFi e MQTT
const char* ssid = "FPF-2Ghz";
const char* password = "10203040";
const char* mqtt_server = "10.31.1.162";
const int   mqtt_port = 1883;
const char* mqtt_user = ""; 
const char* mqtt_pass = "";  

// Tópicos MQTT
const char* topic_pub = "/device/sensores/";
const char* topic_sub = "/device/display/";

// UART para comunicação com Arduino
const int RXD2 = 16; // GPIO16 (RX2)
const int TXD2 = 17; // GPIO17 (TX2)

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conectar MQTT...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_pass)) {
      Serial.println("conectado");
      client.subscribe(topic_sub);
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5s");
      delay(5000);
    }
  }
}

// Callback para mensagens recebidas no tópico de inscrição
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida [");
  Serial.print(topic);
  Serial.print("]: ");
  String msg = "";
  for (unsigned int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }
  Serial.println(msg);

  // Encaminha para o Arduino via Serial2
  Serial2.println(msg);
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  setup_wifi();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Recebe dados do Arduino e publica no MQTT
  if (Serial2.available()) {
    String data = Serial2.readStringUntil('\n');
    data.trim();

    // LDR:1000,T:25.2,H:23.2
    int ldrIdx = data.indexOf("LDR:");
    int tIdx = data.indexOf(",T:");
    int hIdx = data.indexOf(",H:");

    if (ldrIdx != -1 && tIdx != -1 && hIdx != -1) {
      String ldr = data.substring(ldrIdx + 4, tIdx);
      String temp = data.substring(tIdx + 3, hIdx);
      String hum = data.substring(hIdx + 3);

      // Monta o JSON
      StaticJsonDocument<128> doc;
      doc["ldr"] = ldr.toInt();
      doc["temp"] = temp.toFloat();
      doc["hum"] = hum.toFloat();

      char buffer[128];
      size_t n = serializeJson(doc, buffer);

      Serial.print("Publicando MQTT: ");
      Serial.println(buffer);

      client.publish(topic_pub, buffer, n);
    }
  }
}

// [env:esp32dev]
// platform = espressif32
// board = esp32dev
// framework = arduino
// monitor_port=COM2
// monitor_speed=115200
// lib_deps =
//     knolleary/PubSubClient@^2.8
//     bblanchon/ArduinoJson@^6.21.3