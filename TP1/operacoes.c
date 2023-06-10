#include "operacoes.h"
#include "cpu.h"
#include "gerador.h"

#include <stdio.h>


// TENTATIVA DE FAZER A DIVISÃO

/*
float divisao(Machine *machine)
{
    float num1 = machine->RAM.address[0];
    float num2 = machine->RAM.address[1];
    
    if (num2 == 0)
    {
        printf("Erro: Divisão por zero.\n");
        return 0;
    }

    bool num1Negativo = num1 < 0;
    bool num2Negativo = num2 < 0;
    num1 = fabs(num1);
    num2 = fabs(num2);
    
    float resultado = 0;
    float resto = num1;

    while (resto >= num2)
    {
        resto -= num2;
        resultado++;
    }

    if ((num1Negativo && !num2Negativo) || (!num1Negativo && num2Negativo))
        resultado = -resultado;

    machine->RAM.address[2] = resultado;

    return resultado;
}

}*/

float multiplicacao(Machine *machine) // multiplicação
{
    float resultado;
    float num1 = machine->RAM.address[0];
    float num2 = machine->RAM.address[1];
    machine->instrucoes->info2 = 2; 

    if (num1 == 0 || num2 == 0)
        resultado = 0;
    float num1_mod, num2_mod;
    if (num1 < 0)
    {
        num1_mod = -num1;
        machine->RAM.address[0] = num1_mod;
    }
    else
        num1_mod = num1;
    if (num2 < 0)
    {
        num2_mod = -num2;
        machine->RAM.address[1] = num2_mod;
    }
    else
        num2_mod = num2;

    for (int i = 0; i < num2_mod; i++)
    {
        run(machine);
    }
    resultado = machine->RAM.address[0];

    if ((num1 < 0 && num2 > 0) || (num1 > 0 && num2 < 0))
        resultado = -resultado;
    return resultado;
}

float potencia(Machine *machine) // potenciação
{
    float num1 = machine->RAM.address[0];
    float num2 = machine->RAM.address[1];
    float resultado = 1;

    if (num2 == 0)
        return 1;

    
    for (int i = 0; i < num2; i++)
    {
        machine->RAM.address[1] = resultado;
        resultado = machine->RAM.address[0] * machine->RAM.address[1];
    }

    machine->RAM.address[0] = num1;
    machine->RAM.address[1] = num2;
    machine->RAM.address[2] = resultado;

    return resultado;
}