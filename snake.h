#ifndef SNAKE_H
#define SNAKE_H
#include "raylib.h"

typedef struct Bordas{
    Rectangle pos;
}Bordas;

typedef struct Food{
    Rectangle pos;
    Color color;
}Food;

// Estruturas novas/atualizadas
typedef struct Block{
    Rectangle pos;
    Color color;
    struct Block *prox;
} Block;

typedef struct Body{
    Block *head;
    Block *tail;
    int direcao;
    int size;
    Color color;
} Body;

typedef struct Jogo{
    Body body;
    Bordas bordas[4];
    Food food;
    double tempo;
    double cooldown;
} Jogo;


void IniciaBordas(Jogo *j);
void IniciaFood(Jogo *j);
void DesenhaBordas(Jogo *j);
void DesenhaFood(Jogo *j);
void AtualizaLocalFood(Jogo *j);
void DesenhaJogo(Jogo *j);
void AtualizaDirecao(Jogo *j);

// Funções novas
void AtualizaHead(Body *body, float x, float y);
void RemoveCauda(Body *body);

// Funções muito modificadas
void IniciaJogo(Jogo *j);
void AtualizaDirecao(Jogo *j);
void AtualizaPosBody(Jogo *j);
void AtualizaRodada(Jogo *j);

// Funções atualizadas
int ColisaoFood(Jogo *j);
int ColisaoBordas(Jogo *j);



#endif