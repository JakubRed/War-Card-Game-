#pragma once
// #include "functions.c"
#include "constants.h"

//prepareDeck
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
    GAME * gameInst);

//game
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

void actualGame(
    GAME * gameInst);

void clearMemoryLinkedList(
    struct card* pFirstCard);

//simulation

void initializeGameParams(
    GAME * gameInst,
    int decksQuantity,
    int jockersQuantity);

GAME simulation(
    int decksQuantity, 
    int jockersQuantity);

void oneWholeGame(
    GAME * gameInst);

void showResult(
    GAME gameInst);
