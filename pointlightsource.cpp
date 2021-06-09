#include "pointlightsource.h"


PointLightSource::PointLightSource(QVector3D position,
                                   float constant,
                                   float linear,
                                   float quadratic) :
    LightSource(),
    position_(std::move(position)),
    constant_(constant),
    linear_(linear),
    quadratic_(quadratic) {}

void PointLightSource::uploadToShader(QOpenGLShaderProgram* shader) const
{
    shader->bind();

    shader->setUniformValue("pointLightFlag", state_);

    shader->setUniformValue("pointLight.position", position_);

    shader->setUniformValue("pointLight.constant", constant_);
    shader->setUniformValue("pointLight.linear", linear_);
    shader->setUniformValue("pointLight.quadratic", quadratic_);

    shader->setUniformValue("pointLight.ambient", color_);
    shader->setUniformValue("pointLight.diffuse", color_);
    shader->setUniformValue("pointLight.specular", color_);

    shader->setUniformValue("pointLight.intensity", intensity_);
}

QVector3D PointLightSource::getPosition() const
{
    return position_;
}

void PointLightSource::setPosition(const QVector3D &newPos)
{
    position_ = newPos;
}
