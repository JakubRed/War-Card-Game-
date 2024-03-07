#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdbool.h>
#include "Include/functions.h"


GAME_RESULTS oneWholeGame(
    int deckQty,
    int jockers
)
{    
    GAME_RESULTS result;
    TWO_DECKS * pPlayset;
    // inicializePlayset(pPlayset);
    struct card * pDeck1 = NULL;
    struct card * pDeck2 = NULL;
    pPlayset->pDeck1 = pDeck1;
    pPlayset->pDeck2 = pDeck2;
    createTwoDecks(&pDeck1, &pDeck2, deckQty, jockers);
    // showBothDecks(pDeck1, pDeck2); 
    
    result = actualGame(&pDeck1, &pDeck2);
    // showBothDecks(pDeck1, pDeck2); 
    return result;
}

void showResult(
    GAME_RESULTS result)
{
    if ((FISRT_IS_WINNER == result.winner || FISRT_IS_WINNER + OPPONENT_OUT_OF_CARDS == result.winner) && NULL == result.pDeck2);
    else if((SECOND_IS_WINNER == result.winner || SECOND_IS_WINNER + OPPONENT_OUT_OF_CARDS == result.winner) && NULL == result.pDeck1);
    else {
        printf("Result Error~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        // return;
    }
    printf("\nRESULTS:\n");
    printf("Deck %d won in %d rounds.\n", result.winner, result.rounds);
    showBothDecks(result.pDeck1, result.pDeck2);
    
}