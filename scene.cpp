#include "scene.h"

#include <QUrl>

#include "maze_generator.h"
#include "pathfinder.h"

Scene::Scene(int numCubes) : numCubes_(numCubes), cube_(std::make_shared<Cube>()), rect_(std::make_shared<Rect>())
{
    wallTex = Texture::loadTexture(R"(:/textures/brick.jpeg)");
    freeCellTex = Texture::loadTexture(R"(:/textures/ground.jpg)");
    visitedCellTex = Texture::loadTexture(R"(:/textures/grass.jpg)");
    pathTex = Texture::loadTexture(R"(:/textures/flowerbeds.jpg)");
    finishTex = Texture::loadTexture(R"(:/textures/finish.jpg)");
}

void Scene::init(int size, unsigned int seed)
{
    maze_ = MazeGenerator::generate(size, size, seed);
    start = maze_[1][1];
    finish = maze_[static_cast<int>(maze_.size()) - 2][static_cast<int>(maze_[0].size()) - 2];
    path_ = PathFinder::findPath(maze_, start.row, start.col, finish.row, finish.col);
}

void Scene::reload()
{
    for (int i = 0; i < static_cast<int>(maze_.size()); ++i)
    {
        for (int j = 0; j < static_cast<int>(maze_[0].size()); ++j)
        {
            if(maze_[i][j].cellType != WALL)
                maze_[i][j].cellType = CELL;
        }
    }
}


void Scene::drawScene(QOpenGLShaderProgram *shader) const
{
    shader->setUniformValue("textMap",0);
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
                wallTex->bind();
                cube_->render(shader);
            } else
            {
                QVector3D currPos = QVector3D(cube_->getFacetSideLength() * i,
                                              -cube_->getFacetSideLength() / 2,
                                              -cube_->getFacetSideLength() * j);
                mat.translate(currPos);
                shader->setUniformValue(0, mat);
                if(maze_[i][j] == finish)
                {
                    finishTex->bind();
                } else if(showPathFlag && (std::find(path_.begin(), path_.end(), maze_[i][j]) != path_.end()))
                {
                    pathTex->bind();
                } else if (maze_[i][j].cellType == CELL)
                {
                    freeCellTex->bind();
                } else if (maze_[i][j].cellType == VISITED)
                {
                    visitedCellTex->bind();
                }
                rect_->render(shader);
            }
        }
    }
}

std::shared_ptr<Cube> Scene::getCube() const
{
    return cube_;
}

Cell Scene::getStart() const
{
    return start;
}

Cell Scene::getFinish() const
{
    return finish;
}

void Scene::setNumCubes(int newNum)
{
    numCubes_ = newNum;
    init();
}

void Scene::update(int row, int col)
{
    if (maze_[row][col].cellType != WALL && maze_[row][col].cellType != VISITED)
        maze_[row][col].cellType = VISITED;
}

void Scene::setShowPathFlag(bool state)
{
    showPathFlag = state;
}

void Scene::setPath(const std::list<Cell> &newPath)
{
    path_ = newPath;
}

const std::vector<std::vector<Cell> > &Scene::getData() const
{
    return maze_;
}
