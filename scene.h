#ifndef SCENE_H
#define SCENE_H

#include "cube.h"
#include "rect.h"
#include "types.h"
#include "texture.h"

#include <QMatrix4x4>
#include <vector>


class Scene {
public:
    Scene();

    void init(int size = 5, unsigned int seed = 0);
    void reload();
    void drawScene(QOpenGLShaderProgram* shader) const;
    void update(int row, int col);

    std::shared_ptr<Cube> getCube() const;
    Cell getStart() const;
    Cell getFinish() const;
    const std::vector<std::vector<Cell>>& getData() const;

    void setShowPathFlag(bool state);
    void setPath(const std::list<Cell>& newPath);

private:
    std::shared_ptr<Cube> cube_;
    std::shared_ptr<Rect> rect_;

    std::vector<std::vector<Cell>> maze_;
    Cell start, finish;
    std::list<Cell> path_;

    bool showPathFlag = false;

    std::shared_ptr<QOpenGLTexture> wallTex;
    std::shared_ptr<QOpenGLTexture> freeCellTex;
    std::shared_ptr<QOpenGLTexture> visitedCellTex;
    std::shared_ptr<QOpenGLTexture> pathTex;
    std::shared_ptr<QOpenGLTexture> finishTex;


};

#endif // SCENE_H
