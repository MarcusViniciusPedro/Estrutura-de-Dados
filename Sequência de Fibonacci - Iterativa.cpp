#include <stdio.h>

/**
 * Função iterativa para calcular o n-ésimo termo de Fibonacci.
 * Utiliza variáveis de controle para evitar recálculos e otimizar.
 *
 * @param n O índice do termo a ser calculado (n-ésimo).
 * @return O valor do n-ésimo termo de Fibonacci.
 */
long long fibonacci_iterativo(int n) {
    // Casos triviais
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    // Variáveis para armazenar os dois termos anteriores
    long long termo_anterior_2 = 0; // Representa F(i-2), inicia como F(0)
    long long termo_anterior_1 = 1; // Representa F(i-1), inicia como F(1)
    long long termo_atual = 0;

    // Loop de i = 2 até n
    for (int i = 2; i <= n; i++) {
        // O termo atual é a soma dos dois anteriores
        termo_atual = termo_anterior_1 + termo_anterior_2;

        // Atualiza as variáveis para a próxima iteração
        termo_anterior_2 = termo_anterior_1; // F(i-1) se torna F(i-2)
        termo_anterior_1 = termo_atual;      // F(i) se torna F(i-1)
    }

    // Retorna o último termo calculado (F(n))
    return termo_atual;
}

int main() {
    int n;
    printf("--- Cálculo de Fibonacci (Iterativo) ---\n");
    printf("Digite o valor de n (índice do termo): ");

    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Entrada inválida. Digite um número inteiro não negativo.\n");
        return 1;
    }

    long long resultado = fibonacci_iterativo(n);

    printf("\nO %d-ésimo termo de Fibonacci (F%d) é: %lld\n", n, n, resultado);

    return 0;
}
