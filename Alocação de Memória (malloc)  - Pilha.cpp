#include <stdio.h>
#include <stdlib.h>

// Estrutura do Nó (Elemento) da Pilha
typedef struct no_pilha {
    int dado;
    struct no_pilha *proximo;
} NoPilha;

// Estrutura principal da Pilha
typedef struct {
    NoPilha *topo;
} Pilha;

// Inicializa a pilha (topo aponta para NULL)
void inicializar_pilha(Pilha *p) {
    p->topo = NULL;
}

// Operação PUSH (Empilhar)
void push(Pilha *p, int valor) {
    NoPilha *novo_no = (NoPilha *)malloc(sizeof(NoPilha));
    if (novo_no == NULL) {
        printf("Erro de alocação de memória (PUSH).\n");
        exit(EXIT_FAILURE);
    }
    
    novo_no->dado = valor;
    // O novo nó aponta para o antigo topo
    novo_no->proximo = p->topo;
    // O novo nó se torna o novo topo
    p->topo = novo_no;
    printf("PUSH: %d (Empilhado)\n", valor);
}

// Operação POP (Desempilhar)
int pop(Pilha *p) {
    if (p->topo == NULL) {
        printf("Erro: Pilha vazia.\n");
        return -1; // Valor de erro
    }
    
    NoPilha *no_removido = p->topo;
    int valor_removido = no_removido->dado;
    
    // O topo avança para o próximo nó
    p->topo = p->topo->proximo;
    
    free(no_removido);
    return valor_removido;
}

// Função principal para teste da Pilha
int main() {
    Pilha minha_pilha;
    inicializar_pilha(&minha_pilha);
    
    int dados[] = {20, 10, 5, 30, 99, 7};
    int n = sizeof(dados) / sizeof(dados[0]);
    
    printf("--- SIMULAÇÃO DE PILHA (LIFO) ---\n");
    printf("1. Inserindo dados do vetor: {20, 10, 5, 30, 99, 7}\n");
    
    // Inserção
    for (int i = 0; i < n; i++) {
        push(&minha_pilha, dados[i]);
    }
    
    printf("\n2. Removendo (POP) os elementos (Ordem LIFO):\n");
    
    // Remoção (POP) e exibição
    while (minha_pilha.topo != NULL) {
        printf("POP: %d (Desempilhado)\n", pop(&minha_pilha));
    }
    
    printf("\n--- Fim da Simulação da Pilha ---\n");
    return 0;
}
// main_pilha(); // Chame esta função no seu compilador C
