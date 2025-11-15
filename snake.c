#include "raylib.h"
#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "janela.h"


void IniciaBody(Jogo *j){

    // Inicializa a cobrinha, o primeiro bloco.
    Block* new = (Block*)malloc(sizeof(Block));
    if(new == NULL){
        return;
    }

    new->pos = (Rectangle){j->largura/2 - STD_SIZE_X, j->altura - STD_SIZE_Y - 10, STD_SIZE_X, STD_SIZE_Y};
    // Mantive as coordenadas de início utilizadas no IniciaBody do código base enviado pelo professor.

    new->color = SNAKE_COLOR;
    new->prox = NULL;
    j->body.head = new;
    j->body.tail = new;
    j->body.size = 1;
    j->body.direcao = 0;
    j->body.color = SNAKE_COLOR;

    // É o que dá corpo à cobrinha inicial.
    for(int i=1; i<3; i++){
        AtualizaHead(&j->body, j->body.head->pos.x, j->body.head->pos.y);
    }
}

void IniciaBordas(Jogo *j){
    //Borda de cima
    j->bordas[0].pos = (Rectangle) {0, 0, j->largura, 10};
    //Borda da direita
    j->bordas[1].pos = (Rectangle) {j->largura - 10, 0, 10, j->altura};
    //Borda de baixo
    j->bordas[2].pos = (Rectangle) {0, j->altura - 10, j->largura, 10};
    //Borda da esquerda
    j->bordas[3].pos = (Rectangle) {0, 0, 10, j->altura};
}

void IniciaFood(Jogo *j){
    j->food.pos = (Rectangle) {(float)(rand() % ((j->altura - 20) / STD_SIZE_Y) * STD_SIZE_Y + 10), (float)(rand() % ((j->altura - 20) / STD_SIZE_Y) * STD_SIZE_Y + 10), STD_SIZE_X, STD_SIZE_Y};
    j->food.color = FOOD_COLOR;
}

void IniciaTrilhaSonora(Jogo *j){
    j->trilhaSonora.colisaoCorpo = LoadSound("assets/curtoCircuito.mp3");
    j->trilhaSonora.colisaoFruta = LoadSound("assets/carregaBateria.mp3");
    // j->trilhaSonora.musica = LoadMusicStream(""); 
}

void IniciaJogo(Jogo *j){
    IniciaBordas(j);
    IniciaBody(j);
    IniciaFood(j);
    j->tempo = GetTime();
}

void DesenhaFood(Jogo *j){
    DrawRectangleRec(j->food.pos, j->food.color);
}

void DesenhaBordas(Jogo *j){
    //Desenha as barreiras nas bordas
    if(j->map == 0){
        for (int i = 0; i < 4; i++){
            DrawRectangleRec(j->bordas[i].pos, LIGHTGRAY);
        }
    } else if(j->map == 1){
        for (int i = 0; i < 4; i++){
            DrawRectangleRec(j->bordas[i].pos, PINK);
        }
    } else {
        for (int i = 0; i < 4; i++){
            DrawRectangleRec(j->bordas[i].pos, YELLOW);
        }
    }
}

void Draw_Backgound(Jogo* j){
    if(j->map == 0){
        ClearBackground(SKYBLUE);
    } else if(j->map == 1){
        ClearBackground(BLUE);
    } else {
        ClearBackground(GREEN);
    }
}

void AtualizaDirecao(Jogo *j){
    //Atualiza para qual direção a cobra vai  
    if((IsKeyDown(KEY_UP)||IsKeyDown(KEY_W)) && j->body.direcao != 2 && GetTime() - j->cooldown > COOLDOWN){
        j->body.direcao = 0;
        j->cooldown = GetTime();
    }
    if((IsKeyDown(KEY_RIGHT)||IsKeyDown(KEY_D)) && j->body.direcao != 3 && GetTime() - j->cooldown > COOLDOWN){
        j->body.direcao = 1;
        j->cooldown = GetTime();
    }
    if((IsKeyDown(KEY_DOWN)||IsKeyDown(KEY_S)) && j->body.direcao != 0 && GetTime() - j->cooldown > COOLDOWN){
        j->body.direcao = 2;
        j->cooldown = GetTime();
    }
    if((IsKeyDown(KEY_LEFT)||IsKeyDown(KEY_A)) && j->body.direcao != 1 && GetTime() - j->cooldown > COOLDOWN){
        j->body.direcao = 3;
        j->cooldown = GetTime();
    }
}


void DesenhaBody(Jogo *j){
    Block *aux = j->body.head;

    while(aux!=NULL){
        DrawRectangleRec(aux->pos, aux->color);
        aux = aux->prox;
    }
}

void DesenhaJogo(Jogo *j){
    DesenhaBordas(j);
    DesenhaBody(j);
    DesenhaFood(j);
}

