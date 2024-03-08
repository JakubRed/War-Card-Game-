#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdbool.h>
#include "Include/functions.h"

int countCards(
    struct card* pFirstCard)
    {
    int cardCount = 0;
    while (pFirstCard != NULL)
    {
        cardCount++;
        pFirstCard = pFirstCard->nextCard;
    }
    return cardCount;
    }

struct card* createDeck (
    int deckQty,
    int jockers) { 
    struct card* pFirstCard = NULL;
    struct card* pCurrent, * pPrevious = NULL;
    enum SIUTS currentSiuts = Clubs;
    enum RANKS currentRanks = Two;
    for (size_t deckCount = 0; deckCount < deckQty; deckCount++)
    {    
        for (int siut = 0; siut < SIUTS_QTY; siut++)
        {
            for (int rank = 2; rank < 2 + RANKS_QTY; rank++)
            {
                if (NULL == pFirstCard)
                {
                    pFirstCard = (struct card*)malloc(sizeof(struct card));

                    pFirstCard->siut = siut;
                    pFirstCard->rank = rank++;
                    pFirstCard->IdNum = siut * 100 + rank;
                    pPrevious = pFirstCard;
                }
                pCurrent = (struct card*)malloc(sizeof(struct card));
                pCurrent->siut = siut;
                pCurrent->rank = rank;
                pCurrent->IdNum = siut * 100 + rank;    

                pPrevious->nextCard = pCurrent;
                pPrevious = pCurrent;
            }
        }
    }
        for (size_t i = 0; i < jockers; i++)
    {            
        pCurrent = (struct card*)malloc(sizeof(struct card));
        pCurrent->siut = JOKER_SIUT;
        pCurrent->rank = JOKER_RANK;
        pCurrent->IdNum = 415;    

        pPrevious->nextCard = pCurrent;
        pPrevious = pCurrent;
    }
    return pFirstCard;
}

int CardValue(struct card* card)
{
    return card->rank + card->siut*20;
}

void printCard (
    struct card* pCard)
{
    if (NULL == pCard)
    {
        printf("\tNULL\n");
        return;
    }
    
    switch (pCard->rank)
    {
    case Jack:
        printf("\tJ");
        break;        
    case Queen:
        printf("\tQ");
        break;   
    case King:
        printf("\tK" );
        break;           
    case Ace:
        printf("\tA");
        break;   
    case 15:
        printf("\tJKR");
        break;      
    default:
    printf( "\t%d", pCard->rank);
        break;
    }

    switch (pCard->siut)
    {
    case Clubs:
        printf(UNI_CLUB);
        break;
    case Diamonds:
        printf(UNI_B_DIAMOND);
        break;
    case Hearts:
        printf(UNI_B_HEART);
        break;   
    case Spades:
        printf(UNI_SPADE);
        break;   
    default:
        break;
    }
}

void showDeck (
    struct card* pFirstCard){
    int i = 0;

    if (NULL == pFirstCard)
    {
        printf(" EMPTY\n");
        return;
    }    
    // while (NULL != pFirstCard)
    // {   
    //     printCard(pFirstCard);
    //     printf("=%d", CardValue(pFirstCard));
    //     // printf("\n");
    //     if(11 < i++) {
    //         printf("\n");
    //         i = 0;
    //     }        
    //     pFirstCard = pFirstCard->nextCard;
    // } 
    while (NULL != pFirstCard)
    {   
        printCard(pFirstCard);
        // printf("\n");
        if(11 < i++) {
            printf("\n");
            i = 0;
        }        
        pFirstCard = pFirstCard->nextCard;
    }     
    printf("\n");
}

void showBothDecks(
    struct card* Deck1,
    struct card* Deck2)
    {
        printf("Deck1:");
        showDeck(Deck1);
        printf("Deck2:");
        showDeck(Deck2);
    }
    
