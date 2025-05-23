
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "snake.h"
#include "score.h"

void snakeMenu();  // Declaração explícita da função

int main() {
    screenInit(1);        // bordas ativadas
    screenHideCursor();
    keyboardInit();
    timerInit(150);       // delay da cobra

    snakeMenu();          // menu inicial

    snakeInit();
    scoreInit();

    while (!snakeGameOver()) {
        if (timerTimeOver()) {
            snakeUpdate();
            snakeRender();
            timerUpdateTimer(150);
        }
        if (keyhit()) {
            char tecla = readch();
            snakeHandleInput(tecla);
        }
    }

    screenClear();
    screenGotoxy(30, 12);
    printf("Game Over! Pontos: %d\n", scoreGet());
    scoreSave();
    scorePrintRanking();

    screenSetNormal();
    screenShowCursor();
    screenDestroy();
    keyboardDestroy();
    timerDestroy();
    return 0;
}
