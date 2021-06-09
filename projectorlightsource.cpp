#include "projectorlightsource.h"
#include <QtMath>

ProjectorLightSource::ProjectorLightSource(QVector3D position,
                                           QVector3D direction,
                                           float constant,
                                           float linear,
                                           float quadratic,
                                           float cutOff,
                                           float outerCutOff) :
    position_(std::move(position)),
    direction_(std::move(direction)),
    constant_(constant),
    linear_(linear),
    quadratic_(quadratic),
    cutOff_(cutOff),
    outerCutOff_(outerCutOff)
{
}

void ProjectorLightSource::uploadToShader(QOpenGLShaderProgram* shader) const
{
    shader->bind();

    shader->setUniformValue("projectorLightFlag", state_);

    shader->setUniformValue("projectorLight.position", position_);
    shader->setUniformValue("projectorLight.direction", direction_);

    shader->setUniformValue("projectorLight.constant", constant_);
    shader->setUniformValue("projectorLight.linear", linear_);
    shader->setUniformValue("projectorLight.quadratic", quadratic_);

    shader->setUniformValue("projectorLight.cutOff", qDegreesToRadians(cutOff_));
    shader->setUniformValue("projectorLight.outerCutOff", qDegreesToRadians(outerCutOff_));

    shader->setUniformValue("projectorLight.ambient", color_);
    shader->setUniformValue("projectorLight.diffuse", color_);
    shader->setUniformValue("projectorLight.specular", color_);

    shader->setUniformValue("projectorLight.intensity", intensity_);
}

void ProjectorLightSource::setPosition(const QVector3D &newPos)
{
    position_ = newPos;
}

void ProjectorLightSource::setDirection(const QVector3D &newDir)
{
    direction_ = newDir;
}

void ProjectorLightSource::setCutOff(float newCutOff)
{
    if(newCutOff < outerCutOff_)
        cutOff_ = newCutOff;
}

void ProjectorLightSource::setOuterCutOff(float newOuterCutOff)
{
    if (newOuterCutOff > cutOff_)
        outerCutOff_ = newOuterCutOff;
}




