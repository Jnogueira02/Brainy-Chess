#include <stdio.h>

struct Board
{
    long whitePosition[6];
    long blackPosition[6];
};

// Piece Values
#define QUEENVAL = 9;
#define ROOKVAL = 5;
#define BISHOPVAL = 3;
#define KNIGHTVAL = 3;
#define PAWNVAL = 1;

// Position Analysis
long kingPoints[8][8] = {};
long queenPoints[8][8] = {};
long rookPoints[8][8] = {};
long bishopPoints[8][8] = {};
long knightPoints[8][8] = {};
long pawnPoints[8][8] = {};


// White's Pieces
long whitePawn;
long whiteRook;
long whiteKnight;
long whiteBishop;
long whiteQueen;
long whiteKing;

// Black's Pieces
long blackPawn;
long blackRook;
long blackKnight;
long blackBishop;
long blackQueen;
long blackKing;

int eval(long board[]){
    return 0;
}

int main(){
    printf("Hello, world!");
    return 0;
}