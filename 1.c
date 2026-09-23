#include <stdio.h>
#include <stdlib.h>

#define MAX_LEADS 50 

int main() {
    char nomes[MAX_LEADS][50]; 
    int origens[MAX_LEADS]; 
    int temperaturas[MAX_LEADS]; 
    
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
        printf("6. Editar Status do Lead\n"); 
        printf("7. Filtrar Leads por Temperatura\n"); // NOVA OPÇÃO
        printf("8. Sair do Sistema\n"); // SAIR MUDOU PARA 8
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
                    
                    printf("Qual a temperatura? (1-Frio / 2-Morno / 3-Quente): ");
                    scanf("%d", &temperaturas[totalLeads]);
                    
                    if(temperaturas[totalLeads] < 1 || temperaturas[totalLeads] > 3) {
                        printf("[ AVISO ] Temperatura invalida. Cadastrado como Frio (1).\n");
                        temperaturas[totalLeads] = 1;
                    }
                    
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
                        
                        if(origens[i] == 1) printf("Discord");
                        else if(origens[i] == 2) printf("Automacao");
                        else printf("Outro");
                        
                        if(temperaturas[i] == 1) printf(" | Temp: Frio\n");
                        else if(temperaturas[i] == 2) printf(" | Temp: Morno\n");
                        else if(temperaturas[i] == 3) printf(" | Temp: Quente\n");
                        else printf(" | Temp: Indefinido\n");
                    }
                }
                break;
                
            case 3:
                printf("\n--- RELATORIO DE DADOS ---\n");
                if(totalLeads == 0) {
                    printf("Cadastre leads para gerar o relatorio.\n");
                } else {
                    int qtdDiscord = 0, qtdAutomacao = 0, qtdOutros = 0;
                    int quentes = 0, mornos = 0, frios = 0;
                    
                    for(int i = 0; i < totalLeads; i++) {
                        if(origens[i] == 1) qtdDiscord++;
                        else if(origens[i] == 2) qtdAutomacao++;
                        else qtdOutros++;
                        
                        if(temperaturas[i] == 1) frios++;
                        else if(temperaturas[i] == 2) mornos++;
                        else if(temperaturas[i] == 3) quentes++;
                    }
                    
                    printf("Total processado: %d leads\n", totalLeads);
                    printf("\n[ POR ORIGEM ]\n");
                    printf("- Via Discord: %d\n", qtdDiscord);
                    printf("- Via Automacao n8n: %d\n", qtdAutomacao);
                    printf("- Outras origens: %d\n", qtdOutros);
                    
                    printf("\n[ POR TEMPERATURA ]\n");
                    printf("- Leads Quentes: %d\n", quentes);
                    printf("- Leads Mornos: %d\n", mornos);
                    printf("- Leads Frios: %d\n", frios);
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
                            printf("Nome: %s\n", nomes[i]);
                            
                            printf("Origem: ");
                            if(origens[i] == 1) printf("Discord\n");
                            else if(origens[i] == 2) printf("Automacao\n");
                            else printf("Outro\n");
                            
                            printf("Temperatura: ");
                            if(temperaturas[i] == 1) printf("Frio\n");
                            else if(temperaturas[i] == 2) printf("Morno\n");
                            else if(temperaturas[i] == 3) printf("Quente\n");
                            
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
                            temperaturas[i] = temperaturas[i + 1]; 
                            
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
                printf("\n--- EDITAR STATUS DO LEAD ---\n");
                if(totalLeads == 0) {
                    printf("Nenhum lead para editar.\n");
                } else {
                    int idEditar;
                    printf("Digite o ID do Lead que deseja editar (1 a %d): ", totalLeads);
                    scanf("%d", &idEditar);
                    
                    if(idEditar >= 1 && idEditar <= totalLeads) {
                        int indice = idEditar - 1;
                        
                        printf("Editando Lead: %s\n", nomes[indice]);
                        printf("Nova origem (1-Discord / 2-Automacao / 3-Outro): ");
                        scanf("%d", &origens[indice]);
                        
                        printf("Nova temperatura (1-Frio / 2-Morno / 3-Quente): ");
                        scanf("%d", &temperaturas[indice]);
                        
                        printf("\n[ SUCESSO ] Dados do lead atualizados!\n");
                    } else {
                        printf("\n[ ERRO ] ID invalido!\n");
                    }
                }
                break;
                
            case 7:
                
                printf("\n--- FILTRAR LEADS POR TEMPERATURA ---\n");
                if(totalLeads == 0) {
                    printf("Nenhum lead cadastrado para filtrar.\n");
                } else {
                    int filtro;
                    printf("Deseja ver leads de qual temperatura? (1-Frio / 2-Morno / 3-Quente): ");
                    scanf("%d", &filtro);
                    
                    if (filtro < 1 || filtro > 3) {
                        printf("\n[ ERRO ] Opcao invalida!\n");
                    } else {
                        int encontrouFiltro = 0; // Controlador pra saber se achamos algum
                        
                        for(int i = 0; i < totalLeads; i++) {
                            // Se a temperatura do lead for igual à que o usuário digitou, imprime na tela
                            if(temperaturas[i] == filtro) {
                                printf("ID: %d | Nome: %s | Origem: ", i + 1, nomes[i]);
                                if(origens[i] == 1) printf("Discord\n");
                                else if(origens[i] == 2) printf("Automacao\n");
                                else printf("Outro\n");
                                
                                encontrouFiltro = 1;
                            }
                        }
                        
                        if(encontrouFiltro == 0) {
                            printf("\n[ AVISO ] Nenhum lead encontrado com essa temperatura.\n");
                        }
                    }
                }
                break;
                
            case 8:
                printf("\nEncerrando o sistema... Ate logo!\n");
                break;
                
            default:
                printf("\n[ ERRO ] Opcao invalida. Digite de 1 a 8.\n");
        }
        
    } while (opcao != 8);

    return 0;
}
