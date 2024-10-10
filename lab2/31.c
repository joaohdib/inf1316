#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
    int segmento, id1, id2, pid, status, valoresIguais;
    char *p;
    char *str;

    segmento = shmget(7000, 100 * sizeof(char), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR); // associa a memória compartilhada ao processo
	    if (segmento < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    str = (char *)shmat(segmento, 0, 0); // comparar o retorno com -1

    printf("Digite uma string: ");
    scanf("%[^\n]", str);
	
	for (int i = 0; i< 100;i++) {
		if (str[i] == '\n') {
			str[i] = '\0';
		}
	}

    printf("%s\n", str);

    //shmdt(str);
    //shmctl(segmento, IPC_RMID, 0);
    return 0;
}
