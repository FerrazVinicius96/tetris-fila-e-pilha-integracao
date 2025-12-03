/*

Seu programa em C deverá:

 

Inicializar a fila de peças com um número fixo de elementos (por exemplo, 5).
     
Inicializar uma pilha de peças reservadas com capacidade limitada (por exemplo, 3).
     

Permitir as seguintes ações:
 

- Jogar uma peça: remove a peça da frente da fila (dequeue).
     
- Reservar uma peça: move a peça da frente da fila para o topo da pilha, se houver espaço.
     
- Usar uma peça reservada: remove a peça do topo da pilha, simulando seu uso.
     
- Exibir o estado atual: mostra as peças na fila e na pilha após cada ação.
     
- Trocar peça atual: substitui a peça da frente da fila com o topo da pilha.
     
- Troca múltipla: alterna as três primeiras peças da fila com as três peças da pilha (caso ambas tenham, pelo menos, 3 peças).
     
- Visualizar o estado atual da fila e da pilha.
     
- Gerar uma nova peça de forma automática a cada remoção ou envio à pilha, a fim de manter a fila sempre cheia (quando possível).
     
- Encerrar o programa.
     

Lembre-se: as peças removidas da fila ou da pilha não voltam para o jogo.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_FILA 5
#define MAX_PILHA 3

// -----------------------------
// Estruturas
// -----------------------------
typedef struct {
    int id;
    char tipo;
} Peca;

typedef struct {
    Peca item[MAX_FILA];
    int inicio;
    int fim;
    int total;
} Fila;

// Criacao da pilha itens_reserva

typedef struct{
    Peca itens_reserva[MAX_PILHA];
    int topo;
} Pilha;

// ----------------------------
// Controle da Pilha
// ----------------------------

void inicializarPilha(Pilha *pi){
    pi->topo = -1;
}

int pilhaCheia(Pilha *pi){
    return pi->topo == MAX_PILHA - 1;
}

int pilhaVazia(Pilha *pi){
    return pi->topo == -1;
}

void push(Pilha *pi, Peca p){
    if(pilhaCheia(pi)){
        printf("Pilha cheia.\n");
        return;
    }

    pi->topo++;
    pi->itens_reserva[pi->topo] = p;
}

void pop(Pilha *pi, Peca *removida){
    if(pilhaVazia(pi)){
        printf("Pilha reserva vazia.\n");
        return;
    }

    *removida = pi->itens_reserva[pi->topo];
    pi->topo--;
}

void mostrarPilha(Pilha *pi){
    printf("\nPilha reserva: \n");

    if(pilhaVazia(pi)){
        printf("Pilha reserva vazia.\n");
        return;
    }

    for(int i = pi->topo; i > -1; i--){
        printf("[%c %d] ", pi->itens_reserva[i].tipo, pi->itens_reserva[i].id);
    }

    printf("\n\n");


}

// -----------------------------
// Controle da Fila
// -----------------------------
void inicializarFila(Fila *f){
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(Fila *f){
    return f->total == MAX_FILA;
}

int filaVazia(Fila *f){
    return f->total == 0;
}

void inserir(Fila *f, Peca p){
    if(filaCheia(f)){
        printf("Fila cheia.\n");
        return;
    }

    f->item[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->total++;
}

Peca remover(Fila *f){
    Peca removida = {-1, '?'};

    if(filaVazia(f)){
        printf("Fila vazia.\n");
        return removida;
    }

    removida = f->item[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->total--;

    return removida;
}


void mostrar(Fila *f){
    printf("\nFila atual:\n");

    if (filaVazia(f)) {
        printf("[vazia]\n\n");
        return;
    }

    int idx = f->inicio;

    for (int i = 0; i < f->total; i++){
        printf("[%c %d] ", f->item[idx].tipo, f->item[idx].id);
        idx = (idx + 1) % MAX_FILA;
    }

    printf("\n\n");
}

/*

Trocar primeira peca da fila com topo da pilha

*/

void trocarPrimeira(Fila *f, Pilha *pi){
    if(filaVazia(f)){
        printf("Fila vazia.\n");
        return;
    }
    if(pilhaVazia(pi)){
        printf("Pilha vazia.\n");
        return;
    }

    Peca temp;

    temp = f->item[f->inicio];
    f->item[f->inicio] = pi->itens_reserva[pi->topo];
    pi->itens_reserva[pi->topo] = temp;



}

