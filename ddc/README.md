# escalonamento - ddc

Simulador rate e edf para tarefas criticas de voo.

## Arquivos
| Arquivo | Responsabilidade |
|---|---|
| `main.c` | CLI, validacao de args e chamada do simulador |
| `task.h/c` | struct Task e leitura/validacao de voo.txt (C<=D<=P) |
| `sim.h/c` | motor tick-a-tick, prioridades rate/edf, LOST/COMPLETE/KILLED |
| `output.h/c` | formatacao EXECUTION BY, idle e LOST/COMPLETE/KILLED |
| `voo.txt` | exemplo do enunciado (100 / ATT 20 12 8 / NAV 50 30 15) |
| `comparativo.txt` | mesmo caso para analise rate vs edf |
| `run_tests.sh` | suite de casos limite e invalidos |
| `Makefile` | compilacao, limpeza e teste |

## Como compilar
```bash
make clean && make
```

## Como executar
```bash
./scheduler rate voo.txt   # gera rate_ddc.out
./scheduler edf voo.txt    # gera edf_ddc.out
cat rate_ddc.out
cat edf_ddc.out
```

## Como testar
```bash
make test
```

## SO
Ubuntu/WSL, gcc -Wall -Wextra -std=c99