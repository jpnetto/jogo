#ifndef RANKING
#define RANKING
#include "raylib.h"
#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    char nome[50];
    int pontos;
} Jogadores;

void criaRanking();
void insereRanking(char *nome, int pontos);
void exibeRanking();
void ordenaRanking();

#endif