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

typedef struct ObstaculosRetangulares{
    Rectangle pos;
}ObstaculosRetangulares;

typedef struct ObstaculosRedondos{
    Vector2 pos;    
    float raio;
}ObstaculosRedondos;

typedef struct Obstaculos{
    ObstaculosRedondos c[10];
    ObstaculosRetangulares r[10];
}Obstaculos;


typedef struct Food{
    Rectangle pos;
    Color color;
    Texture texture;
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

typedef struct TexturaObstaculos{
    Texture2D r;
    Texture2D c;
}TexturaObstaculos;

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
    
    ObstaculosRetangulares obstaculosMapa0[4];
    ObstaculosRetangulares obstaculosMapa1[4];
    Obstaculos obstaculosMapa2;
    
    TexturaObstaculos textObstaculo;
    Texture2D fundoMap[2];
    Texture2D fundo;
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

void Unload_textures(Jogo*);

#endif