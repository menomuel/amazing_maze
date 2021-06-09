#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <QVector3D>
#include <QOpenGLShaderProgram>

#include <utility>
#include <memory>

class LightSource {

public:
    LightSource(QVector3D ambient  = defaultColor,
                QVector3D diffuse  = defaultColor,
                QVector3D specular = defaultColor) :
        ambient_(std::move(ambient)),
        diffuse_(std::move(diffuse)),
        specular_(std::move(specular)) {}

    virtual void uploadToShader(QOpenGLShaderProgram* shader) const = 0;

    void setColor(QVector3D ambient,
                  QVector3D diffuse,
                  QVector3D specular);

    void switchState(bool state);
    bool getState() const;
    QVector3D getColor() const;
    float getIntensity() const;

    void setColor(const QVector3D& color);
    void setIntensity(float intensity);

protected:
    QVector3D ambient_;
    QVector3D diffuse_;
    QVector3D specular_;

    QVector3D color_ = defaultColor;
    float intensity_ = 1.f;

    bool state_ = false;

    static const QVector3D defaultColor;
};

#endif // LIGHTSOURCE_H
