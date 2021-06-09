#include "meshfactory.h"
#include <QMatrix4x4>

#include <cmath>

std::shared_ptr<Mesh> MeshFactory::createCubeMesh(float sideLength, int nStrips)
{
    auto pCube = std::make_shared<Mesh>();

    pCube->vertices.reserve(6 * (nStrips + 1) * (nStrips + 1));
    pCube->indices.reserve(6 * 6 * nStrips * nStrips);

    float gridStep = sideLength / nStrips;
    QVector3D frontNormal = {0.f, 0.f, 1.f};

    // fill front facet with vertices
    for(int j = 0; j < nStrips + 1; ++j)
        for(int i = 0; i < nStrips + 1; ++i)
            pCube->vertices.emplace_back(QVector3D(-sideLength/2 + gridStep * i, -sideLength/2 + gridStep * j, sideLength/2), frontNormal);

    // fill front facet indices
    for (GLushort j = 0; j < nStrips; ++j)
    {
        //Set idx to point at first vertex of row j
        GLushort idx = j * (nStrips + 1);

        for (GLushort i = 0; i < nStrips; ++i)
        {
            //Bottom triangle of the quad
            pCube->indices.push_back(idx);
            pCube->indices.push_back(idx+1);
            pCube->indices.push_back(idx+(nStrips+1));
            //Top triangle of the quad
            pCube->indices.push_back(idx+1);
            pCube->indices.push_back(idx+(nStrips+1)+1);
            pCube->indices.push_back(idx+(nStrips+1));
            //Move one vertex to the right
            ++idx;
        }
    }

    auto vertexCount = pCube->vertices.size();
    auto indexCount = pCube->indices.size();
    size_t offset = 0;

    QMatrix4x4 rotation;
    QVector3D normal;


    //fill right, back & left facets
    for(int t = 0; t < 3; ++t)
    {
        rotation.rotate(90.f, 0.f, 1.f, 0.f);
        normal = rotation * frontNormal;
        offset = pCube->vertices.size();

        for (size_t i = 0; i < vertexCount; ++i)
           pCube->vertices.emplace_back(rotation * pCube->vertices[i].position, normal);

        for (size_t i = 0; i < indexCount; ++i)
           pCube->indices.push_back(pCube->indices[i] + offset);
    }

    //fill bottom facet
    rotation.setToIdentity();
    rotation.rotate(90.f, 1.f, 0.f, 0.f);
    normal = rotation * frontNormal;
    offset = pCube->vertices.size();

    for (size_t i = 0; i < vertexCount; ++i)
       pCube->vertices.emplace_back(rotation * pCube->vertices[i].position, normal);

    for (size_t i = 0; i < indexCount; ++i)
       pCube->indices.push_back(pCube->indices[i] + offset);


    //fill upper facet
    rotation.setToIdentity();
    rotation.rotate(90.f, -1.f, 0.f, 0.f);
    normal = rotation * frontNormal;
    offset = pCube->vertices.size();

    for (size_t i = 0; i < vertexCount; ++i)
       pCube->vertices.emplace_back(rotation * pCube->vertices[i].position, normal);

    for (size_t i = 0; i < indexCount; ++i)
       pCube->indices.push_back(pCube->indices[i] + offset);

    return pCube;
}

std::shared_ptr<Mesh> MeshFactory::createRectMesh(float width, float height, int nStrips)
{
    auto pRect = std::make_shared<Mesh>();

    pRect->vertices.reserve((nStrips + 1) * (nStrips + 1));
    pRect->indices.reserve(6 * nStrips * nStrips);

    float gridStepW = width / nStrips;
    float gridStepH = height / nStrips;
    QVector3D frontNormal = {0.f, 1.f, 0.f};

    // fill front facet with vertices
    for(int j = 0; j < nStrips + 1; ++j)
        for(int i = 0; i < nStrips + 1; ++i)
            pRect->vertices.emplace_back(QVector3D(-width/2 + gridStepW * i, 0, height/2 - gridStepH * j), frontNormal);

    // fill front facet indices
    for (GLushort j = 0; j < nStrips; ++j)
    {
        //Set idx to point at first vertex of row j
        GLushort idx = j * (nStrips + 1);

        for (GLushort i = 0; i < nStrips; ++i)
        {
            //Bottom triangle of the quad
            pRect->indices.push_back(idx);
            pRect->indices.push_back(idx+1);
            pRect->indices.push_back(idx+(nStrips+1));
            //Top triangle of the quad
            pRect->indices.push_back(idx+1);
            pRect->indices.push_back(idx+(nStrips+1)+1);
            pRect->indices.push_back(idx+(nStrips+1));
            //Move one vertex to the right
            ++idx;
        }
    }

    return pRect;
}

std::shared_ptr<Mesh> MeshFactory::createSphereMesh(float radius, float stackCount, float sectorCount)
{
    auto pSphere = std::make_shared<Mesh>();

    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
    //float s, t;

    float sectorStep = 2 * M_PI / sectorCount;
    float stackStep = M_PI / stackCount;
    float sectorAngle, stackAngle;

    for(int i = 0; i <= stackCount; ++i)
    {
        stackAngle = M_PI / 2 - i * stackStep;        // from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for(int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position (x, y, z)
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)

            // normalized vertex normal (nx, ny, nz)
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;

            // vertex tex coord (s, t) range between [0, 1]
           // s = static_cast<float>(j / sectorCount);
            //t = static_cast<float>(i / stackCount);

            pSphere->vertices.emplace_back(QVector3D(x, y, z), QVector3D(nx, ny, nz));
        }
    }

    int k1, k2;
    for(int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for(int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if(i != 0)
            {
                pSphere->indices.push_back(k1);
                pSphere->indices.push_back(k2);
                pSphere->indices.push_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if(i != (stackCount-1))
            {
                pSphere->indices.push_back(k1 + 1);
                pSphere->indices.push_back(k2);
                pSphere->indices.push_back(k2 + 1);
            }
        }
    }

    return pSphere;
}
