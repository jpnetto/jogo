#ifndef SNAKE_H
#define SNAKE_H

typedef struct Bordas{
    Rectangle pos;
}Bordas;

typedef struct Body{
    Rectangle pos;
    Color color;
    int direcao;
}Body;

typedef struct Food{
    Rectangle pos;
    Color color;
}Food;

typedef struct Jogo{
    Body body;
    Food food;
    Bordas bordas[4];
    double tempo;
    double cooldown;
}Jogo;


void IniciaBody(Jogo *j);
void IniciaBordas(Jogo *j);
void IniciaFood(Jogo *j);
void IniciaJogo(Jogo *j);
void DesenhaBody(Jogo *j);
void DesenhaFood(Jogo *j);
void DesenhaBordas(Jogo *j);
void DesenhaJogo(Jogo *j);
void AtualizaDirecao(Jogo *j);
void AtualizaPosBody(Jogo *j);
void AtualizaRodada(Jogo *j);
void AtualizaLocalFood(Jogo *j);
int ColisaoFood(Jogo *j);
int ColisaoBordas(Jogo *j);


#endif