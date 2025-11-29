#include "raylib.h"
#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "janela.h"
#include "ranking.h"



// Cria arquivo se não existir
void criaRanking() {
    FILE *f = fopen("ranking.txt", "a");
    if (f != NULL) fclose(f);
}

// Insere jogadores no ranking (append)
void insereRanking(char *nome, int pontos) {
    FILE *f = fopen("ranking.txt", "a");
    if (f == NULL) {
        printf("Erro ao abrir ranking.txt\n");
        return;
    }

    fprintf(f, "%s %d\n", nome, pontos);
    fclose(f);
}

// Exibe ranking na interface raylib
void exibeRanking() {
    FILE *f = fopen("ranking.txt", "r");
    char linha[100];
    int y = 100;
    char nome[50];
    int pontuacao, tam=0;
    Jogadores v[10];
    
    //pega do .txt
    while (fgets(linha, sizeof(linha), f)) {
        sscanf(linha, "%s %d", nome, &pontuacao);
        strcpy(v[tam].nome, nome);   
        v[tam].pontos = pontuacao;   
        tam++;
    }

    Jogadores temp;
    //bubble sortzinho de cria
    for (int i=0; i<tam-1;i++) {
        for (int j = 0; j<tam-i-1; j++) {
            if (v[j].pontos < v[j + 1].pontos) {  
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }

    if (f == NULL) {
        DrawText("Ainda nao existe ranking salvo.", 100, y, 20, RED);
        return;
    }

    for (int i = 0; i < tam; i++) {
        // monta "Nome - Pontos"
        DrawText(TextFormat("%d - %s",v[i].pontos, v[i].nome), 100, y, 35, DARKGREEN);
        y += 50;
    }



    fclose(f);
}

