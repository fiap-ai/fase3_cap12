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
  - Conversão: 0-100%
- **Função**: Monitoramento de luminosidade

### 1.5 Buzzer
- **Pino**: GPIO4
- **Especificações**:
  - Frequência: 2000Hz
  - Controle: tone() padrão
  - Padrão: 3 beeps
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
- (Temperatura > 25°C OU Umidade < 40%) E
- Umidade não está acima de 80% E
- Luminosidade > 20% E
- Nível de água > 50cm E
- Sem movimento detectado
```

### 2.2 Sistema de Segurança
```cpp
Condições de alarme:
- Movimento detectado
- Cooldown: 10 segundos
- Padrão sonoro: 3 beeps
```

### 2.3 Interface LCD
```cpp
Linha 1: Temperatura e Umidade
Linha 2: Estados possíveis:
- "IRRIGANDO..." (sistema ativo)
- "ALERTA-MOVIMENTO!" (movimento detectado)
- "Escuro demais!" (pouca luz)
- "Umidade alta!" (umidade > 80%)
- "Agua baixa!" (nível < 50cm)
- "Aguardando..." (condições normais)
- "Agua:XXXcm" (nível de água)
```

## 3. Thresholds e Parâmetros

### 3.1 Limites de Operação
- Temperatura máxima: 25°C
- Umidade: 40-80%
- Nível mínimo de água: 50cm
- Luminosidade: > 20% (não irriga no escuro)

### 3.2 Temporização
- Leitura de sensores: 1 segundo
- Cooldown do alarme: 10 segundos
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
- Status detalhado do sistema

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
   - Aguarda 5s para estabilização

2. Loop Principal
   - Leitura de sensores
   - Processamento de dados
   - Tomada de decisão
   - Atualização de outputs
   - Delay de 1 segundo

## 7. Tratamento de Erros

### 7.1 Verificações
- Leituras inválidas do DHT22 (isnan)
- Nível crítico de água
- Falhas de comunicação I2C
- Condições fora dos limites

### 7.2 Recuperação
- Desativação de irrigação em condições críticas
- Mensagens de erro no LCD e Serial
- Status detalhado no Serial Monitor
- Indicação visual do motivo da não irrigação

## 8. Manutenção

### 8.1 Monitoramento
- Logs detalhados via Serial Monitor
- Status em tempo real no LCD
- Indicadores sonoros de estado
- Mensagens de status claras

### 8.2 Calibração
- Thresholds ajustáveis via constantes
- Parâmetros de temporização configuráveis
- Padrões de alarme personalizáveis
- Mensagens de status customizáveis
