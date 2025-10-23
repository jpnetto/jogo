
#include "raylib.h"
#include "snake.h"
#include "janela.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

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
                Reset_score(); //Quando aperta enter, começa um jogo novo, então o contador é resetado também
                IniciaJogo(&jogo);
                 gameOver = 1;
            }
        }
        DrawText(TextFormat("Pontuação: %d", Contador), 15, 15, 30, WHITE); 
        EndDrawing();
    }
    CloseWindow();
    return 0;
}


