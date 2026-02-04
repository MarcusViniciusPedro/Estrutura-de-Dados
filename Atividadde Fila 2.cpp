#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó.
// Cada nó tem um valor inteiro e um ponteiro para o próximo nó.
typedef struct No {
    int valor;
    struct No *proximo;
} No;

// --- Funções da Fila ---

// Função para enfileirar (enqueue) um valor.
// Adiciona um novo nó com o valor especificado no final da fila.
// Recebe um ponteiro para o ponteiro 'frente' para poder modificar o início da fila.
void enfileirar(No **frente, int valor) {
    // 1. Aloca memória para o novo nó e atribui o valor.
    No *novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }
    novoNo->valor = valor;
    novoNo->proximo = NULL; // O novo nó sempre é o último, então seu 'proximo' é NULL.

    // 2. Verifica se a fila está vazia.
    if (*frente == NULL) {
        // Se a fila estiver vazia, o novo nó se torna o primeiro.
        *frente = novoNo;
    } else {
        // 3. Se a fila não estiver vazia, encontra o último nó.
        No *atual = *frente;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        // 4. Adiciona o novo nó no final.
        atual->proximo = novoNo;
    }
    printf("Valor %d enfileirado.\n", valor);
}

// Função para desenfileirar um valor.
// Remove e retorna o valor do primeiro nó da fila.
void desenfileirar(No **frente) {
    // 1. Verifica se a fila está vazia.
    if (*frente == NULL) {
        printf("A fila esta vazia. Nao e possivel desenfileirar.\n");
        return;
    }

    // 2. Armazena o nó a ser removido (o nó da frente).
    No *noRemover = *frente;
    int valorRemovido = noRemover->valor;

    // 3. Move a frente da fila para o próximo nó.
    *frente = noRemover->proximo;

    // 4. Libera a memória do nó removido.
    free(noRemover);

    printf("Valor %d desenfileirado.\n", valorRemovido);
}

// Função para exibir os elementos da fila.
void exibirFila(No *frente) {
    if (frente == NULL) {
        printf("A fila esta vazia.\n");
        return;
    }

    printf("Elementos da fila: ");
    // 1. Percorre a fila a partir do nó 'frente'.
    No *atual = frente;
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

// Função principal (main) para testar o código.
int main() {
    // Inicializa o ponteiro 'frente' como NULL para indicar uma fila vazia.
    No *fila = NULL;
    int n, valor;

    // Solicita ao usuário o número de valores a serem inseridos.
    printf("Quantos valores voce deseja inserir na fila? ");
    scanf("%d", &n);

    // Loop para enfileirar 'n' valores.
    for (int i = 0; i < n; i++) {
        printf("Insira o valor %d: ", i + 1);
        scanf("%d", &valor);
        enfileirar(&fila, valor);
    }
    
    // Exibe a fila completa.
    exibirFila(fila);

    // Exemplo de desenfileiramento.
    printf("\nIniciando operacoes de desenfileiramento...\n");
    desenfileirar(&fila);
    desenfileirar(&fila);
    
    // Exibe a fila após as remoções.
    exibirFila(fila);

    // Libera a memória de todos os nós restantes.
    while (fila != NULL) {
        desenfileirar(&fila);
    }

    return 0;
}
