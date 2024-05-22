#include <cstdint>
#include <cstdio>
#include <iostream>

#include "diagonalMovement.hpp"
#include "horizontalVerticalMovement.hpp"
#include "knightMovement.hpp"

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

int main(){
    uint64_t whiteBoard = whitePawn | whiteRook | whiteKnight | whiteBishop | whiteQueen | whiteKing;
    uint64_t blackBoard = blackPawn | blackRook | blackKnight | blackBishop | blackQueen | blackKing;
    uint64_t board = whiteBoard | blackBoard;

    print_board(board);
    std::unordered_set<int> moves = generate_bishop(whiteBishop);

    for(int elt : moves){
        std::cout << elt << " ";
    }
    std::cout << std::endl;
    
    return 0;
}