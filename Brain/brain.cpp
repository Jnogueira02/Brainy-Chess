#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <iostream>
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
uint64_t whitePawn =   0x000000000000FF00;
uint64_t whiteRook =   0x0000000000000081;
uint64_t whiteKnight = 0x0000000000000042;
uint64_t whiteBishop = 0x0000000000000024;
uint64_t whiteQueen =  0x0000000000000010;
uint64_t whiteKing =   0x0000000000000008;

// Black's Pieces
uint64_t blackPawn =   0x00FF000000000000;
uint64_t blackRook =   0x8100000000000000;
uint64_t blackKnight = 0x4200000000000000;
uint64_t blackBishop = 0x2400000000000000;
uint64_t blackQueen =  0x1000000000000000;
uint64_t blackKing =   0x0800000000000000;


// Evaluate the score of white based on pieces left and piece square tables
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
            sum -= kingPSTRev[i];
        if(myBoard->bQueen & 1)
            sum -= queenPSTRev[i];
        if(myBoard->bRook & 1)
            sum -= rookPSTRev[i];
        if(myBoard->bBishop & 1)
            sum -= bishopPSTRev[i];
        if(myBoard->bKnight & 1)
            sum -= knightPSTRev[i];
        if(myBoard->bPawn & 1)
            sum -= pawnPSTRev[i];


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

void generateMoves(){

}

bool isOccupied(Board *myBoard, int position){
    return (myBoard->wKing | myBoard->wQueen | myBoard->wRook | myBoard->wBishop | myBoard->wKnight | myBoard->wPawn |
    myBoard->bKing | myBoard->bQueen | myBoard->bRook | myBoard->bBishop | myBoard->bKnight | myBoard->bPawn) & (0b1 << position);
}

Board *populate(){
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

    return board;
}

int main(){
    Board *myBoard = populate();
    bool occupied = isOccupied(myBoard, 16);
    std::cout << occupied;
    return 0;
}