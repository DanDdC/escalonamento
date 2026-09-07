#ifndef TASK_H
#define TASK_H
#define MAX_TAREFAS 10
#define MAX_NOME 32

typedef struct{
    char nome[MAX_NOME];
    int periodo;
    int deadline;
    int burst;
    int ordem;
}Task;

int ler_tarefas(const char *arquivo, Task tarefas[], int *total, int *n);

#endif