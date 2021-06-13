#ifndef ARROW_H
#define ARROW_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QColor>

#include "material.h"

#include "meshfactory.h"
#include "renderobject.h"

class Arrow : public RenderObject
{
public:
    Arrow(float width = 1.f, float height = 1.f);
    virtual ~Arrow();

protected:
    float width_, height_;
};

#endif // ARROW_H