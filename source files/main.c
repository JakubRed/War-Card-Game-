#include <stdio.h>
#include <stdlib.h> 
#include "Include/constants.h"
#include "game.c"
#include "prepareDeck.c"
#include "simulation.c"


int main()
{
    system("cls");
    printf("START\n\n");
    simulation(1, 0);

    printf("\nEND");
    return 0;
}
