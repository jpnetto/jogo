#include "raylib.h"
#include "raymath.h"
#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "janela.h"
#include "obstaculos.h"
#include <math.h>


void IniciaBody(Jogo *j){

    // Inicializa a cobrinha, o primeiro bloco.
    Block* new = (Block*)malloc(sizeof(Block));
    if(new == NULL){
        return;
    }
    
    new->pos = (Rectangle){j->largura/2 - STD_SIZE_X - 200, j->altura - STD_SIZE_Y - 90, STD_SIZE_X, STD_SIZE_Y};
    
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
        AtualizaHead(j,&j->body, j->body.head->pos.x, j->body.head->pos.y);
    }
    IniciaTexturasBody(j);
}

//Bordas, apesar de nao serem obstaculos necessariamente, sao usadas na funcao para fazer elas sairem em um lado e aparecerem do outro
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

//Carrega as imagens das comidas e coloca spawn fixo na comida
void IniciaFood(Jogo *j){
    j->food.pos = (Rectangle) {j->largura/2 - STD_SIZE_X - 200, j->altura - 290, STD_SIZE_X, STD_SIZE_Y};
    j->food.color = FOOD_COLOR;
    j->food.texture[0] = LoadTexture("assets/texture_food/Apple01.png");
    j->food.texture[1] = LoadTexture("assets/texture_food/Apple02.png");
    j->food.texture[2] = LoadTexture("assets/texture_food/Apple03.png");
    j->food.texture[3] = LoadTexture("assets/texture_food/Apple04.png");
    j->food.texture[4] = LoadTexture("assets/texture_food/Apple05.png");
    j->food.texture[5] = LoadTexture("assets/texture_food/Apple06.png");
    j->food.texture[6] = LoadTexture("assets/texture_food/Battery01.png");
    j->food.texture[7] = LoadTexture("assets/texture_food/Battery02.png");
    j->food.texture[8] = LoadTexture("assets/texture_food/Battery03.png");
    j->food.texture[9] = LoadTexture("assets/texture_food/Battery04.png");
    j->food.texture[10] = LoadTexture("assets/texture_food/Battery05.png");
    j->food.texture[11] = LoadTexture("assets/texture_food/Battery06.png");
    j->food.texture[12] = LoadTexture("assets/texture_food/Diamante01.png");
    j->food.texture[13] = LoadTexture("assets/texture_food/Diamante02.png");
    j->food.texture[14] = LoadTexture("assets/texture_food/Diamante03.png");
    j->food.texture[15] = LoadTexture("assets/texture_food/Diamante04.png");
    j->food.texture[16] = LoadTexture("assets/texture_food/Diamante05.png");
    j->food.texture[17] = LoadTexture("assets/texture_food/Diamante06.png");
    
}


void IniciaTrilhaSonora(Jogo *j){
    if(j->map==0){
        j->trilhaSonora.colisaoCorpo = LoadSound("assets/trilha_sonora/gameOver.mp3");
        j->trilhaSonora.colisaoFruta = LoadSound("assets/trilha_sonora/coleta.mp3");
        j->trilhaSonora.musica = LoadMusicStream("assets/trilha_sonora/theBackyardigans.mp3");
    }
    else if(j->map==1){
        j->trilhaSonora.colisaoCorpo = LoadSound("assets/trilha_sonora/curtoCircuito.mp3");
        j->trilhaSonora.colisaoFruta = LoadSound("assets/trilha_sonora/carregaBateria.mp3");
        j->trilhaSonora.musica = LoadMusicStream("assets/trilha_sonora/soundtrack.mp3");
    }
    else if(j->map==2){
        j->trilhaSonora.colisaoCorpo = LoadSound("assets/trilha_sonora/death3.mp3");
        j->trilhaSonora.colisaoFruta = LoadSound("assets/trilha_sonora/coleta.mp3");
        j->trilhaSonora.musica = LoadMusicStream("assets/trilha_sonora/caverna.mp3");
    }
    
    SetMusicVolume(j->trilhaSonora.musica, 1.0f);
    j->trilhaSonora.musica.looping = true;
    PlayMusicStream(j->trilhaSonora.musica);
}

void IniciaJogo(Jogo *j){
    IniciaBordas(j);
    IniciaBody(j);
    IniciaFood(j);
    IniciaObstaculos(j);
    IniciaTrilhaSonora(j);
    IniciaTexturasMap(j);
    j->tempo = GetTime();
}

