#ifndef SCENE_H
#define SCENE_H

#include "material.h"
#include "cube.h"
#include "rect.h"
#include "types.h"
#include "texture.h"

#include <QMatrix4x4>
#include <vector>


class Scene {
public:
    Scene(int numCubes = 1);

    void initScene();
    void drawScene(QOpenGLShaderProgram* shader) const;

    std::shared_ptr<Cube> getCube() const;

    void setNumCubes(int newNum);

    void update(int row, int col);

    const std::vector<std::vector<Cell>>& getData() const
    {
        return maze_;
    };

private:
    int numCubes_;
    std::shared_ptr<Cube> cube_;
    std::shared_ptr<Rect> rect_;

    std::vector<std::vector<Cell>> maze_;
    Cell start, finish;
    std::list<Cell> path_;

    std::shared_ptr<QOpenGLTexture> wallTex;
    std::shared_ptr<QOpenGLTexture> freeCellTex;
    std::shared_ptr<QOpenGLTexture> visitedCellTex;
    std::shared_ptr<QOpenGLTexture> pathTex;
    std::shared_ptr<QOpenGLTexture> finishTex;


};

#endif // SCENE_H
