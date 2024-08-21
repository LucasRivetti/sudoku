#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Dados do usuario
typedef struct {
    char nome[30];
    double tempoGasto;
} Jogador;

void iniciarJogo(Jogador *jogador) {
    printf("****************\n");
    printf("*   Sudoku     *\n");
    printf("****************\n");
    printf("\n");
    printf("Bem-vindo ao Jogo do Sudoku!\n");
    printf("Digite seu nome: ");
    fgets(jogador->nome, 30, stdin);
    jogador->nome[strcspn(jogador->nome, "\n")] = '\0';
}

void simularJogo() {
    // implementar a lógica do Sudoku
    //loop apenas simula o tempo de jogo
    for (int i = 0; i < 1000000000; i++);
}

double calcularTempo(time_t inicio, time_t fim) {
    return difftime(fim, inicio);
}

void exibirResultados(Jogador jogador) {
    printf("\nJogador: %s\n", jogador.nome);
    printf("Tempo gasto: %.2f segundos\n", jogador.tempoGasto);
}

int main() {
    Jogador jogador;
    time_t tempoInicio, tempoFim;

    iniciarJogo(&jogador);
    time(&tempoInicio);

    simularJogo();//logica 

    time(&tempoFim);
    jogador.tempoGasto = calcularTempo(tempoInicio, tempoFim);

    exibirResultados(jogador);

    return 0;
}
