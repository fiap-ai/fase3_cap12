# Documentação Técnica - Sistema de Monitoramento Agrícola

## 1. Especificações dos Sensores e Atuadores

### 1.1 DHT22 (AM2302)
- **Pino**: GPIO22
- **Especificações**:
  - Faixa de temperatura: -40 a 80°C (±0.5°C)
  - Faixa de umidade: 0-100% (±2-5%)
  - Tempo de resposta: 2s
  - Tensão de operação: 3.3V
- **Função**: Monitoramento climático e controle de irrigação

### 1.2 HC-SR04
- **Pinos**: 
  - TRIG: GPIO5
  - ECHO: GPIO18
- **Especificações**:
  - Alcance: 2-400cm
  - Precisão: 3mm
  - Tensão de operação: 5V
- **Função**: Monitoramento de nível de água

### 1.3 PIR (HC-SR501)
- **Pino**: GPIO19
- **Especificações**:
  - Alcance: até 7m
  - Ângulo de detecção: 120°
  - Tensão de operação: 5V
- **Função**: Detecção de movimento e segurança

### 1.4 LDR
- **Pino**: GPIO34 (ADC)
- **Especificações**:
  - Tensão de operação: 3.3V
  - Leitura: ADC 12-bit (0-4095)
- **Função**: Monitoramento de luminosidade

### 1.5 Buzzer
- **Pino**: GPIO4
- **Especificações**:
  - Frequência: 2000Hz
  - Canal PWM: 0
  - Resolução: 8-bit
- **Função**: Alarme sonoro

### 1.6 Relé
- **Pino**: GPIO26
- **Especificações**:
  - Tensão de operação: 5V
  - Controle: Ativo alto
- **Função**: Controle da bomba d'água

### 1.7 LCD I2C
- **Pinos**:
  - SDA: GPIO21
  - SCL: GPIO23
- **Especificações**:
  - Endereço I2C: 0x27
  - Display: 16x2 caracteres
- **Função**: Interface visual do sistema

## 2. Lógica de Integração

### 2.1 Sistema de Irrigação
```cpp
Condições para irrigação:
- Temperatura > 30°C
- Umidade < 40%
- Nível de água > 50cm
- Luminosidade < 60%
```

### 2.2 Sistema de Segurança
```cpp
Condições de alarme:
- Movimento detectado
- Cooldown: 30 segundos
- Padrão sonoro: 3 beeps
```

### 2.3 Interface LCD
```cpp
Linha 1: Temperatura e Umidade
Linha 2: Estado do Sistema ou Alertas
```

## 3. Thresholds e Parâmetros

### 3.1 Limites de Operação
- Temperatura: 20-30°C
- Umidade: 40-80%
- Nível de água: 50-200cm
- Luminosidade: < 60%

### 3.2 Temporização
- Leitura de sensores: 2 segundos
- Cooldown do alarme: 30 segundos
- Duração do beep: 100ms
- Intervalo entre beeps: 100ms

## 4. Bibliotecas Utilizadas

### 4.1 Dependências
```ini
lib_deps = 
    adafruit/Adafruit Unified Sensor@^1.1.14
    adafruit/DHT sensor library@^1.4.6
    marcoschwartz/LiquidCrystal_I2C@^1.1.4
```

## 5. Protocolo de Comunicação

### 5.1 Serial Monitor
- Baud rate: 115200
- Formato: ASCII
- Logs estruturados por seção

### 5.2 I2C
- Frequência: Padrão
- Dispositivos:
  * LCD (0x27)

## 6. Fluxo de Operação

1. Inicialização
   - Configuração de pinos
   - Inicialização de sensores
   - Setup do LCD
   - Configuração do buzzer

2. Loop Principal
   - Leitura de sensores
   - Processamento de dados
   - Tomada de decisão
   - Atualização de outputs
   - Delay de 2 segundos

## 7. Tratamento de Erros

### 7.1 Verificações
- Leituras inválidas do DHT22
- Nível crítico de água
- Falhas de comunicação I2C

### 7.2 Recuperação
- Retry em falhas de leitura
- Desativação de irrigação em níveis críticos
- Mensagens de erro no LCD e Serial

## 8. Manutenção

### 8.1 Monitoramento
- Logs via Serial Monitor
- Status em tempo real no LCD
- Indicadores sonoros de estado

### 8.2 Calibração
- Thresholds ajustáveis via constantes
- Parâmetros de temporização configuráveis
- Padrões de alarme personalizáveis
