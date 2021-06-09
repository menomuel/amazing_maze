#include "camera.h"
#include <cmath>
#include <algorithm>

void Camera::updateVectors()
{
    cameraFront_.setX(std::cos(yaw_) * std::cos(pitch_));
    cameraFront_.setY(-std::sin(pitch_));
    cameraFront_.setZ(std::sin(yaw_) * std::cos(pitch_));
    cameraFront_.normalize();

    // order?
    cameraRight_ = QVector3D::crossProduct(cameraFront_, up_).normalized();
    cameraUp_ = QVector3D::crossProduct(cameraRight_, cameraFront_).normalized();
}

Camera::Camera(
        const QVector3D& pos,
        const QVector3D& front,
        const QVector3D& up
        )
    : cameraPos_(pos),
      cameraFront_(front),
      up_(up)
{
    updateVectors();
}


QMatrix4x4 const& Camera::getViewMatrix()
{
    view_.setToIdentity();
    view_.lookAt(cameraPos_, cameraPos_ + cameraFront_, cameraUp_);
    return view_;
}

const QMatrix4x4& Camera::getProjectionMatrix()
{
    projection_.setToIdentity();
    projection_.perspective(fov_, aspectRatio_, zNear_, zFar_);
    return projection_;
}

void Camera::setProjection(float fov, float aspectRatio, float zNear, float zFar)
{
    setFOV(fov);
    setAspectRatio(aspectRatio);
    setZNear(zNear);
    setZFar(zFar);
}

void Camera::setFOV(float fov)
{
    fov_ = fov;
}

void Camera::setAspectRatio(float ratio)
{
    aspectRatio_ = ratio;
}

void Camera::setZNear(float zNear)
{
    zNear_ = zNear;
}

void Camera::setZFar(float zFar)
{
    zFar_ = zFar;
}

void Camera::move(const QVector3D& offset)
{
    cameraPos_ += cameraFront_ * QVector3D::dotProduct(offset, cameraFront_);
    cameraPos_ += cameraUp_ * QVector3D::dotProduct(offset, cameraUp_);
    cameraPos_ += cameraRight_ * QVector3D::dotProduct(offset, cameraRight_);
}

void Camera::move(Camera::directions direction, float cameraSpeed)
{
    switch (direction)
    {
        case directions::FORWARD :
            cameraPos_ += cameraSpeed * cameraFront_;
            break;
        case directions::BACKWARD:
            cameraPos_ -=  cameraSpeed * cameraFront_;
            break;
        case directions::RIGHT:
            cameraPos_ += cameraSpeed * cameraRight_;
            break;
        case directions::LEFT:
            cameraPos_ -= cameraSpeed * cameraRight_;
            break;
        case directions::UP:
            cameraPos_ += cameraSpeed * cameraUp_;
            break;
        case directions::DOWN:
            cameraPos_ -= cameraSpeed * cameraUp_;
            break;
        default:
            break;
    }
}

void Camera::rotate(float xoffset, float yoffset)
{
    yaw_ += xoffset;
    pitch_ += yoffset;

    if (constrainPitch)
    {
        pitch_ = std::clamp(pitch_, -static_cast<float>(M_PI) / 2.2f, static_cast<float>(M_PI) / 2.2f);
    }

    updateVectors();
}

void Camera::setCameraPos(const QVector3D &pos)
{
    cameraPos_ = pos;
}

void Camera::setCameraFront(const QVector3D &front)
{
    cameraFront_ = front;
}


QVector3D Camera::getCameraPos() const
{
    return cameraPos_;
}

QVector3D Camera::getCameraFront() const
{
    return cameraFront_;
}
