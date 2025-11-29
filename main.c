
#include "raylib.h"
#include "snake.h"
#include "janela.h"
#include "obstaculos.h"
#include "ranking.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
//paro
int main(){
    int spacereset = 1;
    Jogo jogo;
    Startgame(&jogo); //Começa o jogo com o tamanho médio e contador zerado
    IniciaTrilhaSonora(&jogo);
    InitWindow(660, 660, " ");
    while(spacereset){
        spacereset = 0;
        if (Menu_screen(&jogo))return 0; //Garante que o jogo só rode se o jogador apertar em iniciar
        SetWindowSize(jogo.largura, jogo.altura);
        SetWindowTitle("Cobrinha dos BackEndygans");
        int gameOver = 1;
        SetTargetFPS(60);
        srand(time(NULL));  
        
        IniciaJogo(&jogo);
        while (!WindowShouldClose()){
            BeginDrawing();
            Draw_Backgound(&jogo);
            if (gameOver){
                AtualizaMusica(&jogo);
                DesenhaJogo(&jogo);
                AtualizaRodada(&jogo);
                if ((ColisaoBody(&jogo))||(ColisaoObstaculos(&jogo))){
                    gameOver = 0;
                    continue;
                }
                ColisaoBordas(&jogo);
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
                    Reset_score(&jogo);
                    spacereset = 1;
                    break;
                };
            }
            
            EndDrawing();
        }
        EndDrawing();
        if(spacereset){
            SetWindowSize(660, 660);
            SetWindowTitle(" ");
        }
    }
    Unload_textures(&jogo);

    return 0;
}