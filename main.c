#include <stdio.h>
#include <stdlib.h>
#include "leads.h"

int main(void) {
    int opcao;

    for (;;) {
        system("cls");
        printf("\n========================================\n");
        printf("       GERADOR DE LEADS (CRM)\n");
        printf("========================================\n");
        printf("1. Cadastrar novo Lead\n");
        printf("2. Listar Leads (Ler do Ficheiro)\n");
        printf("3. Buscar Lead por Nome\n");
        printf("4. Sair do Sistema\n");
        printf("========================================\n");

        if (!lerInteiro("Escolha uma opcao: ", 1, 4, &opcao)) {
            printf("\nEntrada encerrada. Ate logo!\n");
            return 0;
        }
        switch (opcao) {
            case 1: cadastrarLead(); break;
            case 2: listarLeads(); break;
            case 3: buscarLead(); break;
            case 4:
                system("cls");
                printf("\nEncerrando o programa... Ate logo!\n");
                return 0;
        }
    }
}

