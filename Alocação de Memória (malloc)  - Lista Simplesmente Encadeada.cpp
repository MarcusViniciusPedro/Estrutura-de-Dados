#include <stdio.h>
#include <stdlib.h>

// Estrutura do Nó (Elemento) da Lista
typedef struct no_lista {
    int dado;
    struct no_lista *proximo;
} NoLista;

// Função para inserir um elemento no INÍCIO da lista
NoLista *inserir_no_inicio(NoLista *lista, int valor) {
    NoLista *novo_no = (NoLista *)malloc(sizeof(NoLista));
    if (novo_no == NULL) {
        printf("Erro de alocação de memória (Inserção na Lista).\n");
        exit(EXIT_FAILURE);
    }
    
    novo_no->dado = valor;
    // O novo nó aponta para o antigo primeiro nó
    novo_no->proximo = lista;
    
    // O novo nó se torna a nova cabeça da lista
    return novo_no;
}

// Função para exibir todos os elementos da lista
void exibir_lista(NoLista *lista) {
    if (lista == NULL) {
        printf("A lista está vazia.\n");
        return;
    }
    
    NoLista *p = lista;
    printf("Lista: ");
    while (p != NULL) {
        printf("%d", p->dado);
        p = p->proximo;
        if (p != NULL) {
            printf(" -> ");
        }
    }
    printf("\n");
}

// Função para liberar a memória da lista (prevenção de memory leak)
void liberar_lista(NoLista *lista) {
    NoLista *p = lista;
    while (p != NULL) {
        NoLista *temp = p;
        p = p->proximo;
        free(temp);
    }
}


// Função principal para teste da Lista Simplesmente Encadeada
int main() {
    NoLista *minha_lista = NULL; // Ponteiro inicial (cabeça) é NULL
    
    int dados[] = {20, 10, 5, 30, 99, 7};
    int n = sizeof(dados) / sizeof(dados[0]);
    
    printf("--- SIMULAÇÃO DE LISTA SIMPLESMENTE ENCADEADA ---\n");
    printf("1. Inserindo dados do vetor no INÍCIO da lista: {20, 10, 5, 30, 99, 7}\n");
    
    // Inserção no início
    for (int i = 0; i < n; i++) {
        minha_lista = inserir_no_inicio(minha_lista, dados[i]);
        printf("Inserido: %d\n", dados[i]);
    }
    
    printf("\n2. Estado final da Lista (a ordem é invertida devido à inserção no início):\n");
    exibir_lista(minha_lista);
    
    // Libera a memória alocada
    liberar_lista(minha_lista);
    printf("\n--- Fim da Simulação da Lista (Memória liberada) ---\n");
    return 0;
}
// main_lista(); // Chame esta função no seu compilador C
