/*
 * Código para el control de un LCD por I2C
 * Autor: Augusto Samuel Hernández Martín
 * GitHub: AugustoS97 (https://github.com/AugustoS97)
 */
 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // Se ajusta la direccion a 0x27 y el tamaño 16x2

void setup(){
  lcd.init();                      // Inicializa LCD
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hola, mundo!");
  lcd.setCursor(0,1);
  lcd.print("InFuture 2022!");
}


void loop(){
  
}
