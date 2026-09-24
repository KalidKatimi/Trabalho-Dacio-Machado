// leads.h
#define MAX_LEADS 50

void cadastrarLead();
void listarLeads();
void buscarLead();
Ficheiro 2: Cria o main.c e cola isto:

C
// main.c
#include <stdio.h>
#include <stdlib.h>
#include "leads.h" 

int main() {
    int opcao = 0;
    
    do {
        printf("\n========================================\n");
        printf("       SISTEMA CRM (ARQUIVOS MULTIPLOS)   \n");
        printf("========================================\n");
        printf("1. Cadastrar novo Lead\n");
        printf("2. Listar Leads (Ler do Arquivo)\n");
        printf("3. Buscar Lead por Nome\n");
        printf("4. Sair do Sistema\n");
        printf("========================================\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                cadastrarLead();
                break;
            case 2:
                listarLeads();
                break;
            case 3:
                buscarLead();
                break;
            case 4:
                printf("\nEncerrando o programa e fechando conexoes... Ate logo!\n");
                break;
            default:
                printf("\n[ ERRO ] Opcao invalida.\n");
        }
        
    } while (opcao != 4);

    return 0;
}
