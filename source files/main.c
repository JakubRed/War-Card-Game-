#include <stdio.h>
#include <stdlib.h> 
#include "Include/constants.h"
#include "Include/functions.h"
#include "game.c"
#include "prepareDeck.c"
#include "simulation.c"

int main()
{
    system("cls");
    printf("START\n\n");
    // simulation(1, 2);
    TEST_CASE test1;

    printf("[1]\n");
    test1 = initializeTestCases(1, 2, 0, 5, 3);

    printf("[4]\n");
    researchFunc(&test1);

    printf("[7]\n");
    printf("\nEND");
    return 0;
}
