#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "Include/functions.h"

void showResults(
    int Round, 
    struct card* pDeck1,
    struct card* pDeck2)
    {
        printf("\npRound %d.\n", Round);
        showBothDecks(pDeck1, pDeck2);
    }
int compare(
    struct card* pDeck1Card, 
    struct card* pDeck2Card)
{
    int retVal = GENERIC_ERROR;

    if (pDeck1Card->rank > pDeck2Card->rank) {
        retVal = FISRT_IS_WINNER; //first card wins
    }
    else if (pDeck1Card->rank < pDeck2Card->rank) {
        retVal = SECOND_IS_WINNER; //second card wins
    }
    else if (pDeck1Card->rank == pDeck2Card->rank) {
        retVal = ITS_A_DRAW; //it's a draw
    }
    else{
        printf("ERROR in compare()\n");
    }
    return retVal;
}

void addDeckToEnd(
    struct card* pPrimaryDeck,
    struct card* pToBeAdded)
{
    if (NULL == pPrimaryDeck)
    {
        printf("Error in addDeckToEnd(), pPrimaryDeck is NULL\n");
    }
    if (NULL == pToBeAdded)
    {
        printf("Error in addDeckToEnd(), pToBeAdded is NULL\n");
    }
    
    while (NULL != pPrimaryDeck->nextCard)
    {
        pPrimaryDeck = pPrimaryDeck->nextCard;
    }
    pPrimaryDeck->nextCard = pToBeAdded;    
}

struct card*  shiftPointer(
    struct card* pDeck,
    int amount)
{
    for (size_t i = 0; i < amount; i++)
    {
        pDeck = pDeck->nextCard;
    }
    return pDeck;

}

void conquer(
    struct card** pVictor,
    struct card** pVictorEnd,
    struct card** pVanquished)
{   
    if (NULL == pVictor)
    {
        printf("Error in conquer(), pVictor is NULL\n");
    }
    if (NULL == pVictorEnd)
    {
        printf("Error in conquer(), pVictorEnd is NULL\n");
    }     
    if (NULL == pVanquished)
    {
        printf("Error in conquer(), pVictorEnd is pVanquished\n");
    }
    (*pVictorEnd)->nextCard = (*pVanquished);
    (*pVanquished) = (*pVanquished)->nextCard;
    (*pVictorEnd) = (*pVictorEnd)->nextCard;

    (*pVictorEnd)->nextCard = (*pVictor);
    (*pVictor) = (*pVictor)->nextCard;
    (*pVictorEnd) = (*pVictorEnd)->nextCard;
    (*pVictorEnd)->nextCard= NULL;
}

int war(
    struct card** pDeck1Start,
    struct card** pDeck1End,
    struct card** pDeck2Start,
    struct card** pDeck2End)
{
    struct card* pDeck1Current = (*pDeck1Start);
    struct card* pDeck2Current = (*pDeck2Start);
    struct card* pPool = NULL;
    int winner = 0, insideWinner = 0;

    if (NULL == pDeck1Start)
    {
        printf("Error in war(), pDeck1Start is NULL\n");
    }  
    if (NULL == pDeck1End)
    {
        printf("Error in war(), pDeck1End is NULL\n");
    }   
    if (NULL == pDeck2Start)
    {
        printf("Error in war(), pDeck2Start is NULL\n");
    }    
    if (NULL == pDeck2End)
    {
        printf("Error in war(), pDeck2End is NULL\n");
    }
  
    if (shiftPointer(pDeck1Current, 1) == NULL || shiftPointer(pDeck1Current, 2) == NULL)
    {
        (*pDeck2End)->nextCard = pDeck1Current;
        (*pDeck1Start) = NULL;
        return SECOND_IS_WINNER;
    }
    else if (shiftPointer(pDeck2Current, 1) == NULL || shiftPointer(pDeck2Current, 2) == NULL)
    {
        (*pDeck1End)->nextCard = pDeck2Current;
        (*pDeck2Start) = NULL;
        return FISRT_IS_WINNER;
    }    
    
    //switch to hidden card
    pDeck1Current = shiftPointer(pDeck1Current, 2);
    pDeck2Current = shiftPointer(pDeck2Current, 2);
    // pDeck1Current = pDeck1Current->nextCard;
    // pDeck2Current = pDeck2Current->nextCard;
    // // switch to second combatant
    // pDeck1Current = pDeck1Current->nextCard;
    // pDeck2Current = pDeck2Current->nextCard;