//Aqui roda os "GIFs" das comidas
//Nada mais sao do que 6 imagens carregadas para rodar em loop de 1 seg, cada uma carrega pelo intervalo de 0.1seg
//Feita utilizando modulo de float, usando a funcao da biblioteca math.h fmod
void DesenhaFood(Jogo *j){
    float t = GetTime();
    float onesec = fmod(t, 1.0f);
    if(j->map==0){
        if(onesec < 0.1f)DrawTexture(j->food.texture[0], j->food.pos.x, j->food.pos.y, WHITE);
        if((onesec >= 0.1f && onesec < 0.2f)||(onesec >= 0.9f))DrawTexture(j->food.texture[1], j->food.pos.x, j->food.pos.y, WHITE);
        if((onesec >= 0.2f && onesec < 0.3f)||(onesec >= 0.8f && onesec < 0.9f))DrawTexture(j->food.texture[2], j->food.pos.x, j->food.pos.y, WHITE);
        if((onesec >= 0.3f && onesec < 0.4f)||(onesec >= 0.7f && onesec < 0.8f))DrawTexture(j->food.texture[3], j->food.pos.x, j->food.pos.y, WHITE);
        if((onesec >= 0.4f && onesec < 0.5f)||(onesec >= 0.6f && onesec < 0.7f))DrawTexture(j->food.texture[4], j->food.pos.x, j->food.pos.y, WHITE);
        if(onesec >= 0.5f && onesec < 0.6f)DrawTexture(j->food.texture[5], j->food.pos.x, j->food.pos.y, WHITE);
    }
    if(j->map==1){
        if(onesec < 0.1f)DrawTexture(j->food.texture[6], j->food.pos.x, j->food.pos.y, WHITE);
        if((onesec >= 0.1f && onesec < 0.2f)||(onesec >= 0.9f))DrawTexture(j->food.texture[7], j->food.pos.x, j->food.pos.y, WHITE);
        if((onesec >= 0.2f && onesec < 0.3f)||(onesec >= 0.8f && onesec < 0.9f))DrawTexture(j->food.texture[8], j->food.pos.x, j->food.pos.y, WHITE);
        if((onesec >= 0.3f && onesec < 0.4f)||(onesec >= 0.7f && onesec < 0.8f))DrawTexture(j->food.texture[9], j->food.pos.x, j->food.pos.y, WHITE);
        if((onesec >= 0.4f && onesec < 0.5f)||(onesec >= 0.6f && onesec < 0.7f))DrawTexture(j->food.texture[10], j->food.pos.x, j->food.pos.y, WHITE);
        if(onesec >= 0.5f && onesec < 0.6f)DrawTexture(j->food.texture[11], j->food.pos.x, j->food.pos.y, WHITE);
    }
    if(j->map==2){
        if(onesec < 0.1f)DrawTexture(j->food.texture[12], j->food.pos.x, j->food.pos.y, WHITE);
        if((onesec >= 0.1f && onesec < 0.2f)||(onesec >= 0.9f))DrawTexture(j->food.texture[13], j->food.pos.x, j->food.pos.y, WHITE);
        if((onesec >= 0.2f && onesec < 0.3f)||(onesec >= 0.8f && onesec < 0.9f))DrawTexture(j->food.texture[14], j->food.pos.x, j->food.pos.y, WHITE);
        if((onesec >= 0.3f && onesec < 0.4f)||(onesec >= 0.7f && onesec < 0.8f))DrawTexture(j->food.texture[15], j->food.pos.x, j->food.pos.y, WHITE);
        if((onesec >= 0.4f && onesec < 0.5f)||(onesec >= 0.6f && onesec < 0.7f))DrawTexture(j->food.texture[16], j->food.pos.x, j->food.pos.y, WHITE);
        if(onesec >= 0.5f && onesec < 0.6f)DrawTexture(j->food.texture[17], j->food.pos.x, j->food.pos.y, WHITE);
    }
    

}
void Draw_Backgound(Jogo* j){
    ClearBackground(WHITE);
    if(j->map==0){
        if(j->largura==500){
            DrawTexture(j->fundo[1], 0, 0, WHITE);
        } else if(j->largura==660){
            DrawTexture(j->fundo[2], 0, 0, WHITE);
        } else{
            DrawTexture(j->fundo[3], 0, 0, WHITE);
        }
    } else if(j->map==1){
        if(j->largura==500){
            DrawTexture(j->fundo[4], 0, 0, WHITE);
        } else if(j->largura==660){
            DrawTexture(j->fundo[5], 0, 0, WHITE);
        } else{
            DrawTexture(j->fundo[6], 0, 0, WHITE);
        }
    } else{
        if(j->largura==500){
            DrawTexture(j->fundo[7], 0, 0, WHITE);
        } else if(j->largura==660){
            DrawTexture(j->fundo[8], 0, 0, WHITE);
        } else{
            DrawTexture(j->fundo[9], 0, 0, WHITE);
        }
        
    }
}

