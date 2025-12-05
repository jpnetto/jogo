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
    FILE *f = fopen("ranking.txt", "r");
    Jogadores v[20];
    int tam = 0;
    char linha[100], nome_txt[50];
    int pontuacao;

    if (f != NULL) {
        while (fgets(linha, sizeof(linha), f)) {
            if (sscanf(linha, "%s %d", nome_txt, &pontuacao) == 2) {
                strcpy(v[tam].nome, nome_txt);
                v[tam].pontos = pontuacao;
                tam++;
            }
        }
        fclose(f);
    }

    int existe = 0; //usado para saber se o nome ja existe na array
    for (int i = 0; i < tam; i++) {
        if (strcmp(v[i].nome, nome) == 0) {
            if (pontos > v[i].pontos) {
                v[i].pontos = pontos;
            }
            existe = 1;
            break;
        }
    }
    if (!existe) {
        strcpy(v[tam].nome, nome);
        v[tam].pontos = pontos;
        tam++;
    }
    f = fopen("ranking.txt", "w");
    for (int i = 0; i < tam; i++) {
        fprintf(f, "%s %d\n", v[i].nome, v[i].pontos);
    }
    fclose(f);
}


// Exibe ranking na interface raylib
void exibeRanking() {
    FILE *f = fopen("ranking.txt", "r");
    char linha[100];
    int y = 60;
    char nome[50];
    int pontuacao, tam=0;
    Jogadores v[20];
    
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
        DrawText(TextFormat("%d - %s",v[i].pontos, v[i].nome), 100, y, 20, RED);
        y += 30;
    }



    fclose(f);
}

