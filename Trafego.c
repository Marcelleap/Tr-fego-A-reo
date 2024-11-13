#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> // Nao sei se funciona no linux - Joao Pff testar
#include <time.h>

// Estrutura para definir os dados do avião
typedef struct Trafego
{
    int id;
    float latitude;
    float longitude;
    int altitude;
    char permissao[10];
};

// Funções
void aviao(int writefd, int readfd);
void requisicao(int readfd, int writefd);

// Função principal
int main() {
    int torre;                // Quem vai coordenar as operações (PAI) 
    int piperequisicao[2];    // Requisição dos aviões → torre
    int pipecontrole[2];      // Processamento de torre → avião

    // Para criar o processo do avião
    if (pipe(piperequisicao) < 0 || pipe(pipecontrole) < 0) {
        printf("A pista encontra-se interditada (ERRO AO CRIAR PIPES)");
        exit(1);
    }

    // Se o processo der erro na criação 
    if ((torre = fork()) < 0) {
        printf("Erro da chamada de fork (processo não criado)");
        exit(1);
    }

    if (torre > 0) {  // Processo pai: Torre de Controle
        // Fecha leitura no pipe de requisição e escrita no pipe de controle
        close(piperequisicao[0]); 
        close(pipecontrole[1]);

        // Lógica da torre
        requisicao(piperequisicao[0], pipecontrole[1]);

        // Fechar descritores após uso
        close(piperequisicao[0]);
        close(pipecontrole[1]);

        wait(NULL); // Aguarda o filho (avião) terminar
    }
    else {  // Processo filho: Avião
        // Fecha leitura no pipe de requisição e escrita no pipe de controle
        close(piperequisicao[1]);
        close(pipecontrole[0]);

        // Lógica do avião
        aviao(piperequisicao[1], pipecontrole[0]);

        // Fechar descritores após uso
        close(piperequisicao[1]);
        close(pipecontrole[0]);
    }

    return 0;
}

// Função que simula as requisições do avião na hora do pouso
void aviao(int writefd, int readfd) {
    srand(getpid());  // Gera números aleatórios com base no PID
    srand(time(NULL)); // Gera números aleatórios com base no tempo

    // Função para manipular o tráfego do avião 
    Trafego aviao;

    // Preenche os dados de forma aleatória
    aviao.id = getpid(); // PID como ID único
    aviao.latitude = -90.0 + ((float)rand() / RAND_MAX) * 180.0;  // Gera latitude aleatória entre -90.0 e 90.0
    aviao.longitude = -180.0 + ((float)rand() / RAND_MAX) * 360.0; // Gera longitude aleatória entre -180.0 e 180.0
    aviao.altitude = 1000 + rand() % 39001;  // Gera altitude aleatória entre 1000 e 40000
    snprintf(aviao.permissao, sizeof(aviao.permissao), "Pousar");

    // Se ele solicitou permissão para pouso, ele envia os dados para a torre 
    if (write(writefd, &aviao, sizeof(Trafego)) < 0) {
        perror("Erro ao enviar dados para a torre");
        exit(1);
    }

    // Envio da solicitação 
    printf("Avião %d enviou solicitação de pouso.\n", aviao.id);

    // Se ele vai decolar, primeiro tem que aguardar resposta da torre
    Trafego resposta;
    if (read(readfd, &resposta, sizeof(Trafego)) < 0) {
        perror("Erro ao receber resposta da torre");
        exit(1);
    }

    printf("Avião %d recebeu resposta: %s\n", aviao.id, resposta.permissao);
}

// Função que simula a torre recebendo e processando a solicitação do avião
void requisicao(int readfd, int writefd) {
    FILE *arquivo = fopen("avioes_pipe.csv", "w");  // Cria o arquivo
    if (arquivo == NULL) {
        perror("Erro ao criar o arquivo");
        exit(1);
    }

    // Cabeçalho do arquivo CSV
    fprintf(arquivo, "ID,Latitude,Longitude,Altitude,Permissao\n");

    Trafego aviao;

    // Lê os dados do pipe e processa
    if (read(readfd, &aviao, sizeof(Trafego)) > 0) {
        printf("Torre recebeu solicitação do avião %d\n", aviao.id);

        // Define a permissão para pouso (aleatória para simplificação)
        if (rand() % 2 == 0) {
            snprintf(aviao.permissao, sizeof(aviao.permissao), "Aprovado");
        } else {
            snprintf(aviao.permissao, sizeof(aviao.permissao), "Negado");
        }

        // Escreve os dados no arquivo
        fprintf(arquivo, "%d,%.6f,%.6f,%d,%s\n", 
                aviao.id, aviao.latitude, aviao.longitude, aviao.altitude, aviao.permissao);

        // Envia resposta para o avião
        if (write(writefd, &aviao, sizeof(Trafego)) < 0) {
            perror("Erro ao enviar resposta para o avião");
            fclose(arquivo);
            exit(1);
        }

        printf("Torre enviou resposta ao avião %d: %s\n", aviao.id, aviao.permissao);
    } else {
        perror("Erro ao ler os dados do pipe");
    }

    fclose(arquivo);
    printf("Arquivo 'avioes_pipe.csv' gerado com sucesso.\n");
}
