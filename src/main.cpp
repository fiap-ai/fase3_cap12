#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//=====================================
// Pin Definitions
//=====================================
#define DHT_PIN 22     // DHT22: Sensor de temperatura e umidade
#define TRIG_PIN 5     // HC-SR04: Trigger do sensor ultrassônico
#define ECHO_PIN 18    // HC-SR04: Echo do sensor ultrassônico
#define PIR_PIN 19     // PIR: Sensor de movimento
#define LDR_PIN 34     // LDR: Sensor de luminosidade (ADC)
#define BUZZER_PIN 4   // Buzzer para alarme
#define RELAY_PIN 26   // Relé para bomba d'água

// I2C Pins
#define SDA_PIN 21     // Serial Data
#define SCL_PIN 23     // Serial Clock

//=====================================
// Constants
//=====================================
#define DHT_TYPE DHT22         // Modelo do sensor DHT
#define WATER_MIN 50.0         // Nível mínimo de água (cm)
#define TEMP_MAX 25.0          // Temperatura máxima (°C)
#define HUMIDITY_MIN 40.0      // Umidade mínima (%)
#define HUMIDITY_MAX 80.0      // Umidade máxima (%)
#define LIGHT_THRESHOLD 20.0   // Threshold de luz (%) - Abaixo: escuro, Acima: claro

//=====================================
// Instâncias Globais
//=====================================
// DHT22 para temperatura e umidade
static DHT dht(DHT_PIN, DHT_TYPE);
// LCD I2C para interface visual
static LiquidCrystal_I2C lcd(0x27, 16, 2);

//=====================================
// Estados do Sistema
//=====================================
static bool isPumpActive = false;        // Estado da bomba de irrigação
static bool isAlarmActive = false;       // Estado do alarme de segurança
static unsigned long lastAlarmTrigger = 0;  // Timestamp do último alarme
static const unsigned long ALARM_COOLDOWN = 10000; // 10 segundos entre alarmes

// Armazena o motivo da não irrigação
static String irrigationStatus = "";

//=====================================
// Configuração do Buzzer
//=====================================
#define BUZZER_FREQ 2000      // Frequência do buzzer em Hz
#define BUZZER_DUTY 128       // 50% duty cycle (0-255)
#define BUZZER_RESOLUTION 8   // Resolução em bits

//=====================================
// Funções dos Sensores
//=====================================
float readUltrasonic() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    
    long duration = pulseIn(ECHO_PIN, HIGH);
    return duration * 0.034 / 2;
}

bool readPIR() {
    return digitalRead(PIR_PIN);
}

float readLDR() {
    int ldrValue = analogRead(LDR_PIN);
    return (ldrValue / 4095.0) * 100;
}

//=====================================
// Inicialização I2C e LCD
//=====================================
void initI2C() {
    // Inicializa I2C com os pinos corretos
    Wire.begin(SDA_PIN, SCL_PIN);
    delay(100); // Tempo para estabilização do I2C
    
    // Configura o LCD
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.print("Iniciando...");
    Serial.println("LCD inicializado!");
}

//=====================================
// Interface LCD
//=====================================
void updateLCD(float temp, float hum, float water, bool motion) {
    lcd.clear();
    
    // Linha 1: Temperatura e Umidade
    lcd.setCursor(0, 0);
    lcd.printf("T:%.1fC U:%.1f%%", temp, hum);
    
    // Linha 2: Estado do Sistema
    lcd.setCursor(0, 1);
    if (isAlarmActive) {
        lcd.print("ALERTA-MOVIMENTO!");
    } else if (isPumpActive) {
        lcd.print("IRRIGANDO...");
    } else if (irrigationStatus != "") {
        // Mostra o motivo da não irrigação
        lcd.print(irrigationStatus);
    } else {
        lcd.printf("Agua:%.0fcm", water);
    }
}

//=====================================
// Sistema de Alarme
//=====================================
void soundBuzzer() {
    // Padrão de 3 beeps para alerta
    for (int i = 0; i < 3; i++) {
        tone(BUZZER_PIN, BUZZER_FREQ);  // Tom de 2kHz
        delay(100);                      // Duração do beep
        noTone(BUZZER_PIN);             // Silêncio
        delay(100);                      // Intervalo entre beeps
    }
}

