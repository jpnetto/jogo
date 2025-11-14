
#include "raylib.h"
#include "snake.h"
#include "janela.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(){
    Jogo jogo;
    InitWindow(660, 450, "Cobrinha dos BackyEndigans");
    Size_map(&jogo); //Jogador decide qual tamanho de mapa ele quer
    Reset_score(&jogo); //Começa o jogo com contador 0
    int gameOver = 1;
    
    //Cria a janela;
    InitWindow(jogo.largura, jogo.altura, "Cobrinha dos BackyEndigans");
    SetTargetFPS(60);
    srand(time(NULL));
    
    IniciaJogo(&jogo);
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(SKYBLUE);
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
            DrawText(TextFormat("Pontuação: %d", jogo.contador), 15, 15, 30, WHITE);
        } else {
            Death_message(&jogo);
            if (IsKeyPressed(KEY_ENTER)){
                Reset_score(&jogo); //Quando aperta enter, começa um jogo novo, então o contador é resetado também
                IniciaJogo(&jogo);
                 gameOver = 1;
            }
        }
         
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
