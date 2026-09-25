// leads.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leads.h"

void cadastrarLead() {
    Lead novoLead;
    FILE *arquivo;
    
    system("cls");
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
    printf("\nPressione Enter para voltar ao menu...");
    scanf(" %[^\n]");
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
        scanf(" %[^\n]");
        return; 
    }
    while (fscanf(arquivo, "%d;%[^;];%d;%d\n", &leadAtual.id, leadAtual.nome, &leadAtual.origem, &leadAtual.temperatura) != EOF) {
        printf("ID: %d | Nome: %s | Orig: %d | Temp: %d\n", leadAtual.id, leadAtual.nome, leadAtual.origem, leadAtual.temperatura);
    }
    fclose(arquivo);
    
    printf("\nPressione Enter para voltar ao menu...");
    scanf(" %[^\n]");
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
        scanf(" %[^\n]");
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
    printf("\nPressione Enter para voltar ao menu...");
    scanf(" %[^\n]");
}
