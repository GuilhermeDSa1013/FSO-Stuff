#include <stdio.h>
#include <stdlib.h>

// Função para inicializar o vetor de quadros com valores padrão (-1 neste caso)
void criaVetor(int *vetor, int tam) {
    for (int i = 0; i < tam; i++) {
        vetor[i] = -1;
    }
}

// Função para verificar se uma página está presente no vetor de quadros
int PaginaNoVetor(int *vetor, int tam, int numeroPag) {
    for (int i = 0; i < tam; i++) {
        if (vetor[i] == numeroPag) {
            return 1; // Página encontrada no vetor
        }
    }
    return 0; // Página não encontrada no vetor
}

// Função para mover as páginas no vetor de quadros, aplicando o FIFO
void deslocaPag(int *vetor, int tam, int numeroPag) {
    for (int i = 0; i < tam - 1; i++) {
        vetor[i] = vetor[i + 1]; // Move cada página uma posição para a esquerda
    }
    vetor[tam - 1] = numeroPag; // Insere a nova página no final do vetor
}

int main() {
    int qtdQuadros, qtdPaginas;

    // Leitura do número de quadros e páginas
    scanf("%d", &qtdQuadros);
    scanf("%d", &qtdPaginas);

    // Alocação dinâmica de memória para o vetor de quadros
    int *vetorFifo = malloc(qtdQuadros * sizeof(int));

    // Inicialização do vetor de quadros
    criaVetor(vetorFifo, qtdQuadros);

    int numeroPag, count = 0;

    // Processamento de cada página
    while (qtdPaginas >= 1) {
        // Leitura da próxima página
        scanf("%d", &numeroPag);

        // Verifica se a página não está presente no vetor
        if (!PaginaNoVetor(vetorFifo, qtdQuadros, numeroPag)) {
            // Move as páginas e incrementa o contador de faltas de página
            deslocaPag(vetorFifo, qtdQuadros, numeroPag);
            count++;
        }

        qtdPaginas--; // Decrementa o número total de páginas
    }

    // Imprime o número total de faltas de página
    printf("%d\n", count);

    // Libera a memória
    free(vetorFifo);

    return 0;
}