# Sistema de Controle de Participação em Eventos Estudantis

Este sistema modular tem como objetivo registrar os eventos de um setor de extensão universitário e controlar individualmente os estudantes inscritos, garantindo a integridade dos dados e impedindo duplicidades.

## Justificativa das Estruturas de Dados

* **Eventos (Lista Estática - Vetor):** A gestão dos eventos foi implementada utilizando um vetor de tamanho fixo. Como o calendário de extensão possui um limite previsível de eventos anuais, a lista estática permite a busca sequencial em memória contígua (alta localidade de cache) e inserções em tempo $\mathcal{O}(1)$ no final da lista, garantindo alta eficiência sem a complexidade de alocação dinâmica.
* **Participantes (Lista Ligada com Nó Cabeçalho):** Para a fila de inscritos em cada evento, optou-se pela lista simplesmente encadeada com nó sentinela (cabeçalho). Como o número de participantes varia drasticamente, a alocação dinâmica evita desperdício de memória. O uso específico do nó sentinela assegura que a lógica flua sem condicionais extras (eliminando o caso especial de "lista vazia"), tornando a inserção e a remoção seguras e blindadas contra falhas de segmentação.

## Autoria e Responsabilidades

* **André Dalberti:** Desenvolvedor único do projeto. Responsável por estruturar a arquitetura modular do sistema, implementar o menu interativo, codificar as operações do vetor para os eventos e construir os algoritmos de inserção, busca e remoção na lista encadeada. Também foi o responsável pelo rigoroso gerenciamento de memória (uso de `malloc` e `free` correspondentes, incluindo a limpeza do nó sentinela) para garantir zero vazamentos.

## Compilação e Execução

O projeto exige aderência estrita ao padrão C11 e proteção rigorosa contra bugs de memória.

**Compilação via Terminal:**

```bash
gcc -Wall -Wextra -pedantic -std=c11 -o sistema_eventos main.c eventos.c participantes.c lista.c

```

**Execução:**

```bash
./sistema_eventos

```