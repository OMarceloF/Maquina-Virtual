#include "gerador.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Instruction *geraInstrucoesAleatorias(int RAMSize)
{
    // 01|22|13|45 => isto é uma instrução
    // 02|33|12|01 => isto é outra instrução

    // 0 => salvar na memória
    // 1 => opcode => somar
    // 2 => opcode => subtrair
    //-1 => halt

    // 22 => significa um endereço da RAM (10 endereço)
    // 13 => significa 2o endereço
    // 45 => significa 3o address
    // ramSize => ESTA FORA DO INTERVALO DE 0 A ramSize DA MEMÓRIA RAM
    srand(time(NULL));
    Instruction *instrucoes = (Instruction *)malloc(10 * sizeof(Instruction));

    for (int i = 0; i < 9; i++)
    {
        instrucoes[i].opcode = rand() % 3;         // 0, 1, 2, 3
        instrucoes[i].info1 = rand() % RAMSize; // 0 ... RAM_SIZE
        do
        {
            instrucoes[i].info2 = rand() % RAMSize; // 0 ... RAM_SIZE
        } while (instrucoes[i].info1 == instrucoes[i].info2);
        instrucoes[i].info3 = rand() % RAMSize; // 0 ... RAM_SIZE
    }

    // inserindo a ultima instrucao do programa que nao faz nada que presta
    instrucoes[9].opcode = -1;
    instrucoes[9].info1 = -1;
    instrucoes[9].info2 = -1;
    instrucoes[9].info3 = -1;

    return instrucoes;
}

Instruction *leInstrucoes(char *nomeArquivo, int *RAMSize)
{
    Instruction *instrucoes = (Instruction *)malloc(10 * sizeof(Instruction));
    return instrucoes;
}