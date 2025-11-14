#include "raylib.h"
#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "janela.h"

void Reset_score(Jogo* j){
    j->contador = 0;
}

void Increase_score(Jogo* j){
    j->contador++;
}

void Size_map(Jogo* j){
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Aperte A para jogar no mapa Pequeno", 15, 100, 30, WHITE);
        DrawText("Aperte B para jogar no mapa Médio", 15, 200, 30, WHITE);
        DrawText("Aperte C para jogar no mapa Grande", 15, 300, 30, WHITE);
        if(IsKeyPressed(KEY_A)){
            j->altura = 500;
            j->largura = 500;
            EndDrawing();
            break;
        } else if(IsKeyPressed(KEY_B)){
            j->altura = 660;
            j->largura = 660;
            EndDrawing();
            break;
        } else if(IsKeyPressed(KEY_C)){
            j->altura = 820;
            j->largura = 820;
            EndDrawing();
            break;
        }
        EndDrawing();
    }
    CloseWindow();
}

void Death_message(Jogo* j){
    if(j->largura == 500){
        DrawText("FIM DE JOGO!", 65, 120, 55, RED);
        DrawText(TextFormat("Sua Pontuação: %d", j->contador), 75, 240, 40, BLACK);
        DrawText("PRESSIONE ENTER PARA REINICIAR", 25, 350, 25, RED);
    } else if(j->largura == 660){
        DrawText("FIM DE JOGO!", 80, 160, 75, RED);
        DrawText(TextFormat("Sua Pontuação: %d", j->contador), 110, 280, 50, BLACK);
        DrawText("PRESSIONE ENTER PARA REINICIAR", 50, 420, 30, RED);
    } else{
        DrawText("FIM DE JOGO!", 120, 170, 85, RED);
        DrawText(TextFormat("Sua Pontuação: %d", j->contador), 160, 370, 55, BLACK);
        DrawText("PRESSIONE ENTER PARA REINICIAR", 35, 560, 40, RED);
    }
}
