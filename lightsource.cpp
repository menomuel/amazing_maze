#include "lightsource.h"

const QVector3D LightSource::defaultColor = {1.f, 1.f, 1.f};

void LightSource::setColor(QVector3D ambient, QVector3D diffuse, QVector3D specular)
{
    ambient_ = ambient;
    diffuse_ = diffuse;
    specular_= specular;
}

void LightSource::switchState(bool state)
{
    state_ = state;
}

bool LightSource::getState() const
{
    return state_;
}

QVector3D LightSource::getColor() const
{
    return color_;
}

float LightSource::getIntensity() const
{
    return intensity_;
}

void LightSource::setColor(const QVector3D &color)
{
    color_ = color;
}

void LightSource::setIntensity(float intensity)
{
    intensity_ = intensity;
}
