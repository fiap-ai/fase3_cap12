# Procedimentos de Teste - Sistema de Monitoramento Agrícola

## Como Executar os Testes

### Pré-requisitos

1. Instalação do PlatformIO CLI:

**macOS (usando Homebrew):**
```bash
brew install platformio
```

**Linux:**
```bash
python3 -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/master/scripts/get-platformio.py)"
```

**Windows:**
```bash
python -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/master/scripts/get-platformio.py)"
```

Ou instale o VS Code com a extensão PlatformIO IDE.

2. Dependências do Projeto:
- ESP32 toolchain (instalado automaticamente pelo PlatformIO)
- Unity framework (incluído nas dependências do projeto)

### Verificando a Instalação
```bash
# Verificar se PlatformIO CLI está instalado
pio --version

# Verificar ambiente
pio system info
```

### Comandos para Execução
```bash
# Compilar e executar todos os testes
pio test

# Executar testes específicos
pio test -f test_dht22_reading_range
pio test -f test_ultrasonic_reading_range
pio test -f test_pir_initial_state
pio test -f test_ldr_reading_range

# Executar testes com saída detalhada
pio test -v

# Executar testes em um ambiente específico
pio test -e test
```

### Ambiente de Teste
O ambiente de teste está configurado no `platformio.ini`:
```ini
[env:test]
platform = espressif32
board = esp32doit-devkit-v1
framework = arduino
lib_deps = 
    adafruit/Adafruit Unified Sensor
    adafruit/DHT sensor library
    marcoschwartz/LiquidCrystal_I2C
    throwtheswitch/Unity
test_build_src = yes
build_flags = -D UNITY_INCLUDE_DOUBLE
test_filter = test_*
test_ignore = test/output
```

### Estrutura dos Testes
Os testes estão organizados em:
1. Testes Unitários (por componente)
2. Testes de Integração
3. Validações de Sistema

### Interpretando os Resultados
- ✓ (check): Teste passou
- ✕ (x): Teste falhou
- Detalhes de falha são exibidos no console
- Logs incluem valores esperados vs. obtidos

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
- [x] Validação de dados inválidos (isnan)
- [x] Resposta a diferentes condições
- [x] Limites de umidade (40-80%)

### 1.2 HC-SR04
- [x] Medição de distância
  ```
  Distância: 399.98 cm (OK)
  ```
- [x] Precisão das leituras
- [x] Estabilidade do sensor
- [x] Nível mínimo de água (50cm)

### 1.3 PIR
- [x] Detecção de movimento
  ```
  Movimento Detectado: SIM/NÃO (OK)
  ```
- [x] Tempo de resposta
- [x] Cooldown entre detecções (10s)

### 1.4 LDR
- [x] Leitura de luminosidade
  ```
  Valor Raw: 1891
  Percentual de Luz: 46.18% (OK)
  ```
- [x] Conversão de valores (0-100%)
- [x] Threshold de escuridão (20%)

### 1.5 Buzzer
- [x] Geração de tom
  ```
  Frequência: 2000Hz
  Duração: 100ms
  Padrão: 3 beeps
  ```
- [x] Padrão de beeps
- [x] Função tone()

### 1.6 Relé
- [x] Acionamento
- [x] Estado inicial (LOW)
- [x] Controle da bomba

### 1.7 LCD
- [x] Inicialização I2C
- [x] Exibição de caracteres
- [x] Atualização dinâmica
- [x] Estados do display:
  ```
  - "IRRIGANDO..."
  - "ALERTA-MOVIMENTO!"
  - "Escuro demais!"
  - "Umidade alta!"
  - "Agua baixa!"
  - "Aguardando..."
  - "Agua:XXXcm"
  ```

## 2. Testes de Integração

### 2.1 Sistema de Irrigação
- [x] Decisão baseada em múltiplos sensores:
  ```
  Condições testadas:
  - Temperatura > 25°C
  - Umidade < 40% ou > 80%
  - Nível de água > 50cm
  - Luminosidade > 20%
  ```
- [x] Controle da bomba
- [x] Feedback no LCD
- [x] Mensagens de status

### 2.2 Sistema de Segurança
- [x] Detecção e alarme
  ```
  Sequência:
  1. Detecção de movimento
  2. Ativação do buzzer (3 beeps)
  3. Atualização do LCD
  4. Cooldown de 10s
  ```
- [x] Padrão sonoro
- [x] Indicação visual
- [x] Bloqueio de irrigação

### 2.3 Interface do Usuário
- [x] Atualização do LCD
  ```
  Layout:
  Linha 1: T:24.0C U:40.0%
  Linha 2: Status/Alertas
  ```
- [x] Logs no Serial
- [x] Indicadores de estado
- [x] Mensagens de erro

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
Status: Aguardando...
```

## 4. Validação de Requisitos

### 4.1 Funcionais
- [x] Monitoramento ambiental
  - Temperatura e umidade (com limites)
  - Nível de água (mínimo)
  - Luminosidade (threshold)
  - Detecção de movimento
- [x] Automação
  - Sistema de irrigação
  - Sistema de segurança
  - Mensagens de status
- [x] Interface
  - Display LCD com estados
  - Logs Serial detalhados
  - Indicadores sonoros

### 4.2 Não Funcionais
- [x] Performance
  - Tempo de resposta < 100ms
  - Atualização LCD a cada 1s
- [x] Confiabilidade
  - Tratamento de erros
  - Validação de dados
  - Mensagens claras
- [x] Usabilidade
  - Interface clara
  - Feedback constante
  - Status detalhado

## 5. Conclusão

O sistema foi testado e validado com sucesso, demonstrando:

1. Funcionalidades:
- Todos os sensores operando corretamente
- Atuadores respondendo adequadamente
- Interface funcionando conforme esperado
- Mensagens de status claras

2. Integração:
- Comunicação efetiva entre componentes
- Lógica de automação funcionando
- Sistema de alertas ativo
- Status detalhado no LCD

3. Performance:
- Tempo de resposta adequado
- Estabilidade nas leituras
- Uso eficiente de recursos
- Feedback em tempo real

O sistema está pronto para uso, atendendo todos os requisitos especificados no projeto.
