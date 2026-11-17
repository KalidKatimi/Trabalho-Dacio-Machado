#include <stdio.h>
#include <stdlib.h>
#include "leads.h"

int main(void) {
    int opcao;

    do {
        system("cls");
        printf("\n========================================\n");
        printf("       GERADOR DE LEADS (CRM)\n");
        printf("========================================\n");
        printf("1. Cadastrar novo Lead\n");
        printf("2. Listar Leads\n");
        printf("3. Buscar Lead por Nome\n");
        printf("4. Sair do Sistema\n");
        printf("========================================\n");

        opcao = lerNumero("Escolha uma opcao: ", 1, 4);

        switch (opcao) {
            case 1: cadastrarLead(); break;
            case 2: listarLeads(); break;
            case 3: buscarLead(); break;
            case 4: printf("\nEncerrando o programa... Ate logo!\n"); break;
        }
    } while (opcao != 0 && opcao != 4);

    return 0;
}