void AtualizaDirecao(Jogo *j){
    //Atualiza para qual direção a cobra vai  
    if((IsKeyPressed(KEY_UP)||IsKeyPressed(KEY_W)) && j->body.direcao != 2 && GetTime() - j->cooldown > COOLDOWN){
        j->body.direcao = 0;
        j->cooldown = GetTime();
    }
    if((IsKeyPressed(KEY_RIGHT)||IsKeyPressed(KEY_D)) && j->body.direcao != 3 && GetTime() - j->cooldown > COOLDOWN){
        j->body.direcao = 1;
        j->cooldown = GetTime();
    }
    if((IsKeyPressed(KEY_DOWN)||IsKeyPressed(KEY_S)) && j->body.direcao != 0 && GetTime() - j->cooldown > COOLDOWN){
        j->body.direcao = 2;
        j->cooldown = GetTime();
    }
    if((IsKeyPressed(KEY_LEFT)||IsKeyPressed(KEY_A)) && j->body.direcao != 1 && GetTime() - j->cooldown > COOLDOWN){
        j->body.direcao = 3;
        j->cooldown = GetTime();
    }
}

void AtualizaMusica(Jogo *j) { 
    UpdateMusicStream(j->trilhaSonora.musica); 
}


void DesenhaBody(Jogo *j){
    Block *aux = j->body.head;
    int curently_direction = aux->direcao;

    while(aux!=NULL){
        Rectangle source = {0,0,40,40}; //o source serve para fazer um recorte do pixel que sera mexido
        Rectangle thepos = {aux->pos.x+20 ,aux->pos.y+20 ,40,40}; //o thepos serve para desenhar onde a imagem vai ser colocada na tela. pegamos o recorte com o source e o thepos será onde e com como esse recorte vai ser desenhado
        Vector2 origin = {20,20}; //aqui é o centro de rotacao que o recorte vai fazer
        float rotation = 90.0*aux->direcao; //aqui a rotacao se baseia na direcao da cobra
        if(aux == j->body.head){
            DrawTexturePro(j->body.texture[0+j->map*4], source, thepos, origin, rotation, WHITE);
        }
        else if(aux == j->body.tail){
            rotation = 90.0*curently_direction;
            DrawTexturePro(j->body.texture[2+j->map*4], source, thepos, origin, rotation, WHITE);
        } 
        else if(curently_direction!=aux->direcao){
            if(curently_direction==1){
                if(aux->direcao==0)rotation = 0;
                if(aux->direcao==2)rotation = 270.0;
            }
            if(curently_direction==3){
                if(aux->direcao==2)rotation = 180.0;
                if(aux->direcao==0)rotation = 90.0;
            }
            if(curently_direction==0){
                if(aux->direcao==1)rotation = 180.0;
                if(aux->direcao==3)rotation = 270.0;
            }
            if(curently_direction==2){
                if(aux->direcao==1)rotation = 90.0;
                if(aux->direcao==3)rotation = 0;
            }
            DrawTexturePro(j->body.texture[3+j->map*4], source, thepos, origin, rotation, WHITE);
            curently_direction = aux->direcao;
        }
        else DrawTexturePro(j->body.texture[1+j->map*4], source, thepos, origin, rotation, WHITE);
        aux = aux->prox;
    }
}

void DesenhaJogo(Jogo *j){
    // DesenhaBordas(j);
    DesenhaBody(j);
    DesenhaFood(j);
    // DesenhaObstaculos(j);
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
    AtualizaHead(j,&j->body, x, y);


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
        if(j->largura==500) SetWindowTitle(TextFormat("Pontuação: %d         Cobrinha dos BackyEndigans    ", j->contador));
        else SetWindowTitle(TextFormat("Pontuação: %d                Cobrinha dos BackyEndigans                           ", j->contador));
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
    
    if((verificaColisaoFoodCorpo(j, coordAltura, coordLargura)||(ColisaoFoodObstaculo(j, coordAltura, coordLargura)==1))){
        AtualizaLocalFood(j);
    } else{
        j->food.pos = (Rectangle) {coordAltura, coordLargura, STD_SIZE_X, STD_SIZE_Y};
    }

}

