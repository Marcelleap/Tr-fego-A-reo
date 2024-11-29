# Sistema de Controle de Tráfego Aéreo

Este projeto simula um sistema de controle de tráfego aéreo utilizando conceitos de programação concorrente em C, incluindo processos, threads, pipes e mutex.

## 👥 Autores

- João Henrique
- Marcelle Andrade

## 📋 Descrição

O sistema simula o controle de tráfego aéreo com as seguintes características:
- Controle de pousos e decolagens
- Monitoramento em tempo real de estatísticas
- Registro de operações em arquivo CSV
- Limite máximo de 3 aviões simultâneos no aeroporto

## 🚀 Funcionalidades

- Simulação de múltiplos aviões usando processos
- Comunicação entre torre e aviões através de pipes
- Thread dedicada para monitoramento de estatísticas
- Controle de acesso à pista usando mutex
- Registro de operações em arquivo CSV
- Tratamento de sinais para encerramento seguro

## 🛠️ Tecnologias Utilizadas

- Linguagem C
- POSIX Threads
- IPC (Inter-Process Communication)
- Pipes
- Mutex
- Sinais

## 📦 Pré-requisitos

- GCC (GNU Compiler Collection)
- Sistema operacional Linux/Unix
- Biblioteca pthread

## 🔧 Compilação

Para compilar o programa, execute:
```bash
gcc Trafego.c -o trafego -pthread
```

## 🏃‍♂️ Execução

Para executar o programa:
```bash
./trafego
``` 

## 🎮 Controles

- CTRL+C: Encerra o programa e salva as estatísticas

## ⚙️ Configurações

Constantes configuráveis no código:
- `MAX_AVIOES_AEROPORTO`: Número máximo de aviões permitidos (default: 3)
- `TEMPO_POUSO`: Tempo necessário para pouso (default: 5 segundos)
- `TEMPO_DECOLAGEM`: Tempo necessário para decolagem (default: 3 segundos)

## 📝 Disciplina

- Sistemas Operacionais (2024.2)
- Professor: João Carlos