    winner = compare(pDeck1Current, pDeck2Current);
    switch (winner)
    {
    case FISRT_IS_WINNER:
        (*pDeck1End)->nextCard = (*pDeck1Start);
        (*pDeck1Start) = pDeck1Current->nextCard;
        (*pDeck1End) = pDeck1Current;
        pDeck1Current->nextCard = (*pDeck2Start);
        (*pDeck2Start) = pDeck2Current->nextCard;
        pDeck2Current->nextCard = NULL;
        (*pDeck1End) = pDeck2Current;
        break;
    case SECOND_IS_WINNER:     
        (*pDeck2End)->nextCard = (*pDeck2Start);
        (*pDeck2Start) = pDeck2Current->nextCard;
        (*pDeck2End) = pDeck2Current;
        pDeck2Current->nextCard = (*pDeck1Start);
        (*pDeck1Start) = pDeck1Current->nextCard;
        pDeck1Current->nextCard = NULL;
        (*pDeck2End) = pDeck1Current;
        break;
    case ITS_A_DRAW:
        pPool = (*pDeck1Start);
        (*pDeck1Start) = pDeck1Current;
        pPool->nextCard->nextCard = (*pDeck2Start);
        (*pDeck2Start) = pDeck2Current;        
        pPool->nextCard->nextCard->nextCard->nextCard = NULL;

        winner = war(pDeck1Start, pDeck1End, pDeck2Start, pDeck2End); //switched variable changed in one of statements

        switch (winner)
        {
        case FISRT_IS_WINNER:
            addDeckToEnd((*pDeck1End), pPool);
            (*pDeck1End) = shiftPointer(pPool, 3);         
               break;
        case SECOND_IS_WINNER:
            addDeckToEnd((*pDeck2End), pPool);
            (*pDeck2End) = shiftPointer(pPool, 3);        
            break;
        case ITS_A_DRAW:
            printf("It ain't be like that.\n");        
        default:
            printf("Error in war() - %d\n", winner);
            break;
        }
        break;
    default:
        printf("Error in war() compare - %d\n", winner);
        break;
    }
    return winner;
}

GAME actualGame(
    GAME * gameInst
)
{    
    struct card* pDeck1Start = gameInst->pPlayset.pDeck1;
    struct card* pDeck2Start = gameInst->pPlayset.pDeck2;
    struct card* pDeck1End = pDeck1Start;  
    struct card* pDeck2End = pDeck2Start;

    if (NULL == gameInst)
    {
        printf("Error in actualGame(), gameInst is NULL\n");
    }

    while (NULL != pDeck1End->nextCard)
    {
        pDeck1End = pDeck1End->nextCard;
    }
    while (NULL != pDeck2End->nextCard)
    {
        pDeck2End = pDeck2End->nextCard;
    }

    while (NULL != pDeck1Start && NULL != pDeck2Start)
    {              
        gameInst->winner = compare(pDeck1Start, pDeck2Start);
        switch (gameInst->winner)
        {
        case FISRT_IS_WINNER:
            conquer(&pDeck1Start, &pDeck1End, &pDeck2Start);
            break;
        case SECOND_IS_WINNER:
            conquer(&pDeck2Start, &pDeck2End, &pDeck1Start);
            break;
        case ITS_A_DRAW:
            gameInst->winner = war(&pDeck1Start, &pDeck1End, &pDeck2Start, &pDeck2End);
            break;        
        default:
            printf("Error in actualGame(), impossible comparison result\n");
            break;
        }     
        gameInst->rounds++;     
        // showResults(gameInst->rounds, pDeck1Start, pDeck2Start) ;        
    }  
    gameInst->pPlayset.pDeck1 = pDeck1Start;
    gameInst->pPlayset.pDeck2 = pDeck2Start;
    // free(pDeck1Start);
    // free(pDeck2Start);
    // free(pDeck1End);
    // free(pDeck2End);
}

void clearMemoryLinkedList(
    struct card* pFirstCard) 
{
    struct card* pCurrent = pFirstCard;
    struct card* pNextCard;

    while (NULL != pCurrent) {
        pNextCard = pCurrent->nextCard;  
        free(pCurrent);
        pCurrent = pNextCard;
    }
}