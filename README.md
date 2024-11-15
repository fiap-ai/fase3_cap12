# FIAP - Faculdade de Informática e Administração Paulista

<p align="center">
<a href= "https://www.fiap.com.br/"><img src="assets/logo-fiap.png" alt="FIAP - Faculdade de Informática e Admnistração Paulista" border="0" width=40% height=40%></a>
</p>

<br>

# Sistema de Monitoramento Agrícola Inteligente

## 🔗 Links Importantes
- [Simulação no Wokwi](https://wokwi.com/projects/414657136066505729)

## 👨‍🎓 Integrantes: 
- <a href="https://www.linkedin.com/in/gabemule/">Gabriel Mule Monteiro</a>

## 👩‍🏫 Professores:
### Tutor(a) 
- <a href="https://www.linkedin.com/company/inova-fusca">Lucas Gomes Moreira</a>

## 📜 Descrição

Este projeto implementa um sistema inteligente de monitoramento agrícola utilizando ESP32 e quatro sensores diferentes para otimizar recursos na agricultura. O sistema coleta dados do ambiente e toma decisões automatizadas para controle de irrigação e segurança.

O sistema realiza o monitoramento em tempo real das seguintes variáveis:
- Temperatura e Umidade (DHT22)
- Nível de água no reservatório (HC-SR04)
- Detecção de movimento para segurança (PIR)
- Luminosidade ambiente (LDR)

O sistema automaticamente controla a irrigação através de um relé e fornece alertas de segurança através de um buzzer, baseado nas leituras dos sensores.

### Parâmetros de Controle

O sistema utiliza os seguintes parâmetros para controle:

1. Condições de Temperatura e Umidade (DHT22):
   - Temperatura máxima: 30°C
   - Umidade mínima: 40%
   - Justificativa: Mantém condições ideais para cultivo

2. Nível de Água (HC-SR04):
   - Nível mínimo: 50cm
   - Nível máximo: 200cm
   - Justificativa: Garante disponibilidade de água para irrigação

3. Luminosidade (LDR):
   - Threshold: 60%
   - Justificativa: Otimiza irrigação baseado na luz solar

4. Segurança (PIR):
   - Cooldown: 30 segundos
   - Justificativa: Evita falsos positivos mantendo segurança

### Lógica de Automação

O sistema ativa a irrigação quando as seguintes condições são atendidas:

1. Condições Ambientais:
   - Temperatura acima do máximo OU
   - Umidade abaixo do mínimo
   - Luminosidade adequada

2. Condições de Segurança:
   - Nível de água acima do mínimo
   - Sem detecção de movimento

Esta lógica foi implementada para:
- Otimizar uso de água
- Garantir condições ideais de cultivo
- Prevenir desperdícios
- Manter segurança da área

## 📁 Estrutura de pastas

- <b>src</b>: Código-fonte do projeto
  - <b>main.cpp</b>: Implementação principal do sistema

- <b>include</b>: Arquivos de cabeçalho

- <b>lib</b>: Bibliotecas do projeto

- <b>docs</b>: Documentação
  - <b>README.md</b>: Documentação geral
  - <b>TECHNICAL.md</b>: Especificações técnicas
  - <b>TESTING.md</b>: Procedimentos e resultados de testes
  - <b>CIRCUIT.md</b>: Documentação do circuito

- <b>test</b>: Testes unitários
  - <b>test_sensors.cpp</b>: Testes dos sensores e atuadores

## 💻 Funcionalidades

### Sistema de Monitoramento

O sistema oferece monitoramento contínuo com:
- Leitura de temperatura e umidade
- Medição de nível de água
- Detecção de movimento
- Monitoramento de luminosidade

### Interface e Feedback

1. Display LCD:
- Temperatura e umidade atual
- Estado do sistema
- Alertas ativos

2. Alarmes:
- Buzzer para alertas de segurança
- Padrão de 3 beeps para alertas
- Cooldown entre alertas

### Formato dos Dados (Serial)

O sistema envia dados pela porta serial no formato:
```
============================
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

=== System Status ===
Bomba de Irrigação: DESLIGADA
Sistema de Alarme: DESATIVADO
============================
```

## 📺 Demonstração

O sistema pode ser testado através da [simulação no Wokwi](https://wokwi.com/projects/414657136066505729), que demonstra:
- Funcionamento dos sensores
- Sistema de irrigação automática
- Sistema de segurança
- Interface LCD
- Logs via Serial Monitor

## 🗃 Histórico de lançamentos

* 0.1.0 - 25/03/2024
    * Implementação inicial do sistema de monitoramento
    * Integração de todos os sensores
    * Sistema de irrigação automática
    * Sistema de segurança com alarme
    * Interface LCD
    * Testes unitários

## 📋 Licença

<img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/cc.svg?ref=chooser-v1"><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/by.svg?ref=chooser-v1"><p xmlns:cc="http://creativecommons.org/ns#" xmlns:dct="http://purl.org/dc/terms/">MODELO GIT FIAP por <a rel="cc:attributionURL dct:creator" property="cc:attributionName" href="https://fiap.com.br">Fiap</a> está licenciado sobre <a href="http://creativecommons.org/licenses/by/4.0/?ref=chooser-v1" target="_blank" rel="license noopener noreferrer" style="display:inline-block;">Attribution 4.0 International</a>.</p>