void AtualizaHead(Jogo* j,Body *body, float x, float y){
    Block* new = (Block*)malloc(sizeof(Block));
    new->pos = (Rectangle){x, y, body->head->pos.width, body->head->pos.height};
    new->color = body->color;
    new->prox = body->head;
    new->direcao = j->body.direcao; //importante para desenho da cobra, principalmente as curvas
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
    UnloadMusicStream(j->trilhaSonora.musica);
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

int ColisaoFoodObstaculo(Jogo *j, float x, float y){
    Rectangle comida = (Rectangle){ x, y, STD_SIZE_X, STD_SIZE_Y };
    if (j->map == 0){
        for (int i = 0; i < 4; i++){
            if (CheckCollisionRecs(comida, j->obstaculosMapa0[i].pos))
            return 1;
        }
    }
    else if (j->map == 1){
        for (int i = 0; i < 8; i++) {
            if (CheckCollisionRecs(comida, j->obstaculosMapa1[i].pos))
                return 1;
        }
    }
    else if (j->map == 2)
    {
        for (int i = 0; i < 16; i++) {
            if (CheckCollisionRecs(comida, j->obstaculosMapa2[i].pos))
                return 1;
        }
    }
    return 0; 
}

void ColisaoBordas(Jogo *j){
    if (CheckCollisionRecs(j->body.head->pos, j->bordas[0].pos) || CheckCollisionRecs(j->body.head->pos, j->bordas[1].pos) || CheckCollisionRecs(j->body.head->pos, j->bordas[2].pos) || CheckCollisionRecs(j->body.head->pos, j->bordas[3].pos)){
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
        if(ColisaoFood(j)){
            AtualizaLocalFood(j);
            Increase_score(j);//Toda vez que encosta na comida o Contador aumenta
            if(j->largura==500) SetWindowTitle(TextFormat("Pontuação: %d         Cobrinha dos BackyEndigans    ", j->contador));
            else SetWindowTitle(TextFormat("Pontuação: %d                Cobrinha dos BackyEndigans                           ", j->contador));
        }
    }
    return;
}


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

void IniciaTexturasBody(Jogo* j){
    j->body.texture[0] = LoadTexture("assets/texture_snake/Uniqua_Head.png");
    j->body.texture[1] = LoadTexture("assets/texture_snake/Uniqua_Body.png");
    j->body.texture[2] = LoadTexture("assets/texture_snake/Uniqua_Tail.png");
    j->body.texture[3] = LoadTexture("assets/texture_snake/Uniqua_Turn.png");
    j->body.texture[4] = LoadTexture("assets/texture_snake/Radius_Head.png");
    j->body.texture[5] = LoadTexture("assets/texture_snake/Radius_Body.png");
    j->body.texture[6] = LoadTexture("assets/texture_snake/Radius_Tail.png");
    j->body.texture[7] = LoadTexture("assets/texture_snake/Radius_Turn.png");
    j->body.texture[8] = LoadTexture("assets/texture_snake/Sand_Head.png");
    j->body.texture[9] = LoadTexture("assets/texture_snake/Sand_Body.png");
    j->body.texture[10] = LoadTexture("assets/texture_snake/Sand_Tail.png");
    j->body.texture[11] = LoadTexture("assets/texture_snake/Sand_Turn.png");
}

void IniciaTexturasMap(Jogo* j){
    j->fundo[1] = LoadTexture("assets/texture_background/fundo01.png");
    j->fundo[2] = LoadTexture("assets/texture_background/fundo02.png");
    j->fundo[3] = LoadTexture("assets/texture_background/fundo03.png");
    j->fundo[4] = LoadTexture("assets/texture_background/fundo04.png");
    j->fundo[5] = LoadTexture("assets/texture_background/fundo05.png");
    j->fundo[6] = LoadTexture("assets/texture_background/fundo06.png");
    j->fundo[7] = LoadTexture("assets/texture_background/fundo07.png");
    j->fundo[8] = LoadTexture("assets/texture_background/fundo08.png");
    j->fundo[9] = LoadTexture("assets/texture_background/fundo09.png");
}


void Unload_textures(Jogo* j){
    for(int i=0; i<10; i++){
        UnloadTexture(j->fundo[i]);
    }
    for(int i = 0;i<12;i++){
        UnloadTexture(j->food.texture[i]);
    }
    for(int i = 0; i<12;i++){
        UnloadTexture(j->body.texture[i]);
    }
    for(int i = 0; i<18;i++){
        UnloadTexture(j->food.texture[i]);
    }
    FinalizaTrilhaSonora(j);
    CloseAudioDevice();
}