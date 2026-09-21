#include <stdio.h>
#include <stdlib.h>

#define MAX_LEADS 50

int main() {
    char nomes[MAX_LEADS][50];
    int origens[MAX_LEADS];

    int totalLeads = 0;
    int opcao = 0;

    do {
        printf("\n========================================\n");
        printf("       GERADOR E GESTOR DE LEADS        \n");
        printf("========================================\n");
        printf("Leads na base: %d / %d\n\n", totalLeads, MAX_LEADS);
        printf("1. Cadastrar novo Lead\n");
        printf("2. Listar todos os Leads\n");
        printf("3. Relatorio de Dados\n");
        printf("4. Buscar Lead por Nome\n");
        printf("5. Excluir um Lead\n");
        printf("6. Sair do Sistema\n");
        printf("========================================\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                if(totalLeads < MAX_LEADS) {
                    printf("\n--- CADASTRAR LEAD ---\n");
                    printf("Digite o nome do lead: ");

                    setbuf(stdin, NULL);
                    fgets(nomes[totalLeads], 50, stdin);

                    int j = 0;
                    while (nomes[totalLeads][j] != '\0') {
                        if (nomes[totalLeads][j] == '\n') {
                            nomes[totalLeads][j] = '\0';
                            break;
                        }
                        j++;
                    }

                    printf("Qual a origem? (1-Discord / 2-Automacao / 3-Outro): ");
                    scanf("%d", &origens[totalLeads]);

                    totalLeads++;
                    printf("\n[ SUCESSO ] Lead cadastrado com sucesso!\n");
                } else {
                    printf("\n[ ERRO ] Memoria cheia! Limite de %d atingido.\n", MAX_LEADS);
                }
                break;

            case 2:
                printf("\n--- LISTA DE LEADS CADASTRADOS ---\n");
                if(totalLeads == 0) {
                    printf("Nenhum lead na base ainda.\n");
                } else {
                    for(int i = 0; i < totalLeads; i++) {
                        printf("ID: %d | Nome: %s | Origem: ", i + 1, nomes[i]);
                        if(origens[i] == 1) printf("Discord\n");
                        else if(origens[i] == 2) printf("Automacao\n");
                        else printf("Outro\n");
                    }
                }
                break;

            case 3:
                printf("\n--- RELATORIO DE ORIGENS ---\n");
                if(totalLeads == 0) {
                    printf("Cadastre leads para gerar o relatorio.\n");
                } else {
                    int qtdDiscord = 0, qtdAutomacao = 0, qtdOutros = 0;

                    for(int i = 0; i < totalLeads; i++) {
                        if(origens[i] == 1) qtdDiscord++;
                        else if(origens[i] == 2) qtdAutomacao++;
                        else qtdOutros++;
                    }

                    printf("Total processado: %d leads\n", totalLeads);
                    printf("- Via Discord: %d\n", qtdDiscord);
                    printf("- Via Automacao n8n: %d\n", qtdAutomacao);
                    printf("- Outras origens: %d\n", qtdOutros);
                }
                break;

            case 4:
                printf("\n--- BUSCA DE LEAD ---\n");
                if(totalLeads == 0) {
                    printf("A base de leads esta vazia.\n");
                } else {
                    char termoBusca[50];
                    printf("Digite o nome exato para buscar: ");

                    setbuf(stdin, NULL);
                    fgets(termoBusca, 50, stdin);

                    int k = 0;
                    while (termoBusca[k] != '\0') {
                        if (termoBusca[k] == '\n') {
                            termoBusca[k] = '\0';
                            break;
                        }
                        k++;
                    }

                    int encontrou = 0;

                    for(int i = 0; i < totalLeads; i++) {
                        int iguais = 1;
                        int c = 0;

                        while(nomes[i][c] != '\0' || termoBusca[c] != '\0') {
                            if(nomes[i][c] != termoBusca[c]) {
                                iguais = 0;
                                break;
                            }
                            c++;
                        }

                        if(iguais == 1) {
                            printf("\n[ LEAD ENCONTRADO ]\n");
                            printf("Nome: %s | Origem: ", nomes[i]);
                            if(origens[i] == 1) printf("Discord\n");
                            else if(origens[i] == 2) printf("Automacao\n");
                            else printf("Outro\n");

                            encontrou = 1;
                            break;
                        }
                    }

                    if(encontrou == 0) {
                        printf("\n[ AVISO ] Lead nao encontrado na base.\n");
                    }
                }
                break;

            case 5:
                printf("\n--- EXCLUIR LEAD ---\n");
                if(totalLeads == 0) {
                    printf("A base ja esta vazia.\n");
                } else {
                    int idExcluir;
                    printf("Digite o ID do Lead que deseja excluir (1 a %d): ", totalLeads);
                    scanf("%d", &idExcluir);

                    if(idExcluir < 1 || idExcluir > totalLeads) {
                        printf("\n[ ERRO ] ID invalido!\n");
                    } else {
                        int indice = idExcluir - 1;

                        for(int i = indice; i < totalLeads - 1; i++) {
                            origens[i] = origens[i + 1];

                            int c = 0;
                            while(nomes[i + 1][c] != '\0') {
                                nomes[i][c] = nomes[i + 1][c];
                                c++;
                            }
                            nomes[i][c] = '\0';
                        }

                        totalLeads--;
                        printf("\n[ SUCESSO ] Lead excluido e base reordenada!\n");
                    }
                }
                break;

            case 6:
                printf("\nEncerrando o sistema... Ate logo!\n");
                break;

            default:
                printf("\n[ ERRO ] Opcao invalida. Digite de 1 a 6.\n");
        }

    } while (opcao != 6);

    return 0;
}
