#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "score.h"

static int pontos = 0;

void scoreInit() {
    pontos = 0;
}

void scoreAdd(int valor) {
    pontos += valor;
}

int scoreGet() {
    return pontos;
}

void scoreSave() {
    FILE* f = fopen("ranking.txt", "a");
    if (f) {
        fprintf(f, "%d\n", pontos);
        fclose(f);
    }
}

void scorePrintRanking() {
    FILE* f = fopen("ranking.txt", "r");
    if (!f) {
        printf("Sem ranking disponível.\n");
        return;
    }
    printf("\nRanking de Pontuação:\n----------------------\n");
    int i = 1, p;
    while (fscanf(f, "%d", &p) != EOF && i <= 5) {
        printf("%dº - %d pontos\n", i++, p);
    }
    fclose(f);
}
