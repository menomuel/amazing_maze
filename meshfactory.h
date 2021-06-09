#ifndef MESHFACTORY_H
#define MESHFACTORY_H

#include "mesh.h"

#include <memory>

class MeshFactory
{
public:
    static std::shared_ptr<Mesh> createCubeMesh(float sideLength = 2.f, int nStrips = 10);
    static std::shared_ptr<Mesh> createRectMesh(float width = 2.f, float height = 2.f, int nStrips = 1);
    static std::shared_ptr<Mesh> createSphereMesh(float radius = 1.f, float stackCount = 10, float sectorCount = 10);
};

#endif // MESHFACTORY_H
