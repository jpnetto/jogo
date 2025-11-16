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

void IniciaObstaculosMapa2(Jogo* j){

    float espessura_tronco = 5.0f;
    float margem = 0.10f; 

   if(j->largura == 500){
        
        // Crie uma margem de segurança para Y, afastando do topo e da base
        float margem_y = espessura_tronco * 2.0f; // Ex: 10.0f

        // 1. Tronco Esquerdo Interno
        j->obstaculosMapa2[1].pos = (Rectangle) {
            j->largura * 0.35f, 
            margem_y, // Começa afastado do topo
            espessura_tronco,
            j->altura * 0.80f - margem_y // Reduz a altura para manter a base afastada
        }; 
        
        // 2. Tronco Direito Interno
        j->obstaculosMapa2[2].pos = (Rectangle) {
            j->largura * 0.65f, 
            margem_y* 0.10f, // Começa afastado do topo (não mais em 0)
            espessura_tronco,
            j->altura * 10.0f - margem_y // Reduz a altura
        };
        
         
         // 4. Tronco Caído no topo 
         j->obstaculosMapa2[4].pos = (Rectangle) {
            j->largura * 0.10f, 
            margem_y - 0.1f, // Começa no Y da margem de segurança (não mais em 0.05f)
            j->largura * 0.15f, 
            espessura_tronco
        };


    }
    
    else{
        espessura_tronco = 10.0f; 
        margem = 0.10f; 
    

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


