# Procedimentos de Teste - Sistema de Monitoramento Agrícola

## 1. Testes Unitários

### 1.1 DHT22
- [ ] Verificar leitura de temperatura
  ```cpp
  // Teste de temperatura
  float temp = dht.readTemperature();
  assert(temp >= -40 && temp <= 80);
  ```
- [ ] Verificar leitura de umidade
  ```cpp
  // Teste de umidade
  float hum = dht.readHumidity();
  assert(hum >= 0 && hum <= 100);
  ```
- [ ] Validar tempo de resposta
- [ ] Testar em diferentes condições ambientais

### 1.2 HC-SR04
- [ ] Verificar medição de distância
  ```cpp
  // Teste de distância
  float distance = ultrasonic.read();
  assert(distance >= 2 && distance <= 400);
  ```
- [ ] Testar precisão com diferentes objetos
- [ ] Validar leituras em diferentes ângulos
- [ ] Verificar tempo de resposta

### 1.3 PIR
- [ ] Testar detecção de movimento
  ```cpp
  // Teste de detecção
  bool motion = digitalRead(PIR_PIN);
  logMotionDetection(motion);
  ```
- [ ] Validar área de cobertura
- [ ] Testar sensibilidade
- [ ] Verificar falsos positivos

### 1.4 LDR
- [ ] Verificar leitura de luminosidade
  ```cpp
  // Teste de luz
  int light = analogRead(LDR_PIN);
  assert(light >= 0 && light <= 4095);  // Para ADC de 12 bits
  ```
- [ ] Testar em diferentes condições de iluminação
- [ ] Validar tempo de resposta

## 2. Testes de Integração

### 2.1 Sistema de Irrigação
- [ ] Testar decisão de irrigação baseada em múltiplos sensores
  ```cpp
  // Teste integrado de irrigação
  bool shouldWater = system.shouldIrrigate(temp, humidity, light);
  assert(shouldWater == expectedDecision);
  ```
- [ ] Validar ajuste automático baseado em condições
- [ ] Testar limites de segurança

### 2.2 Sistema de Segurança
- [ ] Testar detecção e alerta
- [ ] Validar registro de eventos
- [ ] Testar sistema em diferentes períodos

### 2.3 Comunicação
- [ ] Verificar formato de dados
- [ ] Testar transmissão serial
- [ ] Validar logs

## 3. Testes de Sistema

### 3.1 Simulação no Wokwi
- [ ] Configurar ambiente virtual
- [ ] Testar todos os sensores
- [ ] Validar integração completa
- [ ] Verificar respostas do sistema

### 3.2 Testes de Stress
- [ ] Operação contínua por 24h
- [ ] Teste com valores extremos
- [ ] Recuperação de erros
- [ ] Uso de memória

### 3.3 Testes de Campo
- [ ] Validação em ambiente real
- [ ] Ajuste de parâmetros
- [ ] Verificação de durabilidade

## 4. Validação e Documentação

### 4.1 Critérios de Aceitação
- [ ] Precisão das leituras
- [ ] Tempo de resposta
- [ ] Confiabilidade do sistema
- [ ] Eficiência energética

### 4.2 Documentação de Testes
- [ ] Registrar resultados
- [ ] Documentar problemas encontrados
- [ ] Registrar soluções implementadas
- [ ] Manter histórico de versões

### 4.3 Monitoramento Serial
```
Formato esperado de log:
[2024-01-20 10:30:15] DHT22 - Temp: 25.5°C, Hum: 65%
[2024-01-20 10:30:15] HC-SR04 - Distance: 150cm
[2024-01-20 10:30:15] PIR - Motion: false
[2024-01-20 10:30:15] LDR - Light: 800
[2024-01-20 10:30:15] System - Irrigation: OFF
```

## 5. Checklist de Validação Final

### 5.1 Funcionalidade
- [ ] Todos os sensores funcionando
- [ ] Sistema de decisão correto
- [ ] Alertas funcionando
- [ ] Logs adequados

### 5.2 Código
- [ ] Comentários apropriados
- [ ] Sem memory leaks
- [ ] Tratamento de erros
- [ ] Padrões de codificação

### 5.3 Documentação
- [ ] README completo
- [ ] Documentação técnica
- [ ] Resultados dos testes
- [ ] Instruções de uso

## 6. Procedimentos de Teste no Wokwi

### 6.1 Configuração Inicial
1. Criar novo projeto
2. Adicionar componentes
3. Configurar conexões
4. Carregar código

### 6.2 Testes Automatizados
```cpp
void runTests() {
    testDHT22();
    testUltrasonic();
    testPIR();
    testLDR();
    testIntegration();
    Serial.println("All tests completed");
}
```

### 6.3 Verificação de Resultados
- Monitorar Serial Output
- Verificar comportamento dos componentes
- Validar lógica de decisão
- Documentar resultados

## 7. Registro de Testes

### 7.1 Formato de Registro
```
Data: YYYY-MM-DD
Testador: [Nome]
Versão: [X.Y.Z]

Resultados:
1. DHT22: [PASS/FAIL]
   - Temperatura: OK
   - Umidade: OK
   - Observações: ...

2. HC-SR04: [PASS/FAIL]
   - Distância: OK
   - Precisão: OK
   - Observações: ...

[...]
```

### 7.2 Análise de Resultados
- Compilar dados
- Identificar padrões
- Propor melhorias
- Documentar conclusões
