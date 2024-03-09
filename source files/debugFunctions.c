
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Include/functions.h"

#define SIZE 10000

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