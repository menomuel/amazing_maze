#pragma once
#include <vector>
#include "types.h"

class MazeGenerator
{
public:
    static std::vector<std::vector<Cell>> generate(int width, int height, unsigned int seed = 90);

};
