#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void printPtr(int iteration,
    struct card* pFirstCard,
    struct card* newDeck,
    struct card* pCurrentOriginalDeck,
    struct card* pCurrentNewDeck);

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
                    // Debug logs
                    // printf("%d:%d\n", siut, rank);
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

                // Debug logs
                // printf("%d:%d\n", siut, rank);
            }
        }
        for (size_t i = 0; i < jockers; i++)
        {            
            pCurrent = (struct card*)malloc(sizeof(struct card));
            pCurrent->siut = 4;
            pCurrent->rank = 15;
            pCurrent->IdNum = 415;    

            pPrevious->nextCard = pCurrent;
            pPrevious = pCurrent;
            // Debug logs
            // printf("Joker\n");
        }
    }
    return pFirstCard;
}

void printCard (
    struct card* pCard)
{
    if (NULL == pCard)
    {
        printf("\tNULL");
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
}

//If there is unequal quantity of cards, newDeck will be bigger
struct card* splitDumb(  
    struct card* pFirstCard){
    struct card* pCurrent = pFirstCard;
    struct card* newDeck = NULL;
    int cardCount = 0;
    int deckSize = 0;

    // Split in two
    while (pCurrent != NULL)
    {
        cardCount++;
        pCurrent = pCurrent->nextCard;
    }

    printf("\nCard count = %d\n", cardCount);
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
    

    // printPtr(iteration++, pFirstCard, pNewDeck, pCurrentOriginalDeck, pCurrentNewDeck);
    while (NULL != pCurrent && NULL != pCurrent->nextCard)
    {   
        pCurrentOriginalDeck->nextCard = pCurrent;
        pCurrent = pCurrent->nextCard;
        pCurrentNewDeck->nextCard = pCurrent;

        pCurrent = pCurrent->nextCard;
        pCurrentOriginalDeck = pCurrentOriginalDeck->nextCard;
        pCurrentNewDeck = pCurrentNewDeck->nextCard;       

        // printPtr(iteration++, pFirstCard, pNewDeck, pCurrentOriginalDeck, pCurrentNewDeck);
    }

    pCurrentOriginalDeck->nextCard = NULL;
    
     return pNewDeck;
}

struct card* shuffle(
    struct card* pDeck,
    int howManyShuffles){
    struct card* pFirstStart = pDeck;
    struct card* pFirstStop = NULL;
    struct card* pSecoondStart = NULL;
    struct card* pScoondStop = NULL;
    struct card* pThirdStart = NULL;
    struct card* pThirdStop = NULL;
    int cardCount = 0;
    int secondStartingPoint = 0;
    int thirdStatringPoint = 0;
    srand(time(NULL));

    for (struct card* pCurrent = pFirstStart; NULL != pCurrent->nextCard; cardCount++)
    {
        pCurrent = pCurrent->nextCard;
    }

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
    return pFirstStart;
}

int compare(
    struct card* Deck1Card, 
    struct card* Deck2Card)
{
    int retVal = GENERIC_ERROR;
    printCard(Deck1Card);
    printf("\t - ");
    printCard(Deck2Card);

    if (Deck1Card->rank > Deck2Card->rank) {
        retVal = FISRT_IS_WINNER; //first card wins
        printf("\twinner is: ");
        printCard(Deck1Card);
    }
    else if (Deck1Card->rank < Deck2Card->rank) {
        retVal = SECOND_IS_WINNER; //second card wins
        printf("\twinner is: ");
        printCard(Deck2Card);
    }
    else if (Deck1Card->rank == Deck2Card->rank) {
        retVal = ITS_A_DRAW; //it's a draw
        printf("\tdraw ");
    }
    printf("\n");
    return retVal;
}

struct card* theWinnerTakesItAll(struct card* victor, struct card* victorEnd, struct card* vanquished)
{

}

struct card* conquer(struct card* victor, struct card* victorEnd, struct card* vanquished)
{
    victorEnd->nextCard = vanquished;
    // printf("\nGurabiga1: ");
    // printCard(vanquished);
    vanquished = vanquished->nextCard;
    // printf("\nGurabiga2: ");
    // printCard(vanquished);
    // printf("\n");
    // showDeck(vanquished);
    victorEnd = victorEnd->nextCard;

