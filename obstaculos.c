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
    float espessura = 10.0f; 
    
    j->obstaculosMapa2.r[0].pos = (Rectangle) {
        j->largura / 4, 
        0, 
        espessura, 
        j->altura * 0.75f
    }; 
    
    j->obstaculosMapa2.r[1].pos = (Rectangle) {
        j->largura * 0.75f, 
        j->altura * 0.25f, 
        espessura, 
        j->altura * 0.75f
    };
    
    j->obstaculosMapa2.r[2].pos = (Rectangle) {
        j->largura / 4, 
        j->altura / 4, 
        j->largura / 2, 
        espessura
    };
    
    float tamanho_bloco_central = espessura * 2.0f;
    j->obstaculosMapa2.r[3].pos = (Rectangle) {
        j->largura / 2 - tamanho_bloco_central / 2.0f, // Centraliza
        j->altura / 2 - tamanho_bloco_central / 2.0f,  // Centraliza
        tamanho_bloco_central, 
        tamanho_bloco_central
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
    for (int i = 0; i < 4; i++) {
        DesenhaTextura(
            j->textObstaculo.r, 
            j->obstaculosMapa2.r[i].pos
        );
    }
}

void DesenhaTextura(Texture2D textura, Rectangle obstaculo)
{
    Rectangle src = { 0, 0, textura.width, textura.height };

    float auxW = textura.width;
    float auxH = textura.height;
    float proporcao = auxW / auxH;

    float finalW = obstaculo.width;
    float finalH = obstaculo.width / proporcao;

    if (finalH > obstaculo.height) {
        finalH = obstaculo.height;
        finalW = obstaculo.height * proporcao;
    }
    Rectangle dest = {
        obstaculo.x + obstaculo.width  / 2.0f,
        obstaculo.y + obstaculo.height / 2.0f,
        finalW,
        finalH
    };
    Vector2 origin = { finalW/2.0f, finalH/2.0f };
    DrawTexturePro(textura, src, dest, origin, 0.0f, WHITE);
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
    return 0;
}

int ColisaoObstaculosMapa2(Jogo *j){
    if(j->map==2){ 
        for(int i = 0; i < 4; i++){
            if(CheckCollisionRecs(j->body.head->pos, j->obstaculosMapa2.r[i].pos)){
                return 1;
            }
        }
    }
    return 0;
}

