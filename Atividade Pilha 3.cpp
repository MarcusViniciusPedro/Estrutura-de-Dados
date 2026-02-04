#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó.
typedef struct No {
    int valor;
    struct No *proximo;
} No;

// --- Funções da Pilha ---

// Adiciona um novo nó com um valor específico no topo da pilha.
// Recebe um ponteiro para o ponteiro 'topo'.
void empilhar(No **topo, int valor) {
    // 1. Alocação de memória para o novo nó.
    No *novoNo = (No*)malloc(sizeof(No));
    // 2. Atribui o valor e faz o novo nó apontar para o antigo topo.
    novoNo->valor = valor;
    novoNo->proximo = *topo;
    // 3. Atualiza o 'topo' da pilha para o novo nó.
    *topo = novoNo;

    printf("Valor %d empilhado.\n", valor);
}

// Remove o nó do topo e imprime seu valor.
void desempilhar(No **topo) {
    // Armazena o nó a ser removido.
    No *noRemover = *topo;
    int valorRemovido = noRemover->valor;

    // Move o 'topo' para o próximo nó.
    *topo = noRemover->proximo;

    // Libera a memória.
    free(noRemover);

    printf("Valor %d desempilhado.\n", valorRemovido);
}

// --- Função Principal ---

int main() {
    // A pilha é representada por um único ponteiro para o topo.
    No *pilha = NULL;
    int n, valor;

    // 1. Solicita e insere 'n' valores na pilha.
    printf("Quantos valores voce deseja inserir na pilha? ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Insira o valor %d: ", i + 1);
        scanf("%d", &valor);
        empilhar(&pilha, valor);
    }
    
    // 2. Exibe os elementos desempilhando e esvaziando a pilha.
    printf("\nElementos da pilha (desempilhando e esvaziando):\n");
    while (pilha != NULL) {
        desempilhar(&pilha);
    }

    // A pilha agora está vazia.
    printf("\nFim das operacoes. A pilha agora esta vazia.\n");
    
    return 0;
}
