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
            printf("%lld ", bit);
            mask >>= 1;
            shift--;
        }
        printf("\n");
    }
}

uint64_t move_knight(uint64_t knight, int direction /*no int n*/){
    switch(direction){
        // Up 2, Right 1
        case 0:
            return knight << 15;
            break;
        // Right 2, Up 1
        case 1:
            break;
        // Right 2, Down 1
        case 2:
            break;
        // Down 2, Right 1
        case 3:
            break;
        // Down 2, Left 1
        case 4:
            break;
        // Left 2, Down 1
        case 5:
            break;
        // Left 2, Up 1
        case 6:
            break;
        // Up 2, Left 1
        default:
            break;                                                                                    
    }
}

int main(){
    print_board(move_knight(0x0000000000000001ULL, 0));
    return 0;
}