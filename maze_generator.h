#pragma once
#include <vector>
#include <random>

#include "types.h"

class MazeGenerator
{
public:
    static std::vector<std::vector<Cell>> generate(int width, int height, unsigned int seed = 0);

};
