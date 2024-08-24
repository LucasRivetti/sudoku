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

void constroiTabuleiro(int tabuleiro[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            tabuleiro[i][j] = '-'; // Inicializa todas as células como '-'
        }
    }
}

int verificarLinha(int tabuleiro[9][9], int linha, int valor) { //vai passsar por todos os valores verificando se existe o valor igual
    for (int i = 0; i < 9; i++) {
        if (tabuleiro[linha][i] == valor) {
            return 0; // Valor já existe na linha
        }
    }
    return 1;;// valor não existe, logo ta mec
}

int verificarColuna(int tabuleiro[9][9], int coluna, int valor){ //mesca coisa do de cima
    for (int i = 0; i < 9; i++) {
        if (tabuleiro[i][coluna] == valor) {
            return 0; // Valor já existe na coluna
        }
    }
    return 1;
}

int verificarQuadrante(int tabuleiro[9][9], int linha, int coluna, int valor) { // mesma coisa porem vai passar quadrante por quadrante verificando
    int linhaInicial = (linha / 3) * 3;
    int colunaInicial = (coluna / 3) * 3;
    for (int i = linhaInicial; i < linhaInicial + 3; i++) {
        for (int j = colunaInicial; j < colunaInicial + 3; j++) {
            if (tabuleiro[i][j] == valor) {
                return 0; // Valor já existe no quadrante 3x3
            }
        }
    }
    return 1;
}

int posicaoValida(int tabuleiro[9][9], int linha, int coluna, int valor) { // aqui ele vai pegar todos os valores de linha coluna e quadrante para verificar retornando 1 se for verdadeiro e 0 caso contrario
    return verificarLinha(tabuleiro, linha, valor) &&
           verificarColuna(tabuleiro, coluna, valor) &&
           verificarQuadrante(tabuleiro, linha, coluna, valor);
}

void preencherTabuleiroInicial(int tabuleiro[9][9], int casasPreenchidas) { //aqui vai preencher o tabuleiro
    srand(time(NULL)); //inicializando para o rad
    int preenchidas = 0;

    while (preenchidas < casasPreenchidas) {
        int linha = rand() % 9;
        int coluna = rand() % 9;
        int valor = (rand() % 9) + 1;

        // Verifica se a célula está vazia e se o valor é válido
        if (tabuleiro[linha][coluna] == '-' && posicaoValida(tabuleiro, linha, coluna, valor)) {
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

void exibirTabuleiro(char tabuleiro[9][9]) {
    printf("\nTabuleiro atual:\n");

    for (int i = 0; i < 9; i++) {
        printf(BLUE "____" RESET);
    }

    for (int i = 0; i < 9; i++) {
        printf(BLUE "\n|" RESET);
        for (int j = 0; j < 9; j++) {
            if (tabuleiro[i][j] != '-') {
                printf(" %c ", tabuleiro[i][j]);
            } else {
                printf("   ");
            }
            if ((j - 2) % 3 == 0 || j == 8) {
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

int validarEntrada(int linha, int coluna, int valor) { // aqui sera verificado se a entrada do usuario é valida para as regras do sudoku( nn verifica a questão das posicoes iguais ou não.)
    if (linha < 1 || linha > 9 || coluna < 1 || coluna > 9 || valor < 0 || valor > 9) {
        printf("Entrada inválida! Linhas, colunas e valores devem estar entre 1 e 9.\n");
        return 0;
    }
    return 1;
}

void jogar(int tabuleiro[9][9]) { //aqui o usuario se diverte
    int linha, coluna, valor;
    printf("Digite a linha (1 a 9): ");
    scanf("%d", &linha);
    printf("Digite a coluna (1 a 9): ");
    scanf("%d", &coluna);
    printf("Digite o valor (1 a 9) ou 0 para apagar: ");
    scanf("%d", &valor);

    if (validarEntrada(linha, coluna, valor)) { //aqui o tabuleiro atualiza de acordo com as entradas do usuario
        if (valor == 0) {
            tabuleiro[linha - 1][coluna - 1] = '-'; // Zera a célula para '-'
            printf("Número removido!\n");
        } else {
            tabuleiro[linha - 1][coluna - 1] = valor; // Atualiza o tabuleiro sem validação
        }
    } else {
        printf("Tente novamente!\n");
    }
}

int main() {  //aqui é onde toda a magica acontece na sua telinha do terminal.
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
