#include <stdio.h>
#include <string.h>
#include "output.h"

void escrever_saida(const char *algoritmo, Task tarefas[], int n, int total, int timeline[], int complete[], int lost[], int killed[]) {
    char nome_arq[64];
    if (strcmp(algoritmo, "rate") == 0) strcpy(nome_arq, "rate_ddc.out");
    else strcpy(nome_arq, "edf_ddc.out");

    FILE *f = fopen(nome_arq, "w");
    if (!f) return;

    if (strcmp(algoritmo, "rate") == 0) fprintf(f, "EXECUTION BY RATE\n");
    else fprintf(f, "EXECUTION BY EDF\n");

    int i = 0;
    while (i < total) {
        int atual = timeline[i];
        int j = i;
        while (j < total && timeline[j] == atual) j++;
        int len = j - i;
        if (atual == -1) {
            fprintf(f, "idle for %d units\n", len);
        } else {
            fprintf(f, "[%s] for %d units - F\n", tarefas[atual].nome, len);
        }
        i = j;
    }

    fprintf(f, "\nLOST DEADLINES\n");
    for (int k = 0; k < n; k++) fprintf(f, "[%s] %d\n", tarefas[k].nome, lost[k]);

    fprintf(f, "\nCOMPLETE EXECUTION\n");
    for (int k = 0; k < n; k++) fprintf(f, "[%s] %d\n", tarefas[k].nome, complete[k]);

    fprintf(f, "\nKILLED\n");
    for (int k = 0; k < n; k++) fprintf(f, "[%s] %d\n", tarefas[k].nome, killed[k]);

    fclose(f);
}
