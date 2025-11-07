
#include "raylib.h"
#include "snake.h"
#include "janela.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(){
    Jogo jogo;
    Reset_score(&jogo); //Começa o jogo com contador 0
    int gameOver = 1;

    //Cria a janela;
    InitWindow(LARGURA, ALTURA, "Cobrinha dos BackyEndigans");
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
            DrawText("FIM DE JOGO!", 155, 160, 50, RED);
            DrawText(TextFormat("Sua Pontuação: %d", jogo.contador), 110, 280, 50, BLACK);
            DrawText("PRESSIONE ENTER PARA REINICIAR", 50, 420, 30, RED);
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


