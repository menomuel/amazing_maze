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
    {
        for(int i = 0; i < nStrips + 1; ++i)
        {
            float s = static_cast<float>(1.f * i / nStrips);
            float t = static_cast<float>(1.f * j / nStrips);
            //pCube->vertices.emplace_back(QVector3D(-sideLength/2 + gridStep * i, -sideLength/2 + gridStep * j, sideLength/2), frontNormal);
            pCube->vertices.emplace_back(QVector3D(-sideLength/2 + gridStep * i, -sideLength/2 + gridStep * j, sideLength/2), frontNormal, QVector2D(s, t));

        }
    }

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
           pCube->vertices.emplace_back(rotation * pCube->vertices[i].position, normal, pCube->vertices[i].texCoord);

        for (size_t i = 0; i < indexCount; ++i)
           pCube->indices.push_back(pCube->indices[i] + offset);
    }

    //fill bottom facet
    rotation.setToIdentity();
    rotation.rotate(90.f, 1.f, 0.f, 0.f);
    normal = rotation * frontNormal;
    offset = pCube->vertices.size();

    for (size_t i = 0; i < vertexCount; ++i)
       pCube->vertices.emplace_back(rotation * pCube->vertices[i].position, normal, pCube->vertices[i].texCoord);

    for (size_t i = 0; i < indexCount; ++i)
       pCube->indices.push_back(pCube->indices[i] + offset);


    //fill upper facet
    rotation.setToIdentity();
    rotation.rotate(90.f, -1.f, 0.f, 0.f);
    normal = rotation * frontNormal;
    offset = pCube->vertices.size();

    for (size_t i = 0; i < vertexCount; ++i)
       pCube->vertices.emplace_back(rotation * pCube->vertices[i].position, normal, pCube->vertices[i].texCoord);

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
    {
        for(int i = 0; i < nStrips + 1; ++i)
        {
            float s = static_cast<float>(1.f * i / nStrips);
            float t = static_cast<float>(1.f * j / nStrips);
            pRect->vertices.emplace_back(QVector3D(-width/2 + gridStepW * i, 0, height/2 - gridStepH * j), frontNormal, QVector2D(s, t));
        }
    }
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
