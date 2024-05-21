#include <cstdint>
#include <cstdio>
#include <iostream>

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

void print_board(uint64_t num){
    uint64_t mask = UINT64_MAX;
    int i;
    int shift = 63;
    for(i = 0; i < 8; i++){
        int j;
        for(j = 0; j <8; j++){
            uint64_t bit = num & mask;
            bit >>= shift;
            printf("%lld ", bit);
            mask >>= 1;
            shift--;
        }
        printf("\n");
    }
}

int main(){
    uint64_t board = whitePawn | whiteRook | whiteKnight | whiteBishop | whiteQueen | whiteKing |
                        blackPawn | blackRook | blackKnight | blackBishop | blackQueen | blackKing;
    print_board(board);
    return 0;
}