#include "raylib.h"
#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "janela.h"

void Startgame(Jogo*j){
    j->map = 0;
    j->contador = 0;
    j->largura = 660;
    j->altura = 660;
}

void Reset_score(Jogo* j){
    j->contador = 0;
}

void Increase_score(Jogo* j){
    j->contador++;
}

void Death_message(Jogo* j){
    if(j->largura == 500){
        DrawText("FIM DE JOGO!", 65, 120, 55, RED);
        DrawText(TextFormat("Sua Pontuação: %d", j->contador), 75, 240, 40, BLACK);
        DrawText("PRESSIONE ENTER PARA REINICIAR", 25, 350, 25, RED);
        DrawText("PRESSIONE ESPAÇO", 120, 400, 25, BLACK);
        DrawText("PARA VOLTAR AO MENU", 100, 425, 25, BLACK);
    } else if(j->largura == 660){
        DrawText("FIM DE JOGO!", 80, 160, 75, RED);
        DrawText(TextFormat("Sua Pontuação: %d", j->contador), 110, 280, 50, BLACK);
        DrawText("PRESSIONE ENTER PARA REINICIAR", 50, 420, 30, RED);
        DrawText("PRESSIONE ESPAÇO", 160, 500, 30, BLACK);
        DrawText("PARA VOLTAR AO MENU", 135, 530, 30, BLACK);
    } else{
        DrawText("FIM DE JOGO!", 120, 170, 85, RED);
        DrawText(TextFormat("Sua Pontuação: %d", j->contador), 160, 370, 55, BLACK);
        DrawText("PRESSIONE ENTER PARA REINICIAR", 35, 530, 40, RED);
        DrawText("PRESSIONE ESPAÇO", 190, 620, 40, BLACK);
        DrawText("PARA VOLTAR AO MENU", 160, 660, 40, BLACK);
    }
}

int Menu_screen(Jogo* j){
    int cursor = 0;
    int retorno = 1;
    Rectangle selection;
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(LIME);
        DrawText("Cobrinha", 210, 50, 50, BLACK);
        DrawText("dos", 280, 115, 50, BLACK);
        DrawText("BackyEndigans", 155, 180, 50, BLACK);
        DrawText("Iniciar", 20, 440, 30, BLACK);
        DrawText("Configurações de Mapa", 20, 500, 30, BLACK);
        DrawText("Ranking", 20, 560, 30, BLACK);
        
        
        if(IsKeyPressed(KEY_UP)){
            if(cursor<=0)cursor = 0;
            else cursor--;
        };
        if(IsKeyPressed(KEY_DOWN)){
            if(cursor>1)cursor = 2;
            else cursor++;
        };
        if(cursor <= 0){
            Size_cursor(&selection, 20, 475, 90, 5);
        } else if(cursor == 1){
            Size_cursor(&selection, 20, 535, 355, 5);
        } else if(cursor > 1){
            Size_cursor(&selection, 20, 595, 120, 5);
        }
        if(IsKeyPressed(KEY_ENTER)){
            if(cursor == 0){
                retorno = 0;
                break;
            } else if(cursor == 1){
                CloseWindow();
                Options_screen(j);
                InitWindow(660, 660, " ");
            } else{
                retorno = 0;
                break; 
            } 
            
        }
        DrawRectangleRec(selection, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return retorno;    
}

void Options_screen(Jogo* j){
    InitWindow(660, 660, "Cobrinha dos BackyEndigans");
    int cursor = 0;
    Rectangle selection;
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Configurações:", 20, 20, 30, WHITE);
        DrawText("Aperte ENTER na posicao desejada", 55, 100, 30, WHITE);
        DrawText("Tamanho", 240, 200, 40, WHITE);
        DrawText("Mapas", 260, 350, 40, WHITE);
        DrawText("Retornar", 235, 500, 40, WHITE);
        
        if(IsKeyPressed(KEY_UP)){
            if(cursor<=0)cursor = 0;
            else cursor--;
        };
        if(IsKeyPressed(KEY_DOWN)){
            if(cursor>1)cursor = 2;
            else cursor++;
        };
        if(cursor <= 0){
            Size_cursor(&selection, 230, 245, 200, 5);
        } else if(cursor == 1){
            Size_cursor(&selection, 230, 395, 200, 5);
        } else if(cursor ==2){
            Size_cursor(&selection, 230, 545, 200, 5);
        }
        if(IsKeyPressed(KEY_ENTER)){
            if(cursor == 0){
                CloseWindow();
                Size_map(j);
                InitWindow(660, 660, "Cobrinha dos BackyEndigans");

            } else if(cursor == 1){
                CloseWindow();
                Choose_of_map(j);
                InitWindow(660, 660, "Cobrinha dos BackyEndigans");
            } else{
                EndDrawing();
                break; 
            }
        }
        DrawRectangleRec(selection, WHITE);
        EndDrawing();
    }
    CloseWindow();
}


