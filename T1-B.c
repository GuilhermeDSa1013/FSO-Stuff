#include<stdio.h>
#include<stdlib.h>

#include<dlfcn.h>

int main(int argc, char **argv){

    //Setando em uma variável o nome da minha biblioteca(lib) que se encontra na segunda posição do vetor argv
    char *libNome = argv[1];

    //Abrindo a biblioteca com o nome especificado, q será ativa apenas quando for requisitada
    void *libAtual = dlopen(libNome, RTLD_LAZY);

    //Setando variáveis numéricas
    int num1 = atoi(argv[2]);
    int num2 = atoi(argv[3]);
    double num3 = atoi(argv[4]);

    //Setando bibliotecas
    int (*imprime)();
    int (*calcula)(int, int);
    int (*trigo)(double);

    //Teste para caso a biblioteca esteja indisponível
    if(libAtual == NULL){
        printf("nao disponivel\n");
        return 0;
    }

    //Setando a biblioteca
    imprime = dlsym(libAtual, "imprime");

    //Teste para ver se está implementada
    if(!imprime){
        printf("nao implementado\n");
    } else {
        printf("%d\n", imprime()); //imprimindo valor de retorno
    }


    calcula = dlsym(libAtual, "calcula");

    if(!calcula){
        printf("nao implementado\n");
    } else {
        printf("%d\n", calcula(num1, num2)); 
    }


    trigo = dlsym(libAtual, "trigo");

    if(!trigo){
        printf("nao implementado\n");
    } else {
        printf("%d\n", trigo(num3)); 
    }

    dlclose(libAtual);

    return 0;
}

/*Uso do vídeo "How to Load Libraries at Runtime" do canal Jacob Sorber como referência,
link: https://www.youtube.com/watch?v=_kIa4D7kQ8I&ab_channel=JacobSorber*/