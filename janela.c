#include "raylib.h"
#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "janela.h"

int Contador = 0;//Contador de quantas comidas foram pegas (Criei momentaneamente de forma global mas depois pretendo mudar)

void Reset_score(){
    Contador = 0;
}

void Increase_score(){
    Contador++;
}
