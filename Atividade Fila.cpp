#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da fila.
// Cada nó contém um valor inteiro e um ponteiro para o próximo nó.
typedef struct No {
    int valor;
    struct No *proximo;
} No;

// Definição da estrutura da fila.
// A fila é composta por dois ponteiros: um para o primeiro (frente) e outro para o último (traseira) nó.
typedef struct Fila {
    No *frente;
    No *traseira;
} Fila;

// --- Funções da Fila ---

// Função para inicializar a fila.
// Ela cria e retorna uma fila vazia, onde a frente e a traseira apontam para NULL.
Fila* criarFila() {
    Fila *fila = (Fila*)malloc(sizeof(Fila));
    if (fila == NULL) {
        printf("Erro de alocacao de memoria para a fila!\n");
        exit(1);
    }
    fila->frente = NULL;
    fila->traseira = NULL;
    return fila;
}

// Função para verificar se a fila está vazia.
// Retorna 1 se a fila estiver vazia (frente == NULL) e 0 caso contrário.
int filaVazia(Fila *fila) {
    return (fila->frente == NULL);
}

// Função para enfileirar (enqueue) um novo valor.
// Adiciona um novo nó com o valor especificado no final da fila.
void enfileirar(Fila *fila, int valor) {
    // 1. Alocação de memória para o novo nó.
    No *novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro de alocacao de memoria para o novo no!\n");
        exit(1);
    }
    
    // 2. Atribuição do valor e do ponteiro do novo nó.
    novoNo->valor = valor;
    novoNo->proximo = NULL; // O novo nó sempre será o último, então seu 'próximo' é NULL.

    // 3. Verificação se a fila está vazia.
    if (filaVazia(fila)) {
        // Se a fila estiver vazia, o novo nó se torna tanto a frente quanto a traseira.
        fila->frente = novoNo;
        fila->traseira = novoNo;
    } else {
        // Se a fila não estiver vazia, o novo nó é adicionado após o nó atual da traseira.
        fila->traseira->proximo = novoNo;
        // A traseira da fila é atualizada para apontar para o novo nó.
        fila->traseira = novoNo;
    }
    printf("Valor %d enfileirado com sucesso.\n", valor);
}

// Função para desenfileirar (dequeue) um valor.
// Remove e retorna o valor do primeiro nó da fila.
int desenfileirar(Fila *fila) {
    // 1. Verificação se a fila está vazia.
    if (filaVazia(fila)) {
        printf("Erro: Fila esta vazia. Nao e possivel desenfileirar.\n");
        // Retorna um valor simbólico de erro.
        return -1; 
    }
    
    // 2. Armazena o nó a ser removido (o nó da frente).
    No *noRemover = fila->frente;
    int valorRemovido = noRemover->valor;

    // 3. Move a frente da fila para o próximo nó.
    fila->frente = noRemover->proximo;

    // 4. Verificação se a fila ficou vazia após a remoção.
    if (fila->frente == NULL) {
        // Se a frente se tornou NULL, significa que a fila ficou vazia.
        // A traseira também deve ser NULL.
        fila->traseira = NULL;
    }
    
    // 5. Libera a memória do nó removido para evitar vazamentos.
    free(noRemover);

    printf("Valor %d desenfileirado com sucesso.\n", valorRemovido);
    return valorRemovido;
}

// Função para exibir os elementos da fila.
void exibirFila(Fila *fila) {
    if (filaVazia(fila)) {
        printf("A fila esta vazia.\n");
        return;
    }

    // 1. Cria um ponteiro temporário para percorrer a fila, começando pela frente.
    No *atual = fila->frente;
    printf("Elementos da fila: ");

    // 2. Percorre a fila enquanto o ponteiro não for NULL.
    while (atual != NULL) {
        printf("%d ", atual->valor);
        // Avança para o próximo nó.
        atual = atual->proximo;
    }
    printf("\n");
}

// Função principal (main) para testar o código.
int main() {
    // 1. Cria uma nova fila vazia.
    Fila *minhaFila = criarFila();
    int n, valor;

    // 2. Solicita ao usuário o número de valores a serem inseridos.
    printf("Quantos valores voce deseja inserir na fila? ");
    scanf("%d", &n);

    // 3. Loop para enfileirar 'n' valores.
    for (int i = 0; i < n; i++) {
        printf("Insira o valor %d: ", i + 1);
        scanf("%d", &valor);
        enfileirar(minhaFila, valor);
    }
    
    // 4. Exibe a fila completa.
    exibirFila(minhaFila);
    
    printf("\n");
    // 5. Exemplo de desenfileiramento.
    printf("Iniciando operacoes de desenfileiramento...\n");
    desenfileirar(minhaFila);
    desenfileirar(minhaFila);
    
    printf("\n");
    // 6. Exibe a fila após as remoções.
    exibirFila(minhaFila);
    
    // 7. Libera a memória da fila para evitar vazamentos.
    // É uma boa prática liberar todos os nós da fila antes de liberar a própria fila.
    while (!filaVazia(minhaFila)) {
        desenfileirar(minhaFila);
    }
    free(minhaFila);
    
    return 0;
}
