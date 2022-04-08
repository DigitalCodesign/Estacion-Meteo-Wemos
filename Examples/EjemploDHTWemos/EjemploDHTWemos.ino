/* Ejemplos para el control del DHT22 o DHT11 con Wemos D1
   Autor: Augusto Samuel Hernández Martín
   Github: https://github.com/AugustoS97
*/

// Requerimientos
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include <DHT.h>

#define DHTPIN D5     // DPin digital conectado al sensor. Debe encabezarse con D.
//En ESP8266 puede usarse pines 3,4,5,12,13 o 14

//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)


DHT dht(DHTPIN, DHTTYPE); //Inicializamos el DHT

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(2000);
  Serial.println("Test del DHTx!");

  dht.begin();
}

void loop() {


  //Se lee la Humedad y Temperatura
  float h = dht.readHumidity();

  float t = dht.readTemperature();


  //Mirar si alguna lectura fallo
  if (isnan(h) || isnan(t)) {
    Serial.println("Fallo al leer el sensor DHT!");
    return;
  }


  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print("%  Temperatura: ");
  Serial.print(t);
  Serial.println("°C ");

  // Esperamos 2 segundos entre medidas
  delay(2000);
}
