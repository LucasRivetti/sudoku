#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define RED    "\x1b[31m"
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
void constroiTabuleiro(int tabuleiro[9][9], int fixos[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            tabuleiro[i][j] = 0; // Inicializa todas as células como 0
            fixos[i][j] = 0;     // Inicializa todas as células fixas como 0
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

void preencherTabuleiroInicial(int tabuleiro[9][9], int fixos[9][9], int casasPreenchidas) {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    int preenchidas = 0;

    while (preenchidas < casasPreenchidas) {
        int linha = rand() % 9;
        int coluna = rand() % 9;
        int valor = (rand() % 9) + 1;

        // Verifica se a célula está vazia e se o valor é válido
        if (tabuleiro[linha][coluna] == 0 && posicaoValida(tabuleiro, linha, coluna, valor)) {
            tabuleiro[linha][coluna] = valor;
            fixos[linha][coluna] = 1; // Marca a célula como fixa
            preenchidas++; // vai preenchendo aleatoriamente até chegar no valor estipulado pelas dificuldades.
        }
    }
}

int escolherDificuldade(int *casasPreenchidas) {
    int escolha;
    printf("Escolha a dificuldade:\n");
    printf("1. Fácil (30 casas preenchidas)\n");
    printf("2. Médio (22 casas preenchidas)\n");
    printf("3. Difícil (17 casas preenchidas)\n");
    printf("4. Jogos Pré-Definidos\n");
    printf("Digite a sua escolha (1-4): ");
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
        case 4:
            return 1;
            break;
        default:
            printf("Escolha inválida! Nível 'Fácil' selecionado por padrão.\n");
            *casasPreenchidas = 30;
            break;
    }
    return 0;
}

// Função que escolhe um tabuleiro já definido anteriormente
void lerTabuleiroDeArquivo(const char *nomeArquivo, int tabuleiro[9][9], int fixos[9][9]) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", nomeArquivo);
        return;
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fscanf(arquivo, "%d", &tabuleiro[i][j]);
            if (tabuleiro[i][j] != 0) {
                fixos[i][j] = 1; // Marca a célula como fixa
            } else {
                fixos[i][j] = 0;
            }
        }
    }

    fclose(arquivo);
}

void escolherTabuleiroPreDefinido(int tabuleiro[9][9], int fixos[9][9]) {
    int escolha;
    printf("Escolha um tabuleiro:\n");
    printf("1. Sudoku 1\n");
    printf("2. Sudoku 2\n");
    printf("3. Sudoku 3\n");
    printf("Digite a sua escolha (1-3): ");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            lerTabuleiroDeArquivo("sudoku1.txt", tabuleiro, fixos);
            break;
        case 2:
            lerTabuleiroDeArquivo("sudoku2.txt", tabuleiro, fixos);
            break;
        case 3:
            lerTabuleiroDeArquivo("sudoku3.txt", tabuleiro, fixos);
            break;
        default:
            printf("Escolha inválida! 'Sudoku 1' selecionado por padrão.\n");
            lerTabuleiroDeArquivo("sudoku1.txt", tabuleiro, fixos);
            break;
    }

    // Exibe o tabuleiro selecionado
    printf("Tabuleiro selecionado:\n");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void exibirTabuleiro(int tabuleiro[9][9], int fixos[9][9]) {
    printf("\nTabuleiro atual:\n");
    printf ("  ");
    for (int i = 1; i <= 9; i++) {
        printf ("  %d ", i);
    }
    printf ("\n   ");

    for (int i = 0; i < 9; i++) {
        printf(BLUE "____" RESET);
    }

    for (int i = 0; i < 9; i++) {
        printf("\n%d ", i + 1);
        printf(BLUE "|" RESET);
        for (int j = 0; j < 9; j++) {
            if (tabuleiro[i][j] != 0) {
                if (fixos[i][j]) {
                    printf(RED " %d " RESET, tabuleiro[i][j]);
                } else {
                    printf(" %d ", tabuleiro[i][j]);
                }
            } else {
                printf("   ");
            }
            if ((j + 1) % 3 == 0 || j == 8) {
                printf(BLUE "|" RESET);
            } else {
                printf("|");
            }
        }
        printf(BLUE "\n  |" RESET);
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

// Aqui o usuário se diverte
void jogar(int tabuleiro[9][9], int fixos[9][9]) {
    int linha, coluna, valor;
    printf("Digite a linha (1 a 9): ");
    scanf("%d", &linha);
    printf("Digite a coluna (1 a 9): ");
    scanf("%d", &coluna);
    printf("Digite o valor (1 a 9) ou 0 para apagar: ");
    scanf("%d", &valor);

    if (validarEntrada(linha, coluna, valor)) { // Atualiza o tabuleiro de acordo com as entradas do usuário
        if (fixos[linha - 1][coluna - 1]) {
            printf("Não é permitido modificar números fixos!\n");
        } else {
            if (valor == 0) {
                tabuleiro[linha - 1][coluna - 1] = 0; // Zera a célula para 0
                printf("Número removido!\n");
            } else {
                // Atualiza o tabuleiro sem validação para regras
                tabuleiro[linha - 1][coluna - 1] = valor;
            }
        }
    } else {
        printf("Tente novamente!\n");
    }
}

int casasPreenchidas(int tabuleiro[9][9]) {
    int preenchidas = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (tabuleiro[i][j] != 0) { // Verifica se a célula está preenchida
                preenchidas++;
            }
        }
    }
    return preenchidas;
}

int jogoAcabou(int tabuleiro[9][9]) { // Confere se todas as casas estão completas
    if (casasPreenchidas(tabuleiro) == 81) {
        return 1;  // Jogo acabou.
    }
    return 0;  // Jogo não acabou.
}

