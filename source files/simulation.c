#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdbool.h>
#include "Include/functions.h"

void initializeGameParams(GAME * gameInst, int decksQuantity, int jockersQuantity)
{
    gameInst->startParams.decksQty = decksQuantity;
    gameInst->startParams.jokersQty = jockersQuantity;
    gameInst->rounds = FIRST_ROUND;
    gameInst->winner = NO_WINNER;
    gameInst->pPlayset.pDeck1 = NULL;
    gameInst->pPlayset.pDeck2 = NULL;
}

GAME simulation(
    int decksQuantity, 
    int jockersQuantity)
{
    GAME gameInst;
    initializeGameParams(&gameInst, decksQuantity, jockersQuantity);
    oneWholeGame(&gameInst);
    showResult(gameInst);
    clearMemoryLinkedList(gameInst.pPlayset.pDeck1);
    clearMemoryLinkedList(gameInst.pPlayset.pDeck2);

    return gameInst;
}

void oneWholeGame(
    GAME * gameInst)
{    
    createTwoDecks(gameInst);
    showBothDecks(gameInst->pPlayset.pDeck1, gameInst->pPlayset.pDeck2); 
    actualGame(gameInst);
}

void showResult(
    GAME gameInst)
{
    if ((FISRT_IS_WINNER == gameInst.winner || FISRT_IS_WINNER + OPPONENT_OUT_OF_CARDS == gameInst.winner) && NULL == gameInst.pPlayset.pDeck2);
    else if((SECOND_IS_WINNER == gameInst.winner || SECOND_IS_WINNER + OPPONENT_OUT_OF_CARDS == gameInst.winner) && NULL == gameInst.pPlayset.pDeck1);
    else {
        printf("Result Error\n");
        // return;
    }
    printf("\nRESULTS:\n");
    printf("Deck %d won in %d rounds.\n", gameInst.winner, gameInst.rounds);
    showBothDecks(gameInst.pPlayset.pDeck1, gameInst.pPlayset.pDeck2);
}