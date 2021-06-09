#include "cubewidget.h"
#include "material.h"

#include <QMouseEvent>
#include <QColor>

#include <cmath>

void CubeWidget::directLightToggle(int state)
{
    bool bstate = state > 0 ? true : false;
    directLight.switchState(bstate);
}

void CubeWidget::directLightChangeX(float newX)
{
    auto currDir = directLight.getDirection();
    directLight.setDirection(QVector3D(newX, currDir.y(), currDir.z()));
}

void CubeWidget::directLightChangeY(float newY)
{
    auto currDir = directLight.getDirection();
    directLight.setDirection(QVector3D(currDir.x(), newY, currDir.z()));
}

void CubeWidget::directLightChangeZ(float newZ)
{
    auto currDir = directLight.getDirection();
    directLight.setDirection(QVector3D(currDir.x(), currDir.y(), newZ));
}

void CubeWidget::directLightIntensityChange(float intensity)
{
    directLight.setIntensity(intensity);
}

void CubeWidget::directLightColorChange(QColor color)
{
    directLight.setColor(QVector3D(color.redF(), color.greenF(), color.blueF()));
}


void CubeWidget::pointLightToggle(int state)
{
    bool bstate = state > 0 ? true : false;
    pointLight.switchState(bstate);
}

void CubeWidget::pointLightChangeX(float newX)
{
    auto currPos = pointLight.getPosition();
    pointLight.setPosition(QVector3D(newX, currPos.y(), currPos.z()));
}

void CubeWidget::pointLightChangeY(float newY)
{
    auto currPos = pointLight.getPosition();
    pointLight.setPosition(QVector3D(currPos.x(), newY, currPos.z()));
}

void CubeWidget::pointLightChangeZ(float newZ)
{
    auto currPos = pointLight.getPosition();
    pointLight.setPosition(QVector3D(currPos.x(), currPos.y(), newZ));
}

void CubeWidget::pointLightIntensityChange(float intensity)
{
    pointLight.setIntensity(intensity);
}

void CubeWidget::pointLightColorChange(QColor color)
{
    pointLight.setColor(QVector3D(color.redF(), color.greenF(), color.blueF()));
}


void CubeWidget::projectorLightToggle(int state)
{
    bool bstate = state > 0 ? true : false;
    projectorLight.switchState(bstate);
}

void CubeWidget::projectorLightCutOffChange(float angle)
{
    projectorLight.setCutOff(angle);
}

void CubeWidget::projectorLightOuterCutOffChange(float angle)
{
    projectorLight.setOuterCutOff(angle);
}

void CubeWidget::projectorLightIntensityChange(float intensity)
{
    projectorLight.setIntensity(intensity);
}

void CubeWidget::projectorLightColorChange(QColor color)
{
    projectorLight.setColor(QVector3D(color.redF(), color.greenF(), color.blueF()));
}

void CubeWidget::sceneNumObjChange(int newNum)
{
    scene->setNumCubes(newNum);
}

void CubeWidget::sceneMaterialChange(QString newMat)
{
    auto currMat = scene->getCube()->getMaterial();

    if(newMat == "White")
        currMat = MaterialFactory::createWhite();
    if(newMat == "Red Rubber")
        currMat = MaterialFactory::createRedRubber();
    if(newMat == "Jade")
        currMat = MaterialFactory::createJade();

    scene->getCube()->setMaterial(currMat);
}


void CubeWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());

    if (e->buttons() & Qt::RightButton)
    {
        mouseLastPosition = QVector2D(e->pos());
    }
}

void CubeWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}

void CubeWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::RightButton)
    {
        QVector2D diff = QVector2D(e->pos()) - mouseLastPosition;
        diff *= 0.001f;
        camera.rotate(diff.x(), diff.y());
    }
    mouseLastPosition = QVector2D(e->pos());
}

void CubeWidget::timerEvent(QTimerEvent *)
{
    doMovement();
    update();
}

void CubeWidget::keyPressEvent(QKeyEvent *e)
{
    if(e->key() < 1024)
        keys[e->key()] = true;
}

void CubeWidget::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key() < 1024)
        keys[e->key()] = false;
}

void CubeWidget::wheelEvent(QWheelEvent *e)
{
    fov += e->angleDelta().y() / 45.f;
}

