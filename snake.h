#ifndef SNAKE_H
#define SNAKE_H
#include "raylib.h"

#define STD_SIZE_X 40
#define STD_SIZE_Y 40
#define TEMPO 0.2
#define COOLDOWN 0.2
#define SNAKE_COLOR BLACK
#define FOOD_COLOR RED


typedef struct Bordas{
    Rectangle pos;
}Bordas;

typedef struct Obstaculos{
    Rectangle pos;
    Texture2D texturaVertical;
    Texture2D texturaHorizontal;
    Texture2D texturaQuadrado;

}Obstaculos;

typedef struct Food{
    Rectangle pos;
    Color color;
    Texture texture[6];
}Food;

// Estruturas novas/atualizadas
typedef struct Block{
    Rectangle pos;
    Color color;
    struct Block *prox;
    int direcao;
} Block;

typedef struct Body{
    Block *head;
    Block *tail;
    int direcao;
    int size;
    Color color;
    Texture texture[4];
} Body;

typedef struct TrilhaSonora{
    Sound colisaoCorpo;
    Sound colisaoFruta;
    Music musica;
} TrilhaSonora;


typedef struct Jogo{
    int largura;
    int altura;
    Body body;
    Bordas bordas[4];
    Food food;
    double tempo;
    double cooldown;
    int contador;
    TrilhaSonora trilhaSonora;
    int map;
    char name_player[16];
    
    Obstaculos obstaculosMapa0[4];
    Obstaculos obstaculosMapa1[4];
    Obstaculos obstaculosMapa2[16];
    
    Texture2D fundo[10];
} Jogo;


void IniciaBordas(Jogo *j);
void IniciaFood(Jogo *j);
void DesenhaBordas(Jogo *j);
void DesenhaFood(Jogo *j);
void AtualizaLocalFood(Jogo *j);
void DesenhaJogo(Jogo *j);
void AtualizaDirecao(Jogo *j);

// Funções novas
void AtualizaHead(Jogo* j,Body *body, float x, float y);
void RemoveCauda(Body *body);
void IniciaTrilhaSonora(Jogo* j);
void AtualizaMusica(Jogo *j);
void FinalizaTrilhaSonora(Jogo* j);
void FinalizaCobra(Jogo* j);
void Draw_Backgound(Jogo*);
// Funções muito modificadas
void IniciaJogo(Jogo *j);
void AtualizaDirecao(Jogo *j);
void AtualizaPosBody(Jogo *j);
void AtualizaRodada(Jogo *j);
int ColisaoBordas(Jogo *j);

// Funções atualizadas
int ColisaoFood(Jogo *j);
int ColisaoBody(Jogo *j);
int ColisaoFoodObstaculo(Jogo *j, float x, float y);

void IniciaTexturasBody(Jogo* j);
void IniciaTexturasMap(Jogo* j);
void IniciaTexturasObstaculos(Jogo* j);


void Unload_textures(Jogo*);

#endif