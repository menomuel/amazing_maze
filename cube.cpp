#include "cube.h"

#include <QVector2D>
#include <QVector3D>
#include <QColor>
#include <QPolygonF>

#include <cstddef>

Cube::Cube(float sideLength, int nStrips, std::shared_ptr<Material> material) :
    RenderObject(),
    sideLength_(sideLength),
    nStrips_(nStrips),
    material_(material)
{
    pMesh_ = MeshFactory::createCubeMesh(sideLength, nStrips);
}

Cube::~Cube()
{
    arrayBuf_.destroy();
    indexBuf_.destroy();
}

float Cube::getFacetSideLength() const
{
    return sideLength_;
}

int Cube::getFacetStripsNum() const
{
    return nStrips_;
}


std::shared_ptr<Material> Cube::getMaterial() const
{
    return material_;
}



void Cube::setMaterial(std::shared_ptr<Material> newMaterial)
{
    material_ = newMaterial;
}
