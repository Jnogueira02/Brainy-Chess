#ifndef KNIGHTMOVEMENT_HPP
#define KNIGHTMOVEMENT_HPP

#include <cstdint>
#include <unordered_set>

std::unordered_set<int> generate_knight(uint64_t knight);
uint64_t move_knight(uint64_t knight, int direction);

#endif