#include "raylib.h"
#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "janela.h"
#include "ranking.h"

void Startgame(Jogo*j){
    InitAudioDevice();
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
    j->fundo = LoadTexture("assets/Fundo_Menu.jpg");
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(LIME);

        DrawTexture(j->fundo, 0, 0, WHITE);
        
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
                EndDrawing();
                Options_screen(j);
                j->fundo = LoadTexture("assets/Fundo_Menu.jpg");
            } else if(cursor == 2){
                EndDrawing();
                Ranking_screen(j);
                continue;
            }else{
                retorno = 0;
                break; 
            } 
            
        }
        DrawRectangleRec(selection, BLACK);
        EndDrawing();
    }
    EndDrawing();
    return retorno;    
}

void Options_screen(Jogo* j){
    int cursor = 0;
    Rectangle selection;
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(j->fundo, 0, 0, WHITE);
        DrawText("Configurações:", 20, 20, 30, BLACK);
        DrawText("Aperte ENTER na posicao desejada", 55, 100, 30, BLACK);
        DrawText("Tamanho", 240, 200, 40, BLACK);
        DrawText("Mapas", 260, 350, 40, BLACK);
        DrawText("Retornar", 235, 500, 40, BLACK);
        
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
                EndDrawing();
                Size_map(j);
                continue;

            } else if(cursor == 1){
                EndDrawing();
                Choose_of_map(j);
                continue;
            } else{
                EndDrawing();
                break; 
            }
        }
        DrawRectangleRec(selection, BLACK);
        EndDrawing();
    }
    EndDrawing();
}

//Paro
void Size_map(Jogo* j){
    int cursor = 0;
    Rectangle selection;
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(j->fundo, 0, 0, WHITE);
        DrawText("Tamanho:", 20, 20, 30, BLACK);
        DrawText("Aperte ENTER na posicao desejada", 55, 100, 30, BLACK);
        DrawText("Mapa Pequeno", 185, 200, 40, BLACK);
        DrawText("Mapa Médio", 185, 350, 40, BLACK);
        DrawText("Mapa Grande", 185, 500, 40, BLACK);
        
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
        DrawRectangleRec(selection, BLACK);
        EndDrawing();
    }
    EndDrawing();
}

void Size_cursor(Rectangle* selection, int a, int b, int c, int d){
    selection->x = a;
    selection->y = b;
    selection->width = c;
    selection->height = d;
}

void Choose_of_map(Jogo* j){
    int cursor = 0;
    Rectangle selection;
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(j->fundo, 0, 0, WHITE);
        DrawText("Mapas:", 20, 20, 30, BLACK);
        DrawText("Aperte ENTER na posicao desejada", 55, 100, 30, BLACK);
        DrawText("Mapa 1", 250, 200, 40, BLACK);
        DrawText("Mapa 2", 250, 350, 40, BLACK);
        DrawText("Mapa 3", 250, 500, 40, BLACK);
        
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
        DrawRectangleRec(selection, BLACK);
        EndDrawing();
    }
    EndDrawing();
}

void Ranking_screen(Jogo* j){
    Rectangle selection;
    j->fundo = LoadTexture("assets/Fundo_Menu.jpg");
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        DrawTexture(j->fundo, 0, 0, WHITE);
        
        DrawText("Ranking", 230, 30, 50, BLACK);
        exibeRanking();
        if(IsKeyPressed(KEY_ENTER)){
            break;   
        }
        DrawRectangleRec(selection, BLACK);
        EndDrawing();
    }
    EndDrawing();
}