//If there is unequal quantity of cards, newDeck will be bigger
struct card* splitDumb(  
    struct card* pFirstCard){
    struct card* pCurrent = pFirstCard;
    struct card* newDeck = NULL;
    int cardCount = 0;
    int deckSize = 0;

    // Split in two
    cardCount = countCards(pCurrent);

    printf("Card count = %d\n", cardCount);
    deckSize = cardCount/2;
    pCurrent = pFirstCard;
    while (1 < deckSize--)
    {
        pCurrent = pCurrent->nextCard;
    }   
    newDeck = pCurrent->nextCard;
    pCurrent->nextCard = NULL;
    return newDeck;
}

//If there is unequal quantity of cards, newDeck will be bigger
struct card* splitEqually(  
    struct card* pFirstCard){
    struct card* pNewDeck = pFirstCard->nextCard;
    struct card* pCurrent = pNewDeck->nextCard;

    struct card* pCurrentOriginalDeck = pFirstCard;
    struct card* pCurrentNewDeck = pNewDeck;
    int iteration = 1; 
    
    while (NULL != pCurrent && NULL != pCurrent->nextCard)
    {   
        pCurrentOriginalDeck->nextCard = pCurrent;
        pCurrent = pCurrent->nextCard;
        pCurrentNewDeck->nextCard = pCurrent;

        pCurrent = pCurrent->nextCard;
        pCurrentOriginalDeck = pCurrentOriginalDeck->nextCard;
        pCurrentNewDeck = pCurrentNewDeck->nextCard;       
    }

    pCurrentOriginalDeck->nextCard = NULL;    
    return pNewDeck;
}

void shuffle(
    struct card** pDeck,
    int howManyShuffles){
    struct card* pFirstStart = (*pDeck);
    struct card* pFirstStop = NULL;
    struct card* pSecoondStart = NULL;
    struct card* pScoondStop = NULL;
    struct card* pThirdStart = NULL;
    struct card* pThirdStop = NULL;
    int cardCount = 0;
    int secondStartingPoint = 0;
    int thirdStatringPoint = 0;
    srand(time(NULL));

    cardCount = countCards(pFirstStart);

    for (size_t shuffleCount = 0; shuffleCount < howManyShuffles; shuffleCount++)
    {
        secondStartingPoint = rand()%(cardCount - 2);
        pSecoondStart = pFirstStart;
        pThirdStart = pFirstStart;
        for (size_t i = 0; i < secondStartingPoint; i++)
        {
            pSecoondStart = pSecoondStart->nextCard;
        }        
        thirdStatringPoint = rand()%(cardCount - secondStartingPoint -2) + secondStartingPoint + 1;
        for (size_t i = 0; i < thirdStatringPoint; i++)
        {
            pThirdStart = pThirdStart->nextCard;
        }  
        pFirstStop = pSecoondStart; 
        pSecoondStart = pFirstStop->nextCard;
        pFirstStop->nextCard = NULL;

        pScoondStop = pThirdStart;
        pThirdStart = pScoondStop->nextCard; 
        pScoondStop->nextCard = NULL;                       

        for (pThirdStop = pThirdStart; NULL != pThirdStop->nextCard ;)
        {
            pThirdStop = pThirdStop->nextCard;
        }     
        if (rand()%2 > 0)
        {
            pThirdStop->nextCard = pSecoondStart;
            pFirstStop->nextCard = pThirdStart;
        }
        else
        {
            pScoondStop->nextCard = pFirstStart;
            pFirstStop->nextCard = pThirdStart;
            pFirstStart = pSecoondStart;
        }        
    }
    (*pDeck) = pFirstStart;
}

void createTwoDecks(
    GAME * gameInst)
{
    gameInst->pPlayset.pDeck1 = createDeck (gameInst->startParams.decksQty, gameInst->startParams.jokersQty);    
    gameInst->pPlayset.pDeck2 = splitEqually (gameInst->pPlayset.pDeck1);
    shuffle(&gameInst->pPlayset.pDeck1, 100);
    shuffle(&gameInst->pPlayset.pDeck2, 100);
}