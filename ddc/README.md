# escalonamento - ddc

Simulador rate e edf para tarefas criticas de voo.

## Arquivos
| Arquivo | Responsabilidade |
|---|---|
| `main.c` | CLI, validacao de args e chamada do parser |
| `task.h/c` | struct Task e leitura/validacao de voo.txt (C<=D<=P) |
| `voo.txt` | exemplo do enunciado (100 / ATT 20 12 8 / NAV 50 30 15) |
| `Makefile` | compilacao e limpeza |

## Como compilar
```bash
make clean && make
```

## Como executar
```bash
./scheduler rate voo.txt
./scheduler edf voo.txt
```

## SO
Ubuntu/WSL, gcc -Wall -Wextra -std=c99