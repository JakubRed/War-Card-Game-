#include <stdio.h>
#include <stdlib.h> 
// #include <stdbool.h>
#include "Include/constants.h"
// #include "functions.h"
#include "game.c"
#include "prepareDeck.c"
#include "simulation.c"

// void inicializePlayset(TWO_DECKS * pPlayset)
// {
//     pPlayset->pDeck1 = NULL;
//     pPlayset->pDeck2 = NULL;
// }
int main()
{
    system("cls");
    printf("START\n");
    GAME_RESULTS result;
    result = oneWholeGame(1, 0);
    showResult(result);
    // // TWO_DECKS * pPlayset;
    // // inicializePlayset(pPlayset);
    // struct card * pDeck1 = NULL;
    // struct card * pDeck2 = NULL;
    // // pPlayset->pDeck1 = pDeck1;
    // // pPlayset->pDeck2 = pDeck2;
    // createTwoDecks(&pDeck1, &pDeck2, 1, 0);
    // showBothDecks(pDeck1, pDeck2); 
    
    // actualGame(&pDeck1, &pDeck2);
    // showBothDecks(pDeck1, pDeck2); 

    // clearMemory(pDeck1);
    // clearMemory(pDeck2);
    printf("\nEND");
    return 0;
}
