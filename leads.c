#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include "leads.h"

#define ARQUIVO_LEADS "dados_leads.txt"
#define TAM_LINHA 256

/* Consome a linha inteira, inclusive quando ela excede o buffer.
   Retorna 1 para sucesso, 0 para fim da entrada e -1 para linha invalida. */
static int lerLinha(FILE *origem, char *texto, size_t capacidade) {
    size_t tamanho = 0;
    int caractere;
    int invalida = 0;
    int recebeu = 0;

    while ((caractere = fgetc(origem)) != EOF && caractere != '\n') {
        recebeu = 1;
        if (caractere == '\0' || tamanho + 1 >= capacidade) {
            invalida = 1;
        } else {
            texto[tamanho++] = (char)caractere;
        }
    }
    texto[tamanho] = '\0';
    if (caractere == EOF && !recebeu) return 0;
    return invalida ? -1 : 1;
}

static void aparar(char *texto) {
    size_t inicio = 0;
    size_t fim = strlen(texto);
    while (inicio < fim && isspace((unsigned char)texto[inicio])) inicio++;
    while (fim > inicio && isspace((unsigned char)texto[fim - 1])) fim--;
    memmove(texto, texto + inicio, fim - inicio);
    texto[fim - inicio] = '\0';
}

static int converterInteiro(const char *texto, int minimo, int maximo, int *valor) {
    char *fim;
    long numero;
    errno = 0;
    numero = strtol(texto, &fim, 10);
    if (texto == fim || errno == ERANGE) return 0;
    while (isspace((unsigned char)*fim)) fim++;
    if (*fim != '\0' || numero < minimo || numero > maximo) return 0;
    *valor = (int)numero;
    return 1;
}

int lerInteiro(const char *mensagem, int minimo, int maximo, int *valor) {
    char linha[TAM_LINHA];
    int resultado;
    for (;;) {
        printf("%s", mensagem);
        fflush(stdout);
        resultado = lerLinha(stdin, linha, sizeof linha);
        if (resultado == 0) return 0;
        if (resultado == 1 && converterInteiro(linha, minimo, maximo, valor)) return 1;
        printf("[ ERRO ] Digite um numero inteiro entre %d e %d.\n", minimo, maximo);
    }
}

static int nomeValido(const char *nome) {
    const unsigned char *p = (const unsigned char *)nome;
    if (*p == '\0' || strlen(nome) >= TAM_NOME) return 0;
    for (; *p; p++) {
        if (*p == ';' || iscntrl(*p)) return 0;
    }
    return 1;
}

static int lerNome(const char *mensagem, char *nome) {
    char linha[TAM_LINHA];
    int resultado;
    for (;;) {
        printf("%s", mensagem);
        fflush(stdout);
        resultado = lerLinha(stdin, linha, sizeof linha);
        if (resultado == 0) return 0;
        aparar(linha);
        if (resultado == 1 && nomeValido(linha)) {
            strcpy(nome, linha);
            return 1;
        }
        printf("[ ERRO ] Nome obrigatorio: reduza o tamanho e nao use ';' ou caracteres de controle.\n");
    }
}

void pausar(void) {
    char linha[TAM_LINHA];
    printf("\nPressione Enter para voltar ao menu...");
    fflush(stdout);
    (void)lerLinha(stdin, linha, sizeof linha);
}

/* O formato continua sendo: id;nome;origem;temperatura. */
static int interpretarLead(char *linha, Lead *lead) {
    char *campos[4];
    char *separador;
    int i;
    campos[0] = linha;
    for (i = 1; i < 4; i++) {
        separador = strchr(campos[i - 1], ';');
        if (separador == NULL) return 0;
        *separador = '\0';
        campos[i] = separador + 1;
    }
    if (strchr(campos[3], ';') != NULL) return 0;
    aparar(campos[1]);
    if (!converterInteiro(campos[0], 1, INT_MAX, &lead->id) ||
        !nomeValido(campos[1]) ||
        !converterInteiro(campos[2], 1, 3, &lead->origem) ||
        !converterInteiro(campos[3], 1, 3, &lead->temperatura)) return 0;
    strcpy(lead->nome, campos[1]);
    return 1;
}

static int proximoLead(FILE *arquivo, Lead *lead, int *linhaNumero, int *invalidos) {
    char linha[TAM_LINHA];
    int resultado;
    while ((resultado = lerLinha(arquivo, linha, sizeof linha)) != 0) {
        (*linhaNumero)++;
        if (resultado == 1 && interpretarLead(linha, lead)) return 1;
        printf("[ AVISO ] Registro invalido na linha %d; ignorado.\n", *linhaNumero);
        (*invalidos)++;
    }
    return 0;
}

static void erroArquivo(const char *acao) {
    printf("[ ERRO ] Nao foi possivel %s '%s': %s.\n", acao, ARQUIVO_LEADS, strerror(errno));
}

