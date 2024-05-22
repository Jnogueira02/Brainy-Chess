#ifndef DIAGONALMOVEMENT_HPP
#define DIAGONALMOVEMENT_HPP

#include <cstdint>
#include <unordered_set>

std::unordered_set<int> generate_bishop(uint64_t bishop);
uint64_t move_bishop(uint64_t bishop, int direction, int n);
void print_board(uint64_t num);

#endif