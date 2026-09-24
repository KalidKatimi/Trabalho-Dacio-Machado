// leads.h
typedef struct {
    int id;
    char nome[50];
    int origem;
    int temperatura;
} Lead;

void cadastrarLead();
void listarLeads();
void buscarLead();

C
// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leads.h"

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

void listarLeads() {}
void buscarLead() {}
    return 0;
}
