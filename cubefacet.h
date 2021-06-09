#ifndef CUBEFACET_H
#define CUBEFACET_H

#include <QVector3D>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>

#include <memory>

class CubeFacet
{
public:
    CubeFacet() = default;

    explicit CubeFacet(float sideLength, int nStrips) :
        sideLength_(sideLength),
        nStrips_(nStrips),
        nVertices_((nStrips+1)*(nStrips+1)),
        nIndices_(0) {}

    explicit CubeFacet(float sideLength, int nStrips, int nVertices, int nIndices, std::shared_ptr<QVector3D> vertices, std::shared_ptr<GLushort> indices) :
        sideLength_(sideLength),
        nStrips_(nStrips),
        nVertices_(nVertices),
        nIndices_(nIndices),
        vertices_(vertices),
        indices_(indices) {}

    void init();

    float getSideLength() const;
    int getVerticesNum() const;
    int getIndicesNum() const;
    int getStripsNum() const;

    CubeFacet rotate(float angle, QVector3D vector);



private:
    void fillVertices();
    void fillIndices();


    float sideLength_;
    int nStrips_;
    int nVertices_, nIndices_;

public:

    std::shared_ptr<QVector3D> vertices_;
    std::shared_ptr<GLushort> indices_;
};

#endif // CUBEFACET_H
