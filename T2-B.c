#include <stdlib.h>
#include <stdio.h>
#include <signal.h> //Manipulação de sinais
#include <unistd.h> //Para usar o a função spleep, que deixa o programa dormingo até certo momento

int signCount = 1;

void tratamento_de_sinais(int signID){
    if (signID == SIGUSR1) {
        printf("SIGUSR1 eh para aproveitar mais um pouco\n");
    } else if (signID == SIGALRM && signCount == 3) {
        signCount++;
        printf("Os incomodados que se mudem, tchau\n");
    } else if (signID == SIGALRM ){
        signCount++;
        printf("Ai que sono, quero dormir mais um pouco\n");
    }   
}

int main(){

    //Registro dos tratamentos dos sinais
    signal(SIGUSR1, tratamento_de_sinais); //tratamento para o sinal SIGUSR1 Sinal de Usuário
    signal(SIGALRM, tratamento_de_sinais); //tratamento para o dinal SIGALRM Sinal de Alarme

    //Fica dormindo até o contador ser 4
    while (signCount < 4) {
        sleep(1);
    }

    return 0;
}

/*Uso do vídeo "Linguagem C - cabeçalho signal.h" do canal O Programador W como referência,
link: https://www.youtube.com/watch?v=btDTGXGAU4M*/