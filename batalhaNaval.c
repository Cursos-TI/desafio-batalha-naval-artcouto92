#include <stdio.h>
#include <stdlib.h>

int main() {
    int tabuleiro[10][10];         // Tabuleiro 10x10
    int navioHV[3] = {3, 3, 3};    // Navios horizontais/verticais
    int navioDiag[3] = {3, 3, 3};  // Navios diagonais
    int i, j;

    // -----------------------------
    // Inicializa o tabuleiro com 0 (água)
    // -----------------------------
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // -----------------------------
    // Coordenadas iniciais dos navios
    // -----------------------------
    int linhaH = 1, colunaH = 2;   // Navio horizontal
    int linhaV = 5, colunaV = 7;   // Navio vertical
    int linhaD1 = 0, colunaD1 = 0; // Navio diagonal descendente
    int linhaD2 = 7, colunaD2 = 2; // Navio diagonal ascendente

    // -----------------------------
    // Posiciona todos os navios
    // -----------------------------
    for (i = 0; i < 3; i++) {
        // Navio horizontal
        if (colunaH + i < 10)
            tabuleiro[linhaH][colunaH + i] = navioHV[i];

        // Navio vertical
        if (linhaV + i < 10)
            tabuleiro[linhaV + i][colunaV] = navioHV[i];

        // Navio diagonal descendente (\)
        if (linhaD1 + i < 10 && colunaD1 + i < 10)
            tabuleiro[linhaD1 + i][colunaD1 + i] = navioDiag[i];

        // Navio diagonal ascendente (/)
        if (linhaD2 - i >= 0 && colunaD2 + i < 10)
            tabuleiro[linhaD2 - i][colunaD2 + i] = navioDiag[i];
    }

    // -----------------------------
    // Definição das habilidades (matrizes 5x5)
    // -----------------------------
    int cone[5][5] = {0};     // Cone apontando para baixo
    int cruz[5][5] = {0};     // Cruz
    int octaedro[5][5] = {0}; // Octaedro (losango)

    // -----------------------------
    // Preenche a matriz cone
    // -----------------------------
    for (i = 0; i < 5; i++) {         // linha
        for (j = 0; j < 5; j++) {     // coluna
            if (i >= 0 && j >= 2 - i && j <= 2 + i) {
                cone[i][j] = 1;       // Área afetada
            }
        }
    }

    // -----------------------------
    // Preenche a matriz cruz
    // -----------------------------
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (i == 2 || j == 2) {   // linha ou coluna do centro
                cruz[i][j] = 1;
            }
        }
    }

    // -----------------------------
    // Preenche a matriz octaedro (losango)
    // -----------------------------
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (abs(i - 2) + abs(j - 2) <= 2) {
                octaedro[i][j] = 1;
            }
        }
    }

    // -----------------------------
    // Ponto de origem das habilidades no tabuleiro
    // -----------------------------
    int origemConeLinha = 2, origemConeColuna = 2;
    int origemCruzLinha = 6, origemCruzColuna = 5;
    int origemOctaedroLinha = 4, origemOctaedroColuna = 7;

    // -----------------------------
    // Sobrepõe o cone no tabuleiro
    // -----------------------------
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            int linhaTab = origemConeLinha - 2 + i;
            int colTab = origemConeColuna - 2 + j;
            if (linhaTab >= 0 && linhaTab < 10 && colTab >= 0 && colTab < 10) {
                if (cone[i][j] == 1 && tabuleiro[linhaTab][colTab] == 0)
                    tabuleiro[linhaTab][colTab] = 5; // Marca área afetada
            }
        }
    }

    // -----------------------------
    // Sobrepõe a cruz no tabuleiro
    // -----------------------------
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            int linhaTab = origemCruzLinha - 2 + i;
            int colTab = origemCruzColuna - 2 + j;
            if (linhaTab >= 0 && linhaTab < 10 && colTab >= 0 && colTab < 10) {
                if (cruz[i][j] == 1 && tabuleiro[linhaTab][colTab] == 0)
                    tabuleiro[linhaTab][colTab] = 5;
            }
        }
    }

    // -----------------------------
    // Sobrepõe o octaedro no tabuleiro
    // -----------------------------
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            int linhaTab = origemOctaedroLinha - 2 + i;
            int colTab = origemOctaedroColuna - 2 + j;
            if (linhaTab >= 0 && linhaTab < 10 && colTab >= 0 && colTab < 10) {
                if (octaedro[i][j] == 1 && tabuleiro[linhaTab][colTab] == 0)
                    tabuleiro[linhaTab][colTab] = 5;
            }
        }
    }

    // -----------------------------
    // Exibe o tabuleiro final
    // -----------------------------
    printf("=== Tabuleiro Batalha Naval com Habilidades ===\n\n");
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
