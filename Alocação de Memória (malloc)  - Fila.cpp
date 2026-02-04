#include <stdio.h>
#include <stdlib.h>

// Estrutura do Nó (Elemento) da Fila
typedef struct no_fila {
    int dado;
    struct no_fila *proximo;
} NoFila;

// Estrutura principal da Fila
typedef struct {
    NoFila *frente;
    NoFila *fim;
} Fila;

// Inicializa a fila
void inicializar_fila(Fila *f) {
    f->frente = NULL;
    f->fim = NULL;
}

// Operação ENQUEUE (Enfileirar)
void enqueue(Fila *f, int valor) {
    NoFila *novo_no = (NoFila *)malloc(sizeof(NoFila));
    if (novo_no == NULL) {
        printf("Erro de alocação de memória (ENQUEUE).\n");
        exit(EXIT_FAILURE);
    }
    
    novo_no->dado = valor;
    novo_no->proximo = NULL; // Novo nó sempre será o último
    
    if (f->fim == NULL) {
        // Se a fila estava vazia, a frente e o fim apontam para o novo nó
        f->frente = novo_no;
    } else {
        // O antigo fim aponta para o novo nó
        f->fim->proximo = novo_no;
    }
    // O novo nó se torna o novo fim
    f->fim = novo_no;
    printf("ENQUEUE: %d (Enfileirado)\n", valor);
}

// Operação DEQUEUE (Desenfileirar)
int dequeue(Fila *f) {
    if (f->frente == NULL) {
        printf("Erro: Fila vazia.\n");
        return -1; // Valor de erro
    }
    
    NoFila *no_removido = f->frente;
    int valor_removido = no_removido->dado;
    
    // A frente avança para o próximo nó
    f->frente = f->frente->proximo;
    
    if (f->frente == NULL) {
        // Se a fila ficou vazia, o fim também deve ser NULL
        f->fim = NULL;
    }
    
    free(no_removido);
    return valor_removido;
}

// Função principal para teste da Fila
int main() {
    Fila minha_fila;
    inicializar_fila(&minha_fila);
    
    int dados[] = {20, 10, 5, 30, 99, 7};
    int n = sizeof(dados) / sizeof(dados[0]);
    
    printf("--- SIMULAÇÃO DE FILA (FIFO) ---\n");
    printf("1. Inserindo dados do vetor: {20, 10, 5, 30, 99, 7}\n");
    
    // Inserção (ENQUEUE)
    for (int i = 0; i < n; i++) {
        enqueue(&minha_fila, dados[i]);
    }
    
    printf("\n2. Removendo (DEQUEUE) os elementos (Ordem FIFO):\n");
    
    // Remoção (DEQUEUE) e exibição
    while (minha_fila.frente != NULL) {
        printf("DEQUEUE: %d (Desenfileirado)\n", dequeue(&minha_fila));
    }
    
    printf("\n--- Fim da Simulação da Fila ---\n");
    return 0;
}
// main_fila(); // Chame esta função no seu compilador C
