# Procedimentos de Teste - Sistema de Monitoramento Agrícola

## 1. Testes Unitários

### 1.1 DHT22
- [x] Leitura de temperatura
  ```
  Temperatura: 24.00°C (OK)
  ```
- [x] Leitura de umidade
  ```
  Umidade: 40.00% (OK)
  ```
- [x] Validação de dados inválidos
- [x] Resposta a diferentes condições

### 1.2 HC-SR04
- [x] Medição de distância
  ```
  Distância: 399.98 cm (OK)
  ```
- [x] Precisão das leituras
- [x] Estabilidade do sensor

### 1.3 PIR
- [x] Detecção de movimento
  ```
  Movimento Detectado: SIM/NÃO (OK)
  ```
- [x] Tempo de resposta
- [x] Cooldown entre detecções

### 1.4 LDR
- [x] Leitura de luminosidade
  ```
  Valor Raw: 1891
  Percentual de Luz: 46.18% (OK)
  ```
- [x] Conversão de valores
- [x] Resposta a mudanças de luz

### 1.5 Buzzer
- [x] Geração de tom
  ```
  Frequência: 2000Hz
  Canal PWM: 0
  Padrão: 3 beeps
  ```
- [x] Padrão de beeps
- [x] Controle PWM

### 1.6 Relé
- [x] Acionamento
- [x] Estado inicial
- [x] Controle da bomba

### 1.7 LCD
- [x] Inicialização I2C
- [x] Exibição de caracteres
- [x] Atualização dinâmica

## 2. Testes de Integração

### 2.1 Sistema de Irrigação
- [x] Decisão baseada em múltiplos sensores:
  ```
  Condições testadas:
  - Temperatura > 30°C
  - Umidade < 40%
  - Nível de água > 50cm
  - Luminosidade < 60%
  ```
- [x] Controle da bomba
- [x] Feedback no LCD

### 2.2 Sistema de Segurança
- [x] Detecção e alarme
  ```
  Sequência:
  1. Detecção de movimento
  2. Ativação do buzzer (3 beeps)
  3. Atualização do LCD
  4. Cooldown de 30s
  ```
- [x] Padrão sonoro
- [x] Indicação visual

### 2.3 Interface do Usuário
- [x] Atualização do LCD
  ```
  Layout:
  Linha 1: T:24.0C U:40.0%
  Linha 2: Status/Alertas
  ```
- [x] Logs no Serial
- [x] Indicadores de estado

## 3. Resultados dos Testes

### 3.1 Leituras dos Sensores
```
============================
Realizando leituras...

=== DHT22 Readings ===
Temperatura: 24.00°C
Umidade: 40.00%

=== HC-SR04 Reading ===
Distância: 399.98 cm

=== PIR Sensor Reading ===
Movimento Detectado: NÃO

=== LDR Sensor Reading ===
Valor Raw: 1891
Percentual de Luz: 46.18%
============================
```

### 3.2 Estado do Sistema
```
=== System Status ===
Bomba de Irrigação: DESLIGADA
Sistema de Alarme: DESATIVADO
```

## 4. Validação de Requisitos

### 4.1 Funcionais
- [x] Monitoramento ambiental
  - Temperatura e umidade
  - Nível de água
  - Luminosidade
  - Detecção de movimento
- [x] Automação
  - Sistema de irrigação
  - Sistema de segurança
- [x] Interface
  - Display LCD
  - Logs Serial
  - Indicadores sonoros

### 4.2 Não Funcionais
- [x] Performance
  - Tempo de resposta < 100ms
  - Atualização LCD a cada 2s
- [x] Confiabilidade
  - Tratamento de erros
  - Validação de dados
- [x] Usabilidade
  - Interface clara
  - Feedback constante

## 5. Conclusão

O sistema foi testado e validado com sucesso, demonstrando:

1. Funcionalidades:
- Todos os sensores operando corretamente
- Atuadores respondendo adequadamente
- Interface funcionando conforme esperado

2. Integração:
- Comunicação efetiva entre componentes
- Lógica de automação funcionando
- Sistema de alertas ativo

3. Performance:
- Tempo de resposta adequado
- Estabilidade nas leituras
- Uso eficiente de recursos

O sistema está pronto para uso, atendendo todos os requisitos especificados no projeto.
