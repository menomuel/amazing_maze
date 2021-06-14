#ifndef RECT_H
#define RECT_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QColor>

#include "meshfactory.h"
#include "renderobject.h"

class Rect : public RenderObject
{
public:
    Rect(float width = 2.f, float height = 2.f, int nStrips = 1);
    virtual ~Rect();

protected:
    float width_, height_;
    int nStrips_;
};


#endif // RECT_H
