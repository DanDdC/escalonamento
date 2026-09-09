#include <stdio.h>
#include <string.h>
#include "task.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "uso: %s <rate|edf> <arquivo>\n", argv[0]);
        return 1;
    }
    if (strcmp(argv[1], "rate") != 0 && strcmp(argv[1], "edf") != 0) {
        fprintf(stderr, "erro: algoritmo deve ser rate ou edf\n");
        return 1;
    }
    Task tarefas[MAX_TAREFAS];
    int total, n;
    if (ler_tarefas(argv[2], tarefas, &total, &n) != 0) {
        return 1;
    }
    printf("parser ok: total=%d n=%d algoritmo=%s\n", total, n, argv[1]);
    for (int i = 0; i < n; i++) {
        printf("%s %d %d %d\n", tarefas[i].nome, tarefas[i].periodo, tarefas[i].deadline, tarefas[i].burst);
    }
    return 0;
}
