#include "pathfinder.h"

#include <iostream>

std::list<Cell> PathFinder::findPath(const std::vector<std::vector<Cell>>& Maze, int x, int y, int x_to, int y_to)
{
    auto maze = Maze;
    //clear previous maze history
    for (int row = 0; row < static_cast<int>(maze.size()); ++row)
    {
        for (int col = 0; col < static_cast<int>(maze[0].size()); ++col)
        {
            if (maze[row][col].cellType != WALL)
            {
                maze[row][col].cellType = CELL;
                maze[row][col].Visited = false;
            }
        }
    }

	std::list<Cell> path;

    if (maze[x][y].cellType == WALL || maze[x_to][y_to].cellType == WALL)
    {
        std::cout << "No path between walls\n";
        return path;
    }

    maze[x][y].Visited = true;
    path.push_back(maze[x][y]);

    while (true)
    {
        Cell _cell = path.back();
        if (_cell.row == x_to && _cell.col == y_to)
            return path;

        std::vector<Cell> nextStep;

        if (_cell.row > 0 && maze[_cell.row - 1][_cell.col].Visited == false && maze[_cell.row - 1][_cell.col].cellType == CELL)
            nextStep.emplace_back(maze[_cell.row - 1][_cell.col]);
        if (_cell.row < maze.size() - 1 && maze[_cell.row + 1][_cell.col].Visited == false && maze[_cell.row + 1][_cell.col].cellType == CELL)
            nextStep.emplace_back(maze[_cell.row + 1][_cell.col]);
        if (_cell.col > 0 && maze[_cell.row][_cell.col - 1].Visited == false && maze[_cell.row][_cell.col - 1].cellType == CELL)
            nextStep.emplace_back(maze[_cell.row][_cell.col - 1]);
        if (_cell.col < maze[0].size() - 1 && maze[_cell.row][_cell.col + 1].Visited == false && maze[_cell.row][_cell.col + 1].cellType == CELL)
            nextStep.emplace_back(maze[_cell.row][_cell.col + 1]);


        if (nextStep.empty())
            path.pop_back();
        else
        {
            Cell next = nextStep[rand() % nextStep.size()];
            next.Visited = true;
            maze[next.row][next.col].Visited = true;
            path.push_back(next);
        }

        if (path.empty())
        {
            std::cout << "No path between cells\n";
            return path;
        }

    }
}
