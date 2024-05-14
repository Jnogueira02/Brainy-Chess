// PieceSquareTables.cpp

#include "PieceSquareTables.h"

// Piece Square Table definitions
float kingPST[]= {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0, -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0, -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0, -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0, -2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0, -1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0, 2.0,  2.0,  0.0,  0.0,  0.0,  0.0,  2.0,  2.0, 2.0,  3.0,  1.0,  0.0,  0.0,  1.0,  3.0,  2.0};
float queenPST[]= {-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0, -1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0, -1.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0, -0.5,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5, 0.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5, -1.0,  0.5,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0, -1.0,  0.0,  0.5,  0.0,  0.0,  0.0,  0.0, -1.0, -2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0};
float rookPST[] =  {0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, 0.5,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  0.5, -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5, -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5, -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5, -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5, -0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5, 0.0,  0.0,  0.0,  0.5,  0.5,  0.0,  0.0,  0.0};
float bishopPST[] = {-2.0,-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0, -1.0, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0, -1.0, 0.0,  0.5,  1.0,  1.0,  0.5,  0.0, -1.0, -1.0, 0.5,  0.5,  1.0,  1.0,  0.5,  0.5, -1.0, -1.0, 0.0,  1.0,  1.0,  1.0,  1.0,  0.0, -1.0, -1.0, 1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0, -1.0, 0.5,  0.0,  0.0,  0.0,  0.0,  0.5, -1.0, -2.0,-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0};
float knightPST[] = {-5.0,-4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0, -4.0,-2.0,  0.0,  0.0,  0.0,  0.0, -2.0, -4.0, -3.0, 0.0,  1.0,  1.5,  1.5,  1.0,  0.0, -3.0, -3.0, 0.5,  1.5,  2.0,  2.0,  1.5,  0.5, -3.0, -3.0, 0.0,  1.5,  2.0,  2.0,  1.5,  0.0, -3.0, -3.0, 0.5,  1.0,  1.5,  1.5,  1.0,  0.5, -3.0, -4.0,-2.0,  0.0,  0.5,  0.5,  0.0, -2.0, -4.0, -5.0,-4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0};
float pawnPST[] = {0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, 5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0, 1.0,  1.0,  2.0,  3.0,  3.0,  2.0,  1.0,  1.0, 0.5,  0.5,  1.0,  2.5,  2.5,  1.0,  0.5,  0.5, 0.0,  0.0,  0.0,  2.0,  2.0,  0.0,  0.0,  0.0, 0.5, -0.5, -1.0,  0.0,  0.0, -1.0, -0.5,  0.5, 0.5,  1.0,  1.0, -2.0, -2.0,  1.0,  1.0,  0.5, 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0};

// Reversed Piece Square Tables
float kingPSTRev[] = {2.0, 3.0, 1.0, 0.0, 0.0, 1.0, 3.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 2.0, -1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0, -2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0, -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0, -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0, -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0, -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0};
float queenPSTRev[] = {-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0, -1.0, 0.0, 0.5, 0.0, 0.0, 0.5, 0.0, -1.0, -1.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, -1.0, 0.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, 0.0, -0.5, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5, -1.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, -2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0};
float rookPSTRev[] = {0.0, 0.0, 0.0, 0.5, 0.5, 0.0, 0.0, 0.0, -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5, -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5, -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5, -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5, -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float bishopPSTRev[] = {-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0, -1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0, -1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, -1.0, -1.0, 0.5, 0.5, 1.0, 1.0, 0.5, 0.5, -1.0, -1.0, 0.0, 0.5, 1.0, 1.0, 0.5, 0.0, -1.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, -2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0};
float knightPSTRev[] = {-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0, -4.0, -2.0, 0.0, 0.5, 0.5, 0.0, -2.0, -4.0, -3.0, 0.5, 1.0, 1.5, 1.5, 1.0, 0.5, -3.0, -3.0, 0.0, 1.5, 2.0, 2.0, 1.5, 0.0, -3.0, -3.0, 0.5, 1.5, 2.0, 2.0, 1.5, 0.5, -3.0, -3.0, 0.0, 1.0, 1.5, 1.5, 1.0, 0.0, -3.0, -4.0, -2.0, 0.0, 0.0, 0.0, 0.0, -2.0, -4.0, -5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0};
float pawnPSTRev[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 1.0, 1.0, -2.0, -2.0, 1.0, 1.0, 0.5, 0.5, -0.5, -1.0, 0.0, 0.0, -1.0, -0.5, 0.5, 0.0, 0.0, 0.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.5, 0.5, 1.0, 2.5, 2.5, 1.0, 0.5, 0.5, 1.0, 1.0, 2.0, 3.0, 3.0, 2.0, 1.0, 1.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};