#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "task.h"

int ler_tarefas(const char *arquivo, Task tarefas[], int *total, int *n) {
    FILE *f = fopen(arquivo, "r");
    if (!f) {
        fprintf(stderr, "erro: arquivo %s nao encontrado\n", arquivo);
        return -1;
    }
    char linha[128];
    if (!fgets(linha, sizeof(linha), f)) {
        fprintf(stderr, "erro: arquivo vazio\n");
        fclose(f);
        return -1;
    }
    char *fim;
    long tot = strtol(linha, &fim, 10);
    if (fim == linha) {
        fprintf(stderr, "erro: tempo total invalido\n");
        fclose(f);
        return -1;
    }
    if (tot <= 0) {
        fprintf(stderr, "erro: tempo total deve ser positivo\n");
        fclose(f);
        return -1;
    }
    *total = (int)tot;
    *n = 0;

    while (fgets(linha, sizeof(linha), f)) {
        if (linha[0] == '\n' || linha[0] == '#') continue;
        int so_espaco = 1;
        for (int i = 0; linha[i] != '\0'; i++) {
            if (linha[i] != ' ' && linha[i] != '\t' && linha[i] != '\n' && linha[i] != '\r') { so_espaco = 0; break; }
        }
        if (so_espaco) continue;

        char nome[MAX_NOME];
        int p, d, c;
        if (sscanf(linha, "%31s %d %d %d", nome, &p, &d, &c) != 4) {
            fprintf(stderr, "erro: linha malformada: %s", linha);
            fclose(f);
            return -1;
        }
        if (p <= 0 || d <= 0 || c <= 0) {
            fprintf(stderr, "erro: tarefa %s tem valor nao positivo\n", nome);
            fclose(f);
            return -1;
        }
        if (c > d || d > p) {
            fprintf(stderr, "erro: tarefa %s viola C <= D <= P\n", nome);
            fclose(f);
            return -1;
        }
        if (*n >= MAX_TAREFAS) {
            fprintf(stderr, "erro: muitas tarefas (max %d)\n", MAX_TAREFAS);
            fclose(f);
            return -1;
        }
        strcpy(tarefas[*n].nome, nome);
        tarefas[*n].periodo = p;
        tarefas[*n].deadline = d;
        tarefas[*n].burst = c;
        tarefas[*n].ordem = *n;
        (*n)++;
    }
    fclose(f);
    if (*n == 0) {
        fprintf(stderr, "erro: nenhuma tarefa encontrada\n");
        return -1;
    }
    return 0;
}
