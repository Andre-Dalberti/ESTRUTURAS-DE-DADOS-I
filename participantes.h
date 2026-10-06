#ifndef PARTICIPANTES_H
#define PARTICIPANTES_H
#include "eventos.h"

void part_inscrever(ListaEventos *eventos, int codigo_evento, int ra, const char *nome);
void part_remover(ListaEventos *eventos, int codigo_evento, int ra);
void part_listar_por_evento(const ListaEventos *eventos, int codigo_evento);
void part_relatorio_individual(const ListaEventos *eventos, int ra);

#endif