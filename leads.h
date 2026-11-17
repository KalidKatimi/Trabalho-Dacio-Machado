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

int lerNumero(const char *mensagem, int minimo, int maximo);
void cadastrarLead(void);
void listarLeads(void);
void buscarLead(void);

#endif
