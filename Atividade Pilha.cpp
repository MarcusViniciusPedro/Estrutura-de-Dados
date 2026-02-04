#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da pilha.
// Cada nó contém um valor inteiro e um ponteiro para o próximo nó.
typedef struct No {
    int valor;
    struct No *proximo;
} No;

// Definição da estrutura da pilha.
// A pilha é composta por um único ponteiro para o topo, que é o ponto de acesso.
typedef struct Pilha {
    No *topo;
} Pilha;

// --- Funções da Pilha ---

// Função para inicializar a pilha.
// Ela cria e retorna uma pilha vazia, onde o topo aponta para NULL.
Pilha* criarPilha() {
    Pilha *pilha = (Pilha*)malloc(sizeof(Pilha));
    if (pilha == NULL) {
        printf("Erro de alocacao de memoria para a pilha!\n");
        exit(1);
    }
    pilha->topo = NULL;
    return pilha;
}

// Função para verificar se a pilha está vazia.
// Retorna 1 se a pilha estiver vazia (topo == NULL) e 0 caso contrário.
int pilhaVazia(Pilha *pilha) {
    return (pilha->topo == NULL);
}

// Função para empilhar (push) um novo valor.
// Adiciona um novo nó com o valor especificado no topo da pilha.
void empilhar(Pilha *pilha, int valor) {
    // 1. Alocação de memória para o novo nó.
    No *novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro de alocacao de memoria para o novo no!\n");
        exit(1);
    }
    
    // 2. Atribuição do valor e do ponteiro do novo nó.
    novoNo->valor = valor;
    
    // 3. O 'proximo' do novo nó aponta para o nó que atualmente é o topo.
    novoNo->proximo = pilha->topo;
    
    // 4. O topo da pilha é atualizado para apontar para o novo nó.
    // O novo nó agora é o primeiro da lista, ou seja, o novo topo.
    pilha->topo = novoNo;

    printf("Valor %d empilhado com sucesso.\n", valor);
}

// Função para desempilhar (pop) um valor.
// Remove e retorna o valor do nó que está no topo da pilha.
int desempilhar(Pilha *pilha) {
    // 1. Verificação se a pilha está vazia.
    if (pilhaVazia(pilha)) {
        printf("Erro: Pilha esta vazia. Nao e possivel desempilhar.\n");
        // Retorna um valor simbólico de erro.
        return -1; 
    }
    
    // 2. Armazena o nó a ser removido (o nó do topo).
    No *noRemover = pilha->topo;
    int valorRemovido = noRemover->valor;

    // 3. Move o topo da pilha para o próximo nó.
    // O topo da pilha agora aponta para o segundo nó da lista.
    pilha->topo = noRemover->proximo;

    // 4. Libera a memória do nó removido para evitar vazamentos.
    free(noRemover);

    printf("Valor %d desempilhado com sucesso.\n", valorRemovido);
    return valorRemovido;
}

// Função para exibir os elementos da pilha.
// Percorre a pilha do topo até o fim.
void exibirPilha(Pilha *pilha) {
    if (pilhaVazia(pilha)) {
        printf("A pilha esta vazia.\n");
        return;
    }

    // 1. Cria um ponteiro temporário para percorrer a pilha, começando pelo topo.
    No *atual = pilha->topo;
    printf("Elementos da pilha (do topo para a base): ");

    // 2. Percorre a pilha enquanto o ponteiro não for NULL.
    while (atual != NULL) {
        printf("%d ", atual->valor);
        // Avança para o próximo nó.
        atual = atual->proximo;
    }
    printf("\n");
}

// Função principal (main) para testar o código.
int main() {
    // 1. Cria uma nova pilha vazia.
    Pilha *minhaPilha = criarPilha();
    int n, valor;

    // 2. Solicita ao usuário o número de valores a serem inseridos.
    printf("Quantos valores voce deseja inserir na pilha? ");
    scanf("%d", &n);

    // 3. Loop para empilhar 'n' valores.
    for (int i = 0; i < n; i++) {
        printf("Insira o valor %d: ", i + 1);
        scanf("%d", &valor);
        empilhar(minhaPilha, valor);
    }
    
    // 4. Exibe a pilha completa.
    exibirPilha(minhaPilha);
    
    printf("\n");
    // 5. Exemplo de desempilhamento.
    printf("Iniciando operacoes de desempilhamento...\n");
    desempilhar(minhaPilha);
    desempilhar(minhaPilha);
    
    printf("\n");
    // 6. Exibe a pilha após as remoções.
    exibirPilha(minhaPilha);
    
    // 7. Libera a memória da pilha para evitar vazamentos.
    // É uma boa prática liberar todos os nós da pilha antes de liberar a própria pilha.
    while (!pilhaVazia(minhaPilha)) {
        desempilhar(minhaPilha);
    }
    free(minhaPilha);
    
    return 0;
}
