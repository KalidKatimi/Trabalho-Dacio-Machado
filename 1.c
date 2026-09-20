#include <stdio.h>
#include <stdlib.h>

int main() {
    int opcao = 0;
    
    // O esqueleto do sistema - Mantém o software rodando até o usuário pedir para sair
    do {
        printf("\n========================================\n");
        printf("       GERADOR E GESTOR DE LEADS        \n");
        printf("========================================\n");
        printf("1. Cadastrar novo Lead\n");
        printf("2. Listar todos os Leads\n");
        printf("3. Relatorio de Temperatura\n");
        printf("4. Sair do Sistema\n");
        printf("========================================\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                printf("\n[ LOG ] Modulo de cadastro sera implementado no Commit 03.\n");
                break;
            case 2:
                printf("\n[ LOG ] Listagem da base sera implementada no Commit 04.\n");
                break;
            case 3:
                printf("\n[ LOG ] Relatorio de dados sera implementado no Commit 05.\n");
                break;
            case 4:
                printf("\nEncerrando o sistema base... Ate logo!\n");
                break;
            default:
                printf("\n[ ERRO ] Opcao invalida. Digite de 1 a 4.\n");
        }
        
    } while (opcao != 4);

    return 0;
}
