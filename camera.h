#pragma once

#include <QVector3D>
#include <QMatrix4x4>
#include <cmath>

class Camera
{
public:
    static constexpr bool constrainPitch = true;

    enum directions{
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN,
    };

    Camera(
            QVector3D const& pos = {},
            QVector3D const& front = {0.f, 0.f, -1.f},
            QVector3D const& up = {0.f, 1.f, 0.f}
            );

    const QMatrix4x4& getViewMatrix();
    const QMatrix4x4& getProjectionMatrix();

    void setFOV(float fov);
    void setAspectRatio(float ratio);
    void setZNear(float zNear);
    void setZFar(float zFar);
    void setProjection(float fov, float aspectRatio, float zNear, float zFar);

    void move(QVector3D const& offset);
    void move(directions direction, float length);
    void rotate(float xoffset, float yoffset);

    void setCameraPos(const QVector3D& pos);
    void setCameraFront(const QVector3D& front);
    QVector3D getCameraPos() const;
    QVector3D getCameraFront() const;

private:
    void updateVectors();

private:
    QMatrix4x4 view_{};
    QMatrix4x4 projection_{};

    QVector3D cameraPos_, cameraFront_, cameraUp_;
    QVector3D cameraRight_;
    QVector3D up_;

    // field of view
    float fov_, aspectRatio_, zNear_, zFar_;

    float yaw_ =  - M_PI / 2;
    float pitch_ = 0.f;

    // +/- 89grad
    float pitchLB = -M_PI / 2.2f;
    float pitchUB = M_PI / 2.2f;
};

