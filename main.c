
#include "raylib.h"
#include "snake.h"
#include "janela.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(){
    InitAudioDevice();
    int spacereset = 1;
    Jogo jogo;
    Startgame(&jogo); //Começa o jogo com o tamanho médio e contador zerado
    IniciaTrilhaSonora(&jogo);

    while(spacereset){
        spacereset = 0;
        InitWindow(660, 660, " ");
    
        if (Menu_screen(&jogo))return 0; //Garante que o jogo só rode se o jogador apertar em iniciar
        int gameOver = 1;
        
        InitWindow(jogo.largura, jogo.altura, "Cobrinha dos BackyEndigans");
        SetTargetFPS(60);
        srand(time(NULL));  
        
        IniciaJogo(&jogo);
        while (!WindowShouldClose()){
            BeginDrawing();
            Draw_Backgound(&jogo);
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
                    FinalizaCobra(&jogo);
                    Reset_score(&jogo); //Quando aperta enter, começa um jogo novo, então o contador é resetado também
                    IniciaJogo(&jogo);
                    gameOver = 1;
                } else if(IsKeyPressed(KEY_SPACE)){
                    FinalizaCobra(&jogo);
                    spacereset = 1;
                    break;
                };
            }
            
            EndDrawing();
        }
        CloseWindow();

    }

    FinalizaTrilhaSonora(&jogo);
    CloseAudioDevice();

    return 0;
}