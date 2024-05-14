#include <cstdio>
#include <cstdlib>
#include <cstdint>

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



// Array of Pointers
float *pts[] = {kingPtr, queenPtr, rookPtr, bishopPtr, knightPtr, pawnPtr};
uint64_t myPieces[] = {whiteKing, whiteQueen, whiteBishop, whiteKnight, whiteRook, whitePawn};
uint64_t theirPieces[] = {blackKing, blackQueen, blackBishop, blackKnight, blackRook, blackPawn};
int vals[] = {0, QUEENVAL, ROOKVAL, BISHOPVAL, KNIGHTVAL, PAWNVAL};









float primitiveEval(){
    float *currPoints = kingPtr;
    int currVal;
    uint64_t currMyPiece = whiteKing;
    uint64_t currTheirPiece = blackKing;
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
        currTheirPiece = currTheirPiece >> 1;
    }

    for(i = 1; i < 6; i++){
        currPoints = pts[i];
        currMyPiece = myPieces[i];
        currTheirPiece = theirPieces[i];
        currVal = vals[i];
        int j;
        for(j = 63; j >= 0; j--){
            // & position with 1
            uint64_t isMinePresent = currMyPiece & 1;
            if(isMinePresent){
                // Add piece value and positional value
                sum += currVal + currPoints[j];
            }
            // Shift right
            currMyPiece = currMyPiece >> 1;
        }
        for(j = 0; j < 64; j++){
            // & position with 1        
            uint64_t isTheirsPresent = currTheirPiece & 1;
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