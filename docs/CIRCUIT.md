# Diagrama de Circuito e Conexões

## 1. Pinout ESP32

### 1.1 Pinos Utilizados
```
GPIO Assignments:
- DHT22: GPIO 4
- HC-SR04 TRIG: GPIO 5
- HC-SR04 ECHO: GPIO 18
- PIR: GPIO 19
- LDR: GPIO 34 (ADC1_6)
```

## 2. Diagrama de Conexões

```
ESP32                                 Sensores
┌──────────┐                    DHT22
│          │                    ┌─────────┐
│ 3.3V ────┼────────────────┬──┤ VCC     │
│          │                │  │         │
│ GPIO4 ───┼────────────────┴──┤ DATA    │
│          │                   │         │
│ GND ─────┼───────────────────┤ GND     │
│          │                   └─────────┘
│          │                    HC-SR04
│          │                    ┌─────────┐
│ 5V ──────┼───────────────────┤ VCC     │
│          │                   │         │
│ GPIO5 ───┼───────────────────┤ TRIG    │
│          │                   │         │
│ GPIO18 ──┼───────────────────┤ ECHO    │
│          │                   │         │
│ GND ─────┼───────────────────┤ GND     │
│          │                   └─────────┘
│          │                    PIR
│          │                    ┌─────────┐
│ 5V ──────┼───────────────────┤ VCC     │
│          │                   │         │
│ GPIO19 ──┼───────────────────┤ OUT     │
│          │                   │         │
│ GND ─────┼───────────────────┤ GND     │
│          │                   └─────────┘
│          │                    LDR
│          │                    ┌─────────┐
│ 3.3V ────┼───────────────────┤ VCC     │
│          │                   │         │
│ GPIO34 ──┼───────────────────┤ OUT     │
│          │                   │         │
│ GND ─────┼───────────────────┤ GND     │
└──────────┘                   └─────────┘
```

## 3. Especificações de Componentes

### 3.1 Componentes Necessários
- 1x ESP32 DevKit
- 1x Sensor DHT22
- 1x Sensor HC-SR04
- 1x Sensor PIR HC-SR501
- 1x LDR
- 1x Resistor 10kΩ (para LDR)
- Jumpers/fios para conexão
- Protoboard

### 3.2 Alimentação
- ESP32: USB ou fonte externa 5V
- DHT22: 3.3V
- HC-SR04: 5V
- PIR: 5V
- LDR: 3.3V

## 4. Considerações de Montagem

### 4.1 DHT22
- Resistor pull-up interno do ESP32
- Distância máxima recomendada: 20m
- Proteção contra interferência: usar cabo blindado se necessário

### 4.2 HC-SR04
- Divisor de tensão não necessário (ESP32 é 5V tolerant no ECHO)
- Posicionar sensor com área livre para medição
- Evitar obstáculos no cone de medição

### 4.3 PIR
- Tempo de warm-up: 1 minuto
- Ajustar sensibilidade e delay via potenciômetros
- Posicionar em altura adequada (2-3m recomendado)

### 4.4 LDR
- Divisor de tensão com resistor 10kΩ
- Posicionar com visão clara do céu
- Proteger contra umidade

## 5. Validação no Wokwi

### 5.1 Checklist de Validação do Diagrama
- [ ] Verificar tensões de alimentação corretas
- [ ] Confirmar pinout do ESP32
- [ ] Validar conexões de cada sensor
- [ ] Verificar resistores e componentes auxiliares
- [ ] Testar continuidade no diagrama

### 5.2 Validação do diagram.json
- [ ] Componentes corretamente especificados
- [ ] Pinos configurados conforme documentação
- [ ] Conexões seguindo o diagrama
- [ ] Valores dos componentes corretos
- [ ] Posicionamento adequado no grid

### 5.3 Testes Iniciais
1. Verificar alimentação de todos os componentes
2. Testar comunicação básica com cada sensor
3. Validar leituras iniciais
4. Confirmar ausência de conflitos de pinos

### 5.4 Pontos de Atenção
- Verificar compatibilidade dos componentes no Wokwi
- Confirmar suporte às bibliotecas necessárias
- Validar limites de corrente e tensão
- Testar diferentes condições de operação

## 6. Pontos de Teste

### 6.1 Tensões Esperadas
```
Ponto         Tensão Esperada
VCC DHT22     3.3V
VCC HC-SR04   5V
VCC PIR       5V
VCC LDR       3.3V
```

### 6.2 Sinais Lógicos
```
Ponto         Nível Lógico
DHT22 DATA    Pull-up (HIGH em repouso)
HC-SR04 TRIG  LOW em repouso
HC-SR04 ECHO  LOW em repouso
PIR OUT       LOW sem movimento
LDR OUT       Variável com luz
```

## 7. Troubleshooting

### 7.1 Problemas Comuns
1. DHT22 não responde
   - Verificar alimentação
   - Testar continuidade do DATA
   - Confirmar resistor pull-up

2. HC-SR04 leituras incorretas
   - Verificar alimentação 5V
   - Testar conexões TRIG/ECHO
   - Verificar obstáculos

3. PIR falsos positivos
   - Ajustar sensibilidade
   - Verificar interferências
   - Reposicionar sensor

4. LDR leituras instáveis
   - Verificar divisor de tensão
   - Testar diferentes resistores
   - Melhorar posicionamento

### 7.2 Soluções
1. Usar multímetro para verificar tensões
2. Testar componentes individualmente
3. Verificar qualidade das conexões
4. Atualizar firmware se necessário

## 8. Próximos Passos
1. Aguardar diagram.json do Wokwi
2. Realizar validação completa das conexões
3. Testar simulação básica
4. Documentar resultados da validação
5. Prosseguir com implementação após aprovação
