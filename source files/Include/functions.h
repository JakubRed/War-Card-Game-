#pragma once
// #include "functions.c"
#include "constants.h"

int countCards(
    struct card* pFirstCard);

struct card* createDeck (
    int deckQty,
    int jockers);

int CardValue(struct card* card);

void printCard (
    struct card* pCard);

void showDeck (
    struct card* pFirstCard);

void showBothDecks(
    struct card* Deck1,
    struct card* Deck2);

//If there is unequal quantity of cards, newDeck will be bigger
struct card* splitDumb(  
    struct card* pFirstCard);

//If there is unequal quantity of cards, newDeck will be bigger
struct card* splitEqually(  
    struct card* pFirstCard);

void shuffle(
    struct card** pDeck,
    int howManyShuffles);

void createTwoDecks(
    struct card** pDeck1, 
    struct card** pDeck2,
    int deckQty,
    int jockers);

int compare(
    struct card* Deck1Card, 
    struct card* Deck2Card);

void addDeckToEnd(
    struct card* primaryDeck,
    struct card* toBeAdded);

void conquer(
    struct card** victor,
    struct card** victorEnd,
    struct card** vanquished);

int war(
    struct card** Deck1Start,
    struct card** Deck1End,
    struct card** Deck2Start,
    struct card** Deck2End);

GAME_RESULTS actualGame(
    struct card** D1, 
    struct card** D2);

void clearMemory(
    struct card* pFirstCard);

//Debug~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void printPtr(int iteration,
    struct card* pFirstCard,
    struct card* newDeck,
    struct card* pCurrentOriginalDeck,
    struct card* pCurrentNewDeck);

void findMinMax(
    int arr[], int size,
    int *min, int *max);

#define SIZE 10000
void random();

void push(
    struct card** head_ref,
    int new_siut, int new_rank);

void turnInfo(
    struct card* Deck1Card,
    struct card* Deck2Card,
    int winner,
    int* turn);