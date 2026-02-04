#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da pilha.
typedef struct No {
    int valor;
    struct No *proximo;
} No;

// Função para empilhar um novo valor no topo da pilha.
// Recebe um ponteiro para o ponteiro topo para poder modificar o topo da pilha.
void empilhar(No **topo, int valor) {
    // 1. Aloca memória para o novo nó.
    No *novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }
    
    // 2. Atribui o valor ao novo nó.
    novoNo->valor = valor;
    
    // 3. O 'proximo' do novo nó aponta para o nó que atualmente é o topo.
    novoNo->proximo = *topo;
    
    // 4. Atualiza o 'topo' da pilha para o novo nó.
    *topo = novoNo;

    printf("Valor %d empilhado.\n", valor);
}

// Função para desempilhar (pop) o valor do topo da pilha.
void desempilhar(No **topo) {
    // 1. Verifica se a pilha está vazia.
    if (*topo == NULL) {
        printf("A pilha esta vazia. Nao e possivel desempilhar.\n");
        return;
    }
    
    // 2. Armazena o nó a ser removido (o nó do topo).
    No *noRemover = *topo;
    int valorRemovido = noRemover->valor;

    // 3. Move o 'topo' para o próximo nó.
    *topo = noRemover->proximo;

    // 4. Libera a memória do nó removido.
    free(noRemover);

    printf("Valor %d desempilhado.\n", valorRemovido);
}

// Função para exibir os elementos da pilha.
void exibirPilha(No *topo) {
    if (topo == NULL) {
        printf("A pilha esta vazia.\n");
        return;
    }

    printf("Elementos da pilha (do topo para a base): ");
    
    // 1. Percorre a pilha a partir do topo.
    No *atual = topo;
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

// Função principal (main) para testar o código.
int main() {
    // Inicializa o ponteiro 'topo' como NULL para indicar uma pilha vazia.
    No *pilha = NULL;
    int n, valor;

    // Solicita ao usuário o número de valores a serem inseridos.
    printf("Quantos valores voce deseja inserir na pilha? ");
    scanf("%d", &n);

    // Loop para empilhar 'n' valores.
    for (int i = 0; i < n; i++) {
        printf("Insira o valor %d: ", i + 1);
        scanf("%d", &valor);
        empilhar(&pilha, valor);
    }
    
    // Exibe a pilha completa.
    exibirPilha(pilha);

    // Exemplo de desempilhamento.
    printf("\nIniciando operacoes de desempilhamento...\n");
    desempilhar(&pilha);
    desempilhar(&pilha);
    
    // Exibe a pilha após as remoções.
    exibirPilha(pilha);

    // Libera a memória de todos os nós restantes.
    while (pilha != NULL) {
        desempilhar(&pilha);
    }

    return 0;
}
