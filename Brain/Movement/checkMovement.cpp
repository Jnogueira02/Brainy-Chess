#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <tuple>
#include <unordered_set>

struct Board{
    uint64_t whiteKing;
    uint64_t whiteQueen;
    uint64_t whiteRook;
    uint64_t whiteBishop;
    uint64_t whiteKnight;
    uint64_t whitePawn;

    uint64_t blackKing;
    uint64_t blackQueen;
    uint64_t blackRook;
    uint64_t blackBishop;
    uint64_t blackKnight;
    uint64_t blackPawn;

    // int whiteKingPos = 4;
    // int whiteQueenPos = 5;
    // int whiteRook1Pos = 8;
    // int whiteRook2Pos = 1;
    // int whiteBishop1Pos = 6;
    // int whiteBishop2Pos = 3;
    // int whiteKnight1Pos = 7;
    // int whiteKnight2Pos = 2;
    // int whitePawn1Pos = 16;
    // int whitePawn2Pos = 15;
    // int whitePawn3Pos = 14;
    // int whitePawn4Pos = 13;
    // int whitePawn5Pos = 12;
    // int whitePawn6Pos = 11;
    // int whitePawn7Pos = 10;
    // int whitePawn8Pos = 9;

    // int blackKingPos = 60;
    // int blackQueenPos = 61;
    // int blackRook1Pos = 64;
    // int blackRook2Pos = 57;
    // int blackBishop1Pos = 62;
    // int blackBishop2Pos = 59;
    // int blackKnight1Pos = 63;
    // int blackKnight2Pos = 58;
    // int blackPawn1Pos = 57;
    // int blackPawn2Pos = 56;
    // int blackPawn3Pos = 55;
    // int blackPawn4Pos = 54;
    // int blackPawn5Pos = 53;
    // int blackPawn6Pos = 52;
    // int blackPawn7Pos = 51;
    // int blackPawn8Pos = 50;


    Board(uint64_t whiteKing, uint64_t whiteQueen, uint64_t whiteRook, uint64_t whiteBishop, uint64_t whiteKnight, uint64_t whitePawn,
          uint64_t blackKing, uint64_t blackQueen, uint64_t blackRook, uint64_t blackBishop, uint64_t blackKnight, uint64_t blackPawn): 
          whiteKing(whiteKing), whiteQueen(whiteQueen), whiteRook(whiteRook), whiteBishop(whiteBishop), whiteKnight(whiteKnight), whitePawn(whitePawn),
          blackKing(blackKing), blackQueen(blackQueen), blackRook(blackRook), blackBishop(blackBishop), blackKnight(blackKnight), blackPawn(blackPawn){}

    uint64_t makeWhiteBoard(){
        return whiteKing | whiteQueen | whiteRook | whiteBishop | whiteKnight | whitePawn;
    }

    uint64_t makeBlackBoard(){
        return blackKing | blackQueen | blackRook | blackBishop | blackKnight | blackPawn;
    }

    uint64_t makeBoard(){
        return makeWhiteBoard() | makeBlackBoard();
    }

