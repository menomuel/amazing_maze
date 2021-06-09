#ifndef CUBE_H
#define CUBE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QColor>

#include "material.h"

#include "meshfactory.h"
#include "renderobject.h"

class Cube : public RenderObject
{
public:
    Cube(float sideLength = 2.f, int nStrips = 1, std::shared_ptr<Material> material = MaterialFactory::createJade());
    virtual ~Cube();

    float getFacetSideLength() const;
    int getFacetStripsNum() const;
    std::shared_ptr<Material> getMaterial() const;

    void setMaterial(std::shared_ptr<Material> newMaterial);

protected:
    float sideLength_;
    int nStrips_;

    std::shared_ptr<Material> material_;
};



#endif // CUBE_H
