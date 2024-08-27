#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int i;
    for (i = 1; i < argc-1; i++)
    {
      (void) printf("%s%s", argv[i], " ");
    }
    (void) printf("%s%s", argv[argc-1], "\n");
    return 0;
}
