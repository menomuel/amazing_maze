#ifndef CUBEWIDGET_H
#define CUBEWIDGET_H

#include "camera.h"
#include "cube.h"
#include "arrow.h"
#include "scene.h"
#include "texture.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QTime>
#include <QElapsedTimer>
#include <QOpenGLShaderProgram>
#include <QMediaPlayer>
#include <QMovie>

#include <memory>

#include "pathfinder.h"

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
    void showPath(bool);
    void godMode(bool);
    void restartScene();
    void resizeScene(int newSize);

signals:
    void fpsChanged(double);
    void setShowPathFlag(bool);
    void setGodModeFlag(bool);
    void secsElapsed(int);
    void minsElapsed(int);

    void setWinMovie(QMovie*);
    void clearWinMovie();


private:
    void collisionDetection(int currRow, int currCol);

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

    bool godModeFlag = false;
    QVector3D historyCameraPos, historyCameraFront, historyCameraRight, historyCameraUp;
    float historyYaw, historyPitch;

    QBasicTimer timer;
    QTime stopwatch;
    QElapsedTimer timeRecord;

    bool winFlag = false;
    bool winMusicFlag = false;

    QOpenGLShaderProgram objectShader;
    std::shared_ptr<Scene> scene;

    std::shared_ptr<Arrow> arrow;
    std::shared_ptr<QOpenGLTexture> arrowTex;

    std::shared_ptr<QMediaPlayer> player;
    std::shared_ptr<QMovie> movie;

    QVector2D mousePressPosition, mouseLastPosition;
    QVector3D rotationAxis;
    qreal angularSpeed = 0;
    QQuaternion rotation;
};

#endif // CUBEWIDGET_H