/*

Trocar as pecas da pilha pelas tres primeiras da fila

*/

void trocarTudo(Fila *f, Pilha *pi){
    // Precisamos de pelo menos 3 peças na fila
    if (f->total < MAX_PILHA) {
        printf("Quantidade de pecas na fila insuficiente para troca.\n");
        return;
    }

    // Pilha precisa estar cheia (3 elementos: topo == 2)
    if (!pilhaCheia(pi)) {
        printf("Pilha reserva precisa estar cheia (3 pecas) para realizar a troca.\n");
        return;
    }

    // Vetor temporário para guardar as 3 primeiras peças da fila
    Peca tempFila[MAX_PILHA];

    // 1) Troca: fila[3 primeiras] <-> pilha[3 posições]
    for (int i = 0; i < MAX_PILHA; i++) {
        int idxFila = (f->inicio + i) % MAX_FILA;

        // Guarda peça atual da fila
        tempFila[i] = f->item[idxFila];

        // Coloca na fila a peça correspondente da pilha
        f->item[idxFila] = pi->itens_reserva[i];
    }

    // 2) Agora coloca na pilha as peças antigas da fila
    for (int i = 0; i < MAX_PILHA; i++) {
        pi->itens_reserva[i] = tempFila[i];
    }

    printf("Troca multipla realizada entre as 3 primeiras pecas da fila e a pilha reserva.\n");
}


// -----------------------------
// Geração Aleatória de Peças
// -----------------------------

Peca gerarPeca(void){
    static int nextId = 0; // garante IDs únicos

    char tipos[] = {'O', 'I', 'T', 'L'};
    int r = rand() % 4; // sorteio entre 0 e 3

    Peca p;
    p.id = nextId++;
    p.tipo = tipos[r];

    return p;
}

/* Menu */

int menu() {
    char buffer[100];
    char *endptr;
    long opcao;

    printf("\n--- MENU INICIAL ---\n\n");
    printf("1 - Jogar peca (remover da fila)\n");
    printf("2 - Armazenar peca na pilha\n");
    printf("3 - Jogar peca do topo da pilha\n");
    printf("4 - Trocar primeira peca da fila pelo topo da pilha\n");
    printf("5 - Trocar toda pilha reserva por fila\n");
    printf("6 - Sair\n");
    printf("Opcao: ");

    if (!fgets(buffer, sizeof(buffer), stdin)) {
        return -1; // erro de leitura
    }

    opcao = strtol(buffer, &endptr, 10);

    return (int)opcao;
}

// -----------------------------
// MAIN
// -----------------------------
int main(void){
    int opcao;
    srand((unsigned)time(NULL)); // inicializa aleatoriedade

    Fila jogo; // Declara uma variavel para o jogo
    Pilha reserva; // Declara uma variavel para fila

    inicializarFila(&jogo);
    inicializarPilha(&reserva);

    // Inserindo 5 peças iniciais
    for(int i = 0; i < MAX_FILA; i++){
        inserir(&jogo, gerarPeca());
    }

    mostrar(&jogo);
    mostrarPilha(&reserva);

    do{
        opcao = menu();
        switch(opcao){
            case 1: {
                // Jogar peça (remover da frente)
                Peca jogada = remover(&jogo);
                printf("Voce jogou a peca: [%c %d]\n", jogada.tipo, jogada.id);

                // Inserir nova peca aleatoria
                Peca nova = gerarPeca();
                inserir(&jogo, nova);
                printf("\nPeca inserida: [%c %d]\n", nova.tipo, nova.id);

                mostrar(&jogo);
                break;
            }
            case 2: {
                Peca proxima = remover(&jogo);
                inserir(&jogo, gerarPeca());

                push(&reserva, proxima);

                mostrar(&jogo);
                mostrarPilha(&reserva);
                break;
            }
            case 3:
                Peca removida;
                pop(&reserva, &removida);
                printf("\nVoce jogou a peca: [%c %d]\n", removida.tipo, removida.id);


                break;
            case 4:
                trocarPrimeira(&jogo, &reserva);

                mostrar(&jogo);
                mostrarPilha(&reserva);
                break;
            case 5:
                trocarTudo(&jogo, &reserva);

                mostrar(&jogo);
                mostrarPilha(&reserva);
                break;
            case 6:
                printf("Saindo do jogo...\n");
                break;                
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while(opcao != 6);

    return 0;
}
