#ifndef POINTLIGHTSOURCE_H
#define POINTLIGHTSOURCE_H

#include "lightsource.h"

class PointLightSource : public LightSource {

public:
    PointLightSource(QVector3D position = QVector3D(0.f, 0.f, 0.f),
                     float constant = 1.f,
                     float linear = 0.045f,
                     float quadratic = 0.0075f);

    void uploadToShader(QOpenGLShaderProgram* shader) const override;

    QVector3D getPosition() const;
    void setPosition(const QVector3D& newPos);

private:
    QVector3D position_;

    float constant_;
    float linear_;
    float quadratic_;

};

#endif // POINTLIGHTSOURCE_H
