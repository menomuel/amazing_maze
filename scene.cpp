#include "scene.h"

#include "maze_generator.h"
#include "pathfinder.h"

Scene::Scene(int numCubes) : numCubes_(numCubes), cube_(std::make_shared<Cube>()), rect_(std::make_shared<Rect>()),
    pathCube_(std::make_shared<Cube>())
{
    pathCube_->setMaterial(MaterialFactory::createGold());
    wallMaterial = MaterialFactory::createJade();
    freeCellMaterial = MaterialFactory::createRedRubber();
    visitedCellMaterial = MaterialFactory::createYellowRubber();
    pathMaterial = MaterialFactory::createGold();
}

void Scene::initScene()
{
    //auto maze = MazeGenerator::generate(8, 8);
    maze_ = MazeGenerator::generate(8, 8);

    /*
    matrices_.clear();
    cellMatrices_.clear();
    for (int i = 0; i < static_cast<int>(maze.size()); ++i)
    {
        for (int j = 0; j < static_cast<int>(maze[0].size()); ++j)
        {
            if(maze[i][j].cellType == WALL)
            {
                QMatrix4x4 mat;
                QVector3D currPos = QVector3D(cube_->getFacetSideLength() * i,
                                              0.f,
                                              -cube_->getFacetSideLength() * j);
                mat.translate(currPos);
                matrices_.push_back(mat);
            } else {
                QMatrix4x4 mat;
                QVector3D currPos = QVector3D(cube_->getFacetSideLength() * i,
                                              -cube_->getFacetSideLength() / 2,
                                              -cube_->getFacetSideLength() * j);
                mat.translate(currPos);
                cellMatrices_.push_back(mat);
            }
        }
    }
    */

    path_ = PathFinder::findPath(maze_, 1, 1, static_cast<int>(maze_.size()) - 2, static_cast<int>(maze_[0].size()) - 2);
    /*
    pathMatrices_.clear();
    for(auto& cell: path)
    {
        QMatrix4x4 mat;
        QVector3D currPos = QVector3D(pathCube_->getFacetSideLength() * cell.row,
                                      0.f,
                                      -pathCube_->getFacetSideLength() * cell.col);
        mat.translate(currPos);
        pathMatrices_.push_back(mat);
    }
    */
}

void Scene::drawScene(QOpenGLShaderProgram *shader) const
{
    for (int i = 0; i < static_cast<int>(maze_.size()); ++i)
    {
        for (int j = 0; j < static_cast<int>(maze_[0].size()); ++j)
        {
            QMatrix4x4 mat;
            if(maze_[i][j].cellType == WALL)
            {
                QVector3D currPos = QVector3D(cube_->getFacetSideLength() * i,
                                              0.f,
                                              -cube_->getFacetSideLength() * j);
                mat.translate(currPos);
                shader->setUniformValue(0, mat);
                wallMaterial->uploadToShader(shader);
                cube_->render(shader);
            } else if (maze_[i][j].cellType == CELL)
            {
                QVector3D currPos = QVector3D(cube_->getFacetSideLength() * i,
                                              -cube_->getFacetSideLength() / 2,
                                              -cube_->getFacetSideLength() * j);
                mat.translate(currPos);
                shader->setUniformValue(0, mat);
                freeCellMaterial->uploadToShader(shader);
                rect_->render(shader);
            } else if (maze_[i][j].cellType == VISITED)
            {
                QVector3D currPos = QVector3D(cube_->getFacetSideLength() * i,
                                              -cube_->getFacetSideLength() / 2,
                                              -cube_->getFacetSideLength() * j);
                mat.translate(currPos);
                shader->setUniformValue(0, mat);
                visitedCellMaterial->uploadToShader(shader);
                rect_->render(shader);
            }
        }
    }
    /*
    for(auto& matrix: matrices_)
    {
        shader->setUniformValue(0, matrix);


        // Expect other params all set
        cube_->getMaterial()->uploadToShader(shader);
        cube_->render(shader);
    }

    for(auto& pmatrix: pathMatrices_)
    {
        shader->setUniformValue(0, pmatrix);

        // Expect other params all set
        pathCube_->getMaterial()->uploadToShader(shader);
        pathCube_->render(shader);
    }

    for(auto& cmatrix: cellMatrices_)
    {
        shader->setUniformValue(0, cmatrix);

        // Expect other params all set
        rect_->getMaterial()->uploadToShader(shader);
        rect_->render(shader);
    }
    */
}

std::shared_ptr<Cube> Scene::getCube() const
{
    return cube_;
}

void Scene::setNumCubes(int newNum)
{
    numCubes_ = newNum;
    initScene();
}

void Scene::update(int row, int col)
{
    if (maze_[row][col].cellType != WALL && maze_[row][col].cellType != VISITED)
        maze_[row][col].cellType = VISITED;
}
