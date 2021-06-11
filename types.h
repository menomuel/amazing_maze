#pragma once
#include <stdio.h>

enum cellTypes { CELL, VISITED, GENCELL, GENVISITED, RENDERED, WALL, WAY, CURRENT, LAST, SEEKED, EXIT };

enum CellState { Close, Open };

class Cell
{
public:
    Cell() = default;
    Cell(int r, int c, bool v, cellTypes type): row(r), col(c), Visited(v), cellType(type) {}
	
	
    int row;
    int col;
    CellState Left;
    CellState Right;
    CellState Top;
    CellState Bottom;
    bool Visited;
    cellTypes cellType;

    friend bool operator==(const Cell &c1, const Cell &c2)
    {
        return c1.row == c2.row && c1.col == c2.col;
    }
};
