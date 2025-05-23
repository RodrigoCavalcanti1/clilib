#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "timer.h"
#include "screen.h"
#include "snake.h"
#include "score.h"
#include "keyboard.h"

#define MAX_LENGTH 100

typedef struct {
    int x, y;
} Position;

static Position cobra[MAX_LENGTH];
static int tamanho;
static int dir; // 0=cima, 1=direita, 2=baixo, 3=esquerda
static int foodX, foodY;
static int gameOver = 0;

void snakeInit() {
    tamanho = 3;
    for (int i = 0; i < tamanho; i++) {
        cobra[i].x = 40 - i;
        cobra[i].y = 12;
    }
    dir = 1; // direita
    gameOver = 0;

    srand(time(NULL));
    foodX = 10 + rand() % 60;
    foodY = 5 + rand() % 15;
}

void snakeHandleInput(char tecla) {
    if (tecla == 'w' && dir != 2) dir = 0;
    else if (tecla == 'd' && dir != 3) dir = 1;
    else if (tecla == 's' && dir != 0) dir = 2;
    else if (tecla == 'a' && dir != 1) dir = 3;
}

void snakeUpdate() {
    Position novaCabeca = cobra[0];

    if (dir == 0) novaCabeca.y--;
    else if (dir == 1) novaCabeca.x++;
    else if (dir == 2) novaCabeca.y++;
    else if (dir == 3) novaCabeca.x--;

    // Verifica colisão com parede
    if (novaCabeca.x <= 0 || novaCabeca.x >= 80 || novaCabeca.y <= 0 || novaCabeca.y >= 24) {
        gameOver = 1;
        return;
    }

    // Move o corpo
    for (int i = tamanho; i > 0; i--) {
        cobra[i] = cobra[i - 1];
    }
    cobra[0] = novaCabeca;

    // Verifica colisão com o próprio corpo (começando do i = 1)
    for (int i = 1; i < tamanho; i++) {
        if (cobra[i].x == cobra[0].x && cobra[i].y == cobra[0].y) {
            gameOver = 1;
            return;
        }
    }

    // Verifica se comeu comida
    if (novaCabeca.x == foodX && novaCabeca.y == foodY) {
        tamanho++;
        scoreAdd(10);
        foodX = 5 + rand() % 70;
        foodY = 3 + rand() % 20;
    } else {
        if (tamanho > MAX_LENGTH) tamanho = MAX_LENGTH;
    }
}

void snakeRender() {
    screenClear();
    screenGotoxy(foodX, foodY);
    printf("@");

    for (int i = 0; i < tamanho; i++) {
        screenGotoxy(cobra[i].x, cobra[i].y);
        printf("#");
    }

    screenGotoxy(1, 1);
    printf("Pontos: %d", scoreGet());
    screenUpdate();
}

int snakeGameOver() {
    return gameOver;
}

void snakeMenu() {
    char option = 0;
    do {
        screenClear();
        screenGotoxy(34, 10);
        printf("SNAKE GAME");
        screenGotoxy(34, 12);
        printf("1. Play");
        screenGotoxy(34, 13);
        printf("2. Ranking");
        screenGotoxy(34, 14);
        printf("3. Exit");
        screenUpdate();

        option = readch();

        if (option == '2') {
            screenClear();
            scorePrintRanking();
            screenGotoxy(30, 23);
            printf("Press any key to return...");
            readch();
        }

    } while (option != '1' && option != '3');

    if (option == '3') {
        exit(0);
    }
}
