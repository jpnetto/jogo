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
    const int T = 10; 
    const int W = j->largura;
    const int H = j->altura;

    // j->obstaculosMapa1[0].pos = (Rectangle) {H/3, W/3, W - W/3, T};
    j->obstaculosMapa1[0].pos = (Rectangle) {W - T, 0, T, H};
    // j->obstaculosMapa1[2].pos = (Rectangle) {0, H - T, W, T};
    j->obstaculosMapa1[1].pos = (Rectangle) {0, 0, T, H};

    const int CX = W / 2;     
    const int CY = H / 2;    
    const int GAP = 50;       

    j->obstaculosMapa1[2].pos = (Rectangle) {
        290,         
        10,                
        80,                
        CY - 40 
    };
    
    j->obstaculosMapa1[3].pos = (Rectangle) {
        CX - T,         
        CY + GAP/2 + 40,       
        40,               
        H - CY - GAP/2,
    };
    
    // j->obstaculosMapa1[4].pos = (Rectangle) {
    //     T,                
    //     CY - T/2,         
    //     CX - T - GAP/2 - 40,   
    //     T                 
    // };
    
    // j->obstaculosMapa1[5].pos = (Rectangle) {
    //     CX + GAP/2 + 40,      
    //     CY - T/2,         
    //     W - CX - GAP/2,
    //     T                 
    // };
}
void IniciaObstaculosMapa2(Jogo* j){
    //Obstaculos de cima
    j->obstaculosMapa0[0].pos = (Rectangle) {0, 0, j->largura, 10};
    //Obstaculos da direita
    j->obstaculosMapa0[1].pos = (Rectangle) {j->largura - 10, 0, 10, j->altura};
    //Obstaculos de baixo
    j->obstaculosMapa0[2].pos = (Rectangle) {0, j->altura - 10, j->largura, 10};
    //Obstaculos da esquerda
    j->obstaculosMapa0[3].pos = (Rectangle) {0, 0, 10, j->altura};

}


void DesenhaObstaculosMapa0(Jogo* j){
    for (int i = 0; i < 4; i++){
        DrawRectangleRec(j->obstaculosMapa0[i].pos, DARKPURPLE);
    }
}

void DesenhaObstaculosMapa1(Jogo* j){
    for(int i=0; i<8; i++){
        DrawRectangleRec(j->obstaculosMapa1[i].pos, WHITE);
    }
}

void DesenhaObstaculosMapa2(Jogo* j){
    for(int i=0; i<8; i++){
        DrawRectangleRec(j->obstaculosMapa2[i].pos, BLUE);
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
    if((j->map==0)&&(j->body.size>2)){
        for(int i=0; i<4; i++){
            if(CheckCollisionRecs(j->body.head->pos, j->obstaculosMapa0[i].pos)){
            return 1;
            }
        }
    }
    return 0;
}

int ColisaoObstaculosMapa1(Jogo* j){
    if((j->map==1)&&(j->body.size>2)){
        for(int i=0; i<8; i++){
            if(CheckCollisionRecs(j->body.head->pos, j->obstaculosMapa1[i].pos)){
            return 1;
            }
        }   
    }
    return 0;
}

int ColisaoObstaculosMapa2(Jogo* j){
    if((j->map==2)&&(j->body.size>2)){
        for(int i=0; i<10; i++){
            if(CheckCollisionRecs(j->body.head->pos, j->obstaculosMapa2[i].pos)){
            return 1;
            }
        }   
    }
    return 0;
}


