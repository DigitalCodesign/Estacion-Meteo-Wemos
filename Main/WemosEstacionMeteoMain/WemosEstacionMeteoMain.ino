/*
   Código para estación meteorologica en Wemos D1 con envio de datos a Thingspeak y visualización
   en tiempo real a través de un Display 16x02 I2C.
   Emplea un BMP280 (Tª, P(hPa) y Altitud (m)) y un DHT22 (Tª y H).
   Autor: Augusto Samuel Hernández Martín
   GitHub: AugustoS97 (https://github.com/AugustoS97)
*/

/*  PINOUT MONTAJE EN WEMOS D1 R1 (PCB TIPO ARDUINO UNO)
 *  BMP280: 
 *    Vcc -> 3.3V
 *    GND -> GND
 *    SDA -> SDA (D4)
 *    SCL -> SCL (D3)
 *  LCD 16x02 I2C:
 *    Vcc -> 5V
 *    GND -> GND
 *    SDA -> SDA (D4)
 *    SCL -> SCL (D3)
 *  DHT22 (modulo con Rpull-up):
 *    Vcc -> 3.3V
 *    Do  -> D5 (GPIO14)
 *    GND -> GND
 */
#define USELCD //Para usar el LCD deje esta linea. Si no lo usa, comentela

#include <DHT.h> //Se incluye para DHT
#include <ESP8266WiFi.h> //Se incluye para el Wemos
#include <BMP280_DEV.h>  //Se incluye para el BMP280

#ifdef USELCD
#include <Wire.h> //Se incluye para el I2C
#include <LiquidCrystal_I2C.h> //Se incluye para el LCD
#endif

#define DHTPIN D5 //No debe usarse el pin D2 en Wemos con DHT
#define DHTTYPE DHT22

// Reemplaza con la clave API de tu canal de thingspeak y tu SSID y password
String apiKey = "M0CHTB0UMQ8OCQO0";
const char* ssid = "Orange-DE5A";
const char* password = "25A4C36E";
const char* server = "api.thingspeak.com";

//Variables para el BMP
float temperatura, presion, altitud;

//Variables para el DHT
float humedad, temperaturaDHT, heatIndexDHT;

DHT dht(DHTPIN, DHTTYPE); //Se crea una instancia del sensor
WiFiClient client; //Se configura Wemos como cliente
BMP280_DEV bmp280;  //Se crea una instancia del sensor

#ifdef USELCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Se ajusta la direccion a 0x27 y el tamaño 16x2
#endif

void setup() {

  Serial.begin(115200); //Iniciamos comunicacion serie

  //Inicializar LCD
#ifdef USELCD
  lcd.init();                      // Inicializa LCD
  lcd.backlight();
#endif
  //Inicializar los sensores
  dht.begin();
  bmp280.begin(BMP280_I2C_ALT_ADDR);
  bmp280.setTimeStandby(TIME_STANDBY_05MS);     //Ajustar tiempo de stand-by del sensor
  bmp280.startNormalConversion();

  //Inicializar el WiFi
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

#ifdef USELCD
  lcd.setCursor(0, 0);
  lcd.print("Conectando a ");
  lcd.print(ssid);
#endif

  WiFi.begin(ssid, password);

#ifdef USELCD
  lcd.setCursor(0, 1);
#endif

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
#ifdef USELCD
    lcd.print(".");
#endif
  }

  Serial.println("");
  Serial.println("WiFi conectado");

#ifdef USELCD
  lcd.setCursor(0, 1);
  lcd.print("WiFi Conectado    ");
#endif
  //Fin de inicializacion WiFi

}

void loop() {
  //Lectura del DHT
  humedad = dht.readHumidity(); //Se lee la humedad
  temperaturaDHT = dht.readTemperature(); //Se lee la temperatura
  heatIndexDHT = dht.computeHeatIndex(temperaturaDHT, humedad); //Se calcula la sensación térmica
  
  if (isnan(humedad) || isnan(temperaturaDHT)) {
    Serial.println("Fallo al leer desde el DHT!");
    humedad = 0.0;
    temperaturaDHT = 0.0;
    return;
  }
  else {
    Serial.print("Humedad: ");
    Serial.print(humedad);
    Serial.print(" %   ");
    Serial.print(" Temperatura DHT: ");
    Serial.print(temperaturaDHT);
    Serial.print("*C   ");
    Serial.print("Sensación térmica: ");
    Serial.print(heatIndexDHT);
    Serial.println("*C   ");
  }

  //Lectura BMP
  bmp280.getCurrentMeasurements(temperatura, presion, altitud);   //Tomar los valores de la ultima medida
  Serial.print("Temperatura: ");  // Mostrar las medidas
  Serial.print(temperatura);
  Serial.print("*C   ");
  Serial.print("Presion: ");
  Serial.print(presion);
  Serial.print("hPa   ");
  Serial.print("Altitud: ");
  Serial.print(altitud);
  Serial.println("m");


  //Se envian los datos a Thingspeak
  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(temperatura);
    postStr += "&field2=";
    postStr += String(humedad);
    postStr += "&field3=";
    postStr += String(presion);
    postStr += "&field4=";
    postStr += String(altitud);
    postStr += "&field5=";
    postStr += String(heatIndexDHT);
    postStr += "rnrn";

    //Mensaje a enviar al Server
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    client.print("Connection: close\n");

    Serial.println("Enviando datos a Thingspeak");
  }
  client.stop(); //Fin del envio de datos

#ifdef USELCD
  //Se imprimen las medidas en el LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperatura, 1);//Se muestra con 1 decimal
  lcd.print("C|");
  lcd.print("H:");
  lcd.print(humedad);
  lcd.print("% ");
  lcd.setCursor(0, 1);
  lcd.print("A:");
  lcd.print(round(altitud),0); //Se muestra sin decimales
  lcd.print("m |");
  lcd.print("P:");
  lcd.print(round(presion),0);
  lcd.print("hPa");
#endif

  //Reposo del sistema hasta siguiente medida
  Serial.println("Esperando 20 segundos");
  /*
     Thingspeak necesita al menos 15 segundos entre actualizaciones
     20 segundos para estar seguros
  */
  delay(20000);
}
