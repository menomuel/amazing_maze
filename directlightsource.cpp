# include "directlightsource.h"


DirectLightSource::DirectLightSource(QVector3D direction) :
    LightSource(),
    direction_(std::move(direction)) {}

void DirectLightSource::uploadToShader(QOpenGLShaderProgram* shader) const
{
    shader->bind();

    shader->setUniformValue("directLightFlag", state_);

    shader->setUniformValue("directLight.direction", direction_);

    shader->setUniformValue("directLight.ambient", color_);
    shader->setUniformValue("directLight.diffuse", color_);
    shader->setUniformValue("directLight.specular", color_);

    shader->setUniformValue("directLight.intensity", intensity_);
}

QVector3D DirectLightSource::getDirection() const
{
    return direction_;
}

void DirectLightSource::setDirection(const QVector3D &newDir)
{
    direction_ = newDir;
}
