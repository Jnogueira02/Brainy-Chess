#include <cstdint>
#include <cstdio>


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

int calculateRank(uint64_t piece){
    if(piece & 0b0000000000000000000000000000000000000000000000000000000011111111)
        return 1;
    else if(piece & 0b0000000000000000000000000000000000000000000000001111111100000000)
        return 2;
    else if(piece & 0b0000000000000000000000000000000000000000111111110000000000000000)
        return 3;
    else if(piece & 0b0000000000000000000000000000000011111111000000000000000000000000)
        return 4;
    else if(piece & 0b0000000000000000000000001111111100000000000000000000000000000000)
        return 5;
    else if(piece & 0b0000000000000000111111110000000000000000000000000000000000000000)
        return 6;
    else if(piece & 0b0000000011111111000000000000000000000000000000000000000000000000)
        return 7;
    else
        return 8;
}

int calculateFile(uint64_t piece){
    if(piece & 0b1000000010000000100000001000000010000000100000001000000010000000)
        return 1;
    else if(piece & 0b0100000001000000010000000100000001000000010000000100000001000000)
        return 2;
    else if(piece & 0b0010000000100000001000000010000000100000001000000010000000100000)
        return 3;
    else if(piece & 0b0001000000010000000100000001000000010000000100000001000000010000)
        return 4;
    else if(piece & 0b0000100000001000000010000000100000001000000010000000100000001000)
        return 5;
    else if(piece & 0b0000010000000100000001000000010000000100000001000000010000000100)
        return 6;
    else if(piece & 0b0000001000000010000000100000001000000010000000100000001000000010)
        return 7; 
    else
        return 8;
    return 0;
}

// Need to explicitly define the difference between current position and Tmax in bytes.
// Cannot rely on result of x << 64 being 0 or 1

int main(){
    uint64_t rook = 0b0000000000000000000000000000000000000000000000000000000000000001;
    uint64_t res = move_rook(rook, 3, 7);
    print_board(rook);
    printf("\nMoved:\n\n");
    print_board(res);
    return 0;
}