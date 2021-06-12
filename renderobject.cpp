#include "renderobject.h"

RenderObject::RenderObject() : indexBuf_(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf_.create();
    indexBuf_.create();
}

RenderObject::~RenderObject()
{
    arrayBuf_.destroy();
    indexBuf_.destroy();
}

void RenderObject::render(QOpenGLShaderProgram *program)
{
    // Initialize VBOs
    arrayBuf_.bind();
    arrayBuf_.allocate(pMesh_->vertices.data(), pMesh_->vertices.size() * sizeof(Mesh::vertexType));

    indexBuf_.bind();
    indexBuf_.allocate(pMesh_->indices.data(), pMesh_->indices.size() * sizeof(Mesh::indexType));
    // Tell OpenGL which VBOs to use
    arrayBuf_.bind();
    indexBuf_.bind();

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int positionLocation = program->attributeLocation("position");
    program->enableAttributeArray(positionLocation);
    program->setAttributeBuffer(positionLocation, GL_FLOAT, offsetof(Mesh::vertexType, position),
                                Mesh::vertexType::positionTupleSize, sizeof(Mesh::vertexType));

    // Set corresponding normal
    int normalLocation = program->attributeLocation("normal");
    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer(normalLocation, GL_FLOAT, offsetof(Mesh::vertexType, normal),
                                Mesh::vertexType::normalTupleSize, sizeof(Mesh::vertexType));

    // Set texture coordinates
    int textureLocation = program->attributeLocation("texCoord");
    program->enableAttributeArray(textureLocation);
    program->setAttributeBuffer(textureLocation, GL_FLOAT, offsetof(Mesh::vertexType, texCoord),
                               Mesh::vertexType::textureTupleSize, sizeof(Mesh::vertexType));

    // Draw cube facets using indices
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(2, 1);
    glDrawElements(GL_TRIANGLES, indexBuf_.size() / sizeof(Mesh::indexType), GL_UNSIGNED_SHORT, nullptr);
}
