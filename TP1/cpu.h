#ifndef CPU_H
#define CPU_H

typedef struct
{
    int opcode;
    int info1;
    int info2;
    int info3;
} Instruction;

typedef struct
{
    float *address;
    int tamanho;
} Memoria;

typedef struct
{
    Instruction *instrucoes;
    Memoria RAM;
} Machine;

void start(Machine *, Instruction *, int);

void stop(Machine *);

void run(Machine *);

void printRAM(Machine *);
// basicamente uma cópia da source

void menu(Machine *, int);

Instruction *instructionDoUsuario(Machine *, int);

#endif // CPU_H