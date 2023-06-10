#include "cpu.h"
#include "operacoes.h"
#include "gerador.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void start(Machine *machine, Instruction *instrucoes, int RAMSize)
{
    machine->instrucoes = instrucoes; 
    machine->RAM.address = (float *)malloc(RAMSize * sizeof(float));
    machine->RAM.tamanho = RAMSize;
    for (int i = 0; i < RAMSize; i++)
        machine->RAM.address[i] = (float)rand() / RAND_MAX;
}

void stop(Machine *machine)
{
    free(machine->instrucoes);
    free(machine->RAM.address);
}

void run(Machine *machine)
{
    // Registradores
    int PC = 0;     // Program Counter - Contador de programa
    int opcode = 0; // para inicializar o loop de instruçoes
    float value;
    int address1, address2, address3; 
    float RAMContent1, RAMContent2;    
    float result;

    while (opcode != -1)
    {
        Instruction instruction = machine->instrucoes[PC]; 
        opcode = instruction.opcode;                     

        switch (opcode)
        {
        case -1:
            printf("  > Finalizando a execução.\n");
            break;
        case 0: // Levando informação para a RAM
            value = (float)instruction.info1;
            address1 = instruction.info2;
            machine->RAM.address[address1] = value;
            printf("  > Levando informação (%f) para a RAM[%d].\n", value, address1);
            break;
        case 1: // Somando
            address1 = instruction.info1;
            address2 = instruction.info2;
            RAMContent1 = machine->RAM.address[address1];
            RAMContent2 = machine->RAM.address[address2];
            result = RAMContent1 + RAMContent2;
            address3 = instruction.info3;
            machine->RAM.address[address3] = result;
            printf("  > Somando RAM[%d] (%f) com RAM[%d] (%f) e salvando na RAM[%d] (%f).\n", address1, RAMContent1, address2, RAMContent2, address3, result);
            break;
        case 2: // Subtraindo
            address1 = instruction.info1;
            address2 = instruction.info2;
            RAMContent1 = machine->RAM.address[address1];
            RAMContent2 = machine->RAM.address[address2];
            result = RAMContent1 - RAMContent2;
            address3 = instruction.info3;
            machine->RAM.address[address3] = result;
            printf("  > Subtraindo RAM[%d] (%f) com RAM[%d] (%f) e salvando na RAM[%d] (%f).\n", address1, RAMContent1, address2, RAMContent2, address3, result);
            break;
        }
        PC++;
    }
}

void printRAM(Machine *machine)
{
    printf("\n  > RAM");
    for (int i = 0; i < machine->RAM.tamanho; i++)
        printf("\t\t[%5d] : %f\n", i, machine->RAM.address[i]);
}

void menu(Machine *machine, int RAMSize) // Menu
{
    int opcao_menu;
    float num1, num2, result;
    Instruction *instruction;

    printf("\nMENU:\n\n");
    printf("Escolha uma opção abaixo:\n0 - Programa Aleatório\n1 - Adição\n2 - Subtração\n3 - Multiplicação\n4 - Potenciação:   ");
    scanf("%d", &opcao_menu);

    switch (opcao_menu)
    {
    case 0: // Random
        instruction = geraInstrucoesAleatorias(RAMSize);

        start(machine, instruction, RAMSize);
        printRAM(machine);
        run(machine);
        break;
    case 1: // Soma
        printf("\nDigite os 2 numeros que deseja somar: ");
        scanf("%f%f", &num1, &num2);

        instruction = instructionDoUsuario(machine, 1); 
        start(machine, instruction, RAMSize);
        machine->RAM.address[0] = num1;
        machine->RAM.address[1] = num2;
        printRAM(machine);
        run(machine);
        break;

    case 2: // Subtração
        printf("\nDigite os 2 numeros que deseja subtrair: ");
        scanf("%f%f", &num1, &num2);

        instruction = instructionDoUsuario(machine, 2);

        start(machine, instruction, RAMSize);
        machine->RAM.address[0] = num1;
        machine->RAM.address[1] = num2;
        printRAM(machine);
        run(machine);
        break;

    case 3: // Multiplicação
        printf("\nDigite os 2 numeros que deseja multiplicar: ");
        scanf("%f%f", &num1, &num2);

        instruction = instructionDoUsuario(machine, 1);

        start(machine, instruction, RAMSize);
        machine->RAM.address[0] = num1;
        machine->RAM.address[1] = num2;
        machine->RAM.address[2] = 0; 
        printRAM(machine);
        result = multiplicacao(machine);
        printf("\n  > Multiplicado RAM[%d] (%f) com RAM[%d] (%f) e salvo na RAM[%d] (%f).\n", 0, num1, 1, num2, 2, result);
        break;
        
    case 4: // potencia
        printf("\nDigite os 2 numeros (base e exponente): ");
        scanf("%f%f", &num1, &num2);

        instruction = instructionDoUsuario(machine, 1);

        start(machine, instruction, RAMSize);
        machine->RAM.address[0] = num1;
        machine->RAM.address[1] = num2;
        machine->RAM.address[2] = 0; 
        printRAM(machine);
        result = potencia(machine);
        printf("\n  > A potência de RAM[%d] (%f) elevado a RAM[%d] (%f) foi salvo na RAM[%d] (%f).\n\n", 0, num1, 1, num2, 2, result);
        break;
    default:
        printf("Erro grave... finalizando.");
        exit(1);
        break;
    }
}

Instruction *instructionDoUsuario(Machine *machine, int opcode)
{
    Instruction *instrucoes = (Instruction *)malloc(2 * sizeof(Instruction));
    Instruction instruction;
    instruction.opcode = opcode;
    instruction.info1 = 0;
    instruction.info2 = 1;
    instruction.info3 = 2;

    Instruction instructionFinal;
    instructionFinal.opcode = -1;
    instructionFinal.info1 = -1;
    instructionFinal.info2 = -1;
    instructionFinal.info3 = -1;

    instrucoes[0] = instruction;
    instrucoes[1] = instructionFinal;

    return instrucoes;
}