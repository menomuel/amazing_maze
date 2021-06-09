#ifndef VERTEX_H
#define VERTEX_H

#include <QVector2D>
#include <QVector3D>
#include <QVector4D>

struct Vertex
{
    QVector3D position;
    inline static constexpr size_t positionTupleSize = sizeof(position) / sizeof(float);

    QVector3D normal;
    inline static constexpr size_t normalTupleSize = sizeof(normal) / sizeof(float);

    Vertex(QVector3D const& pos,
           QVector3D const& norm)
        : position(pos),
          normal(norm) {}
};


#endif // VERTEX_H
