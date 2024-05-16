#include <cstdint>
#include <cstdio>
// Would direct memory manipulation be more valuable (void method) (or even possible?) or returning the new bit string?
// 0-->forward, 1-->right, 2-->backward, 3-->left // Is there a way to do this w/o ifs?
uint64_t move_rook(uint64_t rook, int n, int direction){
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

// Need to explicitly define the difference between current position and Tmax in bytes.
// Cannot rely on result of x << 64 being 0 or 1


int main(){
    uint64_t rook = 0b0000000000000000000000000000000000000000000000000000000000000001;
    uint64_t res = move_rook(rook, 2, 3);
    printf("%lld\n", res);
    return 0;
}