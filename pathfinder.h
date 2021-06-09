#pragma once
#include <list>
#include <vector>

#include "types.h"

class PathFinder
{
public:
    static std::list<Cell> findPath(const std::vector<std::vector<Cell>>& Maze, int x, int y, int x_to, int y_to);
};