void cadastrarLead(void) {
    Lead novoLead;
    Lead atual;
    FILE *arquivo;
    int total = 0, duplicado = 0, linha = 0, invalidos = 0, falhou;
    int precisaQuebra = 0, ultimo;
    long tamanhoArquivo;

    system("cls");
    printf("\n--- CADASTRAR LEAD ---\n");
    if (!lerInteiro("ID: ", 1, INT_MAX, &novoLead.id) ||
        !lerNome("Nome: ", novoLead.nome) ||
        !lerInteiro("Origem (1/2/3): ", 1, 3, &novoLead.origem) ||
        !lerInteiro("Temp (1/2/3): ", 1, 3, &novoLead.temperatura)) {
        printf("\n[ AVISO ] Cadastro cancelado: entrada encerrada.\n");
        return;
    }

    arquivo = fopen(ARQUIVO_LEADS, "rb");
    if (arquivo != NULL) {
        while (proximoLead(arquivo, &atual, &linha, &invalidos)) {
            total++;
            if (atual.id == novoLead.id) duplicado = 1;
        }
        falhou = ferror(arquivo);
        if (falhou) erroArquivo("ler");
        if (fclose(arquivo) != 0) { erroArquivo("fechar"); falhou = 1; }
        if (falhou) { pausar(); return; }
    } else if (errno != ENOENT) {
        erroArquivo("abrir para leitura");
        pausar();
        return;
    }
    if (invalidos || duplicado || total >= MAX_LEADS) {
        if (invalidos) printf("[ ERRO ] Corrija os registros invalidos antes de cadastrar.\n");
        if (duplicado) printf("[ ERRO ] Ja existe um lead com esse ID.\n");
        if (total >= MAX_LEADS) printf("[ ERRO ] Limite de %d leads atingido.\n", MAX_LEADS);
        pausar();
        return;
    }

    /* Aceita arquivo existente cuja ultima linha nao termina com '\n'. */
    arquivo = fopen(ARQUIVO_LEADS, "ab+");
    if (arquivo == NULL) { erroArquivo("abrir para gravacao"); pausar(); return; }
    if (fseek(arquivo, 0, SEEK_END) != 0 || (tamanhoArquivo = ftell(arquivo)) < 0) {
        erroArquivo("verificar"); fclose(arquivo); pausar(); return;
    }
    if (tamanhoArquivo > 0) {
        if (fseek(arquivo, -1L, SEEK_END) != 0 || (ultimo = fgetc(arquivo)) == EOF) {
            erroArquivo("ler"); fclose(arquivo); pausar(); return;
        }
        precisaQuebra = ultimo != '\n';
    }
    if (fseek(arquivo, 0, SEEK_END) != 0) {
        erroArquivo("preparar gravacao"); fclose(arquivo); pausar(); return;
    }
    falhou = fprintf(arquivo, "%s%d;%s;%d;%d\n", precisaQuebra ? "\n" : "",
                     novoLead.id, novoLead.nome, novoLead.origem, novoLead.temperatura) < 0;
    if (falhou) erroArquivo("gravar");
    if (fclose(arquivo) != 0) { erroArquivo("salvar"); falhou = 1; }
    if (!falhou) printf("\n[ SUCESSO ] Lead guardado no ficheiro!\n");
    pausar();
}

void listarLeads(void) {
    Lead lead;
    FILE *arquivo;
    int linha = 0, invalidos = 0, total = 0, falhou;
    system("cls");
    printf("\n--- LISTA DE LEADS ---\n");
    arquivo = fopen(ARQUIVO_LEADS, "rb");
    if (arquivo == NULL) {
        if (errno == ENOENT) printf("[ AVISO ] Nenhum lead cadastrado.\n");
        else erroArquivo("abrir para leitura");
        pausar();
        return;
    }
    while (proximoLead(arquivo, &lead, &linha, &invalidos)) {
        printf("ID: %d | Nome: %s | Orig: %d | Temp: %d\n", lead.id, lead.nome, lead.origem, lead.temperatura);
        total++;
    }
    falhou = ferror(arquivo);
    if (falhou) erroArquivo("ler");
    if (!total && !invalidos && !falhou) printf("[ AVISO ] Nenhum lead cadastrado.\n");
    if (fclose(arquivo) != 0) erroArquivo("fechar");
    pausar();
}

void buscarLead(void) {
    Lead lead;
    FILE *arquivo;
    char termo[TAM_NOME];
    int linha = 0, invalidos = 0, encontrou = 0, falhou;
    system("cls");
    printf("\n--- BUSCAR LEAD ---\n");
    if (!lerNome("Digite o nome exato para buscar: ", termo)) return;
    arquivo = fopen(ARQUIVO_LEADS, "rb");
    if (arquivo == NULL) {
        if (errno == ENOENT) printf("[ AVISO ] Nenhum lead cadastrado.\n");
        else erroArquivo("abrir para leitura");
        pausar();
        return;
    }
    while (proximoLead(arquivo, &lead, &linha, &invalidos)) {
        if (strcmp(lead.nome, termo) == 0) {
            printf("[ ENCONTRADO ] ID: %d | Nome: %s | Orig: %d | Temp: %d\n", lead.id, lead.nome, lead.origem, lead.temperatura);
            encontrou = 1;
        }
    }
    falhou = ferror(arquivo);
    if (falhou) erroArquivo("ler");
    if (!encontrou && !falhou) printf("[ AVISO ] Lead nao encontrado.\n");
    if (fclose(arquivo) != 0) erroArquivo("fechar");
    pausar();
}

