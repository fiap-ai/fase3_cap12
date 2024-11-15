#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin Definitions
#define DHT_PIN 22
#define TRIG_PIN 5
#define ECHO_PIN 18
#define PIR_PIN 19
#define LDR_PIN 34
#define BUZZER_PIN 4
#define RELAY_PIN 26

// I2C Pins
#define SDA_PIN 21
#define SCL_PIN 23

// Constants
#define DHT_TYPE DHT22
#define WATER_MIN 50.0       // Nível mínimo de água (cm)
#define TEMP_MAX 25.0        // Temperatura máxima (°C)
#define HUMIDITY_MIN 40.0    // Umidade mínima (%)
#define HUMIDITY_MAX 80.0    // Umidade máxima (%)
#define LIGHT_THRESHOLD 20.0 // Threshold de luz (%) - Abaixo: escuro, Acima: claro

// Function declarations
float readUltrasonic();
bool readPIR();
float readLDR();

#endif // SENSORS_H