void AtualizaPosBody(Jogo *j){

    // Movimentação da cobra. 
    // Armazenamos a posição atual da cabeça da cobra e calculamos as novas.

    float x = j->body.head->pos.x;
    float y = j->body.head->pos.y;

    if(j->body.direcao == 0){
        y -= STD_SIZE_Y; 
    } 
    else if(j->body.direcao == 1){
        x += STD_SIZE_X;
    }
    else if(j->body.direcao == 2){
        y += STD_SIZE_Y;
    }
    else if(j->body.direcao == 3){
        x -= STD_SIZE_X;
    }

    // Enviamos as coordenadas calculadas para a AtualizaHead.
    // Ou seja, toda posição que a cobra anda, aumenta um novo block. 
    AtualizaHead(&j->body, x, y);


    // Para impedir que a cauda seja removida em caso de colisão com o último bloco.
    if(ColisaoBody(j)){
        return;
    }

    // Movimentação:
    // Caso tenha encontrado comida, esse novo bloco fica.
    // Caso não tenha, o bloco de trás é removido. 
    if(ColisaoFood(j)){
        AtualizaLocalFood(j);
        Increase_score(j);//Toda vez que encosta na comida o Contador aumenta
    }
    else{
        RemoveCauda(&j->body);
    }
}

void AtualizaRodada(Jogo *j){
    AtualizaDirecao(j);
    if (GetTime() - j->tempo > TEMPO){
        AtualizaPosBody(j);
        j->tempo = GetTime();
        j->cooldown = COOLDOWN;
    }
}

int verificaColisaoFoodCorpo(Jogo *j, float ca, float cl){
    Block* aux = j->body.head;
    int colide = 0;

    while(aux != NULL){
        if(aux->pos.x == ca && aux->pos.y == cl){
            colide = 1;
            break;
        }
        aux = aux->prox;
    }
    return colide;
}

//função que atualiza o local da comida toda vez que a cobra se alimenta dela
void AtualizaLocalFood(Jogo *j){ 
    float coordAltura, coordLargura;

    coordAltura = (float)(rand() % ((j->altura - 20) / STD_SIZE_Y) * STD_SIZE_Y + 10);
    coordLargura = (float)(rand() % ((j->largura - 20) / STD_SIZE_Y) * STD_SIZE_Y + 10);
    
    if(verificaColisaoFoodCorpo(j, coordAltura, coordLargura)){
        AtualizaLocalFood(j);
    } else{
        j->food.pos = (Rectangle) {coordAltura, coordLargura, STD_SIZE_X, STD_SIZE_Y};
    }

}

void AtualizaHead(Body *body, float x, float y){
    Block* new = (Block*)malloc(sizeof(Block));
    new->pos = (Rectangle){x, y, body->head->pos.width, body->head->pos.height};
    new->color = body->color;
    new->prox = body->head;
    body->head = new;
    body->size++;
}

void RemoveCauda(Body* body){
    if(body->size <= 1){
        return;
    }

    Block* aux = body->head;
    while(aux->prox != body->tail){
        aux = aux->prox;
    }
    free(body->tail);
    body->tail = aux;
    body->tail->prox = NULL;
    body->size--;

}

void FinalizaTrilhaSonora(Jogo *j) {
    UnloadSound(j->trilhaSonora.colisaoCorpo);
    UnloadSound(j->trilhaSonora.colisaoFruta);
}

void FinalizaCobra(Jogo *j){
    Block *aux = j->body.head;
    while (aux != NULL) {
        Block *prox = aux->prox;
        free(aux);
        aux = prox;
    }
    j->body.head = NULL;
    j->body.tail = NULL;
    j->body.size = 0;
}

int ColisaoFood(Jogo *j){
    if (CheckCollisionRecs(j->body.head->pos, j->food.pos)){
        PlaySound(j->trilhaSonora.colisaoFruta);
        return 1;
    }
    return 0;
}

int ColisaoBordas(Jogo *j){
    /*if (CheckCollisionRecs(j->body.head->pos, j->bordas[0].pos) || CheckCollisionRecs(j->body.head->pos, j->bordas[1].pos) || CheckCollisionRecs(j->body.head->pos, j->bordas[2].pos) || CheckCollisionRecs(j->body.head->pos, j->bordas[3].pos)){
        PlaySound(j->trilhaSonora.colisaoCorpo);
        return 1;
    }*/
    if(CheckCollisionRecs(j->body.head->pos, j->bordas[0].pos)){
        j->body.head->pos.y = j->altura - j->body.head->pos.height - 10;
    } else if(CheckCollisionRecs(j->body.head->pos, j->bordas[1].pos)){
        j->body.head->pos.x = 10;
    } else if(CheckCollisionRecs(j->body.head->pos, j->bordas[2].pos)){
        j->body.head->pos.y = 10;
    } else if(CheckCollisionRecs(j->body.head->pos, j->bordas[3].pos)){
        j->body.head->pos.x = j->largura - j->body.head->pos.width - 10;
    }

    return 0;
}

/*
int ColisaoObstaculos(Jogo *j){
    if(CheckCollisionRecs(j->body->head->pos, j->obstaculos)){

    }
}
    */

int ColisaoBody(Jogo *j){
    if(j->body.size<3){
        return 0;
    }

    Block* aux = j->body.head->prox;
    for(int i=0; i<2; i++){
           if(aux != NULL){
             aux = aux->prox;
           }
    }
    while(aux != NULL){
        if (CheckCollisionRecs(j->body.head->pos, aux->pos)){
            PlaySound(j->trilhaSonora.colisaoCorpo);
            return 1;
        }
        aux = aux->prox;
    }
    
    return 0;
}
