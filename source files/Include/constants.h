#pragma once
#define UNI_CLUB "\u2667"
#define UNI_B_CLUB "\u2663"
#define UNI_DIAMOND "\u2662"
#define UNI_B_DIAMOND "\u2666"
#define UNI_HEART "\u2661"
#define UNI_B_HEART "\u2665"
#define UNI_SPADE "\u2664"
#define UNI_B_SPADE "\u2660"

#define FIRST_ROUND 1
#define NO_WINNER 0
#define FISRT_IS_WINNER 1
#define SECOND_IS_WINNER 2
#define OPPONENT_OUT_OF_CARDS 3
#define ITS_A_DRAW 3

#define JOKER_SIUT 4
#define JOKER_RANK 15

//error codes
#define GENERIC_ERROR 0

const int SIUTS_QTY = 4;
const int RANKS_QTY = 13;
enum SIUTS {
    Clubs, 
    Diamonds, 
    Hearts, 
    Spades};

enum RANKS {
    Two = 2, 
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace};

struct card
{
    int IdNum;
    enum SIUTS siut;
    enum RANKS rank;
    struct card* nextCard;
};

typedef struct{
    struct card * pDeck1;
    struct card * pDeck2;
} TWO_DECKS;

typedef struct{
    int decksQty;
    int jokersQty;
} STARTING_PARAMS;

typedef struct{
    int rounds;
    int winner;
    STARTING_PARAMS startParams;
    TWO_DECKS pPlayset;
} GAME;