int verificarTabuleiro(int tabuleiro[9][9]) { // Verificação final do tabuleiro
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int valor = tabuleiro[i][j];
            if (!verificarLinha(tabuleiro, i, j, valor) ||
                !verificarColuna(tabuleiro, i, j, valor) ||
                !verificarQuadrante(tabuleiro, i, j, valor)) {
                return 0;  // Tabuleiro incorreto
            }
        }
    }
    return 1;  // Tabuleiro está correto
}

void decisaoFinal(int tabuleiro[9][9], int fixos[9][9]) {
    int decisao;
    printf("\nVocê preencheu todas as casas! Escolha o próximo caminho:\n");
    printf("1. Conferir tabuleiro e finalizar o jogo\n");
    printf("2. Ter mais 10 jogadas extras antes de conferir\n");
    printf("Digite sua escolha (1-2): ");
    scanf("%d", &decisao);

    switch (decisao) {
        case 1:
            if (verificarTabuleiro(tabuleiro)) {
                printf("\nParabéns! O tabuleiro está correto.\n");
            } else {
                printf("\nO tabuleiro está incorreto.\n");
            }
            break;
        case 2: {
            int jogadas = 0;
            while (jogadas < 10) {
                exibirTabuleiro(tabuleiro, fixos);
                jogar(tabuleiro, fixos);
                jogadas++;

                if (jogadas < 10) {
                    char continuar;
                    printf("Você já fez %d jogadas, deseja continuar? (S/N): ", jogadas);
                    getchar(); // Limpa o buffer antes de capturar a resposta pra evitar erros 
                    scanf("%c", &continuar);

                    if (continuar == 'N' || continuar == 'n') {
                        break;
                    }
                }
            }

            if (verificarTabuleiro(tabuleiro)) {
                printf("\nParabéns! O tabuleiro está correto.\n");
            } else {
                printf("\nO tabuleiro está incorreto.\n");
            }
            break;
        }
        default:
            printf("Escolha inválida! Opção 1 selecionada por padrão.\n");
            if (verificarTabuleiro(tabuleiro)) {
                printf("\nParabéns! O tabuleiro está correto.\n");
            } else {
                printf("\nO tabuleiro está incorreto.\n");
            }
            break;
    }
}


void salvarTop3Jogadores(Jogador jogador) {
    Jogador top3[3];
    FILE *arquivo = fopen("Top3Jogadores.txt", "r");

    for (int i = 0; i < 3; i++) { //inicialização dos valores
        strcpy(top3[i].nome, "...");
        top3[i].tempoGasto = 999999999;
    }

    if (arquivo != NULL) {
        for (int i = 0; i < 3; i++) {
            fscanf(arquivo, "%s %lf", top3[i].nome, &top3[i].tempoGasto);
        }
        fclose(arquivo);
    }

    // jogador deve ser incluido na classificação caso o tempo seja melhor
    for (int i = 0; i < 3; i++) {
        if (jogador.tempoGasto < top3[i].tempoGasto) {
            // se for melhor que um ja presente, passa esse jogador para baixo no ranking.
            for (int j = 2; j > i; j--) {
                top3[j] = top3[j - 1];
            }
            top3[i] = jogador;
            break;
        }
    }

    // salvamento do arquivo
    arquivo = fopen("Top3Jogadores.txt", "w");
    for (int i = 0; i < 3; i++) {
        fprintf(arquivo, "%s %.2f\n", top3[i].nome, top3[i].tempoGasto);
    }
    fclose(arquivo);
}

void exibirLeaderboard() {
    Jogador top3[3];
    FILE *arquivo = fopen("Top3Jogadores.txt", "r");
    printf("\n***********************************\n");
    printf("***Leaderboard - Top 3 Jogadores***\n");
    printf("***********************************\n");
    if (arquivo == NULL) {
        printf("Nenhum recorde disponível ainda.\n");
    } else {
        for (int i = 0; i < 3; i++) {
            fscanf(arquivo, "%s %lf", top3[i].nome, &top3[i].tempoGasto);
            printf("%d. %s - Tempo: %.2f segundos\n", i + 1, top3[i].nome, top3[i].tempoGasto);
        }
        fclose(arquivo);
    }
}

int main() { // Aqui é onde toda a mágica acontece na sua telinha do terminal.
  Jogador jogador;
    time_t tempoInicio, tempoFim;
    int tabuleiro[9][9];
    int fixos[9][9];
    int casasPreenchidas;

    iniciarJogo(&jogador);
    if (escolherDificuldade(&casasPreenchidas)) {
        escolherTabuleiroPreDefinido(tabuleiro, fixos);
    } else {        
        constroiTabuleiro(tabuleiro, fixos);
        preencherTabuleiroInicial(tabuleiro, fixos, casasPreenchidas);
    }

    time(&tempoInicio);

    while (!jogoAcabou(tabuleiro)) {
        exibirTabuleiro(tabuleiro, fixos);
        jogar(tabuleiro, fixos);
    }

    time(&tempoFim);

    jogador.tempoGasto = difftime(tempoFim, tempoInicio);

    // Quando todas as casas estiverem preenchidas, perguntar o que o jogador deseja fazer
    decisaoFinal(tabuleiro, fixos);

    exibirTabuleiro(tabuleiro, fixos);

    if (verificarTabuleiro(tabuleiro) == 1) {
        printf("\nParabéns %s! Você completou corretamente o desafio do Sudoku!\n", jogador.nome);
        printf("Tempo gasto: %.2f segundos\n", jogador.tempoGasto);
        
        salvarTop3Jogadores(jogador);
        exibirLeaderboard();
    } else {
        printf("\nSeu jogo não está correto.\n");
        printf("Tempo gasto: %.2f segundos\n", jogador.tempoGasto);
    }

    return 0;
}