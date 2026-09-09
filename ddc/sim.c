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

    for (int i = 0; i < n; i++) {
        if (prox_chegada[i] == 0) {
            remaining[i] = tarefas[i].burst;
            deadline_abs[i] = 0 + tarefas[i].periodo;
            prox_chegada[i] = tarefas[i].periodo;
        }
    }

    for (int t = 0; t < total; t++) {
        int escolhida = -1;
        for (int i = 0; i < n; i++) {
            if (remaining[i] <= 0) continue;
            if (escolhida == -1) { escolhida = i; continue; }
            if (is_rate) {
                if (tarefas[i].periodo < tarefas[escolhida].periodo) escolhida = i;
            } else {
                if (tarefas[i].periodo < tarefas[escolhida].periodo) escolhida = i;
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

        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0 && deadline_abs[i] != -1 && t > deadline_abs[i]) {
                lost[i]++;
                remaining[i] = 0;
                deadline_abs[i] = -1;
            }
        }

        for (int i = 0; i < n; i++) {
            if (t + 1 == prox_chegada[i]) {
                remaining[i] = tarefas[i].burst;
                deadline_abs[i] = (t + 1) + tarefas[i].periodo;
                prox_chegada[i] += tarefas[i].periodo;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (remaining[i] > 0) {
            killed[i]++;
        }
    }

    const char *alg = is_rate ? "rate" : "edf";
    escrever_saida(alg, tarefas, n, total, timeline, complete, lost, killed);
    return 0;
}
