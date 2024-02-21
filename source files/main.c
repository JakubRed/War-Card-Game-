#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include "constants.h"
// #include "functions.h"
#include "functions.c"

int main()
{
    // system("cls");
    struct card * Deck1 = NULL;
    struct card * Deck2 = NULL;

    Deck1 = createDeck (1, 0);

    Deck2 = splitEqually(Deck1);  
    // Deck1 = shuffle(Deck1, 200);
    // Deck2 = shuffle(Deck2, 200);
    // printf("\nAfter Shuffle:\n");
    // showDeck (Deck2);
    actualGame(Deck1, Deck2);
    // printf("\nD1\n");
    // showDeck (Deck1);
    // printf("\nD2\n");
    // showDeck (Deck2);

    clearMemory(Deck1);
    clearMemory(Deck2);
    printf("\nEND\n");
    return 0;
}