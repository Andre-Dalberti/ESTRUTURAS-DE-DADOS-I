#ifndef LISTA_H
#define LISTA_H

/* Estrutura do no conforme o padrao da lista com cabecalho*/
typedef struct No {
    int ra;
    char nome[50];
    struct No *proximo;
} No;

/* Estrutura da lista encapsulando o sentinela e o tamanho */
typedef struct {
    No *cabecalho;
    int tamanho;
} ListaCabecalho;

void lc_inicializar(ListaCabecalho *lista);
int lc_inserir_fim(ListaCabecalho *lista, int ra, const char *nome);
int lc_remover_por_ra(ListaCabecalho *lista, int ra);
int lc_buscar_ra(const ListaCabecalho *lista, int ra);
void lc_imprimir(const ListaCabecalho *lista);
void lc_destruir(ListaCabecalho *lista);

#endif