#include <cstdint>
#include <cstdio>
#include <iostream>
#include <tuple>
#include <unordered_set>

#include "horizontalVerticalMovement.hpp"

/* Return inclusive tuple (minValue, maxValue),
    where maxValue is the leftmost square of a given rank,
    and minValue is the rightmost*/ 
std::tuple<uint64_t, uint64_t> calculateRank(uint64_t piece){
    // Rank 1
    if(piece & 0x00000000000000FFULL)
        return std::make_tuple(0x0000000000000001ULL, 0x0000000000000080ULL);
    // Rank 2
    else if(piece & 0x000000000000FF00ULL)
        return std::make_tuple(0x0000000000000100ULL, 0x0000000000008000ULL);
    // Rank 3
    else if(piece & 0x0000000000FF0000ULL)
        return std::make_tuple(0x0000000000010000ULL, 0x0000000000800000ULL);
    // Rank 4
    else if(piece & 0x00000000FF000000ULL)
        return std::make_tuple(0x0000000001000000ULL, 0x0000000080000000ULL);
    // Rank 5
    else if(piece & 0x000000FF00000000ULL)
        return std::make_tuple(0x0000000100000000ULL, 0x0000008000000000ULL);
    // Rank 6
    else if(piece & 0x0000FF0000000000ULL)
        return std::make_tuple(0x0000010000000000ULL, 0x0000800000000000ULL);
    // Rank 7
    else if(piece & 0x00FF000000000000ULL)
        return std::make_tuple(0x0001000000000000ULL, 0x0080000000000000ULL);
    // Rank 8
    else
        return std::make_tuple(0x0100000000000000ULL, 0x8000000000000000ULL);
}

/* Return inclusive tuple (minValue, maxValue),
    where maxValue is the forwardmost square of a given rank,
    and minValue is the backmost*/ 
std::tuple<uint64_t, uint64_t> calculateFile(uint64_t piece){
    // A File
    if(piece & 0x8080808080808080ULL)
        return std::make_tuple(0x0000000000000080ULL, 0x8000000000000000ULL);
    // B File
    else if(piece & 0x4040404040404040ULL)
        return std::make_tuple(0x0000000000000040ULL, 0x4000000000000000ULL);
    // C File
    else if(piece & 0x2020202020202020ULL)
        return std::make_tuple(0x0000000000000020ULL, 0x2000000000000000ULL);
    // D File
    else if(piece & 0x1010101010101010ULL)
        return std::make_tuple(0x0000000000000010ULL, 0x1000000000000000ULL);
    // E File
    else if(piece & 0x0808080808080808ULL)
        return std::make_tuple(0x0000000000000008ULL, 0x0800000000000000ULL);
    // F File
    else if(piece & 0x0404040404040404ULL)
        return std::make_tuple(0x0000000000000004ULL, 0x0400000000000000ULL);
    // G File
    else if(piece & 0x0202020202020202ULL)
        return std::make_tuple(0x0000000000000002ULL, 0x0200000000000000ULL);
    // H File
    else
        return std::make_tuple(0x0000000000000001ULL, 0x0100000000000000ULL);
}


// Would direct memory manipulation be more valuable (void method) (or even possible?) or returning the new bit string?
// 0-->forward, 1-->right, 2-->backward, 3-->left // Is there a way to do this w/o ifs?
uint64_t move_rook(uint64_t rook, int direction, int n){
    switch (direction)
    {
    // Forward
    case 0:
        rook <<= (n * 8);
        break;
    // Right
    case 1:
        rook >>= (1 * n);
        break;
    // Backward
    case 2:
        rook >>= (n * 8);
        break;
    // Left
    default:
        rook <<= (1 * n);
        break;
    }

    return rook;
}

// Maybe have a limit of number of squares we can move in a given direction...
std::unordered_set<int> generate_Rook(uint64_t rook){
    auto [minRank, maxRank] = calculateRank(rook);
    auto [minFile, maxFile] = calculateFile(rook);
    uint64_t rookTmp = rook;

    int leftShift = 0;
    int rightShift = 0;
    int forwardShift = 0;
    int backShift = 0;

    std::unordered_set<int> resMoves = {};

    // # of squares to left // Is there a more efficient way to do this?
    while(rookTmp != maxRank){
        rookTmp <<= 1;
        leftShift++;
        resMoves.insert(leftShift);
    }
    rookTmp = rook;
    // # of squares to right
    while(rookTmp != minRank){
        rookTmp >>=  1;
        rightShift++;
        resMoves.insert(-rightShift);
    }
    rookTmp = rook;
    // # of squares forwards
    while(rookTmp != maxFile){
        rookTmp <<= 8;
        forwardShift++;
        resMoves.insert(forwardShift * 8);
    }
    rookTmp = rook;
    // # of squares backwards
    while(rookTmp != minFile){
        rookTmp >>= 8;
        backShift++;
        resMoves.insert(backShift * -8);
    }
    return resMoves;
}