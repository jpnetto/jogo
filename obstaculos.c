#include "raylib.h"
#include "raymath.h"
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
    float espessura = 10.0f; 
    
    j->obstaculosMapa1[0].pos = (Rectangle) {
        j->largura / 4, 
        0, 
        espessura, 
        j->altura * 0.75f
    }; 
    
    j->obstaculosMapa1[1].pos = (Rectangle) {
        j->largura * 0.75f, 
        j->altura * 0.25f, 
        espessura, 
        j->altura * 0.75f
    };
    
    j->obstaculosMapa1[2].pos = (Rectangle) {
        j->largura / 4, 
        j->altura / 4, 
        j->largura / 2, 
        espessura
    };
    
    float tamanho_bloco_central = espessura * 2.0f;
    j->obstaculosMapa1[3].pos = (Rectangle) {
        j->largura / 2 - tamanho_bloco_central / 2.0f, // Centraliza
        j->altura / 2 - tamanho_bloco_central / 2.0f,  // Centraliza
        tamanho_bloco_central, 
        tamanho_bloco_central
    };
}

void IniciaObstaculosMapa2(Jogo* j) {

    j->obstaculosMapa2.c[0].pos = (Vector2){ 200, 150 };
    j->obstaculosMapa2.c[0].raio = 60;

    j->obstaculosMapa2.c[1].pos = (Vector2){ 400, 300 };
    j->obstaculosMapa2.c[1].raio = 80;

    j->obstaculosMapa2.c[2].pos = (Vector2){ 600, 200 };
    j->obstaculosMapa2.c[2].raio = 50;

    j->obstaculosMapa2.c[3].pos = (Vector2){ 500, 450 };
    j->obstaculosMapa2.c[3].raio = 40;
}

void DesenhaObstaculosMapa0(Jogo* j){
    for (int i = 0; i < 4; i++){
        DrawRectangleRec(j->obstaculosMapa0[i].pos, ORANGE);
    }
}

void DesenhaObstaculosMapa1(Jogo* j){
    for (int i = 0; i < 4; i++) {
        DesenhaTexturaObstaculo(
            j->textObstaculo.r,
            j->obstaculosMapa1[i].pos
        );
    }

}
void DesenhaObstaculosMapa2(Jogo* j){
    for (int i = 0; i < 4; i++) {
        DrawCircleV(j->obstaculosMapa2.c[i].pos, j->obstaculosMapa2.c[i].raio, RED);
    }
}



void DesenhaTexturaObstaculo(Texture2D textura, Rectangle obstaculo){
    Rectangle origem = { 0, 0, textura.width, textura.height };
    float proporcao = (float)textura.width / (float)textura.height;

    float finalW = obstaculo.width;
    float finalH = obstaculo.width / proporcao;

    if (finalH > obstaculo.height) {
        finalH = obstaculo.height;
        finalW = obstaculo.height * proporcao;
    }

    Rectangle final = {
        obstaculo.x + obstaculo.width  / 2.0f,
        obstaculo.y + obstaculo.height / 2.0f,
        finalW,
        finalH
    };

    Vector2 vector = { finalW/2.0f, finalH/2.0f };
    DrawTexturePro(textura, origem, final, vector, 0.0f, WHITE);
    DrawRectangleRec(obstaculo, DARKPURPLE);
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

int ColisaoObstaculosMapa2(Jogo *j){
    if(j->map==2){ 
        for(int i = 0; i < 4; i++){  
        Vector2 centerSnake = {
            j->body.head->pos.x + j->body.size / 2.0f,
            j->body.head->pos.y + j->body.size / 2.0f
        };

        float dist = Vector2Distance(centerSnake, j->obstaculosMapa2.c[i].pos);
        float raioSnake = j->body.size / 2.0f;

        if(dist < (j->obstaculosMapa2.c[i].raio + raioSnake)){
            return 1;
        }
    }
    }
    
    return 0;
}