    void print_board(){
        uint64_t num = makeBoard();
        uint64_t mask = UINT64_MAX;
        int i;
        int shift = 63;
        std::cout << std::endl;
        for(i = 0; i < 8; i++){
            int j;
            for(j = 0; j <8; j++){
                uint64_t bit = num & mask;
                bit >>= shift;
                std::cout << bit << " ";
                mask >>= 1;
                shift--;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

};

int isInCheck(Board board){
    uint64_t whiteBoard = board.makeWhiteBoard();
    uint64_t blackBoard = board.makeBlackBoard();

    uint64_t whiteRook1 = board.whiteRook ^ (1);
    uint64_t whiteRook2 = board.whiteRook ^ (1 << 7);
    uint64_t whiteBishop1 = board.whiteBishop ^ (1 << 2);
    uint64_t whiteBishop2 = board.whiteBishop ^ (1 << 5);
    uint64_t whiteKnight1 = board.whiteKnight ^ (1 << 1);
    uint64_t whiteKnight2 = board.whiteKnight ^ (1 << 6);

    // When taking enemy piece, check if king and return 1

    return 0;
}

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

// Returns 1 if the square is occupied by a piece of the same color, 2 if occupied by an opposing color, 0 if unoccupied
int isOccupied(uint64_t piece, uint64_t whiteBoard, uint64_t blackBoard){
    if ((piece | whiteBoard) == whiteBoard)
        return 1;
    else if((piece | blackBoard) == blackBoard)
        return 2;
    else
        return 0;
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
    if(piece & 0x0100000000000000)
        return std::make_tuple(0x0100000000000000, 0x0100000000000000);
    else if(piece & 0x0201000000000000)
        return std::make_tuple(0x0001000000000000, 0x0200000000000000);
    else if(piece & 0x0402010000000000)
        return std::make_tuple(0x0000010000000000, 0x0400000000000000);
    else if(piece & 0x0804020100000000)
        return std::make_tuple(0x0000000100000000, 0x0800000000000000);
    else if(piece & 0x1008040201000000)
        return std::make_tuple(0x0000000001000000, 0x1000000000000000);
    else if(piece & 0x2010080402010000)
        return std::make_tuple(0x0000000000010000, 0x2000000000000000);
    else if(piece & 0x4020100804020100)
        return std::make_tuple(0x0000000000000100, 0x4000000000000000);
    else if(piece & 0x8040201008040201)
        return std::make_tuple(0x0000000000000001, 0x8000000000000000);
    else if(piece & 0x0080402010080402)
        return std::make_tuple(0x0000000000000002, 0x0080000000000000);
    else if(piece & 0x0000804020100804)
        return std::make_tuple(0x0000000000000004, 0x0000800000000000);
    else if(piece & 0x0000008040201008)
        return std::make_tuple(0x0000008000000008, 0x0000008000000000);
    else if(piece & 0x0000000080402010)
        return std::make_tuple(0x0000000000000010, 0x0000000080000000);
    else if(piece & 0x0000000000804020)
        return std::make_tuple(0x0000000000000020, 0x0000000000800000);
    else if(piece & 0x0000000000008040)
        return std::make_tuple(0x0000000000000040, 0x0000000000008000);
    else
        return std::make_tuple(0x0000000000000080, 0x0000000000000080);
}
std::tuple<uint64_t, uint64_t> calculateMinorDiag(uint64_t piece){ //Don't have to & for unnecessary colors
    if(piece & 0x8000000000000000)
        return std::make_tuple(0x8000000000000000, 0x8000000000000000);
    else if(piece & 0x4080000000000000)
        return std::make_tuple(0x0080000000000000, 0x4000000000000000);
    else if(piece & 0x2040800000000000)
        return std::make_tuple(0x0000800000000000, 0x2000000000000000);
    else if(piece & 0x1020408000000000)
        return std::make_tuple(0x0000008000000000, 0x1000000000000000);
    else if(piece & 0x0810204080000000)
        return std::make_tuple(0x0000000080000000, 0x0800000000000000);
    else if(piece & 0x0408102040800000)
        return std::make_tuple(0x0000000000800000, 0x0400000000000000);
    else if(piece & 0x0204081020408000)
        return std::make_tuple(0x0000000000008000, 0x0200000000000000);
    else if(piece & 0x0102040810204080)
        return std::make_tuple(0x0000000000000080, 0x0100000000000000);
    else if(piece & 0x0001020408102040)
        return std::make_tuple(0x0000000000000040, 0x0001000000000000);
    else if(piece & 0x0000010204081020)
        return std::make_tuple(0x0000000000000020, 0x0000010000000000);  
    else if(piece & 0x0000000102040810)
        return std::make_tuple(0x0000000000000010, 0x0000000100000000); 
    else if(piece & 0x0000000001020408)
        return std::make_tuple(0x0000000000000008, 0x0000000001000000);   
    else if(piece & 0x0000000000010204)
        return std::make_tuple(0x0000000000000004, 0x0000000000010000);
    else if(piece & 0x0000000000000102)
        return std::make_tuple(0x0000000000000002, 0x0000000000000100);
    else
        return std::make_tuple(0x0000000000000001, 0x0000000000000001);         
}
std::unordered_set<int> generate_bishop(uint64_t bishop, Board board){
    uint64_t whiteBoard = board.makeWhiteBoard();
    uint64_t blackBoard = board.makeBlackBoard();

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
        // If the prospective square is occupied by one of your own pieces, break!! // use value so only have to call function once
        if(isOccupied(tempBishop, whiteBoard, blackBoard) == 1)
            break;
        else if(isOccupied(tempBishop, whiteBoard, blackBoard) == 2){
            upLeft++;
            resMoves.insert(upLeft * 9);
            break;
        }
        upLeft++;
        resMoves.insert(upLeft * 9);
    }
    tempBishop = bishop;
    while(tempBishop != minMain){
        tempBishop >>= 9;
        if(isOccupied(tempBishop, whiteBoard, blackBoard) == 1)
            break;
        else if(isOccupied(tempBishop, whiteBoard, blackBoard) == 2){
            downRight++;
            resMoves.insert(downRight * 9);
            break;
        }
        downRight++;
        resMoves.insert(downRight * -9);
    }
    tempBishop = bishop;
    while(tempBishop != maxMinor){
        tempBishop <<= 7;
        if(isOccupied(tempBishop, whiteBoard, blackBoard) == 1)
            break;
        else if(isOccupied(tempBishop, whiteBoard, blackBoard) == 2){
            upRight++;
            resMoves.insert(upRight * 7);
            break;
        }
        upRight++;
        resMoves.insert(upRight * 7);
    }
    tempBishop = bishop;
    while(tempBishop != minMinor){
        tempBishop >>= 7;
        if(isOccupied(tempBishop, whiteBoard, blackBoard) == 1)
            break;
        else if(isOccupied(tempBishop, whiteBoard, blackBoard) == 2){
            downLeft++;
            resMoves.insert(downLeft * 9);
            break;
        }
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
std::unordered_set<int> generate_rook(uint64_t rook, Board board){
    uint64_t whiteBoard = board.makeWhiteBoard();
    uint64_t blackBoard = board.makeBlackBoard();

    auto [minRank, maxRank] = calculateRank(rook);
    auto [minFile, maxFile] = calculateFile(rook);
    uint64_t tempRook = rook;

    int leftShift = 0;
    int rightShift = 0;
    int forwardShift = 0;
    int backShift = 0;

    std::unordered_set<int> resMoves = {};

    // # of squares to left // Is there a more efficient way to do this? // I CAN DO THIS FOR ALL THE MOVES AT ONCE!!!!!!!!!!!!!!!!!!!
    while(tempRook != maxRank){
        tempRook <<= 1;
        // Occupied by own piece
        if(isOccupied(tempRook, whiteBoard, blackBoard) == 1)
            break;
        // Occupied by enemy piece
        else if(isOccupied(tempRook, whiteBoard, blackBoard) == 2){
            leftShift++;
            resMoves.insert(leftShift);
            break;
        }
        leftShift++;
        resMoves.insert(leftShift);
    }
    tempRook = rook;
    // # of squares to right
    while(tempRook != minRank){
        tempRook >>=  1;
        // Occupied by own piece
        if(isOccupied(tempRook, whiteBoard, blackBoard) == 1)
            break;
        // Occupied by enemy piece
        else if(isOccupied(tempRook, whiteBoard, blackBoard) == 2){
            rightShift++;
            resMoves.insert(rightShift);
            break;
        }
        rightShift++;
        resMoves.insert(-rightShift);
    }
    tempRook = rook;
    // # of squares forwards
    while(tempRook != maxFile){
        tempRook <<= 8;
        if(isOccupied(tempRook, whiteBoard, blackBoard) == 1)
            break;
        else if(isOccupied(tempRook, whiteBoard, blackBoard) == 2){
            forwardShift++;
            resMoves.insert(forwardShift * 8);
            break;
        }
        forwardShift++;
        resMoves.insert(forwardShift * 8);
    }
    tempRook = rook;
    // # of squares backwards
    while(tempRook != minFile){
        tempRook >>= 8;
        if(isOccupied(tempRook, whiteBoard, blackBoard) == 1)
            break;
        else if(isOccupied(tempRook, whiteBoard, blackBoard) == 2){
            backShift++;
            resMoves.insert(backShift * -8);
            break;
        }
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
std::unordered_set<int> generate_knight(uint64_t knight, Board board){
    uint64_t whiteBoard = board.makeWhiteBoard();
    uint64_t blackBoard = board.makeBlackBoard();

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
        if(isOccupied(tempKnight, whiteBoard, blackBoard) == 1)
            resMoves.erase(shift);
        tempKnight = knight;
    }

    return resMoves;
}
/*******************************************************************************************************************************************/


int main(){
    Board board(whitePawn, whiteRook, whiteKnight, whiteBishop, whiteQueen, whiteKing, blackPawn, blackRook, blackKnight, blackBishop, blackQueen, blackKing);
    

    uint64_t whiteLeftBishop = board.whiteBishop ^ 0x4;
    whiteLeftBishop <<= 8;
    // whiteLeftBishop <<= 8;
    // whiteLeftBishop <<= 8;
    
    std::unordered_set<int> moves = generate_bishop(whiteLeftBishop, board);
    for(int elt : moves){
        std::cout << elt << " ";
    }
    std::cout << std::endl << std::endl;

    // uint64_t whiteLeftRook = board.whiteRook ^ 0x1;
    // whiteLeftRook <<= 8;
    // whiteLeftRook <<= 8;
    
    // std::unordered_set<int> moves = generate_rook(whiteLeftRook, board);
    // for(int elt : moves){
    //     std::cout << elt << " ";
    // }
    // std::cout << std::endl << std::endl;

    // uint64_t whiteLeftKnight = board.whiteKnight ^ 0x2;
    // print_board(whiteLeftKnight);

    // std::unordered_set<int> moves = generate_knight(whiteLeftKnight, board);
    // for(int elt : moves){
    //     std::cout << elt << " ";
    // }
    // std::cout << std::endl << std::endl;

    return 0;
}