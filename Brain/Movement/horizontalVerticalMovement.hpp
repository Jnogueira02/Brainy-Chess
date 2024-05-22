#ifndef HORIZONTALVERTICALMOVEMENT_HPP
#define HORIZONTALVERTICALMOVEMENT_HPP

#include <cstdint>
#include <unordered_set>

std::unordered_set<int> generate_rook(uint64_t rook);
uint64_t move_rook(uint64_t rook, int direction, int n);

#endif