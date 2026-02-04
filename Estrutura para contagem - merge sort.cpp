#include <stdio.h>
#include <stdlib.h> // necessário para as funções rand() e srand() 
#include <time.h> // para as funções clock_t, clock(), CLOCKS_PER_SEC 
#include <string.h>
#define TAMANHO 5000

int vet[TAMANHO];
FILE *arq;
char filename[30]="numero.txt";


void merge(int v[], int inicio, int meio, int fim){ // Função merge 

    int tamEsq = meio - inicio + 1;
    int tamDir = fim - meio;
    
    // Alocação de arrays temporários. 
    int esq[tamEsq];
    int dir[tamDir];
    int i = 0; // Índice inicial do primeiro sub-array
    int j = 0; // Índice inicial do segundo sub-array
    int k = inicio; // Índice inicial do array mesclado
    
    for(int i = 0; i < tamEsq; i++){ // Copia os dados para o array temporário esq[]
        esq[i] = v[inicio + i];
    }

    for(int j = 0; j < tamDir; j++){ // Copia os dados para o array temporário dir[]
        dir[j] = v[meio + 1 + j];
    }

    while(i < tamEsq && j < tamDir){ // Mescla os arrays temporários de volta para v[inicio..fim]
        if(esq[i] <= dir[j]){
            v[k++] = esq[i++];
        }
		else{
            v[k++] = dir[j++];
        }
    }
    
    while(i < tamEsq){ // Copia os elementos restantes de esq[], se houver 
        v[k++] = esq[i++];
    }

    while(j < tamDir){ // Copia os elementos restantes de dir[], se houver
        v[k++] = dir[j++];
    }
}

void mergeSort (int v[], int inicio, int fim){ // Função mergeSort

    if(inicio >= fim){ // Caso base: Se o sub-array tiver um único elemento (inicio == fim) ou for inválido, não faz nada.
        return;
    }

    int meio = inicio + (fim - inicio) / 2; // Para evitar overflow, embora para inteiros pequenos como este não seja problema. 
    
    // Ordena a primeira e a segunda metade
    mergeSort(v, inicio, meio);
    mergeSort(v, meio + 1, fim);
    merge(v, inicio, meio, fim); // Mescla as duas metades ordenadas
}

int gera_arquivo_numeros(int tam){
	
	int i;
	arq = fopen(filename, "wt+"); // 'wt+' permite escrita e leitura. 

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
		return 0; // O fclose é tecnicamente inalcançável aqui devido ao 'return 0'
	}
}

void le_arquivo(int TAM){ // faz a abertura do arquivo e leitura de uma quantidade de números

	int i;
	arq = fopen(filename, "rt");
	
	if (arq == NULL)
		return; // falha na abertura do arquivo 
	else{ // arquivo aberto com sucesso
		for (i=0; i < TAM; i++){ // Usando TAM (tamanho) para consistência
				// Lendo os valores separados por vírgula
				fscanf(arq, "%d,", &vet[i]); // Adicionando a vírgula para tentar ignorá-la
		}
	}
	fclose (arq);
}

int main(){
	
	int i;
	int r;
	int tam_ordenar = 5000; // ordenação de n números contidos no arquivo
		
	gera_arquivo_numeros(5000);
		
	double time_spent = 0.0; // para armazenar o tempo de execução do código
	
	clock_t begin = clock(); // tempo inicial

	for (r = 0; r < 1000; r++){ // Loop de 1000 repetições para medir o tempo de forma mais precisa	
		mergeSort(vet, 0, tam_ordenar - 1); // MergeSort é chamado com o intervalo [0, tam_ordenar - 1]  
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
