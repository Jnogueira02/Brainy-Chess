#include <cstdint>
#include <cstdio>
#include <iostream>
#include <tuple>
#include <unordered_set>

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
    printf("\n");
}

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

int main(){
    uint64_t knight = 0x0000000800000000;
    print_board(0x0000000800000000);
    std::unordered_set<int> moves = generate_knight(knight);
    for(int elt : moves){
        std::cout << elt << " ";
    }
    std::cout << std::endl;
    return 0;
}