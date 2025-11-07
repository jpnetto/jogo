#include "raylib.h"
#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "janela.h"

void Reset_score(Jogo* j){
    j->contador = 0;
}

void Increase_score(Jogo* j){
    j->contador++;
}
