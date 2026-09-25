#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEADS 50

// Estrutura heterogênea para os dados do Lead
typedef struct {
    int id;
    char nome[50];
    int origem;
    int temperatura;
} Lead;

void cadastrarLead() {
    Lead novoLead;
    FILE *arquivo;
    
    system("cls");
    printf("\n--- CADASTRAR LEAD ---\n");
    
    // Abre o ficheiro em modo de adição ("a") para preservar os dados antigos
    arquivo = fopen("dados_leads.txt", "a");
    if (arquivo == NULL) { 
        printf("[ ERRO ] Nao foi possivel criar ou abrir o ficheiro!\n"); 
        return; 
    }
    
    printf("ID: "); scanf("%d", &novoLead.id);
    printf("Nome: "); scanf(" %[^\n]s", novoLead.nome);
    printf("Origem (1/2/3): "); scanf("%d", &novoLead.origem);
    printf("Temp (1/2/3): "); scanf("%d", &novoLead.temperatura);
    
    // Grava no ficheiro separado por ponto e vírgula
    fprintf(arquivo, "%d;%s;%d;%d\n", novoLead.id, novoLead.nome, novoLead.origem, novoLead.temperatura);
    fclose(arquivo);
    
    printf("\n[ SUCESSO ] Lead guardado no ficheiro!\n");
    printf("\nPressione Enter para voltar ao menu...");
    getchar();
    getchar();
}

void listarLeads() {
    Lead leadAtual;
    FILE *arquivo;
    
    system("cls");
    printf("\n--- LISTA DE LEADS ---\n");
    
    arquivo = fopen("dados_leads.txt", "r");
    if (arquivo == NULL) { 
        printf("[ AVISO ] O ficheiro esta vazio.\n"); 
        printf("\nPressione Enter para voltar ao menu...");
        getchar();
        getchar();
        return; 
    }
    
    // Lê linha a linha até ao final do ficheiro (EOF)
    while (fscanf(arquivo, "%d;%[^;];%d;%d\n", &leadAtual.id, leadAtual.nome, &leadAtual.origem, &leadAtual.temperatura) != EOF) {
        printf("ID: %d | Nome: %s | Orig: %d | Temp: %d\n", leadAtual.id, leadAtual.nome, leadAtual.origem, leadAtual.temperatura);
    }
    fclose(arquivo);
    
    printf("\nPressione Enter para voltar ao menu...");
    getchar();
    getchar();
}

void buscarLead() {
    Lead leadAtual;
    FILE *arquivo;
    char termoBusca[50];
    int encontrou = 0;
    
    system("cls");
    printf("\n--- BUSCAR LEAD ---\n");
    printf("Digite o nome exato para buscar: ");
    scanf(" %[^\n]s", termoBusca);
    
    arquivo = fopen("dados_leads.txt", "r");
    if (arquivo == NULL) { 
        printf("[ ERRO ] Base de dados indisponivel.\n"); 
        printf("\nPressione Enter para voltar ao menu...");
        getchar();
        getchar();
        return; 
    }
    
    // Compara o nome de cada registo com o termo de busca
    while (fscanf(arquivo, "%d;%[^;];%d;%d\n", &leadAtual.id, leadAtual.nome, &leadAtual.origem, &leadAtual.temperatura) != EOF) {
        if (strcmp(leadAtual.nome, termoBusca) == 0) {
            printf("\n[ ENCONTRADO ] ID: %d | Nome: %s\n", leadAtual.id, leadAtual.nome);
            encontrou = 1; 
            break; 
        }
    }
    
    // Aviso obrigatório caso a busca não retorne resultados
    if (encontrou == 0) {
        printf("\n[ AVISO ] A busca nao retornou resultados. Lead nao encontrado.\n");
    }
    
    fclose(arquivo);
    printf("\nPressione Enter para voltar ao menu...");
    getchar();
    getchar();
}

int main() {
    int opcao = 0;
    
    // Ciclo principal do menu interativo
    do {
        system("cls");
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
            case 4: 
                system("cls");
                printf("\nEncerrando o programa... Até logo!\n"); 
                break;
            default: 
                printf("\n[ ERRO ] Opcao invalida.\n");
                printf("Pressione Enter para continuar...");
                getchar();
                getchar();
        }
    } while (opcao != 4);
    
    return 0;
}
