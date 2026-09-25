#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEADS 50

typedef struct {
    int id;
    char nome[50];
    int origem;
    int temperatura;
} Lead;

void cadastrarLead() {
    Lead novoLead;
    FILE *arquivo;
    printf("\n--- CADASTRAR LEAD ---\n");
    arquivo = fopen("dados_leads.txt", "a");
    if (arquivo == NULL) { 
        printf("[ ERRO ] Nao foi possivel criar ou abrir o ficheiro!\n"); 
        return; 
    }
    printf("ID: "); scanf("%d", &novoLead.id);
    printf("Nome: "); scanf(" %[^\n]s", novoLead.nome);
    printf("Origem (1/2/3): "); scanf("%d", &novoLead.origem);
    printf("Temp (1/2/3): "); scanf("%d", &novoLead.temperatura);
    
    fprintf(arquivo, "%d;%s;%d;%d\n", novoLead.id, novoLead.nome, novoLead.origem, novoLead.temperatura);
    fclose(arquivo);
    printf("\n[ SUCESSO ] Lead guardado no ficheiro!\n");
}

void listarLeads() {
    Lead leadAtual;
    FILE *arquivo;
    printf("\n--- LISTA DE LEADS ---\n");
    arquivo = fopen("dados_leads.txt", "r");
    if (arquivo == NULL) { 
        printf("[ AVISO ] O ficheiro esta vazio.\n"); 
        return; 
    }
    while (fscanf(arquivo, "%d;%[^;];%d;%d\n", &leadAtual.id, leadAtual.nome, &leadAtual.origem, &leadAtual.temperatura) != EOF) {
        printf("ID: %d | Nome: %s | Orig: %d | Temp: %d\n", leadAtual.id, leadAtual.nome, leadAtual.origem, leadAtual.temperatura);
    }
    fclose(arquivo);
}

void buscarLead() {
    Lead leadAtual;
    FILE *arquivo;
    char termoBusca[50];
    int encontrou = 0;
    
    printf("\n--- BUSCAR LEAD ---\n");
    printf("Digite o nome exato para buscar: ");
    scanf(" %[^\n]s", termoBusca);
    
    arquivo = fopen("dados_leads.txt", "r");
    if (arquivo == NULL) { 
        printf("[ ERRO ] Base de dados indisponivel.\n"); 
        return; 
    }
    
    while (fscanf(arquivo, "%d;%[^;];%d;%d\n", &leadAtual.id, leadAtual.nome, &leadAtual.origem, &leadAtual.temperatura) != EOF) {
        if (strcmp(leadAtual.nome, termoBusca) == 0) {
            printf("\n[ ENCONTRADO ] ID: %d | Nome: %s\n", leadAtual.id, leadAtual.nome);
            encontrou = 1; 
            break; 
        }
    }
    
    if (encontrou == 0) {
        printf("\n[ AVISO ] A busca nao retornou resultados. Lead nao encontrado.\n");
    }
    
    fclose(arquivo);
}

int main() {
    int opcao = 0;
    do {
        printf("\n========================================\n");
        printf("       GERADOR DE LEADS (CRM)             \n");
        printf("========================================\n");
        printf("1. Cadastrar novo Lead\n");
        printf("2. Listar Leads (Ler do Ficheiro)\n");
        printf("3. Buscar Lead por Nome\n");
        printf("4. Sair do Sistema\n");
        printf("========================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1: cadastrarLead(); break;
            case 2: listarLeads(); break;
            case 3: buscarLead(); break;
            case 4: printf("\nEncerrando...\n"); break;
            default: printf("\n[ ERRO ] Opcao invalida.\n");
        }
    } while (opcao != 4);
    return 0;
}
