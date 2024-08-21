#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

void exibirTabuleiro(int tabuleiro[9][9]) {
    printf("\nTabuleiro atual:\n");
  for (int A = 0; A < 9; A++) {
        printf ("____");
    }
    for (int i = 0; i < 9; i++) {
        printf ("\n|");
        for (int j = 0; j < 9; j++) {
            printf (" %d |",tabuleiro[i][j]);
        }
        printf ("\n|");
        for (int B = 0; B < 9; B++) {
            printf ("___|");
        }
    }
    printf("\n");
}

int validarEntrada(int linha, int coluna, int valor) {

    if (linha < 1 || linha > 9 || coluna < 1 || coluna > 9 || valor < 1 || valor > 9) {
        printf("Entrada inválida! Linhas, colunas e valores devem estar entre 1 e 9.\n");
        return 0;
    }
    return 1;
}

void jogar(int tabuleiro[9][9]) {
    int linha, coluna, valor;
    printf("Digite a linha 1 a 9:\n");
    scanf("%d", &linha);
    printf("Digite a coluna de 1 a 9:\n");
    scanf("%d", &coluna);
    printf("Digite o valor de 1 a 9:\n");
    scanf("%d", &valor);

     if (validarEntrada(linha, coluna, valor)) {
        tabuleiro[linha-1][coluna-1] = valor; // Atualiza o tabuleiro (ajustando para índice 0)
    } else {
        printf("Tente novamente!\n");
    }
}


int main() {
    Jogador jogador;
    time_t tempoInicio, tempoFim;
    int tabuleiro[9][9] = {0}; //por enquanto vazio para teste

    iniciarJogo(&jogador);
    time(&tempoInicio);


    for (int i = 0; i < 5; i++) { // 5 jogos para teste
        exibirTabuleiro(tabuleiro);
        jogar(tabuleiro);
    }

    time(&tempoFim);
    jogador.tempoGasto = difftime(tempoFim, tempoInicio);

    exibirTabuleiro(tabuleiro);
    printf("\nTempo gasto: %.2f segundos\n", jogador.tempoGasto);

    return 0;
}
