#include <stdio.h>
#include "eventos.h"
#include "participantes.h"

/* 
 * Autor: [André Dalberti da Silva]
 * Funcao: main
 * Logica: Inicializa o contexto, lida com a entrada de utilizador e garante o free de memoria ao encerrar.
 * Uso da lista: Ponto focal do sistema.
 * Por que esta estrutura: Padrao modular sugerido em aula para separar logica de armazenamento da interacao com o terminal.
 */
int main(void) {
    ListaEventos sistema;
    ev_inicializar(&sistema);
    
    int opcao, codigo, ra;
    char nome[50], data[11];

    do {
        printf("\n=== SETOR DE EXTENSAO ===\n");
        printf("1. Cadastrar Evento\n2. Inscrever Participante\n3. Listar Participantes de Evento\n");
        printf("4. Remover Participante\n5. Relatorio Individual (RA)\n6. Listar Todos Eventos\n0. Sair\n");
        printf("Opcao: "); scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Codigo: "); scanf("%d", &codigo);
                printf("Nome: "); scanf(" %49[^\n]", nome);
                printf("Data (DD/MM/AAAA): "); scanf(" %10s", data);
                if (ev_cadastrar(&sistema, codigo, nome, data) == 1) printf("Criado com sucesso!\n");
                else printf("Erro.\n");
                break;
            case 2:
                printf("Codigo do Evento: "); scanf("%d", &codigo);
                printf("RA: "); scanf("%d", &ra);
                printf("Nome: "); scanf(" %49[^\n]", nome);
                part_inscrever(&sistema, codigo, ra, nome);
                break;
            case 3:
                printf("Codigo do Evento: "); scanf("%d", &codigo);
                part_listar_por_evento(&sistema, codigo);
                break;
            case 4:
                printf("Codigo do Evento: "); scanf("%d", &codigo);
                printf("RA: "); scanf("%d", &ra);
                part_remover(&sistema, codigo, ra);
                break;
            case 5:
                printf("RA: "); scanf("%d", &ra);
                part_relatorio_individual(&sistema, ra);
                break;
            case 6:
                ev_listar(&sistema);
                break;
            case 0:
                printf("Limpando memoria...\n");
                for(int i = 0; i < sistema.tamanho; i++) {
                    lc_destruir(&sistema.dados[i].participantes);
                }
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while(opcao != 0);
    
    return 0;
}