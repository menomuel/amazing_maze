#include "maze_generator.h"


#include <iostream>
#include <stack>

namespace
{
    std::vector<std::vector<Cell>> generateCore(int width, int height, unsigned int seed)
    {
        std::vector<std::vector<Cell>> labyrinth;
        labyrinth.resize(height);
        for (auto& r : labyrinth)
            r.resize(width);
    	
        for (int col = 0; col < width; ++col)
        {
            for (int row = 0; row < height; ++row)
            {
                labyrinth[row][col].row = row;
                labyrinth[row][col].col = col;
                labyrinth[row][col].Visited = false;
            }
        }

        //Choose start position
        std::mt19937 engine(seed);
        std::uniform_int_distribution<> distrib(0, std::max(width, height));

        int startX = distrib(engine) % width;
        int startY = distrib(engine) % height;

        labyrinth[startX][startY].Visited = true;

        //Begin building path
        std::stack<Cell> path;
        path.push(labyrinth[startX][startY]);

        while (!path.empty())
        {
            Cell _cell = path.top();

            //Track available neighbors 
            std::vector<Cell> nextStep;
            if (_cell.row > 0 && labyrinth[_cell.row - 1][_cell.col].Visited == false)
                nextStep.push_back(labyrinth[_cell.row - 1][_cell.col]);
            if (_cell.row < width - 1 && labyrinth[_cell.row + 1][_cell.col].Visited == false)
                nextStep.push_back(labyrinth[_cell.row + 1][_cell.col]);
            if (_cell.col > 0 && labyrinth[_cell.row][_cell.col - 1].Visited == false)
                nextStep.push_back(labyrinth[_cell.row][_cell.col - 1]);
            if (_cell.col < height - 1 && labyrinth[_cell.row][_cell.col + 1].Visited == false)
                nextStep.push_back(labyrinth[_cell.row][_cell.col + 1]);

            if (!nextStep.empty())
            {
                //Choose a random direction
                Cell next = nextStep[distrib(engine) % nextStep.size()];

                //Open path to the neighbor
                if (next.row != _cell.row)
                {
                    if (_cell.row - next.row > 0)
                    {
                        labyrinth[_cell.row][_cell.col].Top = Open;
                        labyrinth[next.row][next.col].Bottom = Open;
                    }
                    else
                    {
                        labyrinth[_cell.row][_cell.col].Bottom = Open;
                        labyrinth[next.row][next.col].Top = Open;
                    }
                }
                if (next.col != _cell.col)
                {
                    if (_cell.col - next.col > 0)
                    {
                        labyrinth[_cell.row][_cell.col].Left = Open;
                        labyrinth[next.row][next.col].Right = Open;
                    }
                    else
                    {
                        labyrinth[_cell.row][_cell.col].Right = Open;
                        labyrinth[next.row][next.col].Left = Open;
                    }
                }

                labyrinth[next.row][next.col].Visited = true;
                path.push(next);
            }
            else
            {
                //If no neighbors, check the previous cell 
                path.pop();
            }
        }

        return labyrinth;
    }
}

std::vector<std::vector<Cell>> MazeGenerator::generate(int width, int height, unsigned int seed)
{

    std::vector<std::vector<Cell>> labyrinthMap;
    labyrinthMap.resize(2 * height + 1);
    for (auto& r : labyrinthMap)
        r.resize(2 * width + 1);


    //Initialize map
    for (int i = 0; i < 2 * height + 1; ++i)
    {
        for (int j = 0; j < 2 * width + 1; ++j)
        {
            labyrinthMap[i][j].row = i;
            labyrinthMap[i][j].col = j;
            labyrinthMap[i][j].Visited = false;
            labyrinthMap[i][j].cellType = i > 0 && i < 2 * height && i % 2 == 1 && j > 0 && j < 2 * width && j % 2 == 1 ? CELL: WALL;
        }
    }

    auto labyrinth = generateCore(width, height, seed);

    for (int col = 0; col < width; col++)
        for (int row = 0; row < height; row++)
        {
            if (labyrinth[row][col].Left == Open)
            {
                labyrinthMap[2 * row + 1][(2 * col + 1) - 1].cellType = CELL;
            }

            if (labyrinth[row][col].Right == Open)
            {
                labyrinthMap[2 * row + 1][(2 * col + 1) + 1].cellType = CELL;
            }

            if (labyrinth[row][col].Top == Open)
            {
                labyrinthMap[(2 * row + 1) - 1][2 * col + 1].cellType = CELL;
            }

            if (labyrinth[row][col].Bottom == Open)
            {
                labyrinthMap[(2 * row + 1) + 1][2 * col + 1].cellType = CELL;
            }
        }

    return labyrinthMap;
}
