#include <ESP8266WiFi.h> // Para ESP8266
// #include <WiFi.h> // Para ESP32

const char* ssid = "Redmi Note 9S";
const char* password = "*******"; 

const char* host = "api.thingspeak.com";
String apiKey = "M0CHTB0UMQ8OCQO0"; //La clave API para hacer log-in en el server

void setup() {
Serial.begin(115200);
    delay(10);

  // Conecta a la red wifi.
  Serial.println();
  Serial.print("Conectando con ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Conectado con WiFi.");
}

void loop() {
    delay(16000); // Debes poner un tiempo de más de 15 segundos.
    int aleatorio = random(0,90);

    Serial.print("Conectando con ");
    Serial.println(host);

    // Clase cliente
    WiFiClient client;

    if (!client.connect(host, 80)) {
        Serial.println("Fallo en la conexión.");
        return;
    }

    String postStr = apiKey;
       postStr += "&field1=";
       postStr += String(aleatorio);
       postStr += "\r\n\r\n";
   
     client.print("POST /update HTTP/1.1\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(postStr.length());
     client.print("\n\n");
     client.print(postStr);
    client.print("Connection: close\n");
     client.stop();
}
