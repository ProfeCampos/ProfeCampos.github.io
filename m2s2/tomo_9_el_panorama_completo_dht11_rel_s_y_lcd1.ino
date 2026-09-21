/*
 * Misión 09: El Panorama Completo
 * Descripción: Muestra Temp/Humedad del DHT11 en una LCD y activa un relé.
 * Por: Profe Campos
 * CECyTEM 05 Guacamayas
*/

// --- INCLUIR LIBRERÍAS ---
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Para la pantalla LCD
#include "DHT.h"                 // Para el sensor DHT

// --- CONFIGURACIÓN DE COMPONENTES ---
#define DHTPIN 2       // Pin donde está el DHT11
#define DHTTYPE DHT11  // Definimos que es un DHT11
const int pinRele = 7; // Pin para controlar el relé

// Inicializamos los objetos
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); // Dirección I2C, 16 columnas, 2 filas

void setup() {
  Serial.begin(9600);
  pinMode(pinRele, OUTPUT);
  digitalWrite(pinRele, LOW); // Nos aseguramos que el relé empiece apagado

  dht.begin(); // Iniciamos el sensor DHT
  
  lcd.init();      // Iniciamos la pantalla LCD
  lcd.backlight(); // Encendemos la luz de fondo
  lcd.setCursor(0, 0); // Ponemos el cursor en la columna 0, fila 0
  lcd.print("Estacion CTEC");
  lcd.setCursor(0, 1); // Columna 0, fila 1
  lcd.print("Iniciando...");
  delay(2000);
  lcd.clear(); // Limpiamos la pantalla
}

void loop() {
  delay(2000); // Esperamos 2 segundos entre lecturas

  // Leer la humedad y la temperatura toma unos 250ms
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Verificamos si la lectura falló (muy común con los DHT)
  if (isnan(h) || isnan(t)) {
    Serial.println("Error al leer del sensor DHT!");
    lcd.setCursor(0, 0);
    lcd.print("Error de Sensor");
    return; // Salimos del loop y lo intentamos de nuevo
  }

  // --- MOSTRAMOS EN LCD ---
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Hum:  ");
  lcd.print(h);
  lcd.print(" %");

  // --- LÓGICA DEL RELÉ ---
  if (t > 30.0) { // Si la temperatura supera los 30 grados
    digitalWrite(pinRele, HIGH); // Activamos el relé
  } else {
    digitalWrite(pinRele, LOW);  // Lo desactivamos
  }
}

