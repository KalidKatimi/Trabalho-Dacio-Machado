//main.c

#include <stdio.h>
#include <stdlib.h>
#include "leads.h"

int main() {
    int opcao = 0;
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
