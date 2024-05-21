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
    printf("\n");
}

uint64_t move_knight(uint64_t knight, int direction /*no int n*/){
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

int main(){
    uint64_t knight = 0x0000000000200000ULL;
    print_board(knight);
    print_board(move_knight(knight, 0));
    return 0;
}