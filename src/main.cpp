#include <Arduino.h>
#include <DHT.h>

// Pin Definitions
#define DHT_PIN 4
#define TRIG_PIN 5
#define ECHO_PIN 18
#define PIR_PIN 19
#define LDR_PIN 34

// Constants
#define DHT_TYPE DHT22
#define SERIAL_BAUD 115200
#define DELAY_MS 2000  // Delay between readings

// Initialize DHT sensor
DHT dht(DHT_PIN, DHT_TYPE);

// Variables for ultrasonic sensor
long duration;
float distance;

void setup() {
  // Initialize serial communication
  Serial.begin(SERIAL_BAUD);
  Serial.println("\nIniciando Sistema de Monitoramento...");

  // Initialize DHT sensor
  dht.begin();
  
  // Initialize Ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Initialize PIR sensor pin
  pinMode(PIR_PIN, INPUT);
  
  // LDR uses ADC, no pin initialization needed
  
  // Wait for sensors to stabilize (especially DHT22)
  Serial.println("Aguardando estabilização dos sensores...");
  delay(5000);  // Increased delay for better DHT22 initialization
  Serial.println("Sistema Inicializado!");
}

void readDHT() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  Serial.println("\n=== DHT22 Readings ===");
  
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Erro: Falha ao ler sensor DHT22!");
    Serial.println("Verificando possíveis causas:");
    Serial.println("1. Verifique as conexões dos pinos");
    Serial.println("2. Confirme se a biblioteca está correta");
    Serial.println("3. Tente aumentar o delay entre leituras");
    return;
  }

  Serial.print("Temperatura: ");
  Serial.print(temperature, 2);
  Serial.println("°C");
  
  Serial.print("Umidade: ");
  Serial.print(humidity, 2);
  Serial.println("%");
}

void readUltrasonic() {
  // Clear the TRIG_PIN
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Set the TRIG_PIN HIGH for 10 microseconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Read the ECHO_PIN, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHO_PIN, HIGH);
  
  // Calculate the distance
  distance = duration * 0.034 / 2;  // Speed of sound wave divided by 2

  Serial.println("\n=== HC-SR04 Reading ===");
  Serial.print("Distância: ");
  Serial.print(distance, 2);
  Serial.println(" cm");
}

void readPIR() {
  int motionDetected = digitalRead(PIR_PIN);
  
  Serial.println("\n=== PIR Sensor Reading ===");
  Serial.print("Movimento Detectado: ");
  Serial.println(motionDetected ? "SIM" : "NÃO");
}

void readLDR() {
  int ldrValue = analogRead(LDR_PIN);
  // ESP32 ADC is 12-bit (0-4095)
  float percentage = (ldrValue / 4095.0) * 100;
  
  Serial.println("\n=== LDR Sensor Reading ===");
  Serial.print("Valor Raw: ");
  Serial.println(ldrValue);
  Serial.print("Percentual de Luz: ");
  Serial.print(percentage, 2);
  Serial.println("%");
}

void loop() {
  Serial.println("\n============================");
  Serial.println("Realizando leituras...");
  
  readDHT();
  readUltrasonic();
  readPIR();
  readLDR();
  
  Serial.println("============================");
  delay(DELAY_MS);  // Wait before next reading
}
