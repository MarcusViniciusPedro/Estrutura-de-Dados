#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó.
typedef struct No {
    int valor;
    struct No *proximo;
} No;

// --- Funções da Fila ---

// Adiciona um novo nó com um valor específico no final da fila.
// Recebe um ponteiro para o ponteiro 'frente' para poder modificar o início da fila.
void enfileirar(No **frente, int valor) {
    // 1. Aloca memória para o novo nó.
    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->proximo = NULL; // O novo nó é o último da fila, então seu 'próximo' é NULL.
    // 2. Se a fila estiver vazia, o novo nó se torna o primeiro.
    if (*frente == NULL) {
        *frente = novoNo;
    } else {
        // 3. Percorre a fila até o último nó.
        No *atual = *frente;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        // 4. Adiciona o novo nó no final.
        atual->proximo = novoNo;
    }
    printf("Valor %d enfileirado.\n", valor);
}

// Remove o nó do início e informa seu valor.
void desenfileirar(No **frente) {
    // 1. Armazena o nó a ser removido (o nó da frente).
    No *noRemover = *frente;
    int valorRemovido = noRemover->valor;

    // 2. Move o ponteiro 'frente' para o próximo nó.
    *frente = noRemover->proximo;

    // 3. Libera a memória do nó removido.
    free(noRemover);

    printf("Valor %d desenfileirado.\n", valorRemovido);
}

// --- Função Principal ---

int main() {
    // A fila é representada por um único ponteiro para o início.
    No *fila = NULL;
    int n, valor;

    // 1. Solicita e insere 'n' valores na fila.
    printf("Quantos valores voce deseja inserir na fila? ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Insira o valor %d: ", i + 1);
        scanf("%d", &valor);
        enfileirar(&fila, valor);
    }
    
    // 2. Exibe os elementos desenfileirando e esvaziando a fila.
    printf("\nElementos da fila (desenfileirando e esvaziando):\n");
    while (fila != NULL) {
        desenfileirar(&fila);
    }

    // A fila agora está vazia.
    printf("\nFim das operacoes. A fila agora esta vazia.\n");
    
    return 0;
}