//=====================================
// Controle da Bomba
//=====================================
void controlPump(bool active) {
    digitalWrite(RELAY_PIN, active);
    isPumpActive = active;
}

//=====================================
// Lógica de Automação
//=====================================
// Verifica condições ambientais para irrigação
bool checkEnvironmentalConditions(float temperature, float humidity, float lightLevel) {
    // Condições que podem ativar a irrigação
    bool tempTrigger = temperature > TEMP_MAX;      // Temperatura acima de 25°C
    bool humidityLow = humidity < HUMIDITY_MIN;     // Umidade abaixo de 40%
    bool humidityHigh = humidity > HUMIDITY_MAX;    // Umidade acima de 80%
    bool lightOk = lightLevel > LIGHT_THRESHOLD;    // Luz acima de 20%

    // Atualiza status para o LCD
    if (!lightOk) {
        irrigationStatus = "Escuro demais!";
    } else if (humidityHigh) {
        irrigationStatus = "Umidade alta!";
    } else if (!tempTrigger && !humidityLow) {
        irrigationStatus = "Aguardando...";
    } else {
        irrigationStatus = "";
    }

    // Log das condições para debug
    if (tempTrigger) Serial.println("Temperatura acima do máximo!");
    if (humidityLow) Serial.println("Umidade abaixo do mínimo!");
    if (humidityHigh) Serial.println("Umidade acima do máximo!");
    if (!lightOk) Serial.println("Escuro demais para irrigação!");

    // Lógica de irrigação:
    // - Irriga se temperatura alta OU umidade baixa
    // - E umidade não está muito alta
    // - E tem luz suficiente (não irriga no escuro)
    return (tempTrigger || humidityLow) && !humidityHigh && lightOk;
}

// Verifica condições de segurança
bool checkSafetyConditions(float waterLevel, bool motionDetected) {
    // Condições de segurança
    bool waterLevelOk = waterLevel >= WATER_MIN;  // Nível de água acima de 50cm
    bool securityOk = !motionDetected;            // Sem movimento detectado

    // Atualiza status para o LCD
    if (!waterLevelOk) {
        irrigationStatus = "Agua baixa!";
    } else if (!securityOk) {
        irrigationStatus = "Movimento detectado!";
    }

    // Log das condições de segurança
    if (!waterLevelOk) {
        Serial.println("ALERTA: Nível de água abaixo do mínimo!");
    }
    if (!securityOk) {
        Serial.println("ALERTA: Movimento detectado - Irrigação bloqueada!");
    }

    return waterLevelOk && securityOk;
}

// Sistema principal de irrigação
void checkIrrigation(float temperature, float humidity, float waterLevel, float lightLevel, bool motionDetected) {
    // Verifica todas as condições
    bool shouldIrrigate = checkEnvironmentalConditions(temperature, humidity, lightLevel);
    bool safeToIrrigate = checkSafetyConditions(waterLevel, motionDetected);

    // Atualiza estado da irrigação
    if (shouldIrrigate && safeToIrrigate && !isPumpActive) {
        Serial.println("\nIniciando irrigação:");
        if (temperature > TEMP_MAX) Serial.println("- Temperatura alta");
        if (humidity < HUMIDITY_MIN) Serial.println("- Umidade baixa");
        Serial.println("- Luz adequada para irrigação");
        Serial.println("- Condições de segurança OK");
        irrigationStatus = "";  // Limpa status ao iniciar irrigação
        controlPump(true);
    } else if ((!shouldIrrigate || !safeToIrrigate) && isPumpActive) {
        Serial.println("\nParando irrigação:");
        if (!shouldIrrigate) {
            if (lightLevel <= LIGHT_THRESHOLD) {
                Serial.println("- Muito escuro para irrigar");
            } else if (humidity > HUMIDITY_MAX) {
                Serial.println("- Umidade muito alta");
            } else {
                Serial.println("- Condições ambientais normalizadas");
            }
        }
        if (!safeToIrrigate) Serial.println("- Condições de segurança comprometidas");
        controlPump(false);
    }
}

