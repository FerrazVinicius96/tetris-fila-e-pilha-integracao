TETRIS – Protótipo com Fila e Pilha (Estrutura de Dados)
Versão didática em C utilizando fila circular e pilha estática

---------------------------------------------
VISÃO GERAL DO PROJETO
---------------------------------------------
Este repositório contém um protótipo simplificado de mecânicas do jogo Tetris, desenvolvido
para fins didáticos na disciplina de Estruturas de Dados. O projeto demonstra o uso de fila
circular e pilha estática para manipulação de peças, simulando o comportamento real do jogo.

---------------------------------------------
CONCEITOS UTILIZADOS
---------------------------------------------
1. Fila Circular (Queue)
- Armazena as próximas peças disponíveis no jogo.
- Operações: inserir, remover, exibir, trocar primeira peça.
- Tamanho fixo: 5 peças.

2. Pilha Estática (Stack)
- Representa as peças reservadas (hold).
- Operações: push, pop, exibir.
- Capacidade máxima: 3 peças.

---------------------------------------------
FUNCIONALIDADES
---------------------------------------------
✔ Jogar peça (remove o primeiro elemento da fila e gera nova peça)
✔ Reservar peça (primeira peça da fila vai para pilha)
✔ Usar peça reservada (pop)
✔ Troca simples: primeira da fila ↔ topo da pilha
✔ Troca múltipla: 3 primeiras peças da fila ↔ 3 peças da pilha
✔ Fila sempre mantida cheia quando possível
✔ Exibição da fila e pilha a cada operação

---------------------------------------------
MODELAGEM DAS ESTRUTURAS
---------------------------------------------
Estrutura da peça:
typedef struct {
    int id;
    char tipo;
} Peca;

Fila circular:
typedef struct {
    Peca item[MAX_FILA];
    int inicio;
    int fim;
    int total;
} Fila;

Pilha de reserva:
typedef struct {
    Peca itens_reserva[MAX_PILHA];
    int topo;
} Pilha;

---------------------------------------------
COMPILAÇÃO
---------------------------------------------
gcc -Wall -Wextra -std=c11 main.c -o tetris
./tetris

---------------------------------------------
MENU DE AÇÕES
---------------------------------------------
1 - Jogar peça
2 - Armazenar peça na pilha
3 - Jogar peça do topo da pilha
4 - Trocar primeira peça da fila pelo topo da pilha
5 - Trocar fila ↔ pilha (troca múltipla)
6 - Sair

---------------------------------------------
EXPANSÕES FUTURAS
---------------------------------------------
- Interface gráfica com SDL
- Modularização com include/ e src/
- Tabuleiro completo de Tetris
- Persistência em arquivos
- Filas e pilhas dinâmicas

---------------------------------------------
AUTOR
---------------------------------------------
Vinícius Ferraz – Projeto acadêmico para prática de estruturas de dados em C.

---------------------------------------------
LICENÇA
---------------------------------------------
Projeto aberto para fins educacionais.
