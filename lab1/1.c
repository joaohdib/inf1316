#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

  int vetor[10] = {0};
  int statloc;
  int pid = fork();
  
  if (pid != 0) {
  
    for (int i = 0; i< 10; i++) {
      vetor[i]++;
    }
    waitpid(-1,&statloc, 0);
    for (int i = 0; i < 10; i++) {
        printf("posicao %d: %d\n", i, vetor[i]); 
    }
    exit(0);
  }
  else {
    
    for (int i = 0; i< 10; i++) {
      vetor[i] -= 1;
    }
    
        for (int i = 0; i < 10; i++) {
        printf("posicao %d: %d\n", i, vetor[i]); 
    }
    exit(0);
  
  }
  
  

return 0;
}
