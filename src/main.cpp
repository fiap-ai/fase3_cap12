#include <Arduino.h>
#include <DHT.h>

//=====================================
// Pin Definitions
//=====================================
// Sensores
#define DHT_PIN 22     // DHT22: Sensor de temperatura e umidade
#define TRIG_PIN 5     // HC-SR04: Trigger do sensor ultrassônico
#define ECHO_PIN 18    // HC-SR04: Echo do sensor ultrassônico
#define PIR_PIN 19     // PIR: Sensor de movimento
#define LDR_PIN 34     // LDR: Sensor de luminosidade (ADC)

// Atuadores e Indicadores
#define PUMP_PIN 25    // Simulação: Controle da bomba de irrigação
#define ALARM_PIN 26   // Simulação: Alarme de segurança
#define LED_PIN 27     // LED de status do sistema

//=====================================
// Configurações do Sistema
//=====================================
#define DHT_TYPE DHT22         // Modelo do sensor DHT
#define SERIAL_BAUD 115200     // Velocidade da comunicação serial
#define DELAY_MS 2000          // Intervalo entre leituras (2 segundos)

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

// Estados do sistema
bool isPumpActive = false;     // Estado da bomba de irrigação
bool isAlarmActive = false;    // Estado do alarme
unsigned long lastAlarmTrigger = 0;  // Último disparo do alarme
const unsigned long ALARM_COOLDOWN = 30000; // Tempo de espera entre alarmes (30s)

// Variáveis do sensor ultrassônico
long duration;  // Duração do pulso ultrassônico
float distance; // Distância calculada

//=====================================
// Declaração de Funções
//=====================================
void controlIrrigation(float temperature, float humidity, float waterLevel, float lightLevel);
void handleSecurity(bool motionDetected);
void updateStatusLED();

//=====================================
// Configuração Inicial
//=====================================
void setup() {
  // Inicializa comunicação serial
  Serial.begin(SERIAL_BAUD);
  Serial.println("\nIniciando Sistema de Monitoramento...");

  // Inicializa sensor DHT22
  dht.begin();
  
  // Configura pinos dos sensores e atuadores
  pinMode(TRIG_PIN, OUTPUT);   // Trigger do HC-SR04
  pinMode(ECHO_PIN, INPUT);    // Echo do HC-SR04
  pinMode(PIR_PIN, INPUT);     // Entrada do sensor PIR
  pinMode(PUMP_PIN, OUTPUT);   // Controle da bomba
  pinMode(ALARM_PIN, OUTPUT);  // Controle do alarme
  pinMode(LED_PIN, OUTPUT);    // LED de status
  
  // Define estados iniciais dos atuadores
  digitalWrite(PUMP_PIN, LOW);   // Bomba desligada
  digitalWrite(ALARM_PIN, LOW);  // Alarme desligado
  digitalWrite(LED_PIN, LOW);    // LED desligado
  
  // Aguarda estabilização dos sensores
  Serial.println("Aguardando estabilização dos sensores...");
  delay(5000);  // 5 segundos de delay inicial
  Serial.println("Sistema Inicializado!");
}

//=====================================
// Controle de Irrigação
//=====================================
void controlIrrigation(float temperature, float humidity, float waterLevel, float lightLevel) {
  bool shouldIrrigate = false;
  String reason = "";

  // Verifica se há água suficiente no reservatório
  if (waterLevel < WATER_MIN) {
    Serial.println("Irrigação bloqueada: Nível de água muito baixo!");
    isPumpActive = false;
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
    
    // Verifica luminosidade (irriga menos durante alta luminosidade)
    if (lightLevel < LIGHT_THRESHOLD) {
      shouldIrrigate = true;
      reason += "Luminosidade adequada; ";
    }
    
    // Atualiza estado da bomba
    if (shouldIrrigate && !isPumpActive) {
      Serial.println("Iniciando irrigação - Motivo: " + reason);
      isPumpActive = true;
    } else if (!shouldIrrigate && isPumpActive) {
      Serial.println("Parando irrigação - Condições normalizadas");
      isPumpActive = false;
    }
  }
  
  digitalWrite(PUMP_PIN, isPumpActive);
}

//=====================================
// Sistema de Segurança
//=====================================
void handleSecurity(bool motionDetected) {
  unsigned long currentMillis = millis();
  
  // Verifica movimento e tempo desde último alarme
  if (motionDetected && !isAlarmActive && 
      (currentMillis - lastAlarmTrigger > ALARM_COOLDOWN)) {
    Serial.println("ALERTA: Movimento detectado!");
    isAlarmActive = true;
    lastAlarmTrigger = currentMillis;
  } else if (isAlarmActive && 
             (currentMillis - lastAlarmTrigger > ALARM_COOLDOWN)) {
    isAlarmActive = false;  // Desativa alarme após cooldown
  }
  
  digitalWrite(ALARM_PIN, isAlarmActive);
}

//=====================================
// Indicador de Status
//=====================================
void updateStatusLED() {
  if (isAlarmActive) {
    digitalWrite(LED_PIN, HIGH);  // LED fixo quando alarme ativo
  } else if (isPumpActive) {
    // LED piscando quando bomba ativa
    digitalWrite(LED_PIN, (millis() / 500) % 2);
  } else {
    digitalWrite(LED_PIN, LOW);   // LED desligado em estado normal
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
  // Gera pulso de trigger
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Lê o tempo de retorno do eco
  duration = pulseIn(ECHO_PIN, HIGH);
  // Calcula distância (velocidade do som / 2)
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
  // Lê valor analógico (0-4095 para ESP32)
  int ldrValue = analogRead(LDR_PIN);
  // Converte para porcentagem
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
    controlIrrigation(temperature, humidity, waterLevel, lightLevel);
  }
  handleSecurity(motionDetected);
  updateStatusLED();
  
  // Imprime estado do sistema
  Serial.println("\n=== System Status ===");
  Serial.print("Bomba de Irrigação: ");
  Serial.println(isPumpActive ? "LIGADA" : "DESLIGADA");
  Serial.print("Sistema de Alarme: ");
  Serial.println(isAlarmActive ? "ATIVADO" : "DESATIVADO");
  
  Serial.println("============================");
  delay(DELAY_MS);  // Aguarda antes da próxima leitura
}
