#include <stdio.h>

/**
 * Função recursiva para calcular o n-ésimo termo de Fibonacci.
 * F(n) = F(n-1) + F(n-2)
 *
 * @param n O índice do termo a ser calculado (n-ésimo).
 * @return O valor do n-ésimo termo de Fibonacci.
 */
long int fibonacci_recursivo(int n) {
    // Caso Base 1: F(0) = 0
    if (n == 0) {
        return 0;
    }
    // Caso Base 2: F(1) = 1
    else if (n == 1) {
        return 1;
    }
    // Passo Recursivo: F(n) = F(n-1) + F(n-2)
    else {
        return fibonacci_recursivo(n - 1) + fibonacci_recursivo(n - 2);
    }
}

int main() {
    int n;
    printf("--- Cálculo de Fibonacci (Recursivo) ---\n");
    printf("Digite o valor de n (índice do termo): ");

    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Entrada inválida. Digite um número inteiro não negativo.\n");
        return 1;
    }

    if (n > 45) {
        printf("Aviso: Valores muito grandes de n podem levar tempo excessivo de processamento com a recursão pura.\n");
    }

    long int resultado = fibonacci_recursivo(n);

    printf("\nO %d-ésimo termo de Fibonacci (F%d) é: %lld\n", n, n, resultado);

    return 0;
}
