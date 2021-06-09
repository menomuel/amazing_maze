#ifndef PROJECTORLIGHTSOURCE_H
#define PROJECTORLIGHTSOURCE_H

#include "lightsource.h"


class ProjectorLightSource : public LightSource {

public:
    ProjectorLightSource(QVector3D position = QVector3D(0.f, 0.f, 0.f),
                         QVector3D direction = QVector3D(0.f, 0.f, 0.f),
                         float constant = 1.f,
                         float linear = 0.045f,
                         float quadratic = 0.0075f,
                         float cutOff = 12.5f,
                         float outerCutOff = 15.0f);

    void uploadToShader(QOpenGLShaderProgram* shader) const override;

    void setPosition(const QVector3D& newPos);
    void setDirection(const QVector3D& newDir);
    void setCutOff(float newCutOff);
    void setOuterCutOff(float newOuterCutOff);


private:
    QVector3D position_;
    QVector3D direction_;

    float constant_;
    float linear_;
    float quadratic_;

    float cutOff_;
    float outerCutOff_;
};

#endif // PROJECTORLIGHTSOURCE_H
