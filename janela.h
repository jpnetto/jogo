#ifndef JANELA
#define JANELA
#include "raylib.h"
#include "snake.h"

void Reset_score(Jogo*);

void Increase_score(Jogo*);

void Size_map(Jogo*);

void Size_cursor(Rectangle* selection, int a, int b, int c, int d);

void Death_message(Jogo*);

int Menu_screen(Jogo*);

void Startgame(Jogo*j);

void Choose_of_map(Jogo* j);

void Options_screen(Jogo* j);

void Draw_Backgound(Jogo* j);

void Ranking_screen(Jogo* j);

#endif
