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
} Jogador;

void exibeRanking(FILE* f);
void criaRanking();
void adicionaRanking();
void insereRanking(Jogador jogadores[], int n);
int Ranking_screen(Jogo* j);

#endif