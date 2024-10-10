#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
    int segmento, *p, id1, id2, pid, status, valoresIguais;

    valoresIguais = 1;

    // aloca a memória compartilhada
    segmento = shmget(IPC_PRIVATE, 1000000 * sizeof(int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR); // associa a memória compartilhada ao processo
    p = (int *)shmat(segmento, 0, 0);                                                              // comparar o retorno com -1
    for (int i = 0; i < 1000000; ++i)
    {
        p[i] = 5; // Inicializa a memória compartilhada com valores de 0 a 9999
    }

    if ((id1 = fork()) < 0) // processo filho 1
    {
        puts("Erro na criação do novo processo");
        exit(-2);
    }

    else if (id1 == 0)
    {
        for (int i = 0; i < 1000000; ++i)
        {
            p[i] *= 2;
            p[i] += 2;
        }
        shmdt(p);
        exit(EXIT_SUCCESS);
    }

    if ((id2 = fork()) < 0) // processo filho 1
    {
        puts("Erro na criação do novo processo");
        exit(-2);
    }

    else if (id2 == 0)
    {
        for (int i = 0; i < 1000000; ++i)
        {
            p[i] *= 2;
            p[i] += 2;
        }
        shmdt(p);
        exit(EXIT_SUCCESS);
    }

    waitpid(id1, &status, 0);
    waitpid(id2, &status, 0);


    for (int i = 0; i < 1000000; i++)
    {
        if (p[i] != 26)
        {
            valoresIguais = 0;
        }
    }

    if (valoresIguais)
    {
        printf("Todos os valores do vetor resultaram em 26, valor esperado.\n");
    }
    else
    {
        printf("Ha valores diferentes de 26 no vetor.");
    }

    shmdt(p);
    shmctl(segmento, IPC_RMID, 0);
    return 0;
}
