#ifndef TASK_H
#define TASK_H
#define MAX_TAREFAS 10
#define MAX_NOME 32

typedef struct {
    char nome[MAX_NOME];
    int periodo;   // P
    int deadline;  // D
    int burst;     // C
    int ordem;     // posicao no arquivo
} Task;

int ler_tarefas(const char *arquivo, Task tarefas[], int *total, int *n);

#endif