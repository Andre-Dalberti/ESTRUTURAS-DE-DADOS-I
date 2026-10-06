#include <stdio.h>
#include <string.h>
#include "eventos.h"

/* 
 * Autor: [André Dalberti da Silva]
 * Funcao: ev_inicializar
 * Logica: Define a variavel `tamanho` como 0, indicando que nao ha elementos logicos presentes.
 * Uso da lista: Prepara o vetor global de eventos.
 * Por que esta estrutura: Em listas estaticas, o controle eh feito puramente pelo campo tamanho, operando em tempo constante O(1).
 */
void ev_inicializar(ListaEventos *lista) {
    lista->tamanho = 0;
}

/* 
 * Funcao: ev_cadastrar
 * Logica: Verifica se ha espaco e se o codigo nao esta duplicado. Se tudo estiver correto, adiciona na posicao dada por `tamanho` e incrementa o contador.
 * Uso da lista: Cadastra novos eventos no sistema, alocando a lista de participantes internamente.
 * Por que esta estrutura: Num vetor (lista estatica), a insercao no final eh direta e ocorre em O(1), sendo altamente eficiente para cadastros sequenciais.
 */
int ev_cadastrar(ListaEventos *lista, int codigo, const char *nome, const char *data) {
    if (lista->tamanho >= MAX_EVENTOS) return 0;
    if (ev_buscar(lista, codigo) != -1) return -1; /* Duplicado */

    int pos = lista->tamanho;
    lista->dados[pos].codigo = codigo;
    strncpy(lista->dados[pos].nome, nome, 49);
    lista->dados[pos].nome[49] = '\0';
    strncpy(lista->dados[pos].data, data, 10);
    lista->dados[pos].data[10] = '\0';
    
    lc_inicializar(&lista->dados[pos].participantes);
    
    lista->tamanho++;
    return 1;
}

/* 
 * Funcao: ev_buscar
 * Logica: Percorre o vetor estatico de 0 ate `tamanho - 1` e compara o codigo do evento.
 * Uso da lista: Retorna o indice do evento no vetor, vital para associar inscricoes de participantes.
 * Por que esta estrutura: Sendo uma lista estatica, a busca sequencial opera em O(n) sobre dados agrupados de forma contigua na memoria (alta localidade de cache).
 */
int ev_buscar(const ListaEventos *lista, int codigo) {
    for (int i = 0; i < lista->tamanho; i++) {
        if (lista->dados[i].codigo == codigo) return i;
    }
    return -1;
}

/* 
 * Funcao: ev_listar
 * Logica: Itera sequencialmente pelos registros preenchidos e exibe as suas propriedades.
 * Uso da lista: Apresenta os dados globais.
 * Por que esta estrutura: O acesso indexado da lista estatica e rapido e apropriado para leituras repetitivas.
 */
void ev_listar(const ListaEventos *lista) {
    if (lista->tamanho == 0) {
        printf("Nenhum evento registado.\n");
        return;
    }
    for (int i = 0; i < lista->tamanho; i++) {
        printf("Cod: %d | Nome: %s | Data: %s | Inscritos: %d\n",
               lista->dados[i].codigo, lista->dados[i].nome, 
               lista->dados[i].data, lista->dados[i].participantes.tamanho);
    }
}