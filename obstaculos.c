#include "raylib.h"
#include "snake.h"
#include "obstaculos.h"

void IniciaObstaculos(Jogo *j){
    if(j->map==0){
        IniciaObstaculosMapa0(j);
    }
    /*
    else if(j->map==1){
        IniciaObstaculosMapa1(j);
    }
    else if(j->map==2){
        IniciaObstaculosMapa2(j);
    }*/
}

void DesenhaObstaculos(Jogo* j){
    if(j->map==0){
        DesenhaObstaculosMapa0(j);
    }
    /*
    else if(j->map==1){
        DesenhaObstaculosMapa1(j);
    }
    else if(j->map==2){
        DesenhaObstaculosMapa2(j);
    }*/
}

void IniciaObstaculosMapa0(Jogo* j){
    //Obstaculos de cima
    j->obstaculosLaterais[0].pos = (Rectangle) {0, 0, j->largura, 20};
    //Obstaculos da direita
    j->obstaculosLaterais[1].pos = (Rectangle) {j->largura - 20, 0, 20, j->altura};
    //Obstaculos de baixo
    j->obstaculosLaterais[2].pos = (Rectangle) {0, j->altura - 20, j->largura, 20};
    //Obstaculos da esquerda
    j->obstaculosLaterais[3].pos = (Rectangle) {0, 0, 20, j->altura};
}
/*
void IniciaObstaculosMapa1(Jogo* j){
}
void IniciaObstaculosMapa2(Jogo* j){
}
*/

void DesenhaObstaculosMapa0(Jogo* j){
    for (int i = 0; i < 4; i++){
            DrawRectangleRec(j->obstaculosLaterais[i].pos, DARKPURPLE);
        }
}
/*
void DesenhaObstaculosMapa1(Jogo* j){
}
void DesenhaObstaculosMapa2(Jogo* j){
}
*/

