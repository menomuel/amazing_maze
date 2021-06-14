#ifndef CUBE_H
#define CUBE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QColor>

#include "meshfactory.h"
#include "renderobject.h"

class Cube : public RenderObject
{
public:
    Cube(float sideLength = 2.f, int nStrips = 1);
    virtual ~Cube();

    float getFacetSideLength() const;
    int getFacetStripsNum() const;

protected:
    float sideLength_;
    int nStrips_;
};



#endif // CUBE_H
