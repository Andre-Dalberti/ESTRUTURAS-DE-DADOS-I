#ifndef EVENTOS_H
#define EVENTOS_H
#include "lista.h"

#define MAX_EVENTOS 50

/* A Lista Estatica possui o tamanho definido em tempo de compilacao */
typedef struct {
    int codigo;
    char nome[50];
    char data[11];
    ListaCabecalho participantes;
} Evento;

typedef struct {
    Evento dados[MAX_EVENTOS];
    int tamanho;
} ListaEventos;

void ev_inicializar(ListaEventos *lista);
int ev_cadastrar(ListaEventos *lista, int codigo, const char *nome, const char *data);
int ev_buscar(const ListaEventos *lista, int codigo);
void ev_listar(const ListaEventos *lista);

#endif