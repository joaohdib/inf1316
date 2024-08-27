#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    char* argv2;
    execvp(argv[1], &argv[1]);
    return 0;
}
