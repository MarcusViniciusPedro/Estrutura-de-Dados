#include <stdio.h>
#include <stdlib.h>		// necessário para as funções rand() e srand()
#include <time.h>		// para as funções clock_t, clock(), CLOCKS_PER_SEC
#include <string.h>	
#define TAMANHO 5000

int vet[TAMANHO];
FILE *arq;
char filename[30]="numero.txt";

void heap(int vet[], int n, int i){ // Função que realiza o Heap (nos slides é chamada de Sift)
   
    int maior = i; // Inicialização
    int l = 2 * i ; // Inicialiazção do lado esquerdo (2i)
    int r = 2 * i + 1; // Inicialiazção do lado esquerdo (2i+1)

    if (l < n && vet[l] > vet[maior]) // Verifica se o "filho" esquerdo é maior que a raiz
        maior = l;
    
    if (r < n && vet[r] > vet[maior]) // Verifica se o "filho" esquerdo é o maior até então
        maior = r;
    
    if (maior != i) { // Se a raiz não for a maior
        int temp = vet[i];
        vet[i] = vet[maior];
        vet[maior] = temp;
        heap(vet, n, maior);
    }
}
void heapsort(int vet[], int n){ // Função principal, Vet é o vetor e N é a quantidade de elementos no vetor
    
    for (int i = n / 2 - 1; i >= 0; i--) // Cria o Heap (função Build nos Slides)
        heap(vet, n, i);
        
    for (int i = n - 1; i > 0; i--) { // Mudança da raiz para o final
        int temp = vet[0];
        vet[0] = vet[i];
        vet[i] = temp;
        heap(vet, i, 0);
    }
}

int gera_arquivo_numeros(int tam){
	
	int i;
	arq = fopen(filename, "wt+"); // 'wt+' permite escrita e leitura, mas trunca o arquivo.
	
	if (arq == NULL)
		return(-1); // falha na abertura do arquivo
	else{
		srand(time(NULL)); // arquivo aberto com sucesso
		
		for (i=0; i < tam; i++){
			vet[i] = rand() % 10000; // gerando 5000 valores aleatórios na faixa de 0 a 9999
			if (i!=4999)
				fprintf(arq, "%d,", vet[i]);
			else
				fprintf(arq, "%d", vet[i]);
		} 
	return 0; 
	}
}

void le_arquivo(int TAM){ // faz a abertura do arquivo e leitura de uma quantidade de números 

	int i;
	arq = fopen(filename, "rt");
	
	if (arq == NULL)
		return; // falha na abertura do arquivo
	else{
		// arquivo aberto com sucesso 
		for (i=0; i < TAM; i++){ // Usando TAM (tamanho) para consistência 
			fscanf(arq, "%d,", &vet[i]); // Adicionando a vírgula para tentar ignorá-la
		}
	}
	fclose (arq);
}

int main(){
	
	int i;
	int r;
	int tam_ordenar = 5000; // para ordenação controlada de n números
		
	gera_arquivo_numeros(5000);
		
	double time_spent = 0.0; // para armazenar o tempo de execução do código
	
	clock_t begin = clock(); // tempo inicial

	for (r = 0; r < 1000; r++) { // Loop de 1000 repetições para medir o tempo de forma mais precisa
		heapsort(vet, tam_ordenar); // Chama o heapsort
	}	
		
	clock_t end = clock();// tempo final

	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; //calcula o tempo decorrido encontrando a diferença (end - begin) e dividindo a diferença por CLOCKS_PER_SEC para converter para segundos

	printf("\n\nVetor ordenado:\n");
	for (i = 0; i < tam_ordenar; i++){
		printf(" %d ", vet[i]);
	}
	
	printf("\nO tempo decorrido e de %f segundos", time_spent);
	printf("\n\n");
	
	system ("PAUSE");
	return 0;
}
