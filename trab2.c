#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  int pid = fork();
  int statloc;
  
  while (1) {
  type_prompt( ); 
  read_command(command, parameters);
  
  if (pid != 0) {
    waitpid(-1,&statloc, 0);
    exit(0);
  }
  else {
    int i;
    for (i = 1; i < argc-1; i++)
    {
      (void) printf("%s%s", argv[i], " ");
    }
    (void) printf("%s%s", argv[argc-1], "\n");
    execve (command, parameters, 0);
  }
  exit(0);
  }
return 0;
}

//AINDA NAO FUNCIONANDO


