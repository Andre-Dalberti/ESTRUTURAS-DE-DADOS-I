#include <stdio.h>
#include "participantes.h"

/* 
 * Autor: [André Dalberti da Silva]
 * Funcao: part_inscrever
 * Logica: Localiza o evento e utiliza `lc_buscar_ra` para bloquear RA duplicado; apos validacao, cadastra via `lc_inserir_fim`.
 * Uso da lista: Garante a coerencia e exclusividade de dados no momento do cadastro.
 * Por que esta estrutura: Combinamos a busca rapida de um vetor (para localizar o evento) com a insercao flexivel e expansivel da lista encadeada (para acomodar qualquer quantidade de alunos).
 */
void part_inscrever(ListaEventos *eventos, int codigo_evento, int ra, const char *nome) {
    int idx = ev_buscar(eventos, codigo_evento);
    if (idx == -1) {
        printf("Erro: Evento nao localizado.\n"); return;
    }
    if (lc_buscar_ra(&eventos->dados[idx].participantes, ra)) {
        printf("Erro: RA %d ja inscrito neste evento.\n", ra); return;
    }
    lc_inserir_fim(&eventos->dados[idx].participantes, ra, nome);
    printf("Inscricao confirmada!\n");
}

/* 
 * Funcao: part_remover
 * Logica: Localiza o evento e repassa o RA para `lc_remover_por_ra`.
 * Uso da lista: Permite manter a lista atualizada em casos de desistencia.
 * Por que esta estrutura: A lista ligada permite remover elementos do meio sem precisar efetuar o deslocamento de memoria (shift) caracteristico dos vetores estaticos.
 */
void part_remover(ListaEventos *eventos, int codigo_evento, int ra) {
    int idx = ev_buscar(eventos, codigo_evento);
    if (idx == -1) {
        printf("Erro: Evento nao localizado.\n"); return;
    }
    if (lc_remover_por_ra(&eventos->dados[idx].participantes, ra)) {
        printf("Inscricao cancelada.\n");
    } else {
        printf("Erro: RA nao consta neste evento.\n");
    }
}

/* 
 * Funcao: part_listar_por_evento
 * Logica: Resgata o evento estatico e passa a lista cabecalho subjacente para a funcao de emissao.
 * Uso da lista: Gerar uma folha de assinaturas / chamada.
 * Por que esta estrutura: O encapsulamento oculta do programador (aqui na logica de negocios) os ponteiros da lista, tratando as chamadas por modulos.
 */
void part_listar_por_evento(const ListaEventos *eventos, int codigo_evento) {
    int idx = ev_buscar(eventos, codigo_evento);
    if (idx == -1) {
        printf("Erro: Evento nao localizado.\n"); return;
    }
    printf("\n--- Evento: %s ---\n", eventos->dados[idx].nome);
    lc_imprimir(&eventos->dados[idx].participantes);
}

/* 
 * Funcao: part_relatorio_individual
 * Logica: Itera sob todos os eventos cadastrados na lista estatica e, para cada um, pesquisa a presenca do RA na lista encadeada daquele evento.
 * Uso da lista: Fornece um painel cruzado de dados de participacao e assiduidade.
 * Por que esta estrutura: A operacao e eficiente porque apenas os vetores e os nos ativados serao pesquisados. A divisao dos modulos facilita a manutencao.
 */
void part_relatorio_individual(const ListaEventos *eventos, int ra) {
    printf("\n--- Relatorio RA: %d ---\n", ra);
    int encontrou = 0;
    for (int i = 0; i < eventos->tamanho; i++) {
        if (lc_buscar_ra(&eventos->dados[i].participantes, ra)) {
            printf("- %s (%s)\n", eventos->dados[i].nome, eventos->dados[i].data);
            encontrou++;
        }
    }
    if (!encontrou) printf("Aluno nao inscrito em eventos.\n");
}