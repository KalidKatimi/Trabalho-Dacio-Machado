// leads.h
#define MAX_LEADS 50

typedef struct {
    int id;
    char nome[50];
    int origem;
    int temperatura;
} Lead;

void cadastrarLead();
void listarLeads();
void buscarLead();
