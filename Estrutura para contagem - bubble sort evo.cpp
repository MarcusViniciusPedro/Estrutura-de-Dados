#include <stdio.h>
#include <stdlib.h> // necessário para as funções rand() e srand() 
#include <time.h> // for clock_t, clock(), CLOCKS_PER_SEC 
#define TAMANHO 5000

int vet[5000];
FILE *arq;
char filename[30]="numero.txt";

void bubbleSort(int arr[], int n){
    int i, j;
    
    for (i = 0; i < n - 1; i++) { // A última i posição já está no lugar certo
        for (j = 0; j < n - i - 1; j++) { // Troca se o elemento encontrado for maior que o próximo elemento
            if (arr[j] > arr[j + 1]) { // Troca de elementos usando uma variável auxiliar
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int gera_arquivo_numeros(int tam){
	int i;
	arq = fopen(filename, "wt+");
	
	if (arq == NULL)
		return(-1); // falha na abertura do arquivo
	else{
		srand(time(NULL)); // arquivo aberto com sucesso
		for (i=0; i < tam; i++){
			vet[i] = rand() % 10000; // gerando 5000 valores aleatórios na faixa de 0 a 10000
			if (i!=4999)
				fprintf(arq, "%d,", vet[i]);
			else
				fprintf(arq, "%d", vet[i]);
		}
		return 0;
	}
	fclose (arq);
}

void le_arquivo(int TAM){ // faz a abertura do arquivo e leitura de uma quantidade de números
	int i;
	arq = fopen(filename, "rt");
	
	if (arq == NULL)
		return; // falha na abertura do arquivo
	else{
		srand(time(NULL)); // arquivo aberto com sucesso
		for (i=0; i < 5000; i++){
			fscanf(arq, "%d", &vet[i]); // lendo 5000 valores aleatórios na faixa de 0 a 10000
		}
	}
	fclose (arq);
}

int main() {
	int i;
	int r;
	int tam_ordenar= 3500; // função de ordenação que irá indicar quantos elementos quero organizar 
		
	gera_arquivo_numeros(5000);
		
	double time_spent = 0.0; // para armazenar o tempo de execução do código
	clock_t begin = clock(); // tempo inicial 
    
	for (r = 0; r < 1000; r++) { // for que realiza a função r vezes (o quanto for desejável)
		bubbleSort(vet, tam_ordenar);
	}	
	clock_t end = clock(); // tempo final 
	
	
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; // Calcula o tempo decorrido encontrando a diferença (fim - início) e dividindo-a por CLOCKS_PER_SEC para converter em segundos.

	printf("\n\nVetor ordenado:\n");
	for (i = 0; i < tam_ordenar; i++){
		printf(" %d ", vet[i]);
	}
	
	printf("\nO tempo decorrido e de %f segundos", time_spent);
	printf("\n\n");
	
	system ("PAUSE");
	return 0;
}
