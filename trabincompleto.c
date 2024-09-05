#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
  int segmento, *p, id, pid, status;
  int posicao = 0;
  // aloca a memória compartilhada
  segmento = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
  // associa a memória compartilhada ao processo
  p = (int **)shmat(segmento, 0, 0); // comparar o retorno com -1
  *p = vetor;

  for (int i = 0; i < 10000; i++)
  {
    vetor[i] = 5;
  }
  for (int i = 0; i < 10; i++)
  {
    if ((id = fork()) < 0)
    {
      perror("Erro na criação do novo processo");
      exit(-2);
    }
    else if (id == 0)
    {
      printf("ODJKASGDJKSGHDA");
      for (int j = 0; j < 1000; j++)
      {
        *p[posicao + j] *= 2;
      }
      pid = waitpid(-1, &status, 0);
      posicao += 1000;
    }
  }

  for (int k = 0; k<10000; k++) {
    printf("%d:%d\n", k, vetor[k]);
  }
  // printf ("Processo pai = %d\n", *p);


  shmdt(p);

  shmctl(segmento, IPC_RMID, 0);
  return 0;
}
