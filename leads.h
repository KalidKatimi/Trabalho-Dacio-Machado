#ifndef LEADS_H
#define LEADS_H

#define MAX_LEADS 50
#define TAM_NOME 50

typedef struct {
    int id;
    char nome[TAM_NOME];
    int origem;
    int temperatura;
} Lead;

void cadastrarLead(void);
void listarLeads(void);
void buscarLead(void);
int lerInteiro(const char *mensagem, int minimo, int maximo, int *valor);
void pausar(void);

#endif

