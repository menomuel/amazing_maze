#include "rect.h"

Rect::Rect(float width, float height, int nStrips, std::shared_ptr<Material> material) :
    RenderObject(),
    width_(width),
    height_(height),
    nStrips_(nStrips),
    material_(material)
{
    pMesh_ = MeshFactory::createRectMesh(width, height, nStrips);
}

Rect::~Rect()
{
    arrayBuf_.destroy();
    indexBuf_.destroy();
}

std::shared_ptr<Material> Rect::getMaterial() const
{
    return material_;
}

void Rect::setMaterial(std::shared_ptr<Material> newMaterial)
{
    material_ = newMaterial;
}
