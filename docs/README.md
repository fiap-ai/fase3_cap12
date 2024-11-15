# Sistema Inteligente de Monitoramento Agrícola com ESP32

## Objetivo do Projeto
Desenvolver um sistema inteligente de monitoramento agrícola utilizando ESP32 e quatro sensores (DHT22, HC-SR04, PIR e LDR) para otimizar recursos na agricultura através de coleta de dados e automação de decisões.

## Checklist de Desenvolvimento e Entrega

### 1. Configuração do Ambiente e Estrutura do Projeto
- [x] Criar estrutura base do projeto com PlatformIO
- [ ] Validar diagrama do circuito no Wokwi
  - [ ] Revisar conexões do diagrama.json
  - [ ] Verificar pinout correto dos sensores
  - [ ] Confirmar compatibilidade com ESP32
  - [ ] Testar simulação básica
- [ ] Configurar GitHub Repository com estrutura de pastas:
  - `/src`: Códigos-fonte
  - `/docs`: Documentação
  - `/tests`: Testes do sistema
- [ ] Configurar branch 'develop' para desenvolvimento
- [ ] Definir padrão de commits e Pull Requests

### 2. Implementação dos Sensores

#### 2.1 DHT22 (Temperatura e Umidade)
- [ ] Implementar leitura de temperatura
- [ ] Implementar leitura de umidade
- [ ] Criar lógica de decisão para irrigação baseada em temperatura/umidade
- [ ] Implementar sistema de alertas

#### 2.2 HC-SR04 (Ultrassom)
- [ ] Implementar medição de nível de água
- [ ] Criar sistema de monitoramento de reservatório
- [ ] Desenvolver lógica de controle de irrigação baseada no nível

#### 2.3 PIR (Sensor de Movimento)
- [ ] Implementar detecção de movimento
- [ ] Criar sistema de alertas de segurança
- [ ] Desenvolver lógica de acionamento de alarmes

#### 2.4 LDR (Sensor de Luz)
- [ ] Implementar leitura de luminosidade
- [ ] Criar lógica de ajuste de irrigação baseada na luz
- [ ] Desenvolver sistema de otimização de recursos

### 3. Integração e Automação
- [ ] Integrar todos os sensores no sistema
- [ ] Implementar lógica de decisão combinada
- [ ] Criar sistema de priorização de ações
- [ ] Desenvolver rotinas de automação

### 4. Simulação e Testes
- [ ] Criar projeto no Wokwi.com
- [ ] Implementar circuito completo na simulação
- [ ] Realizar testes individuais de cada sensor
- [ ] Executar testes integrados do sistema
- [ ] Documentar resultados dos testes
- [ ] Validar todas as funcionalidades

### 5. Documentação
- [x] Criar diagrama do circuito
- [x] Documentar configuração de cada sensor
- [x] Escrever instruções de instalação
- [x] Documentar dependências do projeto
- [ ] Criar guia de configuração do Wokwi
- [ ] Incluir prints do Monitor Serial
- [ ] Documentar testes realizados

### 6. Entrega Final
- [ ] Revisar código e comentários
- [ ] Verificar commits e histórico
- [ ] Criar Pull Request para main
- [ ] Realizar code review
- [ ] Preparar documentação final
- [ ] Postar link do GitHub no portal do aluno

## Plano de Atuação

### Fase 1: Preparação e Validação do Circuito (Atual)
1. Aguardar diagrama.json do Wokwi
2. Validar conexões e compatibilidade
3. Testar simulação básica
4. Ajustar documentação conforme necessário

### Fase 2: Desenvolvimento Base (Após validação do circuito)
1. Implementação individual dos sensores
2. Testes básicos de funcionamento
3. Documentação inicial

### Fase 3: Integração
1. Integração dos sensores
2. Desenvolvimento da lógica de automação
3. Testes integrados

### Fase 4: Simulação e Documentação
1. Implementação no Wokwi
2. Testes finais
3. Documentação completa
4. Revisão e entrega

## Requisitos Técnicos

### Hardware
- ESP32 DevKit
- Sensor DHT22
- Sensor HC-SR04
- Sensor PIR
- Sensor LDR
- Componentes auxiliares (resistores, cabos, etc.)

### Software
- PlatformIO
- Arduino Framework
- Bibliotecas específicas para cada sensor
- GitHub para versionamento
- Wokwi para simulação

## Monitoramento de Progresso

O progresso será acompanhado através de:
1. Daily commits no GitHub
2. Revisões semanais do checklist
3. Testes contínuos de funcionalidades
4. Documentação atualizada regularmente

## Próximos Passos
1. Aguardar o diagrama.json do Wokwi
2. Validar todas as conexões do circuito
3. Confirmar pinout e compatibilidade
4. Prosseguir com a implementação após validação

## Critérios de Sucesso

1. Diagrama do Wokwi validado e funcional
2. Todos os sensores funcionando corretamente
3. Sistema de automação respondendo adequadamente
4. Documentação completa e clara
5. Simulação funcional no Wokwi
6. Código bem comentado e organizado
7. Testes documentados e bem-sucedidos
