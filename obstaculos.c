#include "raylib.h"
#include "snake.h"
#include "obstaculos.h"

void IniciaObstaculos(Jogo *j){
    if(j->map==0){
        IniciaObstaculosMapa0(j);
    }
    
    else if(j->map==1){
        IniciaObstaculosMapa1(j);
    }
    else if(j->map==2){
        IniciaObstaculosMapa2(j);
    }
}

void DesenhaObstaculos(Jogo* j){
    if(j->map==0){
        DesenhaObstaculosMapa0(j);
    }
    else if(j->map==1){
        DesenhaObstaculosMapa1(j);
    }
    else if(j->map==2){
        DesenhaObstaculosMapa2(j);
    }
}

void IniciaObstaculosMapa0(Jogo* j){
    //Obstaculos de cima
    j->obstaculosMapa0[0].pos = (Rectangle) {0, 0, j->largura, 10};
    //Obstaculos da direita
    j->obstaculosMapa0[1].pos = (Rectangle) {j->largura - 10, 0, 10, j->altura};
    //Obstaculos de baixo
    j->obstaculosMapa0[2].pos = (Rectangle) {0, j->altura - 10, j->largura, 10};
    //Obstaculos da esquerda
    j->obstaculosMapa0[3].pos = (Rectangle) {0, 0, 10, j->altura};
}

void IniciaObstaculosMapa1(Jogo* j){
    j->obstaculosMapa1[0].pos = (Rectangle) {j->largura / 4, 0, 10, j->altura * 0.75f}; 
    
    // Parede Vertical Direita (Aproximadamente 3/4 da largura)
    j->obstaculosMapa1[1].pos = (Rectangle) {j->largura * 0.75f, j->altura * 0.25f, 10, j->altura * 0.75f};
    
    // Parede Horizontal Superior (No centro superior)
    j->obstaculosMapa1[2].pos = (Rectangle) {j->largura / 4, j->altura / 4, j->largura / 2, 10};
    
    // Bloco Central (Pequeno bloco isolado)
    j->obstaculosMapa1[3].pos = (Rectangle) {j->largura / 2 - 10, j->altura / 2 - 10, 20, 20};
}

void IniciaObstaculosMapa2(Jogo* j){
    float espessura_tronco = 10.0f; 
    float margem = 0.10f; 
    
    j->obstaculosMapa2[0].pos = (Rectangle) {
        j->largura * margem, 
        0, 
        espessura_tronco,
        j->altura * 0.90f 
    }; 
    
    j->obstaculosMapa2[1].pos = (Rectangle) {
        j->largura * 0.35f, 
        j->altura * 0.10f, 
        espessura_tronco,
        j->altura * 0.80f 
    }; 
    
    j->obstaculosMapa2[2].pos = (Rectangle) {
        j->largura * 0.65f, 
        0, 
        espessura_tronco,
        j->altura * 0.90f 
    };
    
    j->obstaculosMapa2[3].pos = (Rectangle) {
        j->largura * (1.0f - margem) - espessura_tronco, 
        j->altura * 0.10f, 
        espessura_tronco,
        j->altura * 0.80f 
    };

    j->obstaculosMapa2[4].pos = (Rectangle) {
        j->largura * 0.10f, 
        j->altura * 0.05f, 
        j->largura * 0.15f, 
        espessura_tronco
    };

    j->obstaculosMapa2[5].pos = (Rectangle) {
        j->largura * 0.75f, 
        j->altura * 0.90f, 
        j->largura * 0.15f, 
        espessura_tronco
    };

}




void DesenhaObstaculosMapa0(Jogo* j){
    for (int i = 0; i < 4; i++){
        DrawRectangleRec(j->obstaculosMapa0[i].pos, ORANGE);
    }
}

void DesenhaObstaculosMapa1(Jogo* j){
    for(int i=0; i<8; i++){
        DrawRectangleRec(j->obstaculosMapa1[i].pos, DARKBLUE);
    }
}

void DesenhaObstaculosMapa2(Jogo* j){
    for(int i=0; i<8; i++){
        DrawRectangleRec(j->obstaculosMapa2[i].pos, BLACK);
    }
}


int ColisaoObstaculos(Jogo* j){
    if(ColisaoObstaculosMapa0(j)){
        PlaySound(j->trilhaSonora.colisaoCorpo);
        return 1;
    }
    else if(ColisaoObstaculosMapa1(j)){
        PlaySound(j->trilhaSonora.colisaoCorpo);
        return 1;
    }
    else if(ColisaoObstaculosMapa2(j)){
        PlaySound(j->trilhaSonora.colisaoCorpo);
        return 1;
    }
    return 0;
}

int ColisaoObstaculosMapa0(Jogo* j){
    if(j->map==0){
        for(int i=0; i<4; i++){
            if(CheckCollisionRecs(j->body.head->pos, j->obstaculosMapa0[i].pos)){
            return 1;
            }
        }
    }
    return 0;
}

int ColisaoObstaculosMapa1(Jogo* j){
    if(j->map==1){
        for(int i=0; i<8; i++){
            if(CheckCollisionRecs(j->body.head->pos, j->obstaculosMapa1[i].pos)){
            return 1;
            }
        }   
    }
    return 0;
}

int ColisaoObstaculosMapa2(Jogo* j){
    if(j->map==2){
        for(int i=0; i<10; i++){
            if(CheckCollisionRecs(j->body.head->pos, j->obstaculosMapa2[i].pos)){
            return 1;
            }
        }   
    }
    return 0;
}


