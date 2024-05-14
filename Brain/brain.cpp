#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include "PieceSquareTables.h"

struct Board
{
    uint64_t wKing;
    uint64_t wQueen;
    uint64_t wRook;
    uint64_t wKnight;
    uint64_t wBishop;
    uint64_t wPawn;

    uint64_t bKing;
    uint64_t bQueen;
    uint64_t bRook;
    uint64_t bKnight;
    uint64_t bBishop;
    uint64_t bPawn;
};

// Piece IDs
#define KING 0
#define QUEEN 1
#define ROOK 2
#define BISHOP 3
#define KNIGHT 4
#define PAWN 5

// Piece Values
#define QUEENVAL 9
#define ROOKVAL 5
#define BISHOPVAL 3
#define KNIGHTVAL 3
#define PAWNVAL 1

// White's Pieces
uint64_t whitePawn =   0b0000000000000000000000000000000000000000000000001111111100000000;
uint64_t whiteRook =   0b0000000000000000000000000000000000000000000000000000000010000001;
uint64_t whiteKnight = 0b0000000000000000000000000000000000000000000000000000000001000010;
uint64_t whiteBishop = 0b0000000000000000000000000000000000000000000000000000000000100100;
uint64_t whiteQueen =  0b0000000000000000000000000000000000000000000000000000000000010000;
uint64_t whiteKing =   0b0000000000000000000000000000000000000000000000000000000000001000;

// Black's Pieces
uint64_t blackPawn =   0b0000000011111111000000000000000000000000000000000000000000000000;
uint64_t blackRook =   0b1000000100000000000000000000000000000000000000000000000000000000;
uint64_t blackKnight = 0b0100001000000000000000000000000000000000000000000000000000000000;
uint64_t blackBishop = 0b0010010000000000000000000000000000000000000000000000000000000000;
uint64_t blackQueen =  0b0001000000000000000000000000000000000000000000000000000000000000;
uint64_t blackKing =   0b0000100000000000000000000000000000000000000000000000000000000000;


float newEval(Board *myBoard){
    float sum = 0;
    // Calculate Sum of Pieces
    int wQueenSum = 9 * __builtin_popcountll(myBoard->wQueen);
    int wRookSum = 5 * __builtin_popcountll(myBoard->wRook);
    int wBishopSum = 3 * __builtin_popcountll(myBoard->wBishop);
    int wKnightSum = 3 * __builtin_popcountll(myBoard->wKnight);
    int wPawnSum = 1 * __builtin_popcountll(myBoard->wPawn);

    sum += wQueenSum + wRookSum + wBishopSum + wKnightSum + wPawnSum;

    int bQueenSum = 9 * __builtin_popcountll(myBoard->bQueen);
    int bRookSum = 5 * __builtin_popcountll(myBoard->bRook);
    int bBishopSum = 3 * __builtin_popcountll(myBoard->bBishop);
    int bKnightSum = 3 * __builtin_popcountll(myBoard->bKnight);
    int bPawnSum = 1 * __builtin_popcountll(myBoard->bPawn);

    sum -= bQueenSum + bRookSum + bBishopSum + bKnightSum + bPawnSum;

    // Piece Square Tables
    int i;
    for(i = 63; i >= 0; i--){
        // Player's positions // Simplify later
        if(myBoard->wKing & 1)
            sum += kingPST[i];
        if(myBoard->wQueen & 1)
            sum += queenPST[i];
         if(myBoard->wRook & 1)
            sum += rookPST[i];       
        if(myBoard->wBishop & 1)
            sum += bishopPST[i];
        if(myBoard->wKnight & 1)
            sum += knightPST[i];
        if(myBoard->wPawn & 1)
            sum += pawnPST[i];

        // Opponent's positions
        if(myBoard->bKing & 1)
            sum += kingPSTRev[i];
        if(myBoard->bQueen & 1)
            sum += queenPSTRev[i];
        if(myBoard->bRook & 1)
            sum += rookPSTRev[i];
        if(myBoard->bBishop & 1)
            sum += bishopPSTRev[i];
        if(myBoard->bKnight & 1)
            sum += knightPSTRev[i];
        if(myBoard->bPawn & 1)
            sum += pawnPSTRev[i];


        //Shifts
        myBoard->wKing = myBoard->wKing >> 1;
        myBoard->wQueen = myBoard->wQueen >> 1;
        myBoard->wRook = myBoard->wRook >> 1;
        myBoard->wBishop = myBoard->wBishop >> 1;
        myBoard->wKnight = myBoard->wKnight >> 1;
        myBoard->wPawn = myBoard->wPawn >> 1;

        myBoard->bKing = myBoard->bKing >> 1;
        myBoard->bQueen = myBoard->bQueen >> 1;
        myBoard->bRook = myBoard->bRook >> 1;
        myBoard->bBishop = myBoard->bBishop >> 1;
        myBoard->bKnight = myBoard->bKnight >> 1;
        myBoard->bPawn = myBoard->bPawn >> 1;
    }

    return sum;
}

int main(){
    // primitiveEval();
    auto *board = (Board *) malloc(sizeof(Board));
    board->wKing = whiteKing;
    board->wQueen = whiteQueen;
    board->wRook = whiteRook;
    board->wBishop = whiteBishop;
    board->wKnight = whiteKnight;
    board->wPawn = whitePawn;

    board->bKing = blackKing;
    board->bQueen = blackQueen;
    board->bRook = blackRook;
    board->bBishop = blackBishop;
    board->bKnight = blackKnight;
    board->bPawn = blackPawn;

    float res = newEval(board);
    printf("%f\n", res);

    free(board);
    return 0;
}