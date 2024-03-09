#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdbool.h>
#include "Include/functions.h"
#include "Include/constants.h"

TEST_CASE initializeTestCases(
    int deckLowerLimit,
    int deckUpperLimit,
    int jokerLowerLimit,
    int jokerUpperLimit,
    int iterationsInEach)
{   
    TEST_CASE testCase;

    printf("[2]\n");
    testCase.decks.lowerLimit = deckLowerLimit;
    testCase.decks.upperLimit = deckUpperLimit;
    testCase.jokers.lowerLimit = jokerLowerLimit;
    testCase.jokers.upperLimit = jokerUpperLimit;
    testCase.oneSetIteration = iterationsInEach;

    printf("[3]\n");

    return testCase;
}

void researchFunc(
    TEST_CASE * testCase)
{
    GAME currentGame;
    initializeGameParams(&currentGame, 0, 0); //not necessary
    printf("[5]\n");
    for (size_t currentDeckQty = testCase->decks.lowerLimit; currentDeckQty < testCase->decks.upperLimit; currentDeckQty++)
    {
        printf("[5.1.%d]\n", currentDeckQty+1);
        // printf("[jokers: %d-%d]\n", testCase->jokers.lowerLimit, testCase->jokers.upperLimit);
        for (size_t currentJocerQty = testCase->jokers.lowerLimit; currentJocerQty < testCase->jokers.upperLimit; currentJocerQty++)
        {
            printf("[5.2.%d]\n", currentJocerQty+1);
            for (size_t currentTestCeseNumber = 0; currentTestCeseNumber <  testCase->oneSetIteration; currentTestCeseNumber++)
            {
                printf("[5.3.%d]\n", currentTestCeseNumber+1);
                showTestCaseResults(simulation(currentDeckQty, currentJocerQty));
                // currentGame = simulation(currentDeckQty, currentJocerQty);
                // showTestCaseResults(currentGame);
            }            
        }        
    }    
    
    printf("[6]\n");
}

void showTestCaseResults(
    GAME gameInst)
{
    printf("Decks: %d, jokers: %d, winner: Player%d, rounds: %d\n", 
    gameInst.startParams.decksQty,
    gameInst.startParams.jokersQty,
    gameInst.winner,
    gameInst.rounds);
}

void initializeGameParams(
    GAME * gameInst,
    int decksQuantity,
    int jokersQuantity)
{
    gameInst->startParams.decksQty = decksQuantity;
    gameInst->startParams.jokersQty = jokersQuantity;
    gameInst->rounds = FIRST_ROUND;
    gameInst->winner = NO_WINNER;
    gameInst->pPlayset.pDeck1 = NULL;
    gameInst->pPlayset.pDeck2 = NULL;
}

GAME simulation(
    int decksQuantity, 
    int jokersQuantity)
{
    GAME gameInst;
    initializeGameParams(&gameInst, decksQuantity, jokersQuantity);
    oneWholeGame(&gameInst);
    // showResult(gameInst);
    clearMemoryLinkedList(gameInst.pPlayset.pDeck1);
    clearMemoryLinkedList(gameInst.pPlayset.pDeck2);

    return gameInst;
}

GAME oneWholeGame(
    GAME * gameInst)
{    
    createTwoDecks(gameInst);
    // showBothDecks(gameInst->pPlayset.pDeck1, gameInst->pPlayset.pDeck2); 
    return actualGame(gameInst);
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