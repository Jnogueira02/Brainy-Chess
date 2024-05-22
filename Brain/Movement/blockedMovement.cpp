#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <tuple>
#include <unordered_set>

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

// Returns true if a move would cause a piece to occupy a square already occupied by a piece of the same color, false otherwise
bool isOccupied(uint64_t piece, uint64_t whiteBoard){
    return (piece | whiteBoard) == whiteBoard;
}

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

/*******************************************************************************************************************************************/
// DIAGONAL MOVEMENT
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
std::unordered_set<int> generate_bishop(uint64_t bishop, uint64_t whiteBoard){
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
        // If the prospective square is occupied by one of your own pieces, break!!
        if(isOccupied(tempBishop, whiteBoard))
            break;
        upLeft++;
        resMoves.insert(upLeft * 9);
    }
    tempBishop = bishop;
    while(tempBishop != minMain){
        tempBishop >>= 9;
        if(isOccupied(tempBishop, whiteBoard))
            break;
        downRight++;
        resMoves.insert(downRight * -9);
    }
    tempBishop = bishop;
    while(tempBishop != maxMinor){
        tempBishop <<= 7;
        if(isOccupied(tempBishop, whiteBoard))
            break;
        upRight++;
        resMoves.insert(upRight * 7);
    }
    tempBishop = bishop;
    while(tempBishop != minMinor){
        tempBishop >>= 7;
        if(isOccupied(tempBishop, whiteBoard))
            break;
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
/*******************************************************************************************************************************************/
/*----------------------------------------------------------------------------------------------------------------------------------------**/
/*******************************************************************************************************************************************/
// HORIZONTAL & VERTICAL MOVEMENT
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
std::unordered_set<int> generate_rook(uint64_t rook, uint64_t whiteBoard){
    auto [minRank, maxRank] = calculateRank(rook);
    auto [minFile, maxFile] = calculateFile(rook);
    uint64_t tempRook = rook;

    int leftShift = 0;
    int rightShift = 0;
    int forwardShift = 0;
    int backShift = 0;

    std::unordered_set<int> resMoves = {};

    // # of squares to left // Is there a more efficient way to do this?
    while(tempRook != maxRank){
        tempRook <<= 1;
        if(isOccupied(tempRook, whiteBoard))
            break;
        leftShift++;
        resMoves.insert(leftShift);
    }
    tempRook = rook;
    // # of squares to right
    while(tempRook != minRank){
        tempRook >>=  1;
        if(isOccupied(tempRook, whiteBoard))
            break;
        rightShift++;
        resMoves.insert(-rightShift);
    }
    tempRook = rook;
    // # of squares forwards
    while(tempRook != maxFile){
        tempRook <<= 8;
        if(isOccupied(tempRook, whiteBoard))
            break;
        forwardShift++;
        resMoves.insert(forwardShift * 8);
    }
    tempRook = rook;
    // # of squares backwards
    while(tempRook != minFile){
        tempRook >>= 8;
        if(isOccupied(tempRook, whiteBoard))
            break;
        backShift++;
        resMoves.insert(backShift * -8);
    }
    return resMoves;
}
/*******************************************************************************************************************************************/
/*----------------------------------------------------------------------------------------------------------------------------------------**/
/*******************************************************************************************************************************************/
// KNIGHT MOVEMENT
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
std::unordered_set<int> generate_knight(uint64_t knight, uint64_t whiteBoard){
    std::unordered_set<int> resMoves = knightMoves;

    // Right two columns
    if(knight & 0x0303030303030303){
        resMoves.erase(6);
        resMoves.erase(-10);
        // Rightmost column
        if(knight & 0x0101010101010101){
            resMoves.erase(15);
            resMoves.erase(-17);
        }
    }
    // Left two columns
    else if(knight & 0xC0C0C0C0C0C0C0C0){
        resMoves.erase(-6);
        resMoves.erase(10);
        // Leftmost column
        if(knight & 0x8080808080808080){
            resMoves.erase(-15);
            resMoves.erase(17);
        }
    }
    
    // Top two rows
    if(knight & 0xFFFF000000000000){
        resMoves.erase(15);
        resMoves.erase(17);
        // Top row
        if(knight & 0xFF00000000000000){
            resMoves.erase(6);
            resMoves.erase(10);
        }
    }
    // Bottom two rows
    else if(knight & 0x000000000000FFFF){
        resMoves.erase(-15);
        resMoves.erase(-17);
        // Bottom row
        if(knight & 0x00000000000000FF){
            resMoves.erase(-6);
            resMoves.erase(-10);
        }
    }

    uint64_t tempKnight = knight;
    // Remove occupied moves
    for(int shift : resMoves){
        if(shift > 0)
            tempKnight <<= shift;
        else
            tempKnight >>= -shift;
        if(isOccupied(tempKnight, whiteBoard))
            resMoves.erase(shift);
        tempKnight = knight;
    }

    return resMoves;
}
/*******************************************************************************************************************************************/



int main(){
    uint64_t whiteBoard = whitePawn | whiteRook | whiteKnight | whiteBishop | whiteQueen | whiteKing;
    uint64_t blackBoard = blackPawn | blackRook | blackKnight | blackBishop | blackQueen | blackKing;
    uint64_t board = whiteBoard | blackBoard;

    // uint64_t whiteLeftBishop = whiteBishop ^ 0x4;
    // whiteLeftBishop <<= 8;
    // whiteLeftBishop <<= 8;
    // whiteLeftBishop <<= 8;
    
    // std::unordered_set<int> moves = generate_bishop(whiteLeftBishop, whiteBoard);
    // for(int elt : moves){
    //     std::cout << elt << " ";
    // }
    // std::cout << std::endl << std::endl;

    // uint64_t whiteLeftRook = whiteRook ^ 0x1;
    // whiteLeftRook <<= 8;
    // whiteLeftRook <<= 8;
    
    // std::unordered_set<int> moves = generate_rook(whiteLeftRook, whiteBoard);
    // for(int elt : moves){
    //     std::cout << elt << " ";
    // }
    // std::cout << std::endl << std::endl;

    uint64_t whiteLeftKnight = whiteKnight ^ 0x2;
    print_board(whiteLeftKnight);

    std::unordered_set<int> moves = generate_knight(whiteLeftKnight, whiteBoard);
    for(int elt : moves){
        std::cout << elt << " ";
    }
    std::cout << std::endl << std::endl;

    return 0;
}