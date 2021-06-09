#ifndef DIRECTLIGHTSOURCE_H
#define DIRECTLIGHTSOURCE_H

#include "lightsource.h"

class DirectLightSource : public LightSource {

public:
    DirectLightSource(QVector3D direction = QVector3D(-1.f, -1.f, -1.f));

    void uploadToShader(QOpenGLShaderProgram* shader) const override;

    QVector3D getDirection() const;
    void setDirection(const QVector3D& newDir);

private:
    QVector3D direction_;
};

#endif // DIRECTLIGHTSOURCE_H
