# Sistema Inteligente de Monitoramento Agrícola com ESP32

## Objetivo do Projeto
Desenvolver um sistema inteligente de monitoramento agrícola utilizando ESP32 e quatro sensores (DHT22, HC-SR04, PIR e LDR) para otimizar recursos na agricultura através de coleta de dados e automação de decisões.

## Checklist de Desenvolvimento e Entrega

### 1. Configuração do Ambiente e Estrutura do Projeto
- [x] Criar estrutura base do projeto com PlatformIO
- [x] Validar diagrama do circuito no Wokwi
  - [x] Revisar conexões do diagrama.json
  - [x] Verificar pinout correto dos sensores
  - [x] Confirmar compatibilidade com ESP32
  - [x] Testar simulação básica
- [x] Configurar GitHub Repository com estrutura de pastas:
  - `/src`: Códigos-fonte
  - `/docs`: Documentação
  - `/tests`: Testes do sistema
- [x] Configurar branch 'develop' para desenvolvimento
- [x] Definir padrão de commits e Pull Requests

### 2. Implementação dos Sensores

#### 2.1 DHT22 (Temperatura e Umidade)
- [x] Implementar leitura de temperatura
- [x] Implementar leitura de umidade
- [x] Criar lógica de decisão para irrigação baseada em temperatura/umidade
- [x] Implementar sistema de alertas

#### 2.2 HC-SR04 (Ultrassom)
- [x] Implementar medição de nível de água
- [x] Criar sistema de monitoramento de reservatório
- [x] Desenvolver lógica de controle de irrigação baseada no nível

#### 2.3 PIR (Sensor de Movimento)
- [x] Implementar detecção de movimento
- [x] Criar sistema de alertas de segurança
- [x] Desenvolver lógica de acionamento de alarmes

#### 2.4 LDR (Sensor de Luz)
- [x] Implementar leitura de luminosidade
- [x] Criar lógica de ajuste de irrigação baseada na luz
- [x] Desenvolver sistema de otimização de recursos

### 3. Integração e Automação
- [x] Integrar todos os sensores no sistema
- [x] Implementar lógica de decisão combinada
- [x] Criar sistema de priorização de ações
- [x] Desenvolver rotinas de automação

### 4. Simulação e Testes
- [x] Criar projeto no Wokwi.com
- [x] Implementar circuito completo na simulação
- [x] Realizar testes individuais de cada sensor
- [x] Executar testes integrados do sistema
- [x] Documentar resultados dos testes
- [x] Validar todas as funcionalidades

### 5. Documentação
- [x] Criar diagrama do circuito
- [x] Documentar configuração de cada sensor
- [x] Escrever instruções de instalação
- [x] Documentar dependências do projeto
- [x] Criar guia de configuração do Wokwi
- [x] Incluir prints do Monitor Serial
- [x] Documentar testes realizados

### 6. Entrega Final
- [x] Revisar código e comentários
- [x] Verificar commits e histórico
- [ ] Criar Pull Request para main
- [ ] Realizar code review
- [ ] Preparar documentação final
- [ ] Postar link do GitHub no portal do aluno

## Implementações Realizadas

### 1. Hardware Integrado
- ESP32 DevKit com todos os sensores conectados
- Buzzer para alertas sonoros (GPIO4)
- Relé para controle de bomba d'água (GPIO26)
- Display LCD I2C para visualização (SDA: GPIO21, SCL: GPIO23)

### 2. Funcionalidades Implementadas
- Sistema de irrigação automatizado baseado em múltiplos sensores
- Sistema de segurança com detecção de movimento e alarme sonoro
- Monitoramento de nível de água no reservatório
- Interface visual via LCD com informações em tempo real
- Logs detalhados via Serial Monitor

### 3. Lógica de Automação
- Controle de irrigação baseado em:
  * Temperatura ambiente
  * Umidade do ar
  * Nível de água
  * Luminosidade
- Sistema de segurança com:
  * Detecção de movimento
  * Alarme sonoro com padrão de beeps
  * Cooldown entre alertas
- Display LCD mostrando:
  * Temperatura e umidade
  * Estado do sistema
  * Alertas ativos

### 4. Bibliotecas Utilizadas
- DHT sensor library
- Adafruit Unified Sensor
- LiquidCrystal_I2C
- Wire (I2C)

## Próximos Passos
1. Criar Pull Request da feature branch para develop
2. Realizar code review
3. Preparar documentação final
4. Submeter entrega no portal

## Critérios de Sucesso Atingidos
- [x] Diagrama do Wokwi validado e funcional
- [x] Todos os sensores funcionando corretamente
- [x] Sistema de automação respondendo adequadamente
- [x] Documentação completa e clara
- [x] Simulação funcional no Wokwi
- [x] Código bem comentado e organizado
- [x] Testes documentados e bem-sucedidos