//=====================================
// Sistema de Segurança
//=====================================
void checkSecurity(bool motionDetected) {
    unsigned long currentMillis = millis();
    
    // Ativa alarme se detectar movimento
    if (motionDetected && !isAlarmActive && 
        (currentMillis - lastAlarmTrigger > ALARM_COOLDOWN)) {
        Serial.println("ALERTA: Movimento detectado!");
        isAlarmActive = true;
        lastAlarmTrigger = currentMillis;
        soundBuzzer();
    } 
    // Desativa alarme após o cooldown
    else if (isAlarmActive && 
             (currentMillis - lastAlarmTrigger > ALARM_COOLDOWN)) {
        isAlarmActive = false;
        Serial.println("Sistema de segurança: Situação normalizada");
    }
}

//=====================================
// Leitura dos Sensores
//=====================================
void printSensorReadings(float temperature, float humidity, float waterLevel, bool motion, float lightLevel) {
    // DHT22: Temperatura e Umidade
    Serial.println("\n=== DHT22 Readings ===");
    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Erro: Falha ao ler sensor DHT22!");
    } else {
        Serial.print("Temperatura: ");
        Serial.print(temperature, 2);
        Serial.println("°C");
        
        Serial.print("Umidade: ");
        Serial.print(humidity, 2);
        Serial.println("%");
    }

    // HC-SR04: Nível de Água
    Serial.println("\n=== HC-SR04 Reading ===");
    Serial.print("Distância: ");
    Serial.print(waterLevel, 2);
    Serial.println(" cm");

    // PIR: Detecção de Movimento
    Serial.println("\n=== PIR Sensor Reading ===");
    Serial.print("Movimento Detectado: ");
    Serial.println(motion ? "SIM" : "NÃO");

    // LDR: Luminosidade
    Serial.println("\n=== LDR Sensor Reading ===");
    Serial.print("Percentual de Luz: ");
    Serial.print(lightLevel, 2);
    Serial.println("%");
}

//=====================================
// Inicialização do Sistema
//=====================================
void setup() {
    // Comunicação serial para debug
    Serial.begin(115200);
    Serial.println("\nIniciando Sistema de Monitoramento...");

    // Inicializa componentes
    initI2C();
    dht.begin();
    
    // Configura pinos
    pinMode(TRIG_PIN, OUTPUT);   // Trigger do HC-SR04
    pinMode(ECHO_PIN, INPUT);    // Echo do HC-SR04
    pinMode(PIR_PIN, INPUT);     // Entrada do PIR
    pinMode(BUZZER_PIN, OUTPUT); // Saída do buzzer
    pinMode(RELAY_PIN, OUTPUT);  // Controle do relé
    
    // Estados iniciais
    digitalWrite(RELAY_PIN, LOW);
    irrigationStatus = "";
    
    // Aguarda estabilização
    Serial.println("Aguardando estabilização dos sensores...");
    delay(5000);
    lcd.clear();
    lcd.print("Sistema Pronto!");
    Serial.println("Sistema Inicializado!");
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
    
    // Exibe leituras
    printSensorReadings(temperature, humidity, waterLevel, motionDetected, lightLevel);
    
    // Processa automação
    if (!isnan(humidity) && !isnan(temperature)) {
        checkIrrigation(temperature, humidity, waterLevel, lightLevel, motionDetected);
    }
    checkSecurity(motionDetected);
    
    // Atualiza display
    if (!isnan(humidity) && !isnan(temperature)) {
        updateLCD(temperature, humidity, waterLevel, motionDetected);
    }
    
    // Status do sistema
    Serial.println("\n=== System Status ===");
    Serial.print("Bomba de Irrigação: ");
    Serial.println(isPumpActive ? "LIGADA" : "DESLIGADA");
    Serial.print("Sistema de Alarme: ");
    Serial.println(isAlarmActive ? "ATIVADO" : "DESATIVADO");
    if (!isPumpActive && irrigationStatus != "") {
        Serial.print("Status: ");
        Serial.println(irrigationStatus);
    }
    
    Serial.println("============================");
    delay(1000);  // Intervalo entre leituras
}
