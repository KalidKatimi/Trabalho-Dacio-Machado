#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "leads.h"

#define ARQUIVO "dados_leads.txt"

/* Limpa caracteres que sobraram de uma entrada muito longa. */
void limparEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* Le um numero e pede novamente se a entrada estiver errada. */
int lerNumero(const char *mensagem, int minimo, int maximo) {
    char texto[100], sobra;
    int numero;

    while (1) {
        printf("%s", mensagem);
        if (fgets(texto, sizeof(texto), stdin) == NULL) return 0;

        if (strchr(texto, '\n') == NULL) {
            limparEntrada();
        } else if (sscanf(texto, " %d %c", &numero, &sobra) == 1 &&
                   numero >= minimo && numero <= maximo) {
            return numero;
        }
        printf("[ ERRO ] Digite um numero entre %d e %d.\n", minimo, maximo);
    }
}

/* Le o nome completo, incluindo espacos. */
int lerNome(const char *mensagem, char nome[]) {
    char texto[100];
    int tamanho, i, temLetra;

    while (1) {
        printf("%s", mensagem);
        if (fgets(texto, sizeof(texto), stdin) == NULL) return 0;

        if (strchr(texto, '\n') == NULL) {
            limparEntrada();
        } else {
            texto[strcspn(texto, "\n")] = '\0';
            tamanho = strlen(texto);
            temLetra = 0;
            for (i = 0; i < tamanho; i++) {
                if (texto[i] != ' ' && texto[i] != '\t') temLetra = 1;
            }
            if (temLetra && tamanho < TAM_NOME && strchr(texto, ';') == NULL) {
                strcpy(nome, texto);
                return 1;
            }
        }
        printf("[ ERRO ] Digite um nome de ate 49 letras, sem ';'.\n");
    }
}

void pausar(void) {
    char texto[100];
    printf("\nPressione Enter para voltar ao menu...");
    fgets(texto, sizeof(texto), stdin);
}

/* Copia os leads do arquivo para o vetor. */
int carregarLeads(Lead lista[], int *invalidos) {
    FILE *arquivo = fopen(ARQUIVO, "a+");
    Lead lead;
    char linha[150], sobra;
    int total = 0;

    *invalidos = 0;
    if (arquivo == NULL) {
        printf("[ ERRO ] Nao foi possivel abrir o arquivo.\n");
        return -1;
    }

    rewind(arquivo);
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (sscanf(linha, "%d;%49[^;];%d;%d %c", &lead.id, lead.nome,
                   &lead.origem, &lead.temperatura, &sobra) == 4 &&
            lead.id > 0 && lead.origem >= 1 && lead.origem <= 3 &&
            lead.temperatura >= 1 && lead.temperatura <= 3 &&
            total < MAX_LEADS) {
            lista[total] = lead;
            total++;
        } else {
            (*invalidos)++;
        }
    }

    if (ferror(arquivo)) {
        printf("[ ERRO ] Falha ao ler o arquivo.\n");
        fclose(arquivo);
        return -1;
    }
    if (fclose(arquivo) != 0) {
        printf("[ ERRO ] Falha ao fechar o arquivo.\n");
        return -1;
    }
    return total;
}

void mostrarLead(Lead lead) {
    const char *origens[] = {"", "Instagram", "WhatsApp", "Indicacao"};
    const char *temperaturas[] = {"", "Frio", "Morno", "Quente"};

    printf("ID: %d | Nome: %s | Origem: %s | Temperatura: %s\n",
           lead.id, lead.nome, origens[lead.origem], temperaturas[lead.temperatura]);
}

void cadastrarLead(void) {
    Lead lista[MAX_LEADS], novo;
    FILE *arquivo;
    int total, invalidos, i, salvou = 1;

    system("cls");
    printf("\n--- CADASTRAR LEAD ---\n");
    novo.id = lerNumero("ID: ", 1, 2147483647);
    if (novo.id == 0 || !lerNome("Nome: ", novo.nome)) return;

    printf("\nORIGEM:\n1 - Instagram\n2 - WhatsApp\n3 - Indicacao\n");
    novo.origem = lerNumero("Escolha a origem: ", 1, 3);
    printf("\nTEMPERATURA:\n1 - Frio\n2 - Morno\n3 - Quente\n");
    novo.temperatura = lerNumero("Escolha a temperatura: ", 1, 3);
    if (novo.origem == 0 || novo.temperatura == 0) return;

    total = carregarLeads(lista, &invalidos);
    if (total == -1) { pausar(); return; }
    if (invalidos > 0) {
        printf("[ ERRO ] O arquivo contem registros invalidos.\n");
        pausar();
        return;
    }
    if (total >= MAX_LEADS) {
        printf("[ ERRO ] Limite de 50 leads atingido.\n");
        pausar();
        return;
    }
    for (i = 0; i < total; i++) {
        if (lista[i].id == novo.id) {
            printf("[ ERRO ] Ja existe um lead com esse ID.\n");
            pausar();
            return;
        }
    }

    /* Reescreve o arquivo com os registros existentes e o novo cadastro. */
    lista[total] = novo;
    arquivo = fopen(ARQUIVO, "w");
    if (arquivo == NULL) {
        printf("[ ERRO ] Nao foi possivel salvar o arquivo.\n");
        pausar();
        return;
    }
    for (i = 0; i <= total; i++) {
        if (fprintf(arquivo, "%d;%s;%d;%d\n", lista[i].id, lista[i].nome,
                    lista[i].origem, lista[i].temperatura) < 0) {
            salvou = 0;
        }
    }
    if (fclose(arquivo) != 0) salvou = 0;

    if (salvou) printf("\n[ SUCESSO ] Lead cadastrado!\n");
    else printf("[ ERRO ] Nao foi possivel salvar todos os dados.\n");
    pausar();
}

void listarLeads(void) {
    Lead lista[MAX_LEADS];
    int total, invalidos, i;

    system("cls");
    printf("\n--- LISTA DE LEADS ---\n");
    total = carregarLeads(lista, &invalidos);
    if (total >= 0) {
        if (total == 0) printf("[ AVISO ] Nenhum lead cadastrado.\n");
        for (i = 0; i < total; i++) mostrarLead(lista[i]);
        if (invalidos) printf("[ AVISO ] %d registro(s) invalido(s).\n", invalidos);
    }
    pausar();
}

void buscarLead(void) {
    Lead lista[MAX_LEADS];
    char nome[TAM_NOME];
    int total, invalidos, i, encontrou = 0;

    system("cls");
    printf("\n--- BUSCAR LEAD ---\n");
    if (!lerNome("Digite o nome exato para buscar: ", nome)) return;

    total = carregarLeads(lista, &invalidos);
    if (total >= 0) {
        for (i = 0; i < total; i++) {
            if (strcmp(lista[i].nome, nome) == 0) {
                mostrarLead(lista[i]);
                encontrou = 1;
            }
        }
        if (!encontrou) printf("[ AVISO ] Lead nao encontrado.\n");
        if (invalidos) printf("[ AVISO ] %d registro(s) invalido(s).\n", invalidos);
    }
    pausar();
}
