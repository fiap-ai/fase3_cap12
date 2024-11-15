# Documentação Técnica - Sistema de Monitoramento Agrícola

## 1. Especificações dos Sensores

### 1.1 DHT22 (AM2302)
- **Especificações**:
  - Faixa de temperatura: -40 a 80°C (±0.5°C)
  - Faixa de umidade: 0-100% (±2-5%)
  - Tempo de resposta: 2s
  - Tensão de operação: 3.3-6V
- **Conexões**:
  - VCC: 3.3V
  - DATA: GPIO definido
  - GND: Ground
- **Biblioteca**: DHT.h
- **Função**: Monitoramento climático e controle de irrigação

### 1.2 HC-SR04
- **Especificações**:
  - Alcance: 2-400cm
  - Precisão: 3mm
  - Ângulo de medição: 15°
  - Tensão de operação: 5V
- **Conexões**:
  - VCC: 5V
  - TRIG: GPIO definido
  - ECHO: GPIO definido
  - GND: Ground
- **Biblioteca**: Ultrasonic.h
- **Função**: Monitoramento de nível de água

### 1.3 PIR (HC-SR501)
- **Especificações**:
  - Alcance: até 7m
  - Ângulo de detecção: 120°
  - Tensão de operação: 5-20V
  - Delay ajustável
- **Conexões**:
  - VCC: 5V
  - OUT: GPIO definido
  - GND: Ground
- **Função**: Detecção de movimento e segurança

### 1.4 LDR
- **Especificações**:
  - Resistência variável com luz
  - Tensão de operação: 3.3-5V
  - Necessita resistor pull-down
- **Conexões**:
  - VCC: 3.3V
  - OUT: GPIO/ADC definido
  - GND: Ground (via resistor)
- **Função**: Monitoramento de luminosidade

## 2. Lógica de Integração

### 2.1 Sistema de Decisão
```cpp
struct SensorData {
    float temperature;
    float humidity;
    float waterLevel;
    bool motion;
    int lightLevel;
};

class DecisionSystem {
    public:
        void updateData(SensorData data);
        bool shouldIrrigate();
        bool isSecurityBreached();
        void adjustIrrigation();
    private:
        SensorData currentData;
        // Thresholds e lógica de decisão
};
```

### 2.2 Thresholds e Parâmetros
- Temperatura ideal: 20-30°C
- Umidade ideal: 60-80%
- Nível mínimo de água: 20%
- Luminosidade para irrigação: Ajuste dinâmico
- Tempo entre leituras: 5 minutos
- Tempo de irrigação: Baseado em umidade

## 3. Fluxo de Dados

1. Coleta periódica de dados dos sensores
2. Processamento e análise
3. Tomada de decisão
4. Execução de ações
5. Registro de dados
6. Geração de alertas (se necessário)

## 4. Protocolo de Comunicação

### 4.1 Serial Monitor
- Baud rate: 115200
- Formato de log:
```
[TIMESTAMP] SENSOR:VALUE ACTION:RESULT
```

### 4.2 Formato de Dados
```json
{
    "timestamp": "YYYY-MM-DD HH:MM:SS",
    "sensors": {
        "temperature": 25.5,
        "humidity": 65.0,
        "waterLevel": 80.5,
        "motion": false,
        "light": 750
    },
    "actions": {
        "irrigation": "ON/OFF",
        "alert": "NONE/MOTION/WATER_LOW"
    }
}
```

## 5. Algoritmos de Controle

### 5.1 Controle de Irrigação
```cpp
bool shouldIrrigate() {
    // Verifica condições para irrigação
    if (waterLevel < WATER_MIN_LEVEL) return false;
    if (humidity > HUMIDITY_MAX) return false;
    
    float irrigationScore = 0;
    irrigationScore += (TEMP_MAX - temperature) * TEMP_WEIGHT;
    irrigationScore += (HUMIDITY_IDEAL - humidity) * HUMIDITY_WEIGHT;
    irrigationScore += (lightLevel * LIGHT_WEIGHT);
    
    return irrigationScore > IRRIGATION_THRESHOLD;
}
```

### 5.2 Sistema de Segurança
```cpp
void checkSecurity() {
    if (motion && !isWorkingHours()) {
        triggerAlert();
        logSecurityBreach();
    }
}
```

## 6. Manutenção e Calibração

### 6.1 Rotina de Calibração
1. Inicialização dos sensores
2. Leituras de referência
3. Ajuste de thresholds
4. Validação de leituras

### 6.2 Manutenção Preventiva
- Limpeza dos sensores: mensal
- Verificação de conexões: semanal
- Calibração: trimestral
- Backup de dados: diário

## 7. Tratamento de Erros

### 7.1 Códigos de Erro
- E01: Falha de leitura DHT22
- E02: Timeout HC-SR04
- E03: Falha na irrigação
- E04: Nível crítico de água

### 7.2 Recuperação de Erros
```cpp
void handleError(int errorCode) {
    logError(errorCode);
    switch(errorCode) {
        case E01:
            resetDHT();
            break;
        case E02:
            recalibrateUltrasonic();
            break;
        // ...
    }
}
```

## 8. Testes e Validação

### 8.1 Testes Unitários
- Verificação individual de sensores
- Validação de leituras
- Teste de thresholds

### 8.2 Testes Integrados
- Funcionamento conjunto dos sensores
- Sistema de decisão
- Resposta a condições críticas

### 8.3 Testes de Campo
- Validação em ambiente real
- Ajuste fino de parâmetros
- Verificação de durabilidade
