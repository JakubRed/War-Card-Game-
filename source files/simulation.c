#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdbool.h>
#include "Include/functions.h"


GAME * oneWholeGame(
    GAME * gameInst
)
{    
    printf("LessaGo\n");
    // inicializePlayset(pPlayset);
    struct card * D1;
    struct card * D2;
    gameInst->pPlayset.pDeck1 = D1;
    gameInst->pPlayset.pDeck2 = D2;
    printf("LessaGo\n");
    gameInst->rounds = 1;
    gameInst->winner = 0;
    // pPlayset->pDeck1 = pDeck1;
    // pPlayset->pDeck2 = pDeck2;
    createTwoDecks(gameInst);
    showBothDecks(gameInst->pPlayset.pDeck1, gameInst->pPlayset.pDeck2); 
    
    gameInst = actualGame(gameInst);
    // showBothDecks(pDeck1, pDeck2); 
    return gameInst;
}

void showgameInst(
    GAME * gameInst)
{
    if ((FISRT_IS_WINNER == gameInst->winner || FISRT_IS_WINNER + OPPONENT_OUT_OF_CARDS == gameInst->winner) && NULL == gameInst->pPlayset.pDeck2);
    else if((SECOND_IS_WINNER == gameInst->winner || SECOND_IS_WINNER + OPPONENT_OUT_OF_CARDS == gameInst->winner) && NULL == gameInst->pPlayset.pDeck1);
    else {
        printf("gameInst Error~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        // return;
    }
    printf("\ngameInstS:\n");
    printf("Deck %d won in %d rounds.\n", gameInst->winner, gameInst->rounds);
    showBothDecks(gameInst->pPlayset.pDeck1, gameInst->pPlayset.pDeck2);
    
}