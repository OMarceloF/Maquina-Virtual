#include "cpu.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int RAMSize;
    printf("INSIRA O TAMANHO DA RAM: ");
    scanf("%d", &RAMSize);

    Machine machine;
    printf("Iniciando máquina...\n");
    menu(&machine, RAMSize);
    printRAM(&machine);
    stop(&machine);
    printf("Desligando máquina...\n");

    return 0;
}