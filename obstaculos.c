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

    if(j->largura <= 660){
    float espessura = 10.0f; 
    j->obstaculosMapa1[0].pos = (Rectangle) { j->largura / 4, 0, espessura, j->altura * 0.75f}; 
    j->obstaculosMapa1[1].pos = (Rectangle) { j->largura * 0.75f, j->altura * 0.25f, espessura, j->altura * 0.75f};
    j->obstaculosMapa1[2].pos = (Rectangle) { j->largura / 4, j->altura / 4, j->largura / 2, espessura};
    float tamanho_bloco_central = espessura * 2.0f; 
    j->obstaculosMapa1[3].pos = (Rectangle) { j->largura / 2 - tamanho_bloco_central / 2.0f, j->altura / 2 - tamanho_bloco_central / 2.0f, 
    tamanho_bloco_central, tamanho_bloco_central};  
    }   else{
    float espessura = 20.0f;
    j->obstaculosMapa1[0].pos = (Rectangle) { j->largura / 4, 0, espessura, j->altura * 0.60f}; 
    j->obstaculosMapa1[1].pos = (Rectangle) { j->largura * 0.75f, j->altura * 0.25f, espessura, j->altura * 2};
    j->obstaculosMapa1[2].pos = (Rectangle) { j->largura / 4, j->altura / 4, j->largura / 2, espessura};
    float tamanho_bloco_central = espessura * 2.0f; 
    j->obstaculosMapa1[3].pos = (Rectangle) { j->largura / 2 - tamanho_bloco_central / 2.0f, j->altura / 2 - tamanho_bloco_central / 2.0f, 
    tamanho_bloco_central, tamanho_bloco_central}; 


}


}
void IniciaObstaculosMapa2(Jogo* j) {
    
    float espessura, espessura2, tamanho;

    if(j->largura==500){
        espessura = 25.0f;
        espessura2 = 20.0f;
        tamanho = 80.0f;
    }
    else{
        espessura = 40.0f;
        espessura2 = 20.0f; 
        tamanho = 120.0f;

    }  
    if(j->largura==500){
        j->obstaculosMapa2[0].pos = (Rectangle) {
            j->largura * 0.30f, j->altura  * 0.50f, espessura*3-20 , espessura
        };
        j->obstaculosMapa2[1].pos = (Rectangle) {
            j->largura * 0.55f+20, j->altura  * 0.20f, espessura*3-20, espessura
        };

        j->obstaculosMapa2[2].pos = (Rectangle) {
            j->largura * 0.70f, j->altura  * 0.20, espessura-20, espessura*3-20
        };

        j->obstaculosMapa2[3].pos = (Rectangle) {
            j->largura * 0.70f, j->altura  * 0.75f, espessura-20, espessura*3-20
        };

        j->obstaculosMapa2[4].pos = (Rectangle) {
            j->largura * 0.20f, j->altura  * 0.20, espessura, espessura*3-20
        };

        j->obstaculosMapa2[5].pos = (Rectangle) {
            j->largura * 0.20f, j->altura * 0.70f, espessura, espessura*3-20
        };

        j->obstaculosMapa2[6].pos = (Rectangle) {
            j->largura * 0.55f+20, j->altura  * 0.82f, espessura*3-20, espessura
        };
    }
    else if(j->largura==660){
        j->obstaculosMapa2[0].pos = (Rectangle) {
            j->largura * 0.30f, j->altura  * 0.7f, espessura*3, espessura-20
        };
        j->obstaculosMapa2[1].pos = (Rectangle) {
            j->largura * 0.55f+10, j->altura  * 0.20f, espessura*3-10, espessura-20
        };

        j->obstaculosMapa2[2].pos = (Rectangle) {
            j->largura * 0.70f, j->altura  * 0.20, espessura-20, espessura*3-10
        };

        j->obstaculosMapa2[3].pos = (Rectangle) {
            j->largura * 0.70f, j->altura  * 0.70f, espessura-20, espessura*3-20
        };

        j->obstaculosMapa2[4].pos = (Rectangle) {
            j->largura * 0.30f, j->altura  * 0.20, espessura-10, espessura*3 - 10
        };

        j->obstaculosMapa2[5].pos = (Rectangle) {
            (j->largura-20) * 0.30f, j->altura * 0.70f, espessura-10, espessura*3-20
        };

        j->obstaculosMapa2[6].pos = (Rectangle) {
            j->largura * 0, j->altura  * 0, espessura*0, espessura*0
        };
        j->obstaculosMapa2[7].pos = (Rectangle) {
            j->largura * 0, j->altura  * 0.40f, espessura*2, espessura*3
    };
}
    else{
            j->obstaculosMapa2[0].pos = (Rectangle) {
            j->largura * 0.15f, j->altura  * 0.30f, espessura/2, espessura*8.5
        };
        j->obstaculosMapa2[1].pos = (Rectangle) {
            j->largura * 0.0f, j->altura  * 0.30f+20, espessura*3.2, espessura/2
        };

        j->obstaculosMapa2[2].pos = (Rectangle) {
            j->largura * 0.0f, j->altura  * 0.70, espessura*3.6, espessura/2
        };

        j->obstaculosMapa2[3].pos = (Rectangle) {
            j->largura * 0.15f, j->altura  * 0.50f, espessura*20, espessura/2-10
        };
        
        j->obstaculosMapa2[4].pos = (Rectangle) {
            j->largura * 0.60f+20, j->altura  * 0.10f+20, espessura*2-20, espessura*2
        };
        
        j->obstaculosMapa2[5].pos = (Rectangle) {
            j->largura * 0.30f+10, j->altura * 0.10f+20, espessura*3-20, espessura*3-20
        };
        
        j->obstaculosMapa2[6].pos = (Rectangle) {
            j->largura * 0.40f+10, j->altura  * 0.70f+10, espessura*3-20, espessura*3-20
        };
        j->obstaculosMapa2[7].pos = (Rectangle) {
            j->largura * 0.70f+10, j->altura  * 0.70+10, espessura*3-20, espessura*3-20
            
    };
        
    }
    
    
    // superior esquerdo
    j->obstaculosMapa2[8].pos = (Rectangle) { 0, 0, tamanho-10, espessura2-10 }; // barra horizontal
    j->obstaculosMapa2[9].pos = (Rectangle) { 0, 0, espessura2-10, tamanho-10 }; // barra vertical

    // superior direito
    j->obstaculosMapa2[10].pos = (Rectangle) { j->largura - tamanho+10, 0, tamanho-10, espessura2-10 }; // horizontal
    j->obstaculosMapa2[11].pos = (Rectangle) { j->largura - espessura2+10, 0, espessura2-10, tamanho-10 }; // vertical

    // inferior esquerdo
    j->obstaculosMapa2[12].pos = (Rectangle) { 0, j->altura - espessura2, tamanho-10, espessura2-10}; // horizontal
    j->obstaculosMapa2[13].pos = (Rectangle) { 0, j->altura - tamanho, espessura2-10, tamanho-10 }; // vertical

    // inferior direito
    j->obstaculosMapa2[14].pos = (Rectangle) { j->largura - tamanho+10, j->altura - espessura2, tamanho-10, espessura2-10 }; // horizontal
    j->obstaculosMapa2[15].pos = (Rectangle) { j->largura - espessura2+10, j->altura - tamanho, espessura2-10, tamanho-10 }; // vertical

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
        for(int i=0; i<4; i++){
            if(CheckCollisionRecs(j->body.head->pos, j->obstaculosMapa1[i].pos)){
            return 1;
            }
        }   
    }
    
    return 0;
}

int ColisaoObstaculosMapa2(Jogo *j){
    if(j->map==2){ 
        for(int i=0; i<16; i++){
            if(CheckCollisionRecs(j->body.head->pos, j->obstaculosMapa2[i].pos)){
            return 1;
            }
        }   
    }
    return 0;
}

