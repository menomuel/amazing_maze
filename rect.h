#ifndef RECT_H
#define RECT_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QColor>

#include "material.h"

#include "meshfactory.h"
#include "renderobject.h"

class Rect : public RenderObject
{
public:
    Rect(float width = 2.f, float height = 2.f, int nStrips = 1, std::shared_ptr<Material> material = MaterialFactory::createRedRubber());
    virtual ~Rect();

    std::shared_ptr<Material> getMaterial() const;

    void setMaterial(std::shared_ptr<Material> newMaterial);

protected:
    float width_, height_;
    int nStrips_;

    std::shared_ptr<Material> material_;
};


#endif // RECT_H
