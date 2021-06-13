#include "arrow.h"

Arrow::Arrow(float width, float height) :
    RenderObject(),
    width_(width),
    height_(height)
{
    pMesh_ = MeshFactory::createArrowMesh(width_, height_);
}

Arrow::~Arrow()
{
    arrayBuf_.destroy();
    indexBuf_.destroy();
}
