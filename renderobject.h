#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "mesh.h"

#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

#include <memory>

class RenderObject : protected QOpenGLFunctions
{
public:
    RenderObject();
    virtual ~RenderObject();

    void render(QOpenGLShaderProgram* program);

protected:
    std::shared_ptr<Mesh> pMesh_;

    QOpenGLBuffer arrayBuf_;
    QOpenGLBuffer indexBuf_;
};

#endif // RENDEROBJECT_H
