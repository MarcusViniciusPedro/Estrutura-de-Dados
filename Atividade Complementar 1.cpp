#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10 // Tamanho máximo das estruturas

// --- Estrutura e funções para a FILA ---
int fila[MAX_SIZE];
int frente = -1;
int tras = -1;

// Verifica se a fila está vazia
int fila_vazia() {
    return (frente == -1);
}

// Verifica se a fila está cheia
int fila_cheia() {
    return ((tras + 1) % MAX_SIZE == frente);
}

// Insere um elemento na fila
void enqueue(int valor) {
    if (fila_cheia()) {
        printf("A fila esta cheia!\n");
        return;
    }
    if (fila_vazia()) {
        frente = 0;
    }
    tras = (tras + 1) % MAX_SIZE;
    fila[tras] = valor;
    printf("Elemento %d inserido na fila.\n", valor);
}

// Remove um elemento da fila
void dequeue() {
    if (fila_vazia()) {
        printf("A fila esta vazia!\n");
        return;
    }
    printf("Elemento %d removido da fila.\n", fila[frente]);
    if (frente == tras) {
        frente = -1;
        tras = -1;
    } else {
        frente = (frente + 1) % MAX_SIZE;
    }
}

// Exibe os elementos da fila e suas posições
void exibir_fila() {
    if (fila_vazia()) {
        printf("A fila esta vazia.\n");
        return;
    }
    printf("Elementos da fila:\n");
    int i = frente;
    int pos = 0;
    while (1) {
        printf("Posicao %d: %d\n", pos, fila[i]);
        if (i == tras) {
            break;
        }
        i = (i + 1) % MAX_SIZE;
        pos++;
    }
}

// Localiza um elemento na fila
int localizar_fila(int valor) {
    if (fila_vazia()) {
        return -1;
    }
    int i = frente;
    int pos = 0;
    while (1) {
        if (fila[i] == valor) {
            return pos;
        }
        if (i == tras) {
            break;
        }
        i = (i + 1) % MAX_SIZE;
        pos++;
    }
    return -1;
}

// --- Estrutura e funções para a PILHA ---
int pilha[MAX_SIZE];
int topo = -1;

// Verifica se a pilha está vazia
int pilha_vazia() {
    return (topo == -1);
}

// Verifica se a pilha está cheia
int pilha_cheia() {
    return (topo == MAX_SIZE - 1);
}

// Insere um elemento na pilha
void push(int valor) {
    if (pilha_cheia()) {
        printf("A pilha esta cheia!\n");
        return;
    }
    topo++;
    pilha[topo] = valor;
    printf("Elemento %d inserido na pilha.\n", valor);
}

// Remove um elemento da pilha
void pop() {
    if (pilha_vazia()) {
        printf("A pilha esta vazia!\n");
        return;
    }
    printf("Elemento %d removido da pilha.\n", pilha[topo]);
    topo--;
}

// Mostra o elemento do topo da pilha
void peek() {
    if (pilha_vazia()) {
        printf("A pilha esta vazia.\n");
        return;
    }
    printf("Elemento no topo: %d\n", pilha[topo]);
}

// Função principal para o menu
int main() {
    int opcao_principal, opcao_submenu, valor;
    
    do {
        printf("\n--- Menu Principal ---\n");
        printf("1. Operacoes com FILA\n");
        printf("2. Operacoes com PILHA\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao_principal);

        switch (opcao_principal) {
            case 1:
                do {
                    printf("\n--- Menu FILA ---\n");
                    printf("1. Inserir (enqueue)\n");
                    printf("2. Remover (dequeue)\n");
                    printf("3. Exibir Fila\n");
                    printf("4. Verificar se a fila esta vazia\n");
                    printf("5. Verificar se a fila esta cheia\n");
                    printf("6. Localizar elemento\n");
                    printf("7. Voltar ao menu principal\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opcao_submenu);

                    switch (opcao_submenu) {
                        case 1:
                            printf("Digite o valor a ser inserido: ");
                            scanf("%d", &valor);
                            enqueue(valor);
                            break;
                        case 2:
                            dequeue();
                            break;
                        case 3:
                            exibir_fila();
                            break;
                        case 4:
                            if (fila_vazia())
                                printf("A fila esta vazia.\n");
                            else
                                printf("A fila nao esta vazia.\n");
                            break;
                        case 5:
                            if (fila_cheia())
                                printf("A fila esta cheia.\n");
                            else
                                printf("A fila nao esta cheia.\n");
                            break;
                        case 6:
                            printf("Digite o valor a ser localizado: ");
                            scanf("%d", &valor);
                            int pos = localizar_fila(valor);
                            if (pos != -1)
                                printf("O elemento %d esta na posicao %d da fila.\n", valor, pos);
                            else
                                printf("O elemento %d nao foi encontrado na fila.\n", valor);
                            break;
                        case 7:
                            printf("Voltando ao menu principal.\n");
                            break;
                        default:
                            printf("Opcao invalida!\n");
                    }
                } while (opcao_submenu != 7);
                break;
            case 2:
                do {
                    printf("\n--- Menu PILHA ---\n");
                    printf("1. Inserir (push)\n");
                    printf("2. Remover (pop)\n");
                    printf("3. Topo (peek)\n");
                    printf("4. Verificar se a pilha esta vazia\n");
                    printf("5. Verificar se a pilha esta cheia\n");
                    printf("6. Voltar ao menu principal\n");
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opcao_submenu);

                    switch (opcao_submenu) {
                        case 1:
                            printf("Digite o valor a ser inserido: ");
                            scanf("%d", &valor);
                            push(valor);
                            break;
                        case 2:
                            pop();
                            break;
                        case 3:
                            peek();
                            break;
                        case 4:
                            if (pilha_vazia())
                                printf("A pilha esta vazia.\n");
                            else
                                printf("A pilha nao esta vazia.\n");
                            break;
                        case 5:
                            if (pilha_cheia())
                                printf("A pilha esta cheia.\n");
                            else
                                printf("A pilha nao esta cheia.\n");
                            break;
                        case 6:
                            printf("Voltando ao menu principal.\n");
                            break;
                        default:
                            printf("Opcao invalida!\n");
                    }
                } while (opcao_submenu != 6);
                break;
            case 3:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao_principal != 3);

    return 0;
}
