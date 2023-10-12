#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //Biblioteca para usar threads

int iguais = 1; //Variável que diz se os vetores serão iguais ou n

//Essa função vai comparar dois elementos, 
int Compara(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

//Função que ordena os vetores usando o qsort
void *Ordena(void *arg) {
    int *vetor = (int *)arg;
    int tamanho = vetor[0]; //O tamanho estará na primeira posição do vetor
    qsort(vetor + 1, tamanho, sizeof(int), Compara); //ordeno apenas do 2º elemento adiante
    pthread_exit(NULL);
}

int main() {
    int TAM;
    scanf("%d", &TAM); //Tamanho dos vetores

    //Declarando vetores
    int *v1 = malloc(sizeof(int) * TAM + 1); //uma posição a mais pois salvaremos o tamanho na primeira posição do vetor
    int *v2 = malloc(sizeof(int) * TAM + 1);

    //Faz com que o tamanho dos vetores fique armazenado na primeira posição do vetor
    v1[0] = TAM;
    v2[0] = TAM;

    //Preenchendo v1
    for (int i = 1; i <= TAM; i++){
        scanf("%d", &v1[i]);
    }

    //Preenchendo v2
    for (int i = 1; i <= TAM; i++){
        scanf("%d", &v2[i]);
    }

    //Criando duas threads, onde cada uma vai ordenar os vetores
    pthread_t thread1, thread2; 

    if (pthread_create(&thread1, NULL, Ordena, v1) != 0) {
        perror("pthread_create");
        exit(1);
    }

    if (pthread_create(&thread2, NULL, Ordena, v2) != 0) {
        perror("pthread_create");
        exit(1);
    }

    //Esses dois Ifs, garante que o programa só continua quando ambas as threads estiverem finalizado
    if (pthread_join(thread1, NULL) != 0) {
        perror("pthread_join");
        exit(1);
    }

    if (pthread_join(thread2, NULL) != 0) {
        perror("pthread_join");
        exit(1);
    }

    // Verifica se os vetores ordenados são iguais
    for (int i = 0; i <= TAM; i++) {
        if (v1[i] != v2[i]) {
            iguais = 0;
            break;
        }
    }

    //Imprime se são iguais ou diferentes
    if (iguais) {
        printf("Mesmos elementos\n");
    } else {
        printf("Diferentes\n");
    }

    return 0;
/*Uso do vídeo "CompConc - Introdução a Computação Concorrente com a Biblioteca pthread.h (pt. 1) #1" do canal Pedro Romário como referência,
link: https://www.youtube.com/watch?v=XMfnP2VxEG4*/
}