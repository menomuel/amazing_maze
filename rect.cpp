#include "rect.h"

Rect::Rect(float width, float height, int nStrips) :
    RenderObject(),
    width_(width),
    height_(height),
    nStrips_(nStrips)
{
    pMesh_ = MeshFactory::createRectMesh(width, height, nStrips);
}

Rect::~Rect()
{
    arrayBuf_.destroy();
    indexBuf_.destroy();
}
