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
        pCurrent->rank = RANKS_QTY;
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

    if (NULL == pFirstCard)
    {
        printf("EMPTY\n");
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


void swap(
    struct card* ptr1, 
    struct card* ptr2)
{
    struct card* tmp = ptr2->nextCard;
    ptr2->nextCard = ptr1;
    ptr1->nextCard = tmp;
}

int compare(
    struct card* Deck1Card, 
    struct card* Deck2Card)
{
    int retVal = GENERIC_ERROR;
    // printCard(Deck1Card);
    // printf("\t - ");
    // printCard(Deck2Card);

    if (NULL == Deck1Card)
    {
        return FISRT_IS_WINNER + OPPONENT_LOST;
    }
    else if (NULL == Deck2Card)
    {
        return SECOND_IS_WINNER + OPPONENT_LOST;
    }    

    if (Deck1Card->rank > Deck2Card->rank) {
        retVal = FISRT_IS_WINNER; //first card wins
        // printf("\twinner is: D1");
        // printCard(Deck1Card);
    }
    else if (Deck1Card->rank < Deck2Card->rank) {
        retVal = SECOND_IS_WINNER; //second card wins
        // printf("\twinner is: D2");
        // printCard(Deck2Card);
    }
    else if (Deck1Card->rank == Deck2Card->rank) {
        // printf("\nD1:");
        // showDeck(Deck1Card);
        // printf("\nD2:");
        // showDeck(Deck2Card);
        retVal = ITS_A_DRAW; //it's a draw
        // printf("\n~~~~draw~~~~\n ");
    }
    else{
        printf("ERROR in compare()");
    }
    // printf("\n");
    return retVal;
}

void addDeckToEnd(
    struct card* primaryDeck,
    struct card* toBeAdded)
{
    while (NULL != primaryDeck->nextCard)
    {
        primaryDeck = primaryDeck->nextCard;
    }
    primaryDeck->nextCard = toBeAdded;
    
}

struct card*  shiftPointer(
    struct card* deck,
    int amount)
{
    for (size_t i = 0; i < amount; i++)
    {
        deck = deck->nextCard;
    }
    return deck;

}

void conquer(struct card** victor, struct card** victorEnd, struct card** vanquished)
{
    (*victorEnd)->nextCard = (*vanquished);
    (*vanquished) = (*vanquished)->nextCard;
    (*victorEnd) = (*victorEnd)->nextCard;

    (*victorEnd)->nextCard = (*victor);
    (*victor) = (*victor)->nextCard;
    (*victorEnd) = (*victorEnd)->nextCard;
    (*victorEnd)->nextCard= NULL;
}

int war(
    struct card** Deck1Start,
    struct card** Deck1End,
    struct card** Deck2Start,
    struct card** Deck2End)
{
    struct card* Deck1Current = (*Deck1Start);
    struct card* Deck2Current = (*Deck2Start);
    struct card* pool = NULL;
    int winner = 0, insideWinner = 0;
    // printf("\nDeck1");
    // printCard((*Deck1Start));
    // printf("\nDeck2");
    // printCard((*Deck2Start));

    //switch to hidden card
    Deck1Current = Deck1Current->nextCard;
    Deck2Current = Deck2Current->nextCard;
    //switch to second combatant
    Deck1Current = Deck1Current->nextCard;
    Deck2Current = Deck2Current->nextCard;
    
    // printf("\nDeck1");
    // showDeck((*Deck1Start));
    // printf("\nDeck2");
    // showDeck((*Deck2Start));
    winner = compare(Deck1Current, Deck2Current);
    switch (winner)
    {
    case FISRT_IS_WINNER:
    // printf("\np1win\n");
        (*Deck1End)->nextCard = (*Deck1Start);
        (*Deck1Start) = Deck1Current->nextCard;
        (*Deck1End) = Deck1Current;
        Deck1Current->nextCard = (*Deck2Start);
        (*Deck2Start) = Deck2Current->nextCard;
        Deck2Current->nextCard = NULL;
        (*Deck1End) = Deck2Current;
        break;
    case SECOND_IS_WINNER:        
    // printf("\np2win\n");
        (*Deck2End)->nextCard = (*Deck2Start);
        (*Deck2Start) = Deck2Current->nextCard;
        (*Deck2End) = Deck2Current;
        Deck2Current->nextCard = (*Deck1Start);
        (*Deck1Start) = Deck1Current->nextCard;
        Deck1Current->nextCard = NULL;
        (*Deck2End) = Deck1Current;
        break;
    case ITS_A_DRAW:
    // printf("\nInside Job\n"); 
        pool = (*Deck1Start);
        (*Deck1Start) = Deck1Current;
        pool->nextCard->nextCard = (*Deck2Start);
        (*Deck2Start) = Deck2Current;        
        pool->nextCard->nextCard->nextCard->nextCard = NULL;

        // printf("\npool");
        // showDeck(pool);
        insideWinner = war(Deck1Start, Deck1End, Deck2Start, Deck2End);
        if (FISRT_IS_WINNER == insideWinner) 
        {
            // (*Deck1End)->nextCard->nextCard->nextCard->nextCard = pool;
            addDeckToEnd((*Deck1End), pool);
            (*Deck1End) = shiftPointer(pool, 3);
        }
        else if (SECOND_IS_WINNER == insideWinner)
        {
            
            addDeckToEnd((*Deck2End), pool);
            // (*Deck2End)->nextCard->nextCard->nextCard->nextCard = pool;
            (*Deck2End) = shiftPointer(pool, 3);
            // (*Deck2End) = pool->nextCard->nextCard->nextCard;
            // printf("\nD1:");
            // showDeck(Deck1Current);
            // printf("\nD2:");
            // showDeck(Deck2Current);
            return winner;
        }
        else if(ITS_A_DRAW == insideWinner); //going out of inner war, return not needed
        else {
            printf("\nERROR in WAR() - %d\n", insideWinner);
        }            
        break;    
    case FISRT_IS_WINNER + OPPONENT_LOST:
        (*Deck1End)->nextCard = (*Deck2Start);
        (*Deck1End) = (*Deck2End);
        (*Deck2Start) = NULL;
        (*Deck2End) = NULL;
        break;
    case SECOND_IS_WINNER + OPPONENT_LOST:
        (*Deck2End)->nextCard = (*Deck1Start);
        (*Deck2End) = (*Deck1End);
        (*Deck1Start) = NULL;
        (*Deck1End) = NULL;
        break;
    default:
        break;
    }
    // printf("\nafter\n");
    // printf("\nDeck1Start");
    // printCard((*Deck1Start));
    // printf("\nDeck2Start");
    // printCard((*Deck2Start));
 
    // printf("\nDeck1");
    // showDeck((*Deck1Start));
    // printf("\nDeck2");
    // showDeck((*Deck2Start));
    return winner;
}

int actualGame(
    struct card** D1, 
    struct card** D2)
    {
        int flagg = 0;
        int flagg2 = 0;
        int winner = 0, turn = 1;
        struct card* Deck1Start = (*D1);
        struct card* Deck2Start = (*D2);
        struct card* Deck1End = Deck1Start;  
        struct card* Deck2End = Deck2Start;
        while (NULL != Deck1End->nextCard)
        {
            Deck1End = Deck1End->nextCard;
        }
        while (NULL != Deck2End->nextCard)
        {
            Deck2End = Deck2End->nextCard;
        }
        

    // printf("\nD1\n");
    // showDeck (Deck1Start);
    // printf("\nD2\n");
    // showDeck (Deck2Start);
    // printf("\n");
        while (NULL != Deck1Start && NULL != Deck2Start)
        {              

    // printf("\nTurn %d.", turn++);
    // printf("\n CONQUest no. %d\n", i+1);
    // printf("\n");
    // printf("\n");
        // if (flagg++ < 3)
        // {
        //     printf("\nD1~~ %d", flagg);
        //     showDeck (Deck1Start);
        //     printf("\nD2~~ %d", flagg);
        //     showDeck (Deck2Start);  
        // }
        
            winner = compare(Deck1Start, Deck2Start);
            switch (winner)
            {
            case FISRT_IS_WINNER:
                conquer(&Deck1Start, &Deck1End, &Deck2Start);
                break;
            case SECOND_IS_WINNER:
                conquer(&Deck2Start, &Deck2End, &Deck1Start);
                break;
            case ITS_A_DRAW:
            // printf("\n\nwarrr\n\n");
                war(&Deck1Start, &Deck1End, &Deck2Start, &Deck2End);
                // printf("\nD1!\n");
                // showDeck (Deck1Start);
                // printf("\nD2!\n");
                // showDeck (Deck2Start);    
                break;
            
            default:
                break;
            }    
            // if (flagg2++ < 4)
            // {
            //     printf("\nD1! - %d\n", flagg2);
            //     showDeck (Deck1Start);
            //     printf("\nD2! - %d\n", flagg2);
            //     showDeck (Deck2Start);    
            // }
            // printf("\nDeck 2 end ");
            // printCard(Deck2End);
             
        
        // printf("\t %d Cards\n", countCards(Deck1Start) + countCards(Deck2Start));           
        }  
        (*D1) = Deck1Start;
        (*D2) = Deck2Start;
        return 0;
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

// void bubbleSort(int arr[], int n) {
//     for (int i = 0; i < n - 1; i++) {
//         for (int j = 0; j < n - i - 1; j++) {
//             if (arr[j] > arr[j + 1]) {
//                 // Swap the elements if they are in the wrong order
//                 int temp = arr[j];
//                 arr[j] = arr[j + 1];
//                 arr[j + 1] = temp;
//             }
//         }
//     }
// }
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
    struct card* Deck1Card,
    struct card* Deck2Card,
    int winner,
    int* turn)
{
    printCard(Deck1Card);
    printf("\t - ");
    printCard(Deck2Card);
}