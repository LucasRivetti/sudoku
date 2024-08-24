#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BLUE   "\x1b[34m"
#define RESET  "\x1b[0m"


typedef struct {
    char nome[30];
    double tempoGasto;
} Jogador;

// Função para iniciar o jogo
void iniciarJogo(Jogador *jogador) {
    printf("****************\n");
    printf("*   Sudoku     *\n");
    printf("****************\n");
    printf("\n");
    printf("Bem-vindo ao Jogo do Sudoku!\n");
    printf("Digite seu nome: ");
    fgets(jogador->nome, 30, stdin);
    jogador->nome[strcspn(jogador->nome, "\n")] = '\0';

    printf("\nDicas:\n");
    printf("- Insira '0' como valor para apagar um número e deixar a célula vazia.\n");
    printf("- Linhas, colunas e valores devem estar entre 1 e 9.\n\n");
}

// Função para construir o tabuleiro vazio
void constroiTabuleiro(int tabuleiro[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            tabuleiro[i][j] = 0; // Inicializa todas as células como 0
        }
    }
}

int verificarLinha(int tabuleiro[9][9], int linha, int colunaAtual, int valor) {
    for (int i = 0; i < 9; i++) {
        if (i != colunaAtual && tabuleiro[linha][i] == valor) {
            return 0; // Valor já existe na linha
        }
    }
    return 1; // Valor não existe, logo é válido
}

int verificarColuna(int tabuleiro[9][9], int linhaAtual, int coluna, int valor) {
    for (int i = 0; i < 9; i++) {
        if (i != linhaAtual && tabuleiro[i][coluna] == valor) {
            return 0; // Valor já existe na coluna
        }
    }
    return 1; // Valor não existe, logo é válido
}

int verificarQuadrante(int tabuleiro[9][9], int linha, int coluna, int valor) {
    int linhaInicial = (linha / 3) * 3;
    int colunaInicial = (coluna / 3) * 3;
    for (int i = linhaInicial; i < linhaInicial + 3; i++) {
        for (int j = colunaInicial; j < colunaInicial + 3; j++) {
            if ((i != linha || j != coluna) && tabuleiro[i][j] == valor) {
                return 0; // Valor já existe no quadrante 3x3
            }
        }
    }
    return 1; // Valor não existe no quadrante, logo é válido
}

int posicaoValida(int tabuleiro[9][9], int linha, int coluna, int valor) {
    return verificarLinha(tabuleiro, linha, coluna, valor) &&
           verificarColuna(tabuleiro, linha, coluna, valor) &&
           verificarQuadrante(tabuleiro, linha, coluna, valor);
}


void preencherTabuleiroInicial(int tabuleiro[9][9], int casasPreenchidas) {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    int preenchidas = 0;

    while (preenchidas < casasPreenchidas) {
        int linha = rand() % 9;
        int coluna = rand() % 9;
        int valor = (rand() % 9) + 1;

        // Verifica se a célula está vazia e se o valor é válido
        if (tabuleiro[linha][coluna] == 0 && posicaoValida(tabuleiro, linha, coluna, valor)) {
            tabuleiro[linha][coluna] = valor;
            preenchidas++; // vai preenchendo aleatoriamente ate chegar no valor estipulado pelas dificuldades.
        }
    }
}

void escolherDificuldade(int *casasPreenchidas) {
    int escolha;
    printf("Escolha a dificuldade:\n");
    printf("1. Fácil (30 casas preenchidas)\n");
    printf("2. Médio (22 casas preenchidas)\n");
    printf("3. Difícil (17 casas preenchidas)\n");
    printf("Digite a sua escolha (1-3): ");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            *casasPreenchidas = 30;
            break;
        case 2:
            *casasPreenchidas = 22;
            break;
        case 3:
            *casasPreenchidas = 17;
            break;
        default:
            printf("Escolha inválida! Nível 'Fácil' selecionado por padrão.\n");
            *casasPreenchidas = 30;
            break;
    }
}

void exibirTabuleiro(int tabuleiro[9][9]) {
    printf("\nTabuleiro atual:\n");

    for (int i = 0; i < 9; i++) {
        printf(BLUE "____" RESET);
    }

    for (int i = 0; i < 9; i++) {
        printf(BLUE "\n|" RESET);
        for (int j = 0; j < 9; j++) {
            if (tabuleiro[i][j] != 0) {
                printf(" %d ", tabuleiro[i][j]);
            } else {
                printf("   ");
            }
            if ((j + 1) % 3 == 0 || j == 8) {
                printf(BLUE "|" RESET);
            } else {
                printf("|");
            }
        }
        printf(BLUE "\n|" RESET);
        for (int j = 0; j < 9; j++) {
            if ((i + 1) % 3 == 0 || i == 8) {
                printf(BLUE "___" RESET);
                if ((j + 1) % 3 == 0 || j == 8) {
                    printf(BLUE "|" RESET);
                } else {
                    printf("|");
                }
            } else {
                printf("___");
                if ((j + 1) % 3 == 0 || j == 8) {
                    printf(BLUE "|" RESET);
                } else {
                    printf("|");
                }
            }
        }
    }
    printf("\n");
}


int validarEntrada(int linha, int coluna, int valor) {
    if (linha < 1 || linha > 9 || coluna < 1 || coluna > 9 || valor < 0 || valor > 9) {
        printf("Entrada inválida! Linhas, colunas e valores devem estar entre 1 e 9.\n");
        return 0;
    }
    return 1;
}

//aqui o usuario se diverte
void jogar(int tabuleiro[9][9]) {
    int linha, coluna, valor;
    printf("Digite a linha (1 a 9): ");
    scanf("%d", &linha);
    printf("Digite a coluna (1 a 9): ");
    scanf("%d", &coluna);
    printf("Digite o valor (1 a 9) ou 0 para apagar: ");
    scanf("%d", &valor);

    if (validarEntrada(linha, coluna, valor)) {//aqui o tabuleiro atualiza de acordo com as entradas do usuario
        if (valor == 0) {
            tabuleiro[linha - 1][coluna - 1] = 0; // Zera a célula para 0
            printf("Número removido!\n");
        } else {
            // Atualiza o tabuleiro após validação
            if (posicaoValida(tabuleiro, linha - 1, coluna - 1, valor)) {
                tabuleiro[linha - 1][coluna - 1] = valor;
            } else {
                printf("Número inválido para a posição!\n");
            }
        }
    } else {
        printf("Tente novamente!\n");
    }
}

int main() {  // Aqui é onde toda a mágica acontece na sua telinha do terminal.
    Jogador jogador;
    time_t tempoInicio, tempoFim;
    int tabuleiro[9][9]; // Tabuleiro vazio para teste
    int casasPreenchidas;

    iniciarJogo(&jogador);
    escolherDificuldade(&casasPreenchidas);
    time(&tempoInicio);
    constroiTabuleiro(tabuleiro);
    preencherTabuleiroInicial(tabuleiro, casasPreenchidas);

    for (int i = 0; i < 5; i++) { // 5 jogadas para teste
        exibirTabuleiro(tabuleiro);
        jogar(tabuleiro);
    }

    time(&tempoFim);
    jogador.tempoGasto = difftime(tempoFim, tempoInicio);

    exibirTabuleiro(tabuleiro);
    printf("\nTempo gasto: %.2f segundos\n", jogador.tempoGasto);

    return 0;
}