    victorEnd->nextCard = victor;
    victor = victor->nextCard;
    victorEnd = victorEnd->nextCard;
    victorEnd->nextCard= NULL;
    

    printf("\nvictor\n");
    showDeck (victor);
    printf("\nvanquished\n");
    showDeck (vanquished);
     return vanquished;
}

int actualGame(
    struct card* Deck1Start, 
    struct card* Deck2Start)
    {
        int winner = 0;
        struct card* Deck1Stop = Deck1Start;  
        struct card* Deck2Stop = Deck2Start;
        while (NULL != Deck1Stop->nextCard)
        {
            Deck1Stop = Deck1Stop->nextCard;
        }
        while (NULL != Deck2Stop->nextCard)
        {
            Deck2Stop = Deck2Stop->nextCard;
        }
        

    printf("\nD1\n");
    showDeck (Deck1Start);
    printf("\nD2\n");
    showDeck (Deck2Start);
    printf("\n");
        // while (NULL != Deck1Start && NULL != Deck2Start)
        // {
            winner = compare(Deck1Start, Deck2Start);
            switch (winner)
            {
            case FISRT_IS_WINNER:
                Deck1Start = conquer(Deck1Start, Deck1Stop, Deck2Start);
                printf("\n[1]\n");
                break;
            case SECOND_IS_WINNER:
                // Deck1Start = conquer(Deck2Start, Deck2Stop, Deck1Start);
                Deck2Start = conquer(Deck2Start, Deck2Stop, Deck1Start);
                printf("\n[2]\n");
                break;
            case ITS_A_DRAW:
                /* code */
                break;
            
            default:
                break;
            }            
        // }  
        printf("\nDeck1 start: ");
        printCard(Deck1Start);
        printf("\tDeck1 stop: ");
        printCard(Deck1Stop);
        printf("\nDeck2 start: ");
        printCard(Deck2Start);
        printf("\tDeck2 stop: ");
        printCard(Deck2Stop);

    printf("\nAFTER CONQUER\n");
    printf("\nD1\n");
    showDeck (Deck1Start);
    printf("\nD2\n");
    showDeck (Deck2Start);
        return 0;
    }


void clearMemory(struct card* pFirstCard) {
    struct card* pCurrent = pFirstCard;
    struct card* pNextCard;

    while (pCurrent != NULL) {
        pNextCard = pCurrent->nextCard;  // Save the next node before freeing the current one
        free(pCurrent);             // Free the current node
        pCurrent = pNextCard;        // Move to the next node
    }
}


//Debug
void printPtr(int iteration,
    struct card* pFirstCard,
    struct card* newDeck,
    struct card* pCurrentOriginalDeck,
    struct card* pCurrentNewDeck) {
        printf("\n%d. ", iteration);
        // printCard(pFirstCard);
        // printf(" FirstCard:\t%p\n",pFirstCard );
        // printCard(newDeck);
        // printf(" newDeck:\t%p\n",newDeck );
        // printCard(pCurrentOriginalDeck);
        // printf(" OriginalD:\t%p\n",pCurrentOriginalDeck );
        // printCard(pCurrentNewDeck);
        // printf(" NewDeck:\t%p\n",pCurrentNewDeck );
        printf("\nOld D ");
        showDeck(pFirstCard);
        printf("\nNew D ");
        showDeck(newDeck);
    }

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap the elements if they are in the wrong order
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
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
    printf("finding");
    findMinMax(arr, SIZE, &pMin, &pMax);
printf("\nMin = %d\nMax = %d\n", pMin, pMax);
}