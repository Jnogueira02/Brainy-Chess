#include <cstdint>
#include <cstdio>
#include <iostream>
#include <tuple>
#include <unordered_set>

#include "knightMovement.hpp"

uint64_t move_knight(uint64_t knight, int direction){
    switch(direction){
        // Up 2, Right 1
        case 0:
            knight <<= 15;
            break;
        // Right 2, Up 1
        case 1:
            knight <<= 6;
            break;
        // Right 2, Down 1
        case 2:
            knight >>= 10;
            break;
        // Down 2, Right 1
        case 3:
            knight >>= 17;
            break;
        // Down 2, Left 1
        case 4:
            knight >>= 15;
            break;
        // Left 2, Down 1
        case 5:
            knight >>= 6;
            break;
        // Left 2, Up 1
        case 6:
            knight <<= 10;
            break;
        // Up 2, Left 1
        default:
            knight <<= 17;
            break; 
    }
    return knight;                                                                                   
}

std::unordered_set<int> knightMoves = {15, 6, -10, -17, -15, -6, 10, 17};
// Maybe store right shifts as negative numbers (can be reversed later)
// May not be necessary to check for all masks
std::unordered_set<int> generate_knight(uint64_t knight){
    std::unordered_set<int> resMoves = knightMoves;

    // Right two columns
    if(knight & 0x0303030303030303){
        resMoves.erase(6);
        resMoves.erase(-10);
    }
    // Left two columns
    else if(knight & 0xC0C0C0C0C0C0C0C0){
        resMoves.erase(-6);
        resMoves.erase(10);
    }
    
    // Top two rows
    if(knight & 0xFFFF000000000000){
        resMoves.erase(15);
        resMoves.erase(17);
    }
    // Bottom two rows
    else if(knight & 0x000000000000FFFF){
        resMoves.erase(-15);
        resMoves.erase(-17);
    }
    return resMoves;
}