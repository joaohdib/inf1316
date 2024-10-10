#include <stdio.h> 
  
void print_file(const char* filename) 

{ 
    int ch; 
    FILE* file = fopen(filename, "r"); 
    if (file == NULL) { 
        printf("Erro ao abrir arquivo %s\n", filename); 
        return; 
    } 
    while ((ch = fgetc(file)) != EOF) { 
        putchar(ch); 
    } 
    fclose(file); 
} 
  
int main(int argc, char* argv[]) 
{ 
    for (int i = 1; i < argc; ++i) { 
        printf("%s:\n", argv[i]); 
        print_file(argv[i]); 
        printf("\n"); 
    } 
  
    return 0; 
}
