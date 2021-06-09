#include "material.h"


std::shared_ptr<Material> MaterialFactory::createWhite()
{
    return std::make_shared<Material>(Material{QVector3D(1.f,   1.f,   1.f),
                                               QVector3D(1.f,   1.f,   1.f),
                                               QVector3D(1.f,   1.f,   1.f),
                                               1.0f * 128});
}

std::shared_ptr<Material> MaterialFactory::createJade()
{
    return std::make_shared<Material>(Material{QVector3D(   0.135f,   0.2225f,   0.1575f),
                                               QVector3D(    0.54f,     0.89f,     0.63f),
                                               QVector3D(0.316228f, 0.316228f, 0.316228f),
                                               0.1f * 128});
}

std::shared_ptr<Material> MaterialFactory::createRedRubber()
{
    return std::make_shared<Material>(Material{QVector3D(0.05f,  0.0f,  0.0f),
                                               QVector3D( 0.5f,  0.4f,  0.4f),
                                               QVector3D( 0.7f, 0.04f, 0.04f),
                                               0.078125f * 128});
}

std::shared_ptr<Material> MaterialFactory::createGold()
{
    return std::make_shared<Material>(Material{QVector3D( 0.24725f,   0.1995f,   0.0745f),
                                               QVector3D( 0.75164f,  0.60648f,  0.22648f),
                                               QVector3D(0.628281f, 0.555802f, 0.366065f),
                                               0.4f * 128});
}

std::shared_ptr<Material> MaterialFactory::createYellowRubber()
{
    return std::make_shared<Material>(Material{QVector3D(0.05f, 0.05f,  0.0f),
                                               QVector3D( 0.5f,  0.5f,  0.4f),
                                               QVector3D( 0.7f,  0.7f, 0.04f),
                                               0.078125f * 128});
}

void Material::uploadToShader(QOpenGLShaderProgram* shader) const
{
    shader->bind();

    shader->setUniformValue("material.ambient",  ambient);
    shader->setUniformValue("material.diffuse",  diffuse);
    shader->setUniformValue("material.specular", specular);
    shader->setUniformValue("material.shininess", shininess);

}
