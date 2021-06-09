#ifndef CUBEWIDGET_H
#define CUBEWIDGET_H

#include "camera.h"
#include "cube.h"
#include "scene.h"

#include "pointlightsource.h"
#include "directlightsource.h"
#include "projectorlightsource.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QTime>
#include <QOpenGLShaderProgram>

#include <memory>

class GeometryEngine;

class CubeWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    using QOpenGLWidget::QOpenGLWidget;
    ~CubeWidget() = default;

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent* e) override;
    void timerEvent(QTimerEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;

    void doMovement();

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();

public slots:

    void directLightToggle(int);
    void directLightChangeX(float);
    void directLightChangeY(float);
    void directLightChangeZ(float);
    void directLightIntensityChange(float);
    void directLightColorChange(QColor);

    void pointLightToggle(int);
    void pointLightChangeX(float);
    void pointLightChangeY(float);
    void pointLightChangeZ(float);
    void pointLightIntensityChange(float);
    void pointLightColorChange(QColor);


    void projectorLightToggle(int);
    void projectorLightCutOffChange(float);
    void projectorLightOuterCutOffChange(float);
    void projectorLightIntensityChange(float);
    void projectorLightColorChange(QColor);

    void sceneNumObjChange(int);
    void sceneMaterialChange(QString);

signals:
    void fpsChanged(double);

private:
    static constexpr float zNear = 0.1;
    static constexpr float zFar = 100.;
    static constexpr unsigned deltaTimeMsec = 12;

private:
    Camera camera;
    float cameraSpeed = 5.f;

    bool keys[1024] = {false};

    float fov = 45.f;

    float fps;
    int n;

    QBasicTimer timer;
    QTime stopwatch;
    QOpenGLShaderProgram objectShader, lightShader;
    std::shared_ptr<Scene> scene;
    std::shared_ptr<Cube> pointLightCube;

    DirectLightSource directLight;
    PointLightSource pointLight;
    ProjectorLightSource projectorLight;

    QVector2D mousePressPosition, mouseLastPosition;
    QVector3D rotationAxis;
    qreal angularSpeed = 0;
    QQuaternion rotation;
};

#endif // CUBEWIDGET_H