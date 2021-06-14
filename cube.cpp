#include "cube.h"

#include <QVector2D>
#include <QVector3D>
#include <QColor>
#include <QPolygonF>

#include <cstddef>

Cube::Cube(float sideLength, int nStrips) :
    RenderObject(),
    sideLength_(sideLength),
    nStrips_(nStrips)
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
