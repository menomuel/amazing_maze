#ifndef MESH_H
#define MESH_H

#include "vertex.h"

#include <vector>
#include <QOpenGLFunctions>

struct Mesh
{
    using vertexType = Vertex;
    using indexType = GLushort;
    inline static constexpr GLenum IndexTypeVal = GL_UNSIGNED_SHORT;

    std::vector<vertexType> vertices{};
    std::vector<indexType> indices{};

    Mesh() = default;
    Mesh(std::vector<vertexType> _vertices, std::vector<indexType> _indices) :
        vertices(std::move(_vertices)),
        indices(std::move(_indices))
    {}
};

#endif // MESH_H
