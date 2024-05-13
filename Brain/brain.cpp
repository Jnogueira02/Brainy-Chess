#include <stdio.h>

struct Board
{
    long whitePosition[6];
    long blackPosition[6];
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

// Position Analysis
float kingPoints[64] = {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
                        -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
                        -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
                        -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
                        -2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0,
                        -1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0,
                         2.0,  2.0,  0.0,  0.0,  0.0,  0.0,  2.0,  2.0,
                         2.0,  3.0,  1.0,  0.0,  0.0,  1.0,  3.0,  2.0};

float queenPoints[64] = {-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0,
                         -1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0,
                         -1.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0,
                         -0.5,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5,
                          0.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5,
                         -1.0,  0.5,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0,
                         -1.0,  0.0,  0.5,  0.0,  0.0,  0.0,  0.0, -1.0,
                         -2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0};

float rookPoints[64] =  { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
                          0.5,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  0.5,
                         -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
                         -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
                         -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
                         -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
                         -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
                          0.0,  0.0,  0.0,  0.5,  0.5,  0.0,  0.0,  0.0};

float bishopPoints[64] = {-2.0,-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0,
                          -1.0, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0,
                          -1.0, 0.0,  0.5,  1.0,  1.0,  0.5,  0.0, -1.0,
                          -1.0, 0.5,  0.5,  1.0,  1.0,  0.5,  0.5, -1.0,
                          -1.0, 0.0,  1.0,  1.0,  1.0,  1.0,  0.0, -1.0, 
                          -1.0, 1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0,
                          -1.0, 0.5,  0.0,  0.0,  0.0,  0.0,  0.5, -1.0,
                          -2.0,-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0};

float knightPoints[64] = {-5.0,-4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0,
                          -4.0,-2.0,  0.0,  0.0,  0.0,  0.0, -2.0, -4.0,
                          -3.0, 0.0,  1.0,  1.5,  1.5,  1.0,  0.0, -3.0,
                          -3.0, 0.5,  1.5,  2.0,  2.0,  1.5,  0.5, -3.0,
                          -3.0, 0.0,  1.5,  2.0,  2.0,  1.5,  0.0, -3.0,
                          -3.0, 0.5,  1.0,  1.5,  1.5,  1.0,  0.5, -3.0,
                          -4.0,-2.0,  0.0,  0.5,  0.5,  0.0, -2.0, -4.0,
                          -5.0,-4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0};

float pawnPoints[64] = {0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
                        5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,
                        1.0,  1.0,  2.0,  3.0,  3.0,  2.0,  1.0,  1.0,
                        0.5,  0.5,  1.0,  2.5,  2.5,  1.0,  0.5,  0.5,
                        0.0,  0.0,  0.0,  2.0,  2.0,  0.0,  0.0,  0.0,
                        0.5, -0.5, -1.0,  0.0,  0.0, -1.0, -0.5,  0.5,
                        0.5,  1.0,  1.0, -2.0, -2.0,  1.0,  1.0,  0.5,
                        0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0};


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

int primitiveEval(long board[]){
    int i;
    for(i = 0; i < 6; i++){
        int j;
        // for(j = 0; j < 64; j++){

        // }
        if(i == KING)
            printf("king\n");
    }
    
    return 0;
}

int main(){
    printf("Hello, world!");
    return 0;
}