#include "raylib.h"
#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "janela.h"
#include "ranking.h"

void criaRanking(){
    FILE *f;
    f = fopen("ranking.txt", "a");

}
void exibeRanking(FILE* f){
    FILE *f = fopen("ranking.txt", "r");
    char linha[100];

    if (f == NULL) {
        printf("Ainda não existe ranking salvo.\n");
        return;
    }

    while (fgets(linha, sizeof(linha), f) != NULL) {
        printf("%s", linha);
    }

    fclose(f);
}

void insereRanking(Jogador jogadores[], int n){
    FILE *f = fopen("ranking.txt", "w");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fprintf(f, "=== Ranking de Jogadores ===\n");
    for (int i = 0; i < n; i++) {
        fprintf(f, "%dº %s - %d pontos\n", i+1, jogadores[i].nome, jogadores[i].pontos);
    }

    fclose(f);
    printf("Ranking salvo com sucesso!\n");
}
