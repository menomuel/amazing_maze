#ifndef ARROW_H
#define ARROW_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QColor>

#include "meshfactory.h"
#include "renderobject.h"

class Arrow : public RenderObject
{
public:
    Arrow(float width = 0.5f, float height = 0.5f);
    virtual ~Arrow();

protected:
    float width_, height_;
};

#endif // ARROW_H
