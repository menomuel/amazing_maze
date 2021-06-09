#include <QMatrix4x4>

#include "cubefacet.h"

void CubeFacet::fillVertices()
{
    vertices_ = std::shared_ptr<QVector3D>(new QVector3D[nVertices_]);
    float gridStep = sideLength_ / nStrips_;

    for(int j = 0; j < nStrips_ + 1; ++j)
    {
        for(int i = 0; i < nStrips_ + 1; ++i)
        {
            // fill facet with vertices
            vertices_.get()[j * (nStrips_ + 1) + i] = {-sideLength_/2 + gridStep * i, -sideLength_/2 + gridStep * j, sideLength_/2};
        }
    }
}

void CubeFacet::fillIndices()
{
    std::vector<GLushort> indices;

    for (GLushort j = 0; j < nStrips_; ++j)
    {
        //Set idx to point at first vertex of row j
        GLushort idx = j * (nStrips_ + 1);

        for (GLushort i = 0; i < nStrips_; ++i)
        {
            //Bottom triangle of the quad
            indices.push_back(idx);
            indices.push_back(idx+1);
            indices.push_back(idx+(nStrips_+1));
            //Top triangle of the quad
            indices.push_back(idx+1);
            indices.push_back(idx+(nStrips_+1)+1);
            indices.push_back(idx+(nStrips_+1));
            //Move one vertex to the right
            ++idx;
        }
    }

    nIndices_ = indices.size();
    indices_ = std::shared_ptr<GLushort>(new GLushort[nIndices_]);
    for(int i = 0; i < nIndices_; ++i)
    {
        indices_.get()[i] = indices[i];
    }
}

void CubeFacet::init()
{
    fillVertices();
    fillIndices();
}

float CubeFacet::getSideLength() const
{
    return sideLength_;
}

int CubeFacet::getVerticesNum() const
{
    return nVertices_;
}

int CubeFacet::getIndicesNum() const
{
    return nIndices_;
}

int CubeFacet::getStripsNum() const
{
    return nStrips_;
}

CubeFacet CubeFacet::rotate(float angle, QVector3D vector)
{
    QMatrix4x4 mat;
    mat.rotate(angle, vector);

    auto rotVertices = std::shared_ptr<QVector3D>(new QVector3D[nVertices_]);

    for(int i = 0; i < nVertices_; ++i)
        rotVertices.get()[i] = mat * vertices_.get()[i];

    return CubeFacet(sideLength_, nStrips_, nVertices_, nIndices_, rotVertices, indices_);
}
