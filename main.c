#include "raylib.h"
#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define LARGURA 660
#define ALTURA 660
#define STD_SIZE_X 40
#define STD_SIZE_Y 40
#define TEMPO 0.2
#define COOLDOWN 0.2
#define SNAKE_COLOR BLACK
#define FOOD_COLOR RED

int Contador = 0;//Contador de quantas comidas foram pegas (Criei momentaneamente de forma global mas depois pretendo mudar)

int main(){
    Jogo jogo;
    int gameOver = 1;

    //Cria a janela;
    InitWindow(LARGURA, ALTURA, "Cobrinha dos BackyEndigans");
    SetTargetFPS(40);
    srand(time(NULL));
    
    IniciaJogo(&jogo);
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(SKYBLUE);
        DrawText(TextFormat("Pontuação: %d", Contador), 15, 15, 30, WHITE); 
        if (gameOver){
            DesenhaJogo(&jogo);
            AtualizaRodada(&jogo);
            if (ColisaoBordas(&jogo)){
                gameOver = 0;
                continue;
            }
            if (ColisaoBody(&jogo)){
                gameOver = 0;
                continue;
            }
                
        } else {
            DrawText("FIM DE JOGO!", 200, 250, 40, RED);
            DrawText("PRESSIONE ENTER PARA REINICIAR", 50, 350, 30, RED);
            if (IsKeyPressed(KEY_ENTER)){
                Contador = 0; //Quando aperta enter, começa um jogo novo, então o contador é resetado também
                IniciaJogo(&jogo);
                 gameOver = 1;
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}


void IniciaBody(Jogo *j){
    Block* new = (Block*)malloc(sizeof(Block));
    if(new == NULL){
        return;
    }
    new->pos = (Rectangle){LARGURA/2 - STD_SIZE_X, ALTURA/2, STD_SIZE_X, STD_SIZE_Y};
    // conferir posição

    new->color = SNAKE_COLOR;
    new->prox = NULL;
    j->body.head = new;
    j->body.tail = new;
    j->body.size = 1;
    j->body.direcao = 0;
    j->body.color = SNAKE_COLOR;

    for(int i=0; i<2; i++){
        AtualizaHead(&j->body, j->body.head->pos.x, j->body.head->pos.y);
    }
    
}

void IniciaBordas(Jogo *j){
    //Borda de cima
    j->bordas[0].pos = (Rectangle) {0, 0, LARGURA, 10};
    //Borda da direita
    j->bordas[1].pos = (Rectangle) {LARGURA - 10, 0, 10, ALTURA};
    //Borda de baixo
    j->bordas[2].pos = (Rectangle) {0, ALTURA - 10, LARGURA, 10};
    //Borda da esquerda
    j->bordas[3].pos = (Rectangle) {0, 0, 10, ALTURA};
}

void IniciaFood(Jogo *j){
    j->food.pos = (Rectangle) {(float)(rand() % ((ALTURA - 20) / STD_SIZE_Y) * STD_SIZE_Y + 10), (float)(rand() % ((ALTURA - 20) / STD_SIZE_Y) * STD_SIZE_Y + 10), STD_SIZE_X, STD_SIZE_Y};
    j->food.color = FOOD_COLOR;
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
    for (int i = 0; i < 4; i++){
        DrawRectangleRec(j->bordas[i].pos, LIGHTGRAY);
    }
}


void AtualizaDirecao(Jogo *j){
    //Atualiza para qual direção a cobra vai  
    if(IsKeyDown(KEY_UP) && j->body.direcao != 2 && GetTime() - j->cooldown > COOLDOWN){
        j->body.direcao = 0;
        j->cooldown = GetTime();
    }
    if(IsKeyDown(KEY_RIGHT) && j->body.direcao != 3 && GetTime() - j->cooldown > COOLDOWN){
        j->body.direcao = 1;
        j->cooldown = GetTime();
    }
    if(IsKeyDown(KEY_DOWN) && j->body.direcao != 0 && GetTime() - j->cooldown > COOLDOWN){
        j->body.direcao = 2;
        j->cooldown = GetTime();
    }
    if(IsKeyDown(KEY_LEFT) && j->body.direcao != 1 && GetTime() - j->cooldown > COOLDOWN){
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

    AtualizaHead(&j->body, x, y);
    if(ColisaoFood(j)){
        AtualizaLocalFood(j);
        Contador++;//Toda vez que encosta na comida o Contador aumenta
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

//função que atualiza o local da comida toda vez que a cobra se alimenta dela
void AtualizaLocalFood(Jogo *j){ 
    j->food.pos = (Rectangle) {(float)(rand() % ((ALTURA - 20) / STD_SIZE_Y) * STD_SIZE_Y + 10), (float)(rand() % ((ALTURA - 20) / STD_SIZE_Y) * STD_SIZE_Y + 10), STD_SIZE_X, STD_SIZE_Y};
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
int ColisaoFood(Jogo *j){
    if (CheckCollisionRecs(j->body.head->pos, j->food.pos)){
        return 1;
    }
    return 0;
}

int ColisaoBordas(Jogo *j){
    if (CheckCollisionRecs(j->body.head->pos, j->bordas[0].pos) || CheckCollisionRecs(j->body.head->pos, j->bordas[1].pos) || CheckCollisionRecs(j->body.head->pos, j->bordas[2].pos) || CheckCollisionRecs(j->body.head->pos, j->bordas[3].pos)){
        return 1;
    }
    return 0;
}

int ColisaoBody(Jogo *j){
    if(j->body.size>3){
        Block* aux = j->body.head->prox;
        for(int i=0; i<=2; i++){
            aux = aux->prox;
        }
        while(aux!=j->body.tail->prox){
            if (CheckCollisionRecs(j->body.head->pos, aux->pos)){
                return 1;
            }
            aux = aux->prox;
        }
    }
    return 0;
}