void CubeWidget::doMovement()
{
    float length = cameraSpeed * deltaTimeMsec / 1000.f;

    if (keys[Qt::Key_W])
        camera.move(Camera::directions::FORWARD, length);
    if (keys[Qt::Key_S])
        camera.move(Camera::directions::BACKWARD, length);
    if (keys[Qt::Key_D])
        camera.move(Camera::directions::RIGHT, length);
    if (keys[Qt::Key_A])
        camera.move(Camera::directions::LEFT, length);
    if (keys[Qt::Key_Space])
        camera.move(Camera::directions::UP, length);
    if (keys[Qt::Key_Z])
        camera.move(Camera::directions::DOWN, length);

    double fractPart, intPart;
    fractPart = modf(camera.getCameraPos().x()/scene->getCube()->getFacetSideLength(), &intPart);
    int row = fractPart < 0.5 ? int(intPart) : int(intPart) + 1;

    fractPart = modf(-camera.getCameraPos().z()/scene->getCube()->getFacetSideLength(), &intPart);
    int col = fractPart < 0.5 ? int(intPart) : int(intPart) + 1;

    scene->update(row, col);
}


void CubeWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.f, 0.f, 0.f, 1.f);

    initShaders();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
    pointLightCube = std::make_shared<Cube>();
    scene = std::make_shared<Scene>();
    scene->initScene();

    camera.setZNear(zNear);
    camera.setZFar(zFar);
    camera.setCameraPos(QVector3D(scene->getCube()->getFacetSideLength(), 0, -scene->getCube()->getFacetSideLength()));

    directLight = DirectLightSource();
    pointLight = PointLightSource();
    projectorLight = ProjectorLightSource(camera.getCameraPos(), camera.getCameraFront());

    n = 0;
    // Use QBasicTimer because its faster than QTimer
    timer.start(deltaTimeMsec, this);
}

//! [3]
void CubeWidget::initShaders()
{
    // Compile vertex shader for objects
    if (!objectShader.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader for objects
    if (!objectShader.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!objectShader.link())
        close();

    // Compile vertex shader for objects
    if (!lightShader.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader_light.glsl"))
        close();

    // Compile fragment shader for objects
    if (!lightShader.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!lightShader.link())
        close();

    // Bind shader pipeline for use
    if (!objectShader.bind())
        close();
}


void CubeWidget::resizeGL(int w, int h)
{
    camera.setAspectRatio(float(w) / float(h ? h : 1));
}


void CubeWidget::paintGL()
{
    auto start = stopwatch.currentTime();

    // Clear color and depth buffer
    if(directLight.getState()) {
        auto backgroundColor = directLight.getColor();
        auto backgroundIntensity = directLight.getIntensity();
        glClearColor(backgroundIntensity * backgroundColor.x(),
                     backgroundIntensity * backgroundColor.y(),
                     backgroundIntensity * backgroundColor.z(),
                     1.f);
    } else {
        glClearColor(0.0f, 0.0f, 0.0f, 1.f);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.setFOV(fov);

    projectorLight.setPosition(camera.getCameraPos());
    projectorLight.setDirection(camera.getCameraFront());

    objectShader.bind();
    objectShader.setUniformValue(1, camera.getViewMatrix());
    objectShader.setUniformValue(2, camera.getProjectionMatrix());
    objectShader.setUniformValue(3, camera.getCameraPos());

    scene->getCube()->getMaterial()->uploadToShader(&objectShader);
    directLight.uploadToShader(&objectShader);
    pointLight.uploadToShader(&objectShader);
    projectorLight.uploadToShader(&objectShader);

    // Draw cube geometry
    scene->drawScene(&objectShader);

    if(pointLight.getState()) {
        QMatrix4x4 modelMatLight;
        modelMatLight.translate(pointLight.getPosition());

        lightShader.bind();
        lightShader.setUniformValue(0, modelMatLight);
        lightShader.setUniformValue(1, camera.getViewMatrix());
        lightShader.setUniformValue(2, camera.getProjectionMatrix());
        lightShader.setUniformValue("lightColor", pointLight.getIntensity() * pointLight.getColor());

        pointLightCube->render(&lightShader);
    }

    auto stop = stopwatch.currentTime();

    fps += 1.f / (start.msecsTo(stop));
    ++n;
    if (n >= 100) {
        n = 0;
        emit fpsChanged(static_cast<double>(1000 * fps / 100));
        fps = 0;
    }
}
