# Documentação do Sistema de Monitoramento Agrícola

## 📚 Índice da Documentação

### [📖 Documentação Técnica (TECHNICAL.md)](TECHNICAL.md)
- Especificações detalhadas dos sensores e atuadores
- Pinagem e conexões
- Protocolos de comunicação
- Thresholds e parâmetros
- Fluxo de operação
- Tratamento de erros

### [🧪 Documentação de Testes (TESTING.md)](TESTING.md)
- Instruções de instalação do ambiente
- Procedimentos de teste
- Testes unitários
- Testes de integração
- Resultados esperados
- Validação de requisitos

### [🔌 Documentação do Circuito (CIRCUIT.md)](CIRCUIT.md)
- Diagrama de conexões
- Lista de componentes
- Especificações elétricas
- Considerações de montagem

## 🔍 Visão Geral

Este sistema de monitoramento agrícola utiliza:
- ESP32 como microcontrolador principal
- DHT22 para temperatura e umidade
- HC-SR04 para nível de água
- PIR para detecção de movimento
- LDR para luminosidade
- LCD I2C para interface
- Buzzer para alarmes
- Relé para controle de irrigação

## 🎯 Principais Funcionalidades

1. Monitoramento Ambiental:
   - Temperatura (máx: 25°C)
   - Umidade (40-80%)
   - Nível de água (mín: 50cm)
   - Luminosidade (>20%)

2. Sistema de Segurança:
   - Detecção de movimento
   - Alarme sonoro
   - Cooldown de 10s

3. Interface:
   - Display LCD com status
   - Logs via Serial
   - Mensagens de estado

## 🛠️ Links Úteis

- [Simulação no Wokwi](https://wokwi.com/projects/414657136066505729)
- [Repositório no GitHub](https://github.com/fiap-ai/fase3_cap12)
- [Documentação do ESP32](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
- [Documentação do PlatformIO](https://docs.platformio.org/en/latest/)

## 📝 Notas de Versão

### v0.1.0 (25/03/2024)
- Implementação inicial do sistema
- Integração de sensores
- Sistema de irrigação automática
- Sistema de segurança
- Interface LCD
- Testes unitários
