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
    j->obstaculosLaterais[0].pos = (Rectangle) {0, 0, j->largura, 10};
    //Obstaculos da direita
    j->obstaculosLaterais[1].pos = (Rectangle) {j->largura - 10, 0, 10, j->altura};
    //Obstaculos de baixo
    j->obstaculosLaterais[2].pos = (Rectangle) {0, j->altura - 10, j->largura, 10};
    //Obstaculos da esquerda
    j->obstaculosLaterais[3].pos = (Rectangle) {0, 0, 10, j->altura};
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

int ColisaoObstaculos(Jogo* j){
    if(ColisaoObstaculosMapa0(j)){
        PlaySound(j->trilhaSonora.colisaoCorpo);
        return 1;
    }
    /*
    else if(ColisaoObstaculosMapa1(j)){
        return 1;
    }
    else if(ColisaoObstaculosMapa2(j)){
        return 1;
    }
    */
    return 0;
}

int ColisaoObstaculosMapa0(Jogo* j){
    if((j->map==0)&&(j->body.size>2)){
        if(CheckCollisionRecs(j->body.head->pos, j->obstaculosLaterais[0].pos)){
            return 1;
        }
        else if (CheckCollisionRecs(j->body.head->pos, j->obstaculosLaterais[1].pos)){
            return 1;
        }
        else if (CheckCollisionRecs(j->body.head->pos, j->obstaculosLaterais[2].pos)){
            return 1;
        }
        else if(CheckCollisionRecs(j->body.head->pos, j->obstaculosLaterais[3].pos)){
            return 1;
        }
    }
    return 0;
}


