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


// long board[]
int primitiveEval(){
    float *currPoints = queenPtr;
    float currVal = QUEENVAL;
    float sum = 0;

    int i;
    for(i = 1; i < 6; i++){
        currPoints = pts[i];
        long long currMyPiece = myPieces[i];
        long long currTheirPiece = theirPieces[i];
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
    return 0;
}

int main(){
    primitiveEval();
    return 0;
}