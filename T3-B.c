#include <stdio.h>
#include <stdlib.h>

int qtdQuadros, qtdPaginas;

// Função para inicializar um vetor com valores padrão (-1 neste caso)
void criaVetor(int *vetor, int tam) {
    for (int i = 0; i < tam; i++) {
        vetor[i] = -1;
    }
}

// Função para verificar se uma página está presente no vetor
// e atualizar os contadores de idade das páginas
int PaginaNoVetor(int *pages, int *idadePag, int numeroPagina) {
    int Presente = 0;
    
    for (int i = 0; i < qtdQuadros; i++) {
        if (pages[i] == numeroPagina) {
            Presente = 1;
            // Reseta o contador de idade da página encontrada
            idadePag[i] = 0;
        } else {
            // Incrementa o contador de idade das outras páginas
            idadePag[i]++;
        }
    }
    
    return Presente;
}

// Função para mover as páginas no vetor, atualizando os contadores de idade
void deslocaPag(int *pages, int *idadePag, int numeroPagina) {
    for (int i = 0; i < qtdQuadros - 1; i++) {
        // Move as páginas para frente no vetor
        pages[i] = pages[i + 1];
        // Atualiza os contadores de idade
        idadePag[i] = idadePag[i + 1] + 1;
    }

    // Insere a nova página no final do vetor
    pages[qtdQuadros - 1] = numeroPagina;
    idadePag[qtdQuadros - 1] = 0;
}

// Função para inserir uma página no vetor, atualizando os contadores de idade
void InserePagNoVetor(int *pages, int *idadePag, int numeroPagina) {
    int lruPagIndice = 0;

    // Encontrando a página com o maior contador de idade (LRU)
    for (int i = 1; i < qtdQuadros; i++) {
        if (idadePag[i] > idadePag[lruPagIndice]) {
            lruPagIndice = i;
        } 
    }

    // Incrementando os contadores de idade das outras páginas
    for (int i = 0; i < qtdQuadros; i++) {
        if (i != lruPagIndice)
            idadePag[i]++;
    }

    // Inserindo a nova página na posição encontrada
    pages[lruPagIndice] = numeroPagina;
    idadePag[lruPagIndice] = 0;
}

int main() {
    int numeroPagina, count = 0, i = 0;

    // Leitura do número de quadros e número total de páginas
    scanf("%d%d", &qtdQuadros, &qtdPaginas);

    // Alocação dinâmica de memória para os vetors de páginas e contadores de idade
    int *pages = malloc(qtdQuadros * sizeof(int));
    int *idadePag = calloc(qtdQuadros, sizeof(int));

    // Inicializa os vetors de páginas e contadores de idade
    criaVetor(pages, qtdQuadros);

    // Loop para processar cada página
    while (i < qtdPaginas) {
        scanf("%d", &numeroPagina);

        // Verifica se a página não está no vetor e ainda há espaço disponível
        if (!PaginaNoVetor(pages, idadePag, numeroPagina) && i < qtdQuadros) {
            // Move as páginas para frente no vetor e insere a nova página
            deslocaPag(pages, idadePag, numeroPagina);
            count++;
            i++;
            continue;
        }

        // Verifica se a página não está no vetor
        if (!PaginaNoVetor(pages, idadePag, numeroPagina)) {
            // Insere a nova página no vetor
            InserePagNoVetor(pages, idadePag, numeroPagina);
            count++;
        }

        i++;
    }

    // Imprime o número total de faltas de página
    printf("%d\n", count);

    // Libera a memória alocada
    free(pages);
    free(idadePag);

    return 0;
}
