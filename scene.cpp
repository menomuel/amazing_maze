#include "scene.h"

#include "maze_generator.h"
#include "pathfinder.h"

Scene::Scene(int numCubes) : numCubes_(numCubes), cube_(std::make_shared<Cube>()), rect_(std::make_shared<Rect>())
{
    wallTex = Texture::loadTexture(R"(D:\NSU\6 semester\Graphics\amazing_maze\brick.jpeg)");
    freeCellTex = Texture::loadTexture(R"(D:\NSU\6 semester\Graphics\amazing_maze\ground.jpg)");
    visitedCellTex = Texture::loadTexture(R"(D:\NSU\6 semester\Graphics\amazing_maze\grass.jpg)");
    pathTex = Texture::loadTexture(R"(D:\NSU\6 semester\Graphics\amazing_maze\flowerbeds.jpg)");
    finishTex = Texture::loadTexture(R"(D:\NSU\6 semester\Graphics\amazing_maze\finish.jpg)");
}

void Scene::initScene()
{
    maze_ = MazeGenerator::generate(5, 5);
    start = maze_[1][1];
    finish = maze_[static_cast<int>(maze_.size()) - 2][static_cast<int>(maze_[0].size()) - 2];
    path_ = PathFinder::findPath(maze_, start.row, start.col, finish.row, finish.col);
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
                } else if(std::find(path_.begin(), path_.end(), maze_[i][j]) != path_.end())
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
