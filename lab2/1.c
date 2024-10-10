#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/stat.h>

#define PARCELA_TRABALHADORES (10000 / 10)

int main() {
    int segmento, *a, status, soma_total = 0;
    int inicio_parcela = 0;
    int fim_parcela = 0;
    int soma_parcelas = 0;

    // Criação de memória compartilhada para um vetor de 10000 espaços
    segmento = shmget(IPC_PRIVATE, 10000 * sizeof(int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

    if (segmento == -1) {
        perror("Erro ao criar a memória compartilhada");
        exit(EXIT_FAILURE);
    }

    // Acessa a memória compartilhada
    a = (int *) shmat(segmento, 0, 0);
    if (a == (int *)(-1)) {
        perror("Erro ao associar a memória compartilhada");
        exit(EXIT_FAILURE);
    }

    // Inicializa o vetor com valores iguais a 5
    for (int i = 0; i < 10000; i++) {
        a[i] = 5;
    }

    // Criação dos processos trabalhadores
    for (int i = 0; i < 10; i++) {
        pid_t pid = fork();
        
        if (pid < 0) { // Verifica se o processo foi executado com sucesso
            perror("Erro na criacao do novo processo");
            exit(EXIT_FAILURE);
        } 
        else if (pid == 0) { // Processo filho
            inicio_parcela = i * PARCELA_TRABALHADORES;
            fim_parcela = inicio_parcela + PARCELA_TRABALHADORES;
            soma_parcelas = 0;

            for (int j = inicio_parcela; j < fim_parcela; j++) {
                a[j] *= 2;  // Multiplica os valores
                soma_parcelas += a[j];  // Soma os valores
            }

            printf("Trabalhador %d: soma das parcelas = %d\n", i + 1, soma_parcelas);

            // Armazena a soma parcial na primeira posição da parcela
            a[inicio_parcela] = soma_parcelas;

            shmdt(a); // Desassocia a memória compartilhada
            exit(0); // Termina o processo filho
        }
    }

    // Processo pai aguarda todos os filhos terminarem
    for (int i = 0; i < 10; i++) {
        wait(&status);
    }

    // Soma os resultados parciais de cada trabalhador
    for (int i = 0; i < 10; i++) {
        soma_total += a[i * PARCELA_TRABALHADORES];
    }

    printf("Soma total das parcelas dos trabalhadores: %d\n", soma_total);

    // Desassocia a memória compartilhada e a remove
    shmdt(a);
    shmctl(segmento, IPC_RMID, 0);

    return 0;
}
