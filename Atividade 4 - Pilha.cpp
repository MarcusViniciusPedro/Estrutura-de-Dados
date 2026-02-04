#include <stdio.h>
#include <stdlib.h>
typedef struct NoPilha {
    int info;
    struct NoPilha *prox;
} NoPilha;
typedef NoPilha *Pilha;
Pilha P = NULL;
int esta_vazia(Pilha p) {
    return (p == NULL);
}
void push(Pilha *p, int valor) {
    NoPilha *novo = (NoPilha *)malloc(sizeof(NoPilha));
    if (novo == NULL) {
        perror("Erro de alocação de memória");
        exit(EXIT_FAILURE);
    }
    novo->info = valor;
    novo->prox = *p; 
    *p = novo;      
}
int pop(Pilha *p) {
    if (esta_vazia(*p)) {
        printf("Erro: Pilha vazia ao tentar pop.\n");
        exit(EXIT_FAILURE);
    }
    NoPilha *topo = *p;
    int valor = topo->info;
    *p = topo->prox;
    free(topo);
    return valor;
}
void ExibirInversoRecursivo() {
    int ValorTopo;
    if (!esta_vazia(P)) {
        ValorTopo = pop(&P);
        ExibirInversoRecursivo();
        printf("%d", ValorTopo);
        if (!esta_vazia(P)) {
        }
    }
}
void Principal() {
    int V[13] = {55, 43, 45, 31, 32, 35, 60, 70, 79, 59, 65, 58, 42};
    int i;
    int TamanhoVetor = 13;
    for (i = 0; i < TamanhoVetor; i++) { 
        push(&P, V[i]);
    }
    printf("Elementos do vetor em ordem inversa (usando POP recursivo):\n");
    ExibirInversoRecursivo();
}
int main() {
    Principal();
    while (!esta_vazia(P)) {
        pop(&P);
    }
    return 0;
}
