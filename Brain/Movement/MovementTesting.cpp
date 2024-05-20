#include <cstdint>
#include <cstdio>
#include <iostream>
#include <tuple>

void print_board(uint64_t num){
    uint64_t mask = UINT64_MAX;
    int i;
    int shift = 63;
    for(i = 0; i < 8; i++){
        int j;
        for(j = 0; j <8; j++){
            uint64_t bit = num & mask;
            bit >>= shift;
            printf("%lld", bit);
            mask >>= 1;
            shift--;
        }
        printf("\n");
    }
}

/* Return inclusive tuple (minValue, maxValue),
    where maxValue is the leftmost square of a given rank,
    and minValue is the rightmost*/ 
std::tuple<uint64_t, uint64_t> calculateRank(uint64_t piece){
    // Rank 1
    if(piece & 0x00000000000000FF)
        return std::make_tuple(0x0000000000000001, 0x0000000000000080);
    // Rank 2
    else if(piece & 0x000000000000FF00)
        return std::make_tuple(0x0000000000000100, 0x0000000000008000);
    // Rank 3
    else if(piece & 0x0000000000FF0000)
        return std::make_tuple(0x0000000000010000, 0x0000000000800000);
    // Rank 4
    else if(piece & 0x00000000FF000000)
        return std::make_tuple(0x0000000001000000, 0x0000000080000000);
    // Rank 5
    else if(piece & 0x000000FF00000000)
        return std::make_tuple(0x0000000100000000, 0x0000008000000000);
    // Rank 6
    else if(piece & 0x0000FF0000000000)
        return std::make_tuple(0x0000010000000000, 0x0000800000000000);
    // Rank 7
    else if(piece & 0x00FF000000000000)
        return std::make_tuple(0x0001000000000000, 0x0080000000000000);
    // Rank 8
    else
        return std::make_tuple(0x0100000000000000, 0x8000000000000000);
}

/* Return inclusive tuple (minValue, maxValue),
    where maxValue is the forwardmost square of a given rank,
    and minValue is the backmost*/ 
std::tuple<uint64_t, uint64_t> calculateFile(uint64_t piece){
    // A File
    if(piece & 0x8080808080808080)
        return std::make_tuple(0x0000000000000080, 0x8000000000000000);
    // B File
    else if(piece & 0x4040404040404040)
        return std::make_tuple(0x0000000000000040, 0x4000000000000000);
    // C File
    else if(piece & 0x2020202020202020)
        return std::make_tuple(0x0000000000000020, 0x2000000000000000);
    // D File
    else if(piece & 0x1010101010101010)
        return std::make_tuple(0x0000000000000010, 0x1000000000000000);
    // E File
    else if(piece & 0x0808080808080808)
        return std::make_tuple(0x0000000000000008, 0x0800000000000000);
    // F File
    else if(piece & 0x0404040404040404)
        return std::make_tuple(0x0000000000000004, 0x0400000000000000);
    // G File
    else if(piece & 0x0202020202020202)
        return std::make_tuple(0x0000000000000002, 0x0200000000000000);
    // H File
    else
        return std::make_tuple(0x0000000000000001, 0x0100000000000000);
}


// Would direct memory manipulation be more valuable (void method) (or even possible?) or returning the new bit string?
// 0-->forward, 1-->right, 2-->backward, 3-->left // Is there a way to do this w/o ifs?
uint64_t move_rook(uint64_t rook, int direction, int n){
    switch (direction)
    {
    // Forward
    case 0:
        rook = rook << (n * 8);
        break;
    // Right
    case 1:
        rook = rook >> (1 * n);
        break;
    // Backward
    case 2:
        rook = rook >> (n * 8);
        break;
    // Left
    case 3:
        rook = rook << (1 * n);
        break;
    default:
        break;
    }

    return rook;
}

// Maybe have a limit of number of squares we can move in a given direction...
void generate_Rook(uint64_t rook){
    auto [minRank, maxRank] = calculateRank(rook);
    auto [minFile, maxFile] = calculateFile(rook);
    uint64_t rookTmp = rook;

    int leftShift = 0;
    int rightShift = 0;
    int forwardShift = 0;
    int backShift = 0;

    // # of squares to left // Is there a more efficient way to do this?
    while(rookTmp != maxRank){
        rookTmp <<= 1;
        leftShift++;
    }
    rookTmp = rook;
    // # of squares to right
    while(rookTmp != minRank){
        rookTmp >>=  1;
        rightShift++;
    }
    rookTmp = rook;
    // # of squares forwards
    while(rookTmp != maxFile){
        rookTmp <<= 8;
        forwardShift++;
    }
    rookTmp = rook;
    // # of squares backwards
    while(rookTmp != minFile){
        rookTmp >>= 8;
        backShift++;
    }
    printf("Forward: %d\nRight: %d\nBack: %d\nLeft: %d\n\n", forwardShift, rightShift, backShift, leftShift);
}


int main(){
    uint64_t rook = 0b1000000000000000000000000000000000000000000000000000000000000000;
    generate_Rook(rook);
    return 0;
}