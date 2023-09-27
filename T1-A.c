#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv){

    //argc - 1, para n contar o nome do programa
    printf("%d\n", argc-1);

    //i=1, para não printar o nome do programa, q está em argv[0]
    //i<=argc-1 para não printar o "Segmentation fault", q está em na última posição de argv
    for(int i=1; i<=argc-1; i++){
        printf("%s\n", argv[i]);
    }

    return 0;
}