void Size_map(Jogo* j){
    InitWindow(660, 660, "Cobrinha dos BackyEndigans");
    int cursor = 0;
    Rectangle selection;
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Tamanho:", 20, 20, 30, WHITE);
        DrawText("Aperte ENTER na posicao desejada", 55, 100, 30, WHITE);
        DrawText("Mapa Pequeno", 185, 200, 40, WHITE);
        DrawText("Mapa Médio", 185, 350, 40, WHITE);
        DrawText("Mapa Grande", 185, 500, 40, WHITE);
        
        if(IsKeyPressed(KEY_UP)){
            if(cursor<=0)cursor = 0;
            else cursor--;
        };
        if(IsKeyPressed(KEY_DOWN)){
            if(cursor>1)cursor = 2;
            else cursor++;
        };
        if(cursor <= 0){
            Size_cursor(&selection, 180, 245, 300, 5);
        } else if(cursor == 1){
            Size_cursor(&selection, 180, 395, 300, 5);
        } else if(cursor > 1){
            Size_cursor(&selection, 180, 545, 300, 5);
        }
        if(IsKeyPressed(KEY_ENTER)){
            if(cursor == 0){
                j->altura = 500;
                j->largura = 500;
            } else if(cursor == 1){
                j->altura = 660;
                j->largura = 660;
            } else{
                j->altura = 820;
                j->largura = 820;
            }
            EndDrawing();
            break; 
        }
        DrawRectangleRec(selection, WHITE);
        EndDrawing();
    }
    CloseWindow();
}

void Size_cursor(Rectangle* selection, int a, int b, int c, int d){
    selection->x = a;
    selection->y = b;
    selection->width = c;
    selection->height = d;
}

void Choose_of_map(Jogo* j){
    InitWindow(660, 660, "Cobrinha dos BackyEndigans");
    int cursor = 0;
    Rectangle selection;
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Mapas:", 20, 20, 30, WHITE);
        DrawText("Aperte ENTER na posicao desejada", 55, 100, 30, WHITE);
        DrawText("Mapa 1", 250, 200, 40, WHITE);
        DrawText("Mapa 2", 250, 350, 40, WHITE);
        DrawText("Mapa 3", 250, 500, 40, WHITE);
        
        if(IsKeyPressed(KEY_UP)){
            if(cursor<=0)cursor = 0;
            else cursor--;
        };
        if(IsKeyPressed(KEY_DOWN)){
            if(cursor>1)cursor = 2;
            else cursor++;
        };
        if(cursor <= 0){
            Size_cursor(&selection, 220, 245, 200, 5);
        } else if(cursor == 1){
            Size_cursor(&selection, 220, 395, 200, 5);
        } else if(cursor > 1){
            Size_cursor(&selection, 220, 545, 200, 5);
        }
        if(IsKeyPressed(KEY_ENTER)){
            if(cursor == 0){
                j->map = 0;
            } else if(cursor == 1){
                j->map = 1;
            } else{
                j->map = 2;
            }
            EndDrawing();
            break; 
        }
        DrawRectangleRec(selection, WHITE);
        EndDrawing();
    }
    CloseWindow();
}
