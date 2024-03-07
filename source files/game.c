#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdbool.h>
#include "Include/functions.h"

// void printPtr(int iteration,
//     struct card* pFirstCard,
//     struct card* newDeck,
//     struct card* pCurrentOriginalDeck,
//     struct card* pCurrentNewDeck);

GAME_RESULTS showResults(
    int* pRound, 
    struct card* pDeck1,
    struct card* pDeck2)
    {
        printf("\npRound %d.", (*pRound)++);
        showBothDecks(pDeck1, pDeck2);
    }
// void swap(
//     struct card* ptr1, 
//     struct card* ptr2)
// {
//     struct card* tmp = ptr2->nextCard;
//     ptr2->nextCard = ptr1;
//     ptr1->nextCard = tmp;
// }

int compare(
    struct card* pDeck1Card, 
    struct card* pDeck2Card)
{
    int retVal = GENERIC_ERROR;

    // if (NULL == pDeck1Card)
    // {
    //     return FISRT_IS_WINNER + OPPONENT_OUT_OF_CARDS;
    // }
    // else if (NULL == pDeck2Card)
    // {
    //     return SECOND_IS_WINNER + OPPONENT_OUT_OF_CARDS;
    // }    

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

void conquer(struct card** pVictor, struct card** pVictorEnd, struct card** pVanquished)
{
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

    //tbd - should return so all other wars would be lost as well  
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
    pDeck1Current = pDeck1Current->nextCard;
    pDeck2Current = pDeck2Current->nextCard;
    //switch to second combatant
    pDeck1Current = pDeck1Current->nextCard;
    pDeck2Current = pDeck2Current->nextCard;

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
            printf("ERROR in WAR() - %d\n", winner);
            break;
        }
        break;
    default:
        printf("ERROR in WAR() compare - %d\n", winner);
        break;
    }
    return winner;
}

GAME_RESULTS actualGame(
    struct card**pDeck1, 
    struct card** pDeck2)
{
    int winner = 0, round = 1;
    struct card* pDeck1Start = (*pDeck1);
    struct card* pDeck2Start = (*pDeck2);
    struct card* pDeck1End = pDeck1Start;  
    struct card* pDeck2End = pDeck2Start;
    GAME_RESULTS result;
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
        winner = compare(pDeck1Start, pDeck2Start);
        switch (winner)
        {
        case FISRT_IS_WINNER:
            conquer(&pDeck1Start, &pDeck1End, &pDeck2Start);
            break;
        case SECOND_IS_WINNER:
            conquer(&pDeck2Start, &pDeck2End, &pDeck1Start);
            break;
        case ITS_A_DRAW:
            winner = war(&pDeck1Start, &pDeck1End, &pDeck2Start, &pDeck2End);

            break;
        
        default:
            break;
        }     
        round++;
    // showResults(&round, pDeck1Start, pDeck2Start);                 
    }  
    // printf("End after mere %d. rounds :)\n", round);
    (*pDeck1) = pDeck1Start;
    (*pDeck2) = pDeck2Start;

    result.pDeck1 = (*pDeck1);
    result.pDeck2 = (*pDeck2);
    result.rounds = round;
    result.winner = winner;

    return result;
}
    
void clearMemory(
    struct card* pFirstCard) {
    struct card* pCurrent = pFirstCard;
    struct card* pNextCard;

    while (NULL != pCurrent) {
        pNextCard = pCurrent->nextCard;  // Save the next node before freeing the current one
        free(pCurrent);             // Free the current node
        pCurrent = pNextCard;        // Move to the next node
    }
}
//Debug~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void printPtr(int iteration,
    struct card* pFirstCard,
    struct card* newDeck,
    struct card* pCurrentOriginalDeck,
    struct card* pCurrentNewDeck) {
        printf("%d. \n", iteration);

        printf("Old D \n");
        showDeck(pFirstCard);
        printf("New D \n");
        showDeck(newDeck);
    }
void findMinMax(int arr[], int size, int *min, int *max) {
    // Check if the array is empty
    if (size == 0) {
        printf("Array is empty.\n");
        return;
    }
    // Initialize min and max with the first element
    *min = arr[0];
    *max = arr[0];
    // Iterate through the array to find min and max
    for (int i = 1; i < size; i++) {
        if (arr[i] < *min) {
            *min = arr[i];
        }
        if (arr[i] > *max) {
            *max = arr[i];
        }
    }
}
#define SIZE 10000
void random()
{
    int pMin = 0;
    int pMax = 0;
    srand(time(NULL));
    int arr[SIZE] = {0};
    for (size_t i = 0; i < SIZE; i++)
    {
       arr[i] = rand()%(152 -5) + 1;
    }
    printf("finding\n");
    findMinMax(arr, SIZE, &pMin, &pMax);
printf("Min = %d\nMax = %d\n", pMin, pMax);
}

void push(struct card** head_ref, int new_siut, int new_rank) {
    // Tworzenie nowego elementu
    struct card* new_node = (struct card*)malloc(sizeof(struct card));
    // Ustawienie wartości nowego elementu
    new_node->siut = new_siut;
    new_node->rank = new_rank;
    // Ustawienie wskaźnika na kolejny element jako aktualny pierwszy element listy
    new_node->nextCard = (*head_ref);
    // Przestawienie wskaźnika na początek listy na nowy element
    (*head_ref) = new_node;
}
void turnInfo(
    struct card* pDeck1Card,
    struct card* pDeck2Card,
    int winner,
    int* turn)
{
    printCard(pDeck1Card);
    printf("\t - ");
    printCard(pDeck2Card);
}