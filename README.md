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
- Registro de pousos e decolagens.
- Tratamento de sinais de interrupção (SIGINT).
- Escrita de dados e estatísticas finais em arquivo CSV.
- Utilização de *threads* para monitoramento paralelo.
- Controle de acesso simultâneo com *mutex*

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

## 🔧 Prrincipais Funções 

1.void aviao (int readfd, int writefd)
2.void requisicao(int readfd, int writefd)
3.void handle_sigint(int sig)
4.void thread_funcao(void *args)
5.void iniciar_contador()

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





