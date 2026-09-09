#include <stdio.h>
#include <string.h>
#include "sim.h"
#include "output.h"

int simular(Task tarefas[], int n, int total, int is_rate) {
    int remaining[MAX_TAREFAS];
    int deadline_abs[MAX_TAREFAS];
    int prox_chegada[MAX_TAREFAS];
    int complete[MAX_TAREFAS];
    int lost[MAX_TAREFAS];
    int killed[MAX_TAREFAS];
    int timeline[2000];

    for (int i = 0; i < n; i++) {
        remaining[i] = 0;
        deadline_abs[i] = -1;
        prox_chegada[i] = 0;
        complete[i] = 0;
        lost[i] = 0;
        killed[i] = 0;
    }

    for (int t = 0; t < total; t++) {
        for (int i = 0; i < n; i++) {
            if (t == prox_chegada[i]) {
                remaining[i] = tarefas[i].burst;
                deadline_abs[i] = t + tarefas[i].deadline;
                prox_chegada[i] += tarefas[i].periodo;
            }
        }
        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0 && deadline_abs[i] != -1 && t == deadline_abs[i]) {
                lost[i]++;
                remaining[i] = 0;
                deadline_abs[i] = -1;
            }
        }
        int escolhida = -1;
        for (int i = 0; i < n; i++) {
            if (remaining[i] <= 0) continue;
            if (escolhida == -1) { escolhida = i; continue; }
            if (is_rate) {
                if (tarefas[i].periodo < tarefas[escolhida].periodo) escolhida = i;
            } else {
                if (deadline_abs[i] < deadline_abs[escolhida]) escolhida = i;
            }
        }
        timeline[t] = escolhida;
        if (escolhida != -1) {
            remaining[escolhida]--;
            if (remaining[escolhida] == 0) {
                complete[escolhida]++;
                deadline_abs[escolhida] = -1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (remaining[i] > 0) killed[i]++;
    }

    char nome_arq[64];
    if (is_rate) strcpy(nome_arq, "rate_ddc.out");
    else strcpy(nome_arq, "edf_ddc.out");
    FILE *f = fopen(nome_arq, "w");
    if (!f) return -1;
    if (is_rate) fprintf(f, "EXECUTION BY RATE\n");
    else fprintf(f, "EXECUTION BY EDF\n");

    int i = 0;
    while (i < total) {
        int cur = timeline[i];
        int j = i;
        while (j < total && timeline[j] == cur) j++;
        int len = j - i;
        if (cur == -1) {
            fprintf(f, "idle for %d units\n", len);
        } else {
            int arrival = (i / tarefas[cur].periodo) * tarefas[cur].periodo;
            int deadline = arrival + tarefas[cur].deadline;
            char flag = 'F';
            if (j == deadline) flag = 'L';
            else {
                int has_next = 0;
                for (int k = j; k < deadline && k < total; k++) {
                    if (timeline[k] == cur) { has_next = 1; break; }
                }
                if (has_next) flag = 'H';
                else flag = 'F';
            }
            if (flag == 'L') {
                int found = 0;
                for (int k = 0; k < n; k++) if (k == cur && lost[k] > 0) found = 1;
                if (!found) flag = 'H';
            }
            fprintf(f, "[%s] for %d units - %c\n", tarefas[cur].nome, len, flag);
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
    return 0;
}
