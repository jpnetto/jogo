#ifndef OBSTACULOS_H
#define OBSTACULOS_H
#include "snake.h"

void IniciaObstaculos(Jogo* j);
void DesenhaObstaculos(Jogo* j);
int ColisaoObstaculos(Jogo* j);

void IniciaObstaculosMapa0(Jogo* j);
void IniciaObstaculosMapa1(Jogo* j);
void IniciaObstaculosMapa2(Jogo* j);

void DesenhaObstaculosMapa0(Jogo* j);
void DesenhaObstaculosMapa1(Jogo* j);
void DesenhaObstaculosMapa2(Jogo* j);

int ColisaoObstaculosMapa0(Jogo* j);
int ColisaoObstaculosMapa1(Jogo* j);
int ColisaoObstaculosMapa2(Jogo* j);

#endif