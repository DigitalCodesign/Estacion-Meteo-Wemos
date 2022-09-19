# Estación Meteorológica con ThingSpeak

Proyecto desarrollado para implementar una estación meteorológica con volcado de datos a la red a través del servicio web de Thingspeak y su API de acceso gratuito.

## Autores: 
- José Luis González de Chávez 
- Augusto Samuel Hernández Martín
- Miqueas Z. Fortes

## Materiales

- [BMP280 I2C](https://www.digitalcodesign.com/shop/00016148-sensor-de-presion-y-temperatura-bmp280-3959?search=bmp280#attr=)
- [DHT22](https://www.digitalcodesign.com/shop/00016131-modulo-con-sensor-de-temperatura-y-humedad-dht22-3958?search=dht22#attr=)
- [Wemos D1](https://www.digitalcodesign.com/shop/00018340-wemos-d1-esp8266-wifi-4179?search=wemos#attr=)
- [Shield Protoboard Arduino UNO](https://www.digitalcodesign.com/shop/00016889-shield-protoboard-170-puntos-v-5-para-arduino-uno-4033?search=shield)
- [Portapilas 6F22](https://www.digitalcodesign.com/shop/00010528-adaptador-pila-9v-6f22-con-conector-dc-3397?search=6f22#attr=)
- [Pila 6F22 9V](https://www.digitalcodesign.com/shop/00010498-duracell-dur01925-pila-alcalina-plus-power-9v-6f22-3394?search=6f22#attr=)
- [Reloj RTC DS1307](https://www.digitalcodesign.com/shop/00016520-modulo-reloj-rtc-ds1307-at24c32-compatible-con-arduino-3997?search=rtc#attr=)
- [Display LCD 16x2 I2C](https://www.digitalcodesign.com/shop/00016025-pantalla-lcd-16x2-modulo-i2c-3947?search=lcd#attr=)

## Conexiones

- BMP280: 
	- Vcc -> 3.3V
	- GND -> GND
	- SDA -> SDA (D4)
	- SCL -> SCL (D3)
 - LCD 16x02 I2C:
 	- Vcc -> 5V
 	- GND -> GND
 	- SDA -> SDA (D4)
 	- SCL -> SCL (D3)
 - DHT22 (modulo con Rpull-up):
 	- Vcc -> 3.3V
 	- Do  -> D5 (GPIO14)
 	- GND -> GND

## Librerias

Debe instalarse lo siguiente:

- Placas Wemos D1 desde el Gestor de Placas de Arduino, añadiendo previamente el enlace de consulta: http://arduino.esp8266.com/stable/package_esp8266com_index.json
- Librería DHT.h desarrollada por Adafruit (disponible de forma oficial en Gestor de Librerías)
- Librería [BMP280_DEV](disponible en https://github.com/MartinL1/BMP280_DEV)
- Librería LiquidCrystal I2C disponible en el Gestor de Librerias

## Tools

- Se dispone de un escaner I2C para determinar las direcciones del BMP y del PCF8574 del Display LCD.
