#include <stdio.h>
#include <stdlib.h>

struct Board
{
    long long wKing;
    long long wQueen;
    long long wRook;
    long long wKnight;
    long long wBishop;
    long long wPawn;

    long long bKing;
    long long bQueen;
    long long bRook;
    long long bKnight;
    long long bBishop;
    long long bPawn;
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
float kingPts[64] = {    -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
                         -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
                         -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
                         -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0,
                         -2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0,
                         -1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0,
                          2.0,  2.0,  0.0,  0.0,  0.0,  0.0,  2.0,  2.0,
                          2.0,  3.0,  1.0,  0.0,  0.0,  1.0,  3.0,  2.0};

float queenPts[64] = {    -2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0,
                          -1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0,
                          -1.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0,
                          -0.5,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5,
                           0.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5,
                          -1.0,  0.5,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0,
                          -1.0,  0.0,  0.5,  0.0,  0.0,  0.0,  0.0, -1.0,
                          -2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0};

float rookPts[64] =  {     0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
                           0.5,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  0.5,
                          -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
                          -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
                          -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
                          -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
                          -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5,
                           0.0,  0.0,  0.0,  0.5,  0.5,  0.0,  0.0,  0.0};

float bishopPts[64] = {   -2.0,-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0,
                          -1.0, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0,
                          -1.0, 0.0,  0.5,  1.0,  1.0,  0.5,  0.0, -1.0,
                          -1.0, 0.5,  0.5,  1.0,  1.0,  0.5,  0.5, -1.0,
                          -1.0, 0.0,  1.0,  1.0,  1.0,  1.0,  0.0, -1.0, 
                          -1.0, 1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0,
                          -1.0, 0.5,  0.0,  0.0,  0.0,  0.0,  0.5, -1.0,
                          -2.0,-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0};

float knightPts[64] = {   -5.0,-4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0,
                          -4.0,-2.0,  0.0,  0.0,  0.0,  0.0, -2.0, -4.0,
                          -3.0, 0.0,  1.0,  1.5,  1.5,  1.0,  0.0, -3.0,
                          -3.0, 0.5,  1.5,  2.0,  2.0,  1.5,  0.5, -3.0,
                          -3.0, 0.0,  1.5,  2.0,  2.0,  1.5,  0.0, -3.0,
                          -3.0, 0.5,  1.0,  1.5,  1.5,  1.0,  0.5, -3.0,
                          -4.0,-2.0,  0.0,  0.5,  0.5,  0.0, -2.0, -4.0,
                          -5.0,-4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0};

float pawnPts[64] = {      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
                           5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,
                           1.0,  1.0,  2.0,  3.0,  3.0,  2.0,  1.0,  1.0,
                           0.5,  0.5,  1.0,  2.5,  2.5,  1.0,  0.5,  0.5,
                           0.0,  0.0,  0.0,  2.0,  2.0,  0.0,  0.0,  0.0,
                           0.5, -0.5, -1.0,  0.0,  0.0, -1.0, -0.5,  0.5,
                           0.5,  1.0,  1.0, -2.0, -2.0,  1.0,  1.0,  0.5,
                           0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0};

// Points Pointers
float *kingPtr = kingPts;
float *queenPtr = queenPts;
float *rookPtr = rookPts;
float *bishopPtr = bishopPts;
float *knightPtr = knightPts;
float *pawnPtr = pawnPts;

// White's Pieces
long long whitePawn =   0b0000000000000000000000000000000000000000000000001111111100000000;
long long whiteRook =   0b0000000000000000000000000000000000000000000000000000000010000001;
long long whiteKnight = 0b0000000000000000000000000000000000000000000000000000000001000010;
long long whiteBishop = 0b0000000000000000000000000000000000000000000000000000000000100100;
long long whiteQueen =  0b0000000000000000000000000000000000000000000000000000000000010000;
long long whiteKing =   0b0000000000000000000000000000000000000000000000000000000000001000;

// Black's Pieces
long long blackPawn =   0b0000000011111111000000000000000000000000000000000000000000000000;
long long blackRook =   0b1000000100000000000000000000000000000000000000000000000000000000;
long long blackKnight = 0b0100001000000000000000000000000000000000000000000000000000000000;
long long blackBishop = 0b0010010000000000000000000000000000000000000000000000000000000000;
long long blackQueen =  0b0001000000000000000000000000000000000000000000000000000000000000;
long long blackKing =   0b0000100000000000000000000000000000000000000000000000000000000000;



// Array of Pointers
float *pts[] = {kingPtr, queenPtr, rookPtr, bishopPtr, kingPtr, pawnPtr};
long long myPieces[] = {whiteKing, whiteQueen, whiteBishop, whiteKnight, whiteRook, whitePawn};
long long theirPieces[] = {blackKing, blackQueen, blackBishop, blackKnight, blackRook, blackPawn};
int vals[] = {0, QUEENVAL, ROOKVAL, BISHOPVAL, KNIGHTVAL, PAWNVAL};









float primitiveEval(){
    float *currPoints = kingPtr;
    int currVal;
    long long currMyPiece = whiteKing;
    long long currTheirPiece = blackKing;
    float sum = 0;
    int i;

    for(i = 63; i >= 0; i--){
        if(currMyPiece & 1)
            sum += currPoints[i];
        currMyPiece = currMyPiece >> 1;
    }

    for(i = 0; i < 64; i++){
        if(currTheirPiece & 1)
            sum -= currPoints[i];
        currTheirPiece >> 1;
    }

    for(i = 1; i < 6; i++){
        currPoints = pts[i];
        currMyPiece = myPieces[i];
        currTheirPiece = theirPieces[i];
        currVal = vals[i];
        int j;
        for(j = 63; j >= 0; j--){
        // & position with 1        
        long isMinePresent = currMyPiece & 1;
            if(isMinePresent){
                // Add piece value and positional value
                sum += currVal + currPoints[j];
            }
            // Shift right
            currMyPiece = currMyPiece >> 1;
        }
        for(j = 0; j < 64; j++){
            // & position with 1        
            long isTheirsPresent = currTheirPiece & 1;
                if(isTheirsPresent){
                    sum -= currVal + currPoints[j];
                }
                // Shift right
                currTheirPiece = currTheirPiece >> 1;
        }
    }

    printf("%f\n", sum);
    return sum;
}










float newEval(Board *myBoard){
    float sum = 0;
    int i;
    // Calculate Sum of Pieces
    int wQueenSum = 9 * __builtin_popcount(myBoard->wQueen);
    int wRookSum = 5 * __builtin_popcount(myBoard->wRook);
    int wBishopSum = 3 * __builtin_popcount(myBoard->wBishop);
    int wKnightSum = 3 * __builtin_popcount(myBoard->wKnight);
    int wPawnSum = 1 * __builtin_popcount(myBoard->wPawn);

    sum += wQueenSum + wRookSum + wBishopSum + wKnightSum + wPawnSum;

    int bQueenSum = 9 * __builtin_popcount(myBoard->bQueen);
    int bRookSum = 5 * __builtin_popcount(myBoard->bRook);
    int bBishopSum = 3 * __builtin_popcount(myBoard->bBishop);
    int bKnightSum = 3 * __builtin_popcount(myBoard->bKnight);
    int bPawnSum = 1 * __builtin_popcount(myBoard->bPawn);

    sum -= bQueenSum + bRookSum + bBishopSum + bKnightSum + bPawnSum;

    // Piece Square Tables

    return sum;
}

int main(){
    // primitiveEval();
    Board *board = (Board *) malloc(sizeof(Board));
    board->wKing = whiteKing;
    board->wQueen = whiteQueen;
    board->wRook = whiteRook;
    board->wBishop = whiteBishop;
    board->wKnight = whiteKnight;
    board->wPawn = whitePawn;

    board->bKing = blackKing;
    board->bQueen = blackQueen;
    int count = __builtin_popcount(blackQueen);
    printf("count: %d\n", count);
    int bQueenCount  = __builtin_popcount(board->bQueen);
    printf("bQueenCount: %d\n", bQueenCount);
    board->bRook = blackRook;
    board->bBishop = blackBishop;
    board->bKnight = blackKnight;
    board->bPawn = blackPawn;

    float res = newEval(board);
    // printf("%f\n", res);
    return 0;
}