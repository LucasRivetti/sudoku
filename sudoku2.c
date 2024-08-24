#include<stdio.h>
int VerificarLinhas (int Tabuleiro[9][9]) {
    for (int A = 0; A < 9; A++) {
        int Num_Linha[10] = {0};
        for (int B = 0; B < 9; B++) {
            if (Tabuleiro[A][B] != 0 && Tabuleiro[A][B] != '-') {
                return 0;
            } else {
                Num_Linha[Tabuleiro[A][B]]++;
            }
        }
    }
    return 1;
}
int VerificarColunas (int Tabuleiro[9][9]) {
    for (int A = 0; A < 9; A++) {
        int N_Coluna[10] = {0};
        for (int B = 0; B < 9; B++) {
            if (Tabuleiro[B][A] != 0 && Tabuleiro[B][A] != '-') {
                return 0;
            } else {
                Num_Coluna[Tabuleiro[B][A]]++;
            }
        }
    }
    return 1;
}
int VerificarQuadrantes (int tabuleiro[9][9]) {
    for (int A = 0; A < 9; A += 3) {
        for (int B = 0; B < 9; B += 3) {
            int N_Quadrante[10] = {0};
            for (int C = 0; C < 3; C++) {
                for (int D = 0; D < 3; D++) {
                    if (N_Quadrante[tabuleiro[A + C][B + D]] != 0 && tabuleiro[A + C][B + D] != '-') {
                        return 0;
                    } else {
                        N_Quadrante[tabuleiro[A + C][B + D]]++;
                    }
                }
            }
        }
    }
    return 1;
}