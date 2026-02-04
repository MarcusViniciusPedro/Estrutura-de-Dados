#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do Contato
typedef struct {
    char nome[50];
    char email[50];
    char telefone[20]; // Ex: (XX) XXXX-XXXX
    char aniversario[11]; // Formato: DD/MM/AAAA
} Contato;

// Nome do arquivo onde os dados serão armazenados
#define ARQUIVO_DADOS "DATA.BIN"

// Protótipos das funções
void exibir_menu();
void cadastrar_contato();
void alterar_contato();
void excluir_contato();
void exibir_contato_especifico();
void exibir_todos_contatos();

int main() {
    int opcao;

    printf("--- Agenda de Contatos (Armazenamento em Arquivo) ---\n");

    do {
        exibir_menu();
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            // Limpa o buffer de entrada em caso de erro de leitura
            while (getchar() != '\n');
            opcao = 0; // Força repetição ou opção inválida
        }
        while (getchar() != '\n'); // Limpa o buffer após a leitura de int

        switch (opcao) {
            case 1:
                cadastrar_contato();
                break;
            case 2:
                alterar_contato();
                break;
            case 3:
                excluir_contato();
                break;
            case 4:
                exibir_contato_especifico();
                break;
            case 5:
                exibir_todos_contatos();
                break;
            case 6:
                printf("\nSaindo da aplicação. Até mais!\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}

// Implementação das funções

void exibir_menu() {
    printf("\n=============================\n");
    printf("MENU DA AGENDA\n");
    printf("=============================\n");
    printf("1 - Cadastrar novo contato\n");
    printf("2 - Alterar dados de um contato\n");
    printf("3 - Excluir os dados de um contato\n");
    printf("4 - Exibir os dados de um contato específico\n");
    printf("5 - Exibir os dados de todos os contatos\n");
    printf("6 - Sair da aplicação\n");
    printf("-----------------------------\n");
}

/* * Função Auxiliar: Encontra um contato pelo nome e retorna sua posição no arquivo.
 * Retorna -1 se não encontrar.
 */
long buscar_posicao_contato(const char *nome_busca) {
    FILE *fp = fopen(ARQUIVO_DADOS, "rb");
    if (fp == NULL) {
        return -1; // Arquivo não existe ou não pode ser aberto
    }

    Contato c;
    long posicao = 0;
    long encontrado = -1;

    while (fread(&c, sizeof(Contato), 1, fp)) {
        if (strcmp(c.nome, nome_busca) == 0) {
            encontrado = posicao;
            break;
        }
        posicao++;
    }

    fclose(fp);
    return encontrado;
}


void cadastrar_contato() {
    FILE *fp = fopen(ARQUIVO_DADOS, "ab"); // "ab" para adicionar ao final (append binary)
    if (fp == NULL) {
        perror("Erro ao abrir/criar o arquivo");
        return;
    }

    Contato novo;
    printf("\n--- CADASTRO DE NOVO CONTATO ---\n");

    printf("Nome: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    // Remove o '\n' lido pelo fgets, se existir
    novo.nome[strcspn(novo.nome, "\n")] = 0;

    printf("E-mail: ");
    fgets(novo.email, sizeof(novo.email), stdin);
    novo.email[strcspn(novo.email, "\n")] = 0;

    printf("Telefone (ex: (XX) XXXX-XXXX): ");
    fgets(novo.telefone, sizeof(novo.telefone), stdin);
    novo.telefone[strcspn(novo.telefone, "\n")] = 0;

    printf("Data de Aniversário (DD/MM/AAAA): ");
    fgets(novo.aniversario, sizeof(novo.aniversario), stdin);
    novo.aniversario[strcspn(novo.aniversario, "\n")] = 0;

    // Grava a estrutura no arquivo
    fwrite(&novo, sizeof(Contato), 1, fp);

    fclose(fp);
    printf("\nContato '%s' cadastrado com sucesso!\n", novo.nome);
}

void alterar_contato() {
    char nome_busca[50];
    printf("\n--- ALTERAR CONTATO ---\n");
    printf("Digite o NOME do contato que deseja alterar: ");
    fgets(nome_busca, sizeof(nome_busca), stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;

    long posicao = buscar_posicao_contato(nome_busca);

    if (posicao == -1) {
        printf("Erro: Contato '%s' não encontrado.\n", nome_busca);
        return;
    }

    FILE *fp = fopen(ARQUIVO_DADOS, "r+b"); // "r+b" para leitura e escrita binária
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    // Move o ponteiro para a posição do registro encontrado
    fseek(fp, posicao * sizeof(Contato), SEEK_SET);

    Contato c_antigo;
    fread(&c_antigo, sizeof(Contato), 1, fp); // Lê o contato antigo

    printf("\nDados Atuais de %s:\n", c_antigo.nome);
    printf("  Email: %s\n", c_antigo.email);
    printf("  Telefone: %s\n", c_antigo.telefone);
    printf("  Aniversário: %s\n", c_antigo.aniversario);

    // ----------------------------------------------------
    // Lendo Novos Dados
    // ----------------------------------------------------
    Contato c_novo = c_antigo; // Copia os dados, mantendo o nome

    printf("\nDigite os NOVOS dados (deixe em branco para manter o atual):\n");

    char temp[50];
    
    printf("Novo E-mail (%s): ", c_antigo.email);
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = 0;
    if (strlen(temp) > 0) {
        strcpy(c_novo.email, temp);
    }

    printf("Novo Telefone (%s): ", c_antigo.telefone);
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = 0;
    if (strlen(temp) > 0) {
        strcpy(c_novo.telefone, temp);
    }

    printf("Nova Data de Aniversário (%s): ", c_antigo.aniversario);
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = 0;
    if (strlen(temp) > 0) {
        strcpy(c_novo.aniversario, temp);
    }

    // Move o ponteiro de volta para o início do registro (necessário para o fwrite)
    fseek(fp, posicao * sizeof(Contato), SEEK_SET);

    // Sobrescreve o registro com os novos dados
    fwrite(&c_novo, sizeof(Contato), 1, fp);

    fclose(fp);
    printf("\nContato '%s' alterado com sucesso!\n", c_novo.nome);
}

void excluir_contato() {
    char nome_busca[50];
    printf("\n--- EXCLUIR CONTATO ---\n");
    printf("Digite o NOME do contato que deseja EXCLUIR: ");
    fgets(nome_busca, sizeof(nome_busca), stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;

    // Buscar a posição do contato para confirmar se existe
    long posicao_excluir = buscar_posicao_contato(nome_busca);

    if (posicao_excluir == -1) {
        printf("Erro: Contato '%s' não encontrado para exclusão.\n", nome_busca);
        return;
    }

    // Em arquivos, a exclusão é feita criando um novo arquivo temporário
    // ou reescrevendo o original, copiando todos, exceto o excluído.

    FILE *fp_original = fopen(ARQUIVO_DADOS, "rb");
    FILE *fp_temp = fopen("temp.bin", "wb");

    if (fp_original == NULL || fp_temp == NULL) {
        perror("Erro ao abrir arquivos para exclusão");
        if (fp_original) fclose(fp_original);
        if (fp_temp) fclose(fp_temp);
        return;
    }

    Contato c;
    long i = 0;
    int excluidos = 0;

    while (fread(&c, sizeof(Contato), 1, fp_original)) {
        if (i != posicao_excluir) {
            // Copia para o arquivo temporário
            fwrite(&c, sizeof(Contato), 1, fp_temp);
        } else {
            excluidos++;
        }
        i++;
    }

    fclose(fp_original);
    fclose(fp_temp);

    // Substitui o arquivo original pelo temporário
    remove(ARQUIVO_DADOS);
    rename("temp.bin", ARQUIVO_DADOS);

    if (excluidos > 0) {
        printf("\nContato '%s' excluído com sucesso!\n", nome_busca);
    } else {
        printf("\nErro ao excluir o contato.\n");
    }
}

void exibir_contato_especifico() {
    char nome_busca[50];
    printf("\n--- EXIBIR CONTATO ESPECÍFICO ---\n");
    printf("Digite o NOME do contato que deseja exibir: ");
    fgets(nome_busca, sizeof(nome_busca), stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;

    FILE *fp = fopen(ARQUIVO_DADOS, "rb");
    if (fp == NULL) {
        printf("Agenda vazia ou erro ao abrir o arquivo.\n");
        return;
    }

    Contato c;
    int encontrado = 0;

    while (fread(&c, sizeof(Contato), 1, fp)) {
        if (strcmp(c.nome, nome_busca) == 0) {
            printf("\n--- DADOS DO CONTATO ---\n");
            printf("Nome: %s\n", c.nome);
            printf("Email: %s\n", c.email);
            printf("Telefone: %s\n", c.telefone);
            printf("Aniversário: %s\n", c.aniversario);
            printf("------------------------\n");
            encontrado = 1;
            break; // Contato encontrado, para a busca
        }
    }

    fclose(fp);

    if (!encontrado) {
        printf("\nContato '%s' não encontrado na agenda.\n", nome_busca);
    }
}

void exibir_todos_contatos() {
    FILE *fp = fopen(ARQUIVO_DADOS, "rb");
    if (fp == NULL) {
        printf("\nAgenda vazia ou erro ao abrir o arquivo.\n");
        return;
    }

    Contato c;
    int contador = 0;

    printf("\n=================================================================\n");
    printf("LISTA COMPLETA DE CONTATOS\n");
    printf("=================================================================\n");

    while (fread(&c, sizeof(Contato), 1, fp)) {
        printf("Contato #%d\n", ++contador);
        printf("  Nome: %s\n", c.nome);
        printf("  Email: %s\n", c.email);
        printf("  Telefone: %s\n", c.telefone);
        printf("  Aniversário: %s\n", c.aniversario);
        printf("-----------------------------------------------------------------\n");
    }

    fclose(fp);

    if (contador == 0) {
        printf("Nenhum contato cadastrado.\n");
        printf("-----------------------------------------------------------------\n");
    }
}
