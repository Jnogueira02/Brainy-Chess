#include <cstdint>
#include <cstdio>
#include <iostream>

struct Board{
    uint64_t whiteKing;
    uint64_t whiteQueen;
    uint64_t whiteRook;
    uint64_t whiteBishop;
    uint64_t whiteKnight;
    uint64_t whitePawn;

    uint64_t blackKing;
    uint64_t blackQueen;
    uint64_t blackRook;
    uint64_t blackBishop;
    uint64_t blackKnight;
    uint64_t blackPawn;

    Board(uint64_t whiteKing, uint64_t whiteQueen, uint64_t whiteRook, uint64_t whiteBishop, uint64_t whiteKnight, uint64_t whitePawn,
          uint64_t blackKing, uint64_t blackQueen, uint64_t blackRook, uint64_t blackBishop, uint64_t blackKnight, uint64_t blackPawn): 
          whiteKing(whiteKing), whiteQueen(whiteQueen), whiteRook(whiteRook), whiteBishop(whiteBishop), whiteKnight(whiteKnight), whitePawn(whitePawn),
          blackKing(blackKing), blackQueen(blackQueen), blackRook(blackRook), blackBishop(blackBishop), blackKnight(blackKnight), blackPawn(blackPawn){}

    uint64_t makeWhiteBoard(){
        return whiteKing | whiteQueen | whiteRook | whiteBishop | whiteKnight | whitePawn;
    }

    uint64_t makeBlackBoard(){
        return blackKing | blackQueen | blackRook | blackBishop | blackKnight | blackPawn;
    }

    uint64_t makeBoard(){
        return makeWhiteBoard() | makeBlackBoard();
    }

    void print_board(){
        uint64_t num = makeBoard();
        uint64_t mask = UINT64_MAX;
        int i;
        int shift = 63;
        std::cout << std::endl;
        for(i = 0; i < 8; i++){
            int j;
            for(j = 0; j <8; j++){
                uint64_t bit = num & mask;
                bit >>= shift;
                std::cout << bit << " ";
                mask >>= 1;
                shift--;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

};



int main(){
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

    uint64_t whiteBoard = whiteKing | whiteQueen | whiteRook | whiteBishop | whiteKnight | whitePawn;
    uint64_t blackBoard = blackKing | blackQueen | blackRook | blackBishop | blackKnight | blackPawn;
    uint64_t board = whiteBoard | blackBoard;

    Board myBoard(whiteKing, whiteQueen, whiteRook, whiteBishop, whiteKnight, whitePawn,
                  blackKing, blackQueen, blackRook, blackBishop, blackKnight, blackPawn);

    myBoard.print_board();
    return 0;
}