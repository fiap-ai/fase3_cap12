#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//=====================================
// Pin Definitions
//=====================================
// Sensores
#define DHT_PIN 22     // DHT22: Sensor de temperatura e umidade
#define TRIG_PIN 5     // HC-SR04: Trigger do sensor ultrassônico
#define ECHO_PIN 18    // HC-SR04: Echo do sensor ultrassônico
#define PIR_PIN 19     // PIR: Sensor de movimento
#define LDR_PIN 34     // LDR: Sensor de luminosidade (ADC)

// Atuadores
#define BUZZER_PIN 4   // Buzzer para alarme
#define RELAY_PIN 26   // Relé para bomba d'água

// I2C Pins (LCD)
#define SDA_PIN 21     // Serial Data
#define SCL_PIN 23     // Serial Clock

//=====================================
// Configurações do Sistema
//=====================================
#define DHT_TYPE DHT22         // Modelo do sensor DHT
#define SERIAL_BAUD 115200     // Velocidade da comunicação serial
#define DELAY_MS 2000          // Intervalo entre leituras (2 segundos)
#define LCD_ADDR 0x27          // Endereço I2C do LCD
#define LCD_COLS 16            // Número de colunas do LCD
#define LCD_ROWS 2             // Número de linhas do LCD

// Configurações do Buzzer
#define BUZZER_FREQ 2000      // Frequência do som (2KHz)
#define BUZZER_CHANNEL 0      // Canal PWM para o buzzer
#define BEEP_DURATION 100     // Duração de cada beep (ms)
#define BEEP_INTERVAL 100     // Intervalo entre beeps (ms)
#define NUM_BEEPS 3           // Número de beeps no alerta

//=====================================
// Thresholds (Limites) do Sistema
//=====================================
// Limites para controle de irrigação
#define TEMP_MAX 30.0        // Temperatura máxima antes de irrigar
#define TEMP_MIN 20.0        // Temperatura mínima (referência)
#define HUMIDITY_MIN 40.0    // Umidade mínima antes de irrigar
#define HUMIDITY_MAX 80.0    // Umidade máxima (referência)
#define WATER_MIN 50.0       // Nível mínimo de água no reservatório
#define WATER_MAX 200.0      // Nível máximo do reservatório
#define LIGHT_THRESHOLD 60.0 // Limite de luz para ajuste de irrigação

//=====================================
// Variáveis Globais
//=====================================
// Inicialização do sensor DHT
DHT dht(DHT_PIN, DHT_TYPE);

// Inicialização do LCD
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

// Estados do sistema
bool isPumpActive = false;     // Estado da bomba
bool isAlarmActive = false;    // Estado do alarme
unsigned long lastAlarmTrigger = 0;  // Último disparo do alarme
const unsigned long ALARM_COOLDOWN = 3000; // Tempo entre alarmes (30s)

// Variáveis do sensor ultrassônico
long duration;  // Duração do pulso ultrassônico
float distance; // Distância calculada

//=====================================
// Configuração Inicial
//=====================================
void setup() {
  // Inicializa comunicação serial
  Serial.begin(SERIAL_BAUD);
  Serial.println("\nIniciando Sistema de Monitoramento...");

  // Inicializa I2C para LCD
  Wire.begin(SDA_PIN, SCL_PIN);
  
  // Inicializa LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Iniciando...");
  
  // Inicializa sensor DHT22
  dht.begin();
  
  // Configura pinos
  pinMode(TRIG_PIN, OUTPUT);   // Trigger do HC-SR04
  pinMode(ECHO_PIN, INPUT);    // Echo do HC-SR04
  pinMode(PIR_PIN, INPUT);     // Entrada do sensor PIR
  pinMode(BUZZER_PIN, OUTPUT); // Saída do buzzer
  pinMode(RELAY_PIN, OUTPUT);  // Saída do relé
  
  // Estados iniciais
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);
  
  // Configura canal do buzzer
  ledcSetup(BUZZER_CHANNEL, BUZZER_FREQ, 8); // Canal 0, 2000 Hz, 8-bit resolução
  ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
  
  // Aguarda estabilização dos sensores
  Serial.println("Aguardando estabilização dos sensores...");
  delay(5000);
  lcd.clear();
  lcd.print("Sistema Pronto!");
  Serial.println("Sistema Inicializado!");
}

//=====================================
// Funções do LCD
//=====================================
void updateLCD(float temp, float hum, float water, bool motion) {
  lcd.clear();
  
  // Primeira linha: Temperatura e Umidade
  lcd.setCursor(0, 0);
  lcd.printf("T:%.1fC U:%.1f%%", temp, hum);
  
  // Segunda linha: Estado do sistema
  lcd.setCursor(0, 1);
  if (isAlarmActive) {
    lcd.print("ALERTA-MOVIMENTO!");
  } else if (isPumpActive) {
    lcd.print("IRRIGANDO...");
  } else {
    lcd.printf("Agua:%.0fcm", water);
  }
}

