#ifndef SCENE_H
#define SCENE_H

#include "material.h"
#include "cube.h"
#include "rect.h"
#include "types.h"

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

    std::shared_ptr<Cube> pathCube_;

    std::vector<QMatrix4x4> matrices_;
    std::vector<QMatrix4x4> cellMatrices_;
    std::vector<QMatrix4x4> pathMatrices_;

    std::vector<std::vector<Cell>> maze_;
    std::list<Cell> path_;

    std::shared_ptr<Material> wallMaterial;
    std::shared_ptr<Material> freeCellMaterial;
    std::shared_ptr<Material> visitedCellMaterial;
    std::shared_ptr<Material> pathMaterial;


};

#endif // SCENE_H
