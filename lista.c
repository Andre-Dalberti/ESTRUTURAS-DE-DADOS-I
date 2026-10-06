#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

/* 
 * Autor: [André Dalberti da Silva]
 * Funcao: lc_inicializar
 * Logica: Aloca dinamicamente o no sentinela e inicializa os campos da lista].
 * Uso da lista: Prepara a estrutura para receber os primeiros participantes.
 * Por que esta estrutura: O no cabecalho (sentinela) nunca guarda dado util e nunca e removido, garantindo que o ponteiro inicial da lista nunca mude de valor. Isso elimina a necessidade de tratar o caso de "lista vazia" nas futuras insercoes.
 */
void lc_inicializar(ListaCabecalho *lista) {
    lista->cabecalho = (No *) malloc(sizeof(No));
    if (!lista->cabecalho) {
        fprintf(stderr, "Erro: sem memoria.\n");
        exit(1);
    }
    lista->cabecalho->ra = 0;
    lista->cabecalho->proximo = NULL;
    lista->tamanho = 0;
}

/* 
 * Funcao: lc_inserir_fim
 * Logica: Aloca um novo no, copia os dados e percorre a lista a partir do cabecalho ate o ultimo no real, anexando o novo no ao final.
 * Uso da lista: Permite adicionar novos participantes a um evento, respeitando a ordem de chegada.
 * Por que esta estrutura: O uso do sentinela garante que o laco `while` sempre tera um no inicial valido para comecar a travessia, tornando o codigo mais linear e livre de ramificacoes.
 */
int lc_inserir_fim(ListaCabecalho *lista, int ra, const char *nome) {
    No *novo = (No *) malloc(sizeof(No));
    if (!novo) return 0;
    
    novo->ra = ra;
    strncpy(novo->nome, nome, 49);
    novo->nome[49] = '\0';
    novo->proximo = NULL;

    No *atual = lista->cabecalho;
    while (atual->proximo != NULL) {
        atual = atual->proximo;
    }
    atual->proximo = novo;
    lista->tamanho++;
    return 1;
}

/* 
 * Funcao: lc_remover_por_ra
 * Logica: Mantem um ponteiro `anterior` (que comeca no cabecalho) e avanca ate encontrar o RA desejado no `proximo` no. Ao encontrar, "pula" o no removido e liberta a sua memoria.
 * Uso da lista: Cancela a inscricao de um participante.
 * Por que esta estrutura: Na lista com cabecalho, sempre existe um no anterior (o proprio sentinela, no pior caso). Isso torna o algoritmo de remocao uniforme, pois remover o primeiro elemento segue a exata mesma logica de remover no meio.
 */
int lc_remover_por_ra(ListaCabecalho *lista, int ra) {
    No *anterior = lista->cabecalho;
    while (anterior->proximo != NULL && anterior->proximo->ra != ra) {
        anterior = anterior->proximo;
    }
    
    if (anterior->proximo == NULL) return 0; /* Nao encontrado */
    
    No *remover = anterior->proximo;
    anterior->proximo = remover->proximo;
    free(remover);
    lista->tamanho--;
    return 1;
}

/* 
 * Funcao: lc_buscar_ra
 * Logica: Percorre a lista ignorando o sentinela (`cabecalho->proximo`) e compara o RA.
 * Uso da lista: Utilizada para impedir inscricoes duplicadas no sistema.
 * Por que esta estrutura: A busca puramente sequencial eh a operacao padrao em listas lineares encadeadas, operando em tempo O(n).
 */
int lc_buscar_ra(const ListaCabecalho *lista, int ra) {
    No *atual = lista->cabecalho->proximo;
    while (atual != NULL) {
        if (atual->ra == ra) return 1;
        atual = atual->proximo;
    }
    return 0;
}

/* 
 * Funcao: lc_imprimir
 * Logica: Inicia no primeiro no real (`cabecalho->proximo`) e percorre imprimindo RA e Nome.
 * Uso da lista: Emite a lista de presenca de um evento.
 * Por que esta estrutura: A lista ligada permite o percurso flexivel. Pular o cabecalho evita imprimir lixo de memoria.
 */
void lc_imprimir(const ListaCabecalho *lista) {
    No *atual = lista->cabecalho->proximo;
    if (!atual) {
        printf("  [Nenhum participante inscrito]\n");
        return;
    }
    while (atual != NULL) {
        printf("  - RA: %d | Nome: %s\n", atual->ra, atual->nome);
        atual = atual->proximo;
    }
}

/* 
 * Funcao: lc_destruir
 * Logica: Liberta todos os nos da lista e, por fim, liberta tambem o proprio no sentinela.
 * Uso da lista: Chamada ao encerrar o sistema para garantir zero vazamento de memoria.
 * Por que esta estrutura: Como a alocacao eh dinamica (um bloco por no), eh obrigatorio fazer um `free` correspondente para cada `malloc`.
 */
void lc_destruir(ListaCabecalho *lista) {
    No *atual = lista->cabecalho;
    No *proximo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    lista->cabecalho = NULL;
    lista->tamanho = 0;
}