//=====================================
// Controle de Atuadores
//=====================================
void soundBuzzer() {
  // Padrão de beep usando tone
  for (int i = 0; i < NUM_BEEPS; i++) {
    ledcWriteTone(BUZZER_CHANNEL, BUZZER_FREQ); // Inicia o tom
    delay(BEEP_DURATION);
    ledcWriteTone(BUZZER_CHANNEL, 0);           // Para o tom
    delay(BEEP_INTERVAL);
  }
}

void controlPump(bool active) {
  digitalWrite(RELAY_PIN, active);
  isPumpActive = active;
}

//=====================================
// Sistema de Irrigação
//=====================================
void checkIrrigation(float temperature, float humidity, float waterLevel, float lightLevel) {
  bool shouldIrrigate = false;
  String reason = "";

  // Verifica se há água suficiente no reservatório
  if (waterLevel < WATER_MIN) {
    Serial.println("ALERTA: Nível de água muito baixo no reservatório!");
    controlPump(false);
  } else {
    // Verifica temperatura
    if (temperature > TEMP_MAX) {
      shouldIrrigate = true;
      reason += "Temperatura alta; ";
    }
    
    // Verifica umidade
    if (humidity < HUMIDITY_MIN) {
      shouldIrrigate = true;
      reason += "Umidade baixa; ";
    }
    
    // Verifica luminosidade
    if (lightLevel < LIGHT_THRESHOLD) {
      shouldIrrigate = true;
      reason += "Luminosidade adequada; ";
    }
    
    // Atualiza estado da bomba
    if (shouldIrrigate && !isPumpActive) {
      Serial.println("Iniciando irrigação - Motivo: " + reason);
      controlPump(true);
    } else if (!shouldIrrigate && isPumpActive) {
      Serial.println("Parando irrigação - Condições normalizadas");
      controlPump(false);
    }
  }
}

//=====================================
// Sistema de Segurança
//=====================================
void checkSecurity(bool motionDetected) {
  unsigned long currentMillis = millis();
  
  if (motionDetected && !isAlarmActive && 
      (currentMillis - lastAlarmTrigger > ALARM_COOLDOWN)) {
    Serial.println("ALERTA: Movimento detectado!");
    isAlarmActive = true;
    lastAlarmTrigger = currentMillis;
    soundBuzzer();  // Ativa o alarme sonoro
  } else if (isAlarmActive && 
             (currentMillis - lastAlarmTrigger > ALARM_COOLDOWN)) {
    isAlarmActive = false;
  }
}

//=====================================
// Leitura dos Sensores
//=====================================
// Leitura do DHT22
void readDHT() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  Serial.println("\n=== DHT22 Readings ===");
  
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Erro: Falha ao ler sensor DHT22!");
    return;
  }

  Serial.print("Temperatura: ");
  Serial.print(temperature, 2);
  Serial.println("°C");
  
  Serial.print("Umidade: ");
  Serial.print(humidity, 2);
  Serial.println("%");
}

// Leitura do HC-SR04
float readUltrasonic() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  Serial.println("\n=== HC-SR04 Reading ===");
  Serial.print("Distância: ");
  Serial.print(distance, 2);
  Serial.println(" cm");
  
  return distance;
}

// Leitura do PIR
bool readPIR() {
  bool motionDetected = digitalRead(PIR_PIN);
  
  Serial.println("\n=== PIR Sensor Reading ===");
  Serial.print("Movimento Detectado: ");
  Serial.println(motionDetected ? "SIM" : "NÃO");
  
  return motionDetected;
}

// Leitura do LDR
float readLDR() {
  int ldrValue = analogRead(LDR_PIN);
  float percentage = (ldrValue / 4095.0) * 100;
  
  Serial.println("\n=== LDR Sensor Reading ===");
  Serial.print("Valor Raw: ");
  Serial.println(ldrValue);
  Serial.print("Percentual de Luz: ");
  Serial.print(percentage, 2);
  Serial.println("%");
  
  return percentage;
}

//=====================================
// Loop Principal
//=====================================
void loop() {
  Serial.println("\n============================");
  Serial.println("Realizando leituras...");
  
  // Lê todos os sensores
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  float waterLevel = readUltrasonic();
  bool motionDetected = readPIR();
  float lightLevel = readLDR();
  
  // Processa lógica de automação
  if (!isnan(humidity) && !isnan(temperature)) {
    checkIrrigation(temperature, humidity, waterLevel, lightLevel);
  }
  checkSecurity(motionDetected);
  
  // Atualiza LCD
  if (!isnan(humidity) && !isnan(temperature)) {
    updateLCD(temperature, humidity, waterLevel, motionDetected);
  }
  
  // Imprime estado do sistema
  Serial.println("\n=== System Status ===");
  Serial.print("Bomba de Irrigação: ");
  Serial.println(isPumpActive ? "LIGADA" : "DESLIGADA");
  Serial.print("Sistema de Alarme: ");
  Serial.println(isAlarmActive ? "ATIVADO" : "DESATIVADO");
  
  Serial.println("============================");
  delay(DELAY_MS);
}
