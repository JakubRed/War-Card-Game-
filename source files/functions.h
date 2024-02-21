#pragma once
// #include "functions.c"

struct card* createDeck(
    int deckQty, 
    int jockers);

void printCard (
    struct card* card);

void showDeck(
    struct card* );

struct card* shuffle(
    struct card* pFirstCard);

struct card* split(
    struct card* pFirstCard);
    
void clearMemory(struct card * pFirstCard);