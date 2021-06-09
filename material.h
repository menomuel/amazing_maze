#ifndef MATERIAL_H
#define MATERIAL_H

#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <memory>

struct Material
{
    QVector3D ambient;
    QVector3D diffuse;
    QVector3D specular;
    float shininess;

    void uploadToShader(QOpenGLShaderProgram* shader) const;
};

class MaterialFactory {

public:
    static std::shared_ptr<Material> createWhite();
    static std::shared_ptr<Material> createJade();
    static std::shared_ptr<Material> createRedRubber();
    static std::shared_ptr<Material> createGold();
    static std::shared_ptr<Material> createYellowRubber();
};

#endif // MATERIAL_H
