#include <cstdint>
#include <cstdio>
#include <iostream>
#include <tuple>
#include <unordered_set>

#include "diagonalMovement.hpp"

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

std::tuple<uint64_t, uint64_t> calculateMainDiag(uint64_t piece){
    if(piece & 0x0100000000000000ULL)
        return std::make_tuple(0x0100000000000000ULL, 0x0100000000000000ULL);
    else if(piece & 0x0201000000000000ULL)
        return std::make_tuple(0x0001000000000000ULL, 0x0200000000000000ULL);
    else if(piece & 0x0402010000000000ULL)
        return std::make_tuple(0x0000010000000000ULL, 0x0400000000000000ULL);
    else if(piece & 0x0804020100000000ULL)
        return std::make_tuple(0x0000000100000000ULL, 0x0800000000000000ULL);
    else if(piece & 0x1008040201000000ULL)
        return std::make_tuple(0x0000000001000000ULL, 0x1000000000000000ULL);
    else if(piece & 0x2010080402010000ULL)
        return std::make_tuple(0x0000000000010000ULL, 0x2000000000000000ULL);
    else if(piece & 0x4020100804020100ULL)
        return std::make_tuple(0x0000000000000100ULL, 0x4000000000000000ULL);
    else if(piece & 0x8040201008040201ULL)
        return std::make_tuple(0x0000000000000001ULL, 0x8000000000000000ULL);
    else if(piece & 0x0080402010080402ULL)
        return std::make_tuple(0x0000000000000002ULL, 0x0080000000000000ULL);
    else if(piece & 0x0000804020100804ULL)
        return std::make_tuple(0x0000000000000004ULL, 0x0000800000000000ULL);
    else if(piece & 0x0000008040201008ULL)
        return std::make_tuple(0x0000008000000008ULL, 0x0000008000000000ULL);
    else if(piece & 0x0000000080402010ULL)
        return std::make_tuple(0x0000000000000010ULL, 0x0000000080000000ULL);
    else if(piece & 0x0000000000804020ULL)
        return std::make_tuple(0x0000000000000020ULL, 0x0000000000800000ULL);
    else if(piece & 0x0000000000008040ULL)
        return std::make_tuple(0x0000000000000040ULL, 0x0000000000008000ULL);
    else
        return std::make_tuple(0x0000000000000080ULL, 0x0000000000000080ULL);
}

std::tuple<uint64_t, uint64_t> calculateMinorDiag(uint64_t piece){ //Don't have to & for unnecessary colors
    if(piece & 0x8000000000000000ULL)
        return std::make_tuple(0x8000000000000000ULL, 0x8000000000000000ULL);
    else if(piece & 0x4080000000000000ULL)
        return std::make_tuple(0x0080000000000000ULL, 0x4000000000000000ULL);
    else if(piece & 0x2040800000000000ULL)
        return std::make_tuple(0x0000800000000000ULL, 0x2000000000000000ULL);
    else if(piece & 0x1020408000000000ULL)
        return std::make_tuple(0x0000008000000000ULL, 0x1000000000000000ULL);
    else if(piece & 0x0810204080000000ULL)
        return std::make_tuple(0x0000000080000000ULL, 0x0800000000000000ULL);
    else if(piece & 0x0408102040800000ULL)
        return std::make_tuple(0x0000000000800000ULL, 0x0400000000000000ULL);
    else if(piece & 0x0204081020408000ULL)
        return std::make_tuple(0x0000000000008000ULL, 0x0200000000000000ULL);
    else if(piece & 0x0102040810204080ULL)
        return std::make_tuple(0x0000000000000080ULL, 0x0100000000000000ULL);
    else if(piece & 0x0001020408102040ULL)
        return std::make_tuple(0x0000000000000040ULL, 0x0001000000000000ULL);
    else if(piece & 0x0000010204081020ULL)
        return std::make_tuple(0x0000000000000020ULL, 0x0000010000000000ULL);  
    else if(piece & 0x0000000102040810ULL)
        return std::make_tuple(0x0000000000000010ULL, 0x0000000100000000ULL); 
    else if(piece & 0x0000000001020408ULL)
        return std::make_tuple(0x0000000000000008ULL, 0x0000000001000000ULL);   
    else if(piece & 0x0000000000010204ULL)
        return std::make_tuple(0x0000000000000004ULL, 0x0000000000010000ULL);
    else if(piece & 0x0000000000000102ULL)
        return std::make_tuple(0x0000000000000002ULL, 0x0000000000000100ULL);
    else
        return std::make_tuple(0x0000000000000001ULL, 0x0000000000000001ULL);         
}

std::unordered_set<int> generate_bishop(uint64_t bishop){
    auto[minMain, maxMain] = calculateMainDiag(bishop);
    auto[minMinor, maxMinor] = calculateMinorDiag(bishop);
    uint64_t upRight = 0;
    uint64_t downRight = 0;
    uint64_t downLeft = 0;
    uint64_t upLeft = 0;
    uint64_t tempBishop = bishop;

    std::unordered_set<int> resMoves = {};

    while(tempBishop != maxMain){
        tempBishop <<= 9;
        upLeft++;
        resMoves.insert(upLeft * 9);
    }
    tempBishop = bishop;
    while(tempBishop != minMain){
        tempBishop >>= 9;
        downRight++;
        resMoves.insert(downRight * -9);
    }
    tempBishop = bishop;
    while(tempBishop != maxMinor){
        tempBishop <<= 7;
        upRight++;
        resMoves.insert(upRight * 7);
    }
    tempBishop = bishop;
    while(tempBishop != minMinor){
        tempBishop >>= 7;
        downLeft++;
        resMoves.insert(downLeft * -7);
    }
    return resMoves;
}

uint64_t move_bishop(uint64_t bishop, int direction, int n){
    switch(direction){
        case 0:
            bishop <<= (n * 7);
            break;
        case 1:
            bishop >>= (n * 9);
            break;
        case 2:
            bishop >>= (n * 7);
            break;
        default:
            bishop <<= (n * 9);
            break;
    }
    return bishop;
}

int main(){
    uint64_t bishop = 0x0000000800000000;
    print_board(bishop);
    std::unordered_set<int> moves = generate_bishop(bishop);
    for(int elt : moves){
        std::cout << elt << " ";
    }
    std::cout << std::endl;
    return 0